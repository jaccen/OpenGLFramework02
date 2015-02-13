/* ヘッダファイル */
#include "SmallBeamOption.h"
#include "OptionDropState.h"
#include "RigidBodyStraightMoveLogic.h"
#include "OptionGunFactory.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"
#include "../../Library/OpenGL/Manager/OpenGlManager.h"
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
     *  @param  座標
     *
     ****************************************************************/
    C_SmallBeamOption::C_SmallBeamOption(const std::string& rId, int32_t type) : C_BaseOption(rId, type)
    {
        // オプションの情報を取得
        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSMALL_BEAM_OPTION));
        auto pOptionData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSMALL_BEAM_OPTION).get();

        // 球形状を性生成
        radius_ = static_cast<float>((*pOptionData)["CreateData"]["Radius"].GetValue<JSON::Real>());

        // 剛体を作成し、物理エンジンに追加
        Physics::Transform transform;
        transform.setIdentity();

        int32_t collisionMask = C_CollisionObject::FILTER_TYPE_PLAYER
                              | C_CollisionObject::FILTER_TYPE_OPTION
                              | C_CollisionObject::FILTER_TYPE_ENEMY 
                              | C_CollisionObject::FILTER_TYPE_ENEMY_BULLET
                              | C_CollisionObject::FILTER_TYPE_OBSTACLE;

		upRigidBody_ = std::make_unique<Physics::C_RigidBody>(newEx Physics::C_SphereShape(radius_), transform, static_cast<float>((*pOptionData)["CreateData"]["Mass"].GetValue<JSON::Real>()));
        
        upRigidBody_->EnableCollisionResponse(false);
        upRigidBody_->EnableFreezeRotation(true, true, true);
        
        Physics::C_PhysicsEngine::s_GetInstance()->AddRigidBody(upRigidBody_.get(), 
                                                                C_CollisionObject::FILTER_TYPE_OPTION,
                                                                collisionMask);

        // 自身を設定
        upRigidBody_->SetUserPointer(this);

        // モデル情報を取得
        assert(OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pSMALL_BEAM_OPTION));
        pModelData_ = OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pSMALL_BEAM_OPTION).get();

        // テクスチャ情報を取得
        assert(Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pSMALL_BEAM_OPTION));
        pModelTextureData_ = Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pSMALL_BEAM_OPTION).get();

        // GLSLオブジェクトを取得
        assert(Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pPHONG_TEXTURE));
        pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pPHONG_TEXTURE).get();

        // ユニフォームバッファとインデックスを取得
        assert(Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pMAIN_CAMERA));
        pUniformBuffer_ = Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pMAIN_CAMERA).get();
        uniformBlockIndex_ = pUniformBuffer_->GetBlockIndexFromProgramObject(pGlslObject_->GetProgramObjectHandle());

        // パワーとヒットポイントを作成
        upPower_ = std::make_unique<C_BasePower>((*pOptionData)["CreateData"]["Power"].GetValue<JSON::Integer>());
        upHitPoint_ = std::make_unique<C_BaseHitPoint>((*pOptionData)["CreateData"]["HitPoint"].GetValue<JSON::Integer>());

        // 移動のロジックを作成
        upMoveLogic_ = std::make_unique<C_RigidBodyStraightMoveLogic>();
        upMoveLogic_->SetDirection(Physics::Vector3(0.0f, -1.0f, 0.0f));
        upMoveLogic_->SetMovement(static_cast<float>((*pOptionData)["CreateData"]["Movement"].GetValue<JSON::Real>()));

        // 銃の情報の数を取得
        gunDataCount_ = (*pOptionData)["GunDataCount"].GetValue<JSON::Integer>();

        // ユニフォーム変数を設定
        pGlslObject_->Begin();

        SetMaterial(pBasicMaterial_);
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
    C_SmallBeamOption::~C_SmallBeamOption()
    {
        Physics::C_PhysicsEngine::s_GetInstance()->RemoveRigidBody(upRigidBody_.get());
    }


    /*************************************************************//**
     *
     *  @brief  連結時の効果を処理する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SmallBeamOption::ConnectEffect()
    {
        assert(pPlayer_);

        // 銃を作成
        C_OptionSmallBeamGunFactory optionSmallBeamGunFactory;
        upGuns_.reserve(gunDataCount_);

        for (int32_t i = 0; i < gunDataCount_; ++i)
        {
            upGuns_.emplace_back(optionSmallBeamGunFactory.Create(this, i));
        }
    }


    /*************************************************************//**
     *
     *  @brief  非公開の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SmallBeamOption::DoDraw()
    {
        pGlslObject_->BeginWithUnifomBuffer(pUniformBuffer_->GetHandle(), uniformBlockIndex_);

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
        pModelTextureData_ = Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pSMALL_BEAM_OPTION).get();
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