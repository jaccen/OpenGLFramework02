/* ヘッダファイル */
#include "BoxEnemy.h"
#include "BaseGun.h"
#include "RigidBodyForceMoveLogic.h"
#include "EnemyAdventState.h"
#include "../../Library/Physics/CollisionShape/Convex/Box/BoxShape.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"
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
     *
     ****************************************************************/
    C_BoxEnemy::C_BoxEnemy(const std::string& rId, int32_t type) : C_BaseEnemy(rId, type),

        // ステートマシーン
        upStateMachine_(std::make_unique<State::C_StateMachine<C_BaseEnemy>>(this))

    {
        // 現在のステートを設定
        upStateMachine_->SetCurrentState(C_EnemyAdventState::s_GetInstance());
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BoxEnemy::~C_BoxEnemy()
    {
        // 剛体を物理エンジンから除く
        Physics::C_PhysicsEngine::s_GetInstance()->RemoveRigidBody(upRigidBody_.get());
    }


    /*************************************************************//**
     *
     *  @brief  移動制限の確認を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BoxEnemy::MoveLimitCheck()
    {
    }


    /*************************************************************//**
     *
     *  @brief  JSONオブジェクトからデータを設定する
     *  @param  JSONオブジェクト
     *  @return なし
     *
     ****************************************************************/
    void C_BoxEnemy::SetCreateDataWithJson(JSON::JsonObject* pJsonObject)
    {
        // 剛体を作成し、物理エンジンに追加
        Physics::Transform transform;
        transform.setIdentity();
        transform.setOrigin(Physics::Vector3(static_cast<float>((*pJsonObject)["Position"][0].GetValue<JSON::Real>()),
                                             static_cast<float>((*pJsonObject)["Position"][1].GetValue<JSON::Real>()),
                                             static_cast<float>((*pJsonObject)["Position"][2].GetValue<JSON::Real>())));
        
        int32_t collisionMask = C_CollisionObject::FILTER_TYPE_PLAYER
                              | C_CollisionObject::FILTER_TYPE_OPTION
                              | C_CollisionObject::FILTER_TYPE_CONNECTMACHINE_BULLET
                              | C_CollisionObject::FILTER_TYPE_OBSTACLE;
        
        upRigidBody_ = std::make_unique<Physics::C_RigidBody>(newEx Physics::C_BoxShape(static_cast<float>((*pJsonObject)["CollisionSize"][0].GetValue<JSON::Real>()),
                                                                                        static_cast<float>((*pJsonObject)["CollisionSize"][1].GetValue<JSON::Real>()),
                                                                                        static_cast<float>((*pJsonObject)["CollisionSize"][2].GetValue<JSON::Real>())),
                                                                                        transform,
                                                                                        static_cast<float>((*pJsonObject)["Mass"].GetValue<JSON::Real>()));
        
        Physics::C_PhysicsEngine::s_GetInstance()->AddRigidBody(upRigidBody_.get(), 
                                                                C_CollisionObject::FILTER_TYPE_ENEMY,
                                                                collisionMask);
        
        // 自身を設定
        upRigidBody_->SetUserPointer(this);
        
        // モデル情報を取得
        assert(OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pBOX_ENEMY));
        pModelData_ = OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pBOX_ENEMY).get();
        
        // GLSLオブジェクトを取得
        assert(Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pHALF_LAMBERT_PHONG));
        pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pHALF_LAMBERT_PHONG).get();
        
        // ユニフォームバッファとインデックスを取得
        assert(Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pMAIN_CAMERA));
        pUniformBuffer_ = Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pMAIN_CAMERA).get();
        uniformBlockIndex_ = pUniformBuffer_->GetBlockIndexFromProgramObject(pGlslObject_->GetProgramObjectHandle());
        
        // パワーとヒットポイントを作成
        upPower_ = std::make_unique<C_BasePower>((*pJsonObject)["Power"].GetValue<JSON::Integer>());
        upHitPoint_ = std::make_unique<C_BaseHitPoint>((*pJsonObject)["HitPoint"].GetValue<JSON::Integer>());
        
        // 移動のロジックを作成
        auto firstAddForce = Physics::Vector3(static_cast<float>((*pJsonObject)["FirstAddForce"][0].GetValue<JSON::Real>()),
                                              static_cast<float>((*pJsonObject)["FirstAddForce"][1].GetValue<JSON::Real>()),
                                              static_cast<float>((*pJsonObject)["FirstAddForce"][2].GetValue<JSON::Real>()));
        
        auto firstAddTorque = Physics::Vector3(static_cast<float>((*pJsonObject)["FirstAddTorque"][0].GetValue<JSON::Real>()),
                                               static_cast<float>((*pJsonObject)["FirstAddTorque"][1].GetValue<JSON::Real>()),
                                               static_cast<float>((*pJsonObject)["FirstAddTorque"][2].GetValue<JSON::Real>()));
        
        auto pMoveLogic = newEx C_RigidBodyForceMoveLogic(firstAddForce, firstAddTorque);
        
        pMoveLogic->SetDirection(Physics::Vector3(0.0f, -1.0f, 0.0f));
        pMoveLogic->SetMovement(static_cast<float>((*pJsonObject)["Movement"].GetValue<JSON::Real>()));
        pMoveLogic->SetDirection(Physics::Vector3(static_cast<float>((*pJsonObject)["Direction"][0].GetValue<JSON::Real>()),
                                                  static_cast<float>((*pJsonObject)["Direction"][1].GetValue<JSON::Real>()),
                                                  static_cast<float>((*pJsonObject)["Direction"][2].GetValue<JSON::Real>())));
        
        auto addTorque = Physics::Vector3(static_cast<float>((*pJsonObject)["AddTorque"][0].GetValue<JSON::Real>()),
                                          static_cast<float>((*pJsonObject)["AddTorque"][1].GetValue<JSON::Real>()),
                                          static_cast<float>((*pJsonObject)["AddTorque"][2].GetValue<JSON::Real>()));
        
        pMoveLogic->SetAddTorque(addTorque);
    }


    /*************************************************************//**
     *
     *  @brief  座標を取得する
     *  @param  なし
     *  @return 座標
     *
     ****************************************************************/
    const Physics::Vector3& C_BoxEnemy::GetPosition() const
    {
        return upRigidBody_->GetTransform().getOrigin();
    }


    /*************************************************************//**
     *
     *  @brief  座標を設定する
     *  @param  座標
     *  @return なし
     *
     ****************************************************************/
    void C_BoxEnemy::SetPosition(const Physics::Vector3& rPosition)
    {
        auto transform = upRigidBody_->GetTransform();
        transform.setOrigin(rPosition);
        upRigidBody_->SetTransform(transform);
    }


    /*************************************************************//**
     *
     *  @brief  回転量を取得する
     *  @param  なし
     *  @return 回転量
     *
     ****************************************************************/
    const Physics::Matrix3x3& C_BoxEnemy::GetRotation() const
    {
        return upRigidBody_->GetTransform().getBasis();
    }


    /*************************************************************//**
     *
     *  @brief  非公開の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BoxEnemy::DoUpdate()
    {
        upStateMachine_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  非公開の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BoxEnemy::DoDraw()
    {
        pGlslObject_->BeginWithUnifomBuffer(pUniformBuffer_->GetHandle(), uniformBlockIndex_);

        // マテリアルを設定
        pGlslObject_->SetUniformVector3("material.diffuse", Vector3(0.5f, 1.0f, 0.5f));
        pGlslObject_->SetUniformVector3("material.ambient", Vector3(0.1f, 0.1f, 0.1f));
        pGlslObject_->SetUniformVector3("material.specular", Vector3(0.9f, 0.9f, 0.9f));
        pGlslObject_->SetUniform1f("material.shininess", 100.0f);
        pGlslObject_->SetUniformVector3("light.position", Vector3(0.0f, 100.0f, 0.0f));
        pGlslObject_->SetUniformVector3("light.diffuse", Vector3(0.9f, 0.9f, 0.9f));
        pGlslObject_->SetUniformVector3("light.ambient", Vector3(0.9f, 0.9f, 0.9f));
        pGlslObject_->SetUniformVector3("light.specular", Vector3(0.9f, 0.9f, 0.9f));

        upRigidBody_->GetTransform().getOpenGLMatrix(modelMatrix_.a_);
        modelMatrix_ = modelMatrix_ * Matrix4x4::s_CreateScaling(size_);
        pGlslObject_->SetUniformMatrix4x4("modelMatrix", modelMatrix_);

        auto pOpenGlManager = OpenGL::C_OpenGlManager::s_GetInstance();

        pOpenGlManager->DrawPrimitiveWithIndices(OpenGL::Primitive::s_TRIANGLE,
                                                 pModelData_->GetVertexArrayObjectHandle(), 
                                                 pModelData_->GetIndexBufferObjectHandle(),
                                                 OpenGL::DataType::s_UNSIGNED_SHORT,
                                                 static_cast<int32_t>(pModelData_->GetIndexCount()));

        pGlslObject_->End();
    }


    /*************************************************************//**
     *
     *  @brief  非公開のメッセージ処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    bool C_BoxEnemy::DoMessageProcess(const Telegram& rTelegram)
    {
        return upStateMachine_->MessageProcess(rTelegram);
    }
}