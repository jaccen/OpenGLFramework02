/* ヘッダファイル */
#include "NormalPlayer.h"
#include "RigidBodyInputMoveLogic.h"
#include "NormalGun.h"
#include "PlayerGunFactory.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"
#include "../../Library/OpenGL/Manager/OpenGlManager.h"
#include "../../Library/Shader/GLSL/Uniform/Manager/UniformBufferManager.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"
#include "../../Library/Debug/Helper/DebugHelper.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ID
     *  @param  種類
     *
     ****************************************************************/
    C_NormalPlayer::C_NormalPlayer(const std::string& rId, int32_t type) : C_BasePlayer(rId, type)
    {
        // プレイヤーの情報を取得
        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pNORMAL_PLAYER));
        auto pPlayerData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pNORMAL_PLAYER).get();

        // 球形状を生成
        radius_ = static_cast<float>((*pPlayerData)["CreateData"]["Radius"].GetValue<JSON::Real>());
        ResetMoveLimitBoundingBox();

        // 剛体を作成し、物理エンジンに追加
        Physics::Transform transform;
        transform.setIdentity();
        transform.setOrigin(Physics::Vector3(static_cast<float>((*pPlayerData)["CreateData"]["Position"][0].GetValue<JSON::Real>()),
                                             static_cast<float>((*pPlayerData)["CreateData"]["Position"][1].GetValue<JSON::Real>()),
                                             static_cast<float>((*pPlayerData)["CreateData"]["Position"][2].GetValue<JSON::Real>())));

        int32_t collisionMask = C_CollisionObject::FILTER_TYPE_OPTION
                              | C_CollisionObject::FILTER_TYPE_ENEMY 
                              | C_CollisionObject::FILTER_TYPE_ENEMY_BULLET
                              | C_CollisionObject::FILTER_TYPE_OBSTACLE;

		upRigidBody_ = std::make_unique<Physics::C_RigidBody>(newEx Physics::C_SphereShape(radius_), transform, static_cast<float>((*pPlayerData)["CreateData"]["Mass"].GetValue<JSON::Real>()));
        
        // 衝突応答をなくし、回転を全てフリーズ
        upRigidBody_->EnableCollisionResponse(false);
        upRigidBody_->EnableFreezeRotation(true, true, true);
        
        Physics::C_PhysicsEngine::s_GetInstance()->AddRigidBody(upRigidBody_.get(), 
                                                                C_CollisionObject::FILTER_TYPE_PLAYER,
                                                                collisionMask);

        // 自身を設定
        upRigidBody_->SetUserPointer(this);

        // GLSLオブジェクトを取得
        assert(Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pPHONG_TEXTURE));
        pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pPHONG_TEXTURE).get();
        cameraSubroutineIndex_ =  pGlslObject_->GetSubroutineIndex(Shader::GLSL::Type::s_VERTEX, "GetMainViewProjectionMatrix");

        // ユニフォームバッファとインデックスを取得
        assert(Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pMAIN_CAMERA));
        pUniformBuffer_ = Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pMAIN_CAMERA).get();
        uniformBlockIndex_ = pUniformBuffer_->GetBlockIndexFromProgramObject(pGlslObject_->GetProgramObjectHandle());

        // モデル情報を取得
        assert(OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pNORMAL_PLAYER));
        pModelData_ = OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pNORMAL_PLAYER).get();

        // テクスチャ情報を取得
        assert(Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pNORMAL_PLAYER));
        pModelTextureData_ = Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pNORMAL_PLAYER).get();

        // パワーとヒットポイントを作成
        upPower_ = std::make_unique<C_BasePower>((*pPlayerData)["CreateData"]["Power"].GetValue<JSON::Integer>());
        upHitPoint_ = std::make_unique<C_BaseHitPoint>((*pPlayerData)["CreateData"]["HitPoint"].GetValue<JSON::Integer>());

        // 移動のロジックを作成
        moveSpeedLevel_ = (*pPlayerData)["CreateData"]["MoveSpeedLevel"].GetValue<JSON::Integer>();
        moveSpeedUpInterval_ = static_cast<float>((*pPlayerData)["CreateData"]["MoveSpeedUpInterval"].GetValue<JSON::Real>());
        upMoveLogic_ = std::make_unique<C_RigidBodyInputMoveLogic>(static_cast<float>((*pPlayerData)["CreateData"]["Movement"].GetValue<JSON::Real>()), 1.0f);

        // 銃を作成
        C_PlayerBeamGunFactory playerBeamGunFactory;
        int32_t gunDataCount = (*pPlayerData)["GunDataCount"].GetValue<JSON::Integer>();

        upGuns_.reserve(gunDataCount);

        for (int32_t i = 0; i < gunDataCount; ++i)
        {
            upGuns_.emplace_back(playerBeamGunFactory.Create(this, i));
        }

        // その他のデータを設定
        remainLife_ = (*pPlayerData)["CreateData"]["RemainLife"].GetValue<JSON::Integer>();
        connectPetrifyFrame_ = (*pPlayerData)["CreateData"]["ConnectPetrifyFrame"].GetValue<JSON::Integer>();
        bombChargeFrame_ = (*pPlayerData)["CreateData"]["BombChargeFrame"].GetValue<JSON::Integer>();
        bombInvincibleFrame_ = (*pPlayerData)["CreateData"]["BombInvincibleFrame"].GetValue<JSON::Integer>();

        // ユニフォーム変数を設定
        pGlslObject_->Begin();

        pGlslObject_->SetUniform1i("u_texture", 0);
        pGlslObject_->SetUniform1f("u_gamma", 2.2f);

        pGlslObject_->End();
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_NormalPlayer::~C_NormalPlayer()
    {
        // 剛体を物理エンジンから除く
        Physics::C_PhysicsEngine::s_GetInstance()->RemoveRigidBody(upRigidBody_.get());
    }


    /*************************************************************//**
     *
     *  @brief  非公開の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_NormalPlayer::DoDraw()
    {
        pGlslObject_->BeginWithUnifomBuffer(pUniformBuffer_->GetHandle(), uniformBlockIndex_);
        pGlslObject_->BindActiveSubroutine(cameraSubroutineIndex_, Shader::GLSL::Type::s_VERTEX);

        upRigidBody_->GetTransform().getOpenGLMatrix(modelMatrix_.a_);
        modelMatrix_ = modelMatrix_ * Matrix4x4::s_CreateScaling(Vector3(radius_));
        pGlslObject_->SetUniformMatrix4x4("u_modelMatrix", modelMatrix_);

        // ライトとマテリアルを設定
        SetLight(pMainLight_);
        SetMaterial(pNowMaterial_);

        auto pOpenGlManager = OpenGL::C_OpenGlManager::s_GetInstance();
        auto pTextureManager = Texture::C_TextureManager::s_GetInstance();

        // アクティブなテクスチャユニットを設定し、テクスチャをバインド
        pTextureManager->SetActiveUnit(0);
        pTextureManager->Bind(Texture::Type::s_2D, pModelTextureData_->handle_);

        pOpenGlManager->DrawPrimitiveWithIndices(OpenGL::Primitive::s_TRIANGLE,
                                                 pModelData_->GetVertexArrayObjectHandle(), 
                                                 pModelData_->GetIndexBufferObjectHandle(),
                                                 OpenGL::DataType::s_UNSIGNED_SHORT,
                                                 static_cast<int32_t>(pModelData_->GetIndexCount()));

        pTextureManager->Unbind(Texture::Type::s_2D);

        pGlslObject_->End();
    }
}