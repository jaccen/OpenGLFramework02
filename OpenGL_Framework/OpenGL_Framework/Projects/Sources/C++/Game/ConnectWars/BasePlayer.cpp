/* ヘッダファイル */
#include "BasePlayer.h"
#include "BaseOption.h"
#include "CollisionProcess.h"
#include "RigidBodyInputMoveLogic.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/Model/SelfMade/Loader/ModelLoader.h"
#include "../../Library/OpenGL/Buffer/Primitive/PrimitiveDefine.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"
#include "../../Library/OpenGL/Manager/OpenGlManager.h"
#include "../../Library/Shader/GLSL/Uniform/Manager/UniformBufferManager.h"


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
    C_BasePlayer::C_BasePlayer(const std::string& rId, int32_t type) : C_ConnectMachine(rId, type),

        // ステートマシーン
        upStateMachine_(std::make_unique<State::C_StateMachine<C_BasePlayer>>(this))

    {
        // 球形状を性生成
        radius_ = 0.9f;
        upSphereShape_ = std::make_unique<Physics::C_SphereShape>(radius_);
        ResetMoveLimitBoundingBox();

        Physics::Transform transform;
        transform.setIdentity();
        
        transform.setOrigin(Physics::Vector3(5.0f, 0.0f, 0.0f));

        upRigidBody_ = std::make_unique<Physics::C_RigidBody>(upSphereShape_.get(), transform, 1.0f);
        Physics::C_PhysicsEngine::s_GetInstance()->AddRigidBody(upRigidBody_.get());

        Model::SelfMade::C_ModelLoader modelLoader;
        modelLoader.LoadModel("Projects/Models/Test/Sphere/Sphere.model");
        auto& rMesh = modelLoader.GetMesh(0);

        uint32_t vertexCount = rMesh.vertices_.size();
        std::vector<OpenGL::S_VertexPNT> vertices(vertexCount);

        for (size_t i = 0; i < vertexCount; ++i)
        {
            vertices[i].position_ = rMesh.vertices_[i].position_;
            vertices[i].normal_ = rMesh.vertices_[i].normal_;
            vertices[i].textureCoord_ = rMesh.vertices_[i].textureCoord_;
        }

        uint32_t vertexAttributeElementCountList[] = { 3, 3, 2 };
        OpenGL::DataEnum vertexAttributeDataTypeList[] = { OpenGL::DataType::s_FLOAT, OpenGL::DataType::s_FLOAT, OpenGL::DataType::s_FLOAT };
        
        pModelData_ = OpenGL::C_PrimitiveBuffer::s_Create(vertices.data(),
                                                          vertexCount,
                                                          3,
                                                          vertexAttributeElementCountList,
                                                          vertexAttributeDataTypeList,
                                                          OpenGL::Modify::s_STATIC,
                                                          rMesh.indices_.data(),
                                                          rMesh.indices_.size(),
                                                          OpenGL::Modify::s_STATIC);

        pGlslObject_ = Shader::GLSL::C_GlslObject::s_Create();

        pGlslObject_->CompileFromFile("Projects/Shaders/GLSL/HalfLambert/HalfLambert.vert", Shader::GLSL::Type::s_VERTEX);
        pGlslObject_->CompileFromFile("Projects/Shaders/GLSL/HalfLambert/HalfLambert.frag", Shader::GLSL::Type::s_FRAGMENT);
        pGlslObject_->Link();

        assert(Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer("CameraData"));
        pUniformBuffer_ = Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer("CameraData").get();
        uniformBlockIndex_ = pUniformBuffer_->GetBlockIndexFromProgramObject(pGlslObject_->GetProgramObjectHandle());

        pGlslObject_->Begin();
        
        pGlslObject_->SetUniformMatrix4x4("modelMatrix", Math::Matrix4x4::s_IDENTITY);
        pGlslObject_->SetUniformVector3("material.diffuse", Vector3(0.5f, 1.0f, 0.5f));
        pGlslObject_->SetUniformVector3("material.ambient", Vector3(0.1f, 0.1f, 0.1f));
        pGlslObject_->SetUniformVector3("material.specular", Vector3(0.9f, 0.9f, 0.9f));
        pGlslObject_->SetUniform1f("material.shininess", 100.0f);

        pGlslObject_->SetUniformVector3("light.position", Vector3(0.0f, 100.0f, 0.0f));
        pGlslObject_->SetUniformVector3("light.diffuse", Vector3(0.9f, 0.9f, 0.9f));
        pGlslObject_->SetUniformVector3("light.ambient", Vector3(0.9f, 0.9f, 0.9f));
        pGlslObject_->SetUniformVector3("light.specular", Vector3(0.9f, 0.9f, 0.9f));

        pGlslObject_->End();


        upMoveLogic_ = std::make_unique<C_RigidBodyInputMoveLogic>(0.1f, 1.0f);

        // 移動制限境界ボックスをリセット
        //ResetMoveLimitBoundingBox();
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BasePlayer::~C_BasePlayer()
    {
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return タスク続行：true
     *  @return タスク終了：false
     *
     ****************************************************************/
    bool C_BasePlayer::Update()
    {
        DoUpdate();

        return existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::Draw()
    {
        DoDraw();
    }


    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_BasePlayer::MessageProcess(const Telegram& rTelegram)
    {
        if (DoMessageProcess(rTelegram) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  衝突検出の発行を行う
     *  @param  衝突オブジェクト
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::DispatchCollision(C_CollisionObject* pCollisionObject)
    {
        pCollisionObject->CollisionProcess(this);
    }


    /*************************************************************//**
     *
     *  @brief  プレイヤーとの衝突時処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BasePlayer* pPlayer)
    {
        C_CollisionProcess::s_PlayerAndPlayer(this, pPlayer);
    }


    /*************************************************************//**
     *
     *  @brief  オプションとの衝突時処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BaseOption* pOption)
    {
        C_CollisionProcess::s_PlayerAndOption(this, pOption);
    }


    /*************************************************************//**
     *
     *  @brief  敵との衝突時処理を行う
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BaseEnemy* pEnemy)
    {
        C_CollisionProcess::s_PlayerAndEnemy(this, pEnemy);
    }


    /*************************************************************//**
     *
     *  @brief  弾との衝突時処理を行う
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BaseBullet* pBullet)
    {
        C_CollisionProcess::s_PlayerAndBullet(this, pBullet);
    }


    /*************************************************************//**
     *
     *  @brief  障害物との衝突時処理を行う
     *  @param  障害物
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BaseObstacle* pObstacle)
    {
        C_CollisionProcess::s_PlayerAndObstacle(this, pObstacle);
    }


    /*************************************************************//**
     *
     *  @brief  ボムとの衝突時処理を行う
     *  @param  ボム
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BaseBomb* pBomb)
    {
        C_CollisionProcess::s_PlayerAndBomb(this, pBomb);
    }


    /*************************************************************//**
     *
     *  @brief  移動処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::Move()
    {
        upMoveLogic_->Move(upRigidBody_.get());
    }


    /*************************************************************//**
     *
     *  @brief  射撃処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::Shot()
    {
        //for (auto& pGun : upGuns_) pGun->Shot();
    }


    /*************************************************************//**
     *
     *  @brief  ボム処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::Bomb()
    {
        /*
        if (bombEnableFlag_ == true && C_KeyboardManager::s_GetInstance()->GetPressingCount(KeyCode::SDL_SCANCODE_X) == 1)
        {
            upStateMachine_->ChangeState(C_PlayerBombChargeState::s_GetInstance());
            bombEnableFlag_ = false;

            // オプションをすべて待機状態にする
            auto pGameObjects = C_GameObjectManager::s_GetManagementInstance().GetGameObjectsWithType(GameObjectDefine::eType::OPTION);

            for (auto& prGameObject : pGameObjects)
            {
                auto& prOption = std::dynamic_pointer_cast<C_BaseOption>(prGameObject);
                if (prOption->IsOnceConnectFlag() == true) prOption->Wait();
            }
        }*/
    }


    /*************************************************************//**
     *
     *  @brief  連結しているオプションのIDを追加する
     *  @param  連結しているオプションのID
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::AddConnectOption(C_BaseOption* pOption)
    {
        pConnectOptionList_.push_back(pOption);
    }


    /*************************************************************//**
     *
     *  @brief  連結のリセットを行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::ResetConnect()
    {
        pConnectOptionList_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  連結の確認を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::ConnectCheck()
    {
        for (auto pOption : pConnectOptionList_)
        {
            // オプションリストの、移動制限境界ボックスの更新と連結の確認
            UpdateMoveLimitBoundingBox(pOption);
            ConnectCheck(pOption);
        }
    }


    /*************************************************************//**
     *
     *  @brief  連結の確認を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::ConnectCheck(C_BaseOption* pOption)
    {
        for (auto pAnotherOption : *pOption->GetConnectOptionList())
        {
            if (pAnotherOption->IsConnectFlag() == false)
            {
                // 連結フラグを設定
                pAnotherOption->SetConnectFlag(true);

                if (pAnotherOption->IsOnceConnectFlag() == false)
                {
                    // 一度連結したか判断するフラグ
                    pAnotherOption->SetOnceConnectFlag(true);


                    // プレイヤーからのオフセットを求める
                    auto anotherOptionTransform = pAnotherOption->GetRigidBody()->GetTransform();

                    Physics::Vector3 anotherOptionOffsetFromPlayer = anotherOptionTransform.getOrigin() - pOption->GetRigidBody()->GetTransform().getOrigin();
                    anotherOptionOffsetFromPlayer = anotherOptionOffsetFromPlayer.normalize();
                    anotherOptionOffsetFromPlayer = pOption->GetOffsetFromPlayer()
                                                  + (anotherOptionOffsetFromPlayer * pOption->GetRadius())
                                                  + (anotherOptionOffsetFromPlayer * pAnotherOption->GetRadius());
                    anotherOptionOffsetFromPlayer *= Connect::s_OffsetFactor;
                    pAnotherOption->SetOffsetFromPlayer(anotherOptionOffsetFromPlayer);

                    // オプションの座標を設定
                    anotherOptionTransform.setOrigin(upRigidBody_->GetTransform().getOrigin() + anotherOptionOffsetFromPlayer);
                    pAnotherOption->GetRigidBody()->SetTransform(anotherOptionTransform);

                    // 新規連結処理を行う
                    NewConnect();
                    pAnotherOption->NewConnect();

                    // オプション数を1増加
                    AddOptionCount(1);

                    // 連結の効果を処理
                    pAnotherOption->ConnectEffect();

                    // 移動制限境界ボックスの更新
                    UpdateMoveLimitBoundingBox(pAnotherOption);
                }

                // そのオプションの連結の確認
                ConnectCheck(pAnotherOption);
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  新規連結を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::NewConnect()
    {
        // ボムを有効化
        if (bombEnableFlag_ == false) bombEnableFlag_ = true;

        // ステートを連結状態に変更
        //upStateMachine_->ChangeState(C_PlayerConnectionState::s_GetInstance());
    }


    /*************************************************************//**
     *
     *  @brief  移動制限の確認を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::MoveLimitCheck()
    {
        auto transform = upRigidBody_->GetTransform();
        auto& rPosition = transform.getOrigin();

        if (rPosition.x() + moveLimitBoundingBox_.min_.x_ < StageSize::s_left)
        {
            rPosition.setX(StageSize::s_left - moveLimitBoundingBox_.min_.x_);
        }
        else if (rPosition.x() + moveLimitBoundingBox_.max_.x_ > StageSize::s_right)
        {
            rPosition.setX(StageSize::s_right - moveLimitBoundingBox_.max_.x_);
        }

        if (rPosition.y() + moveLimitBoundingBox_.min_.y_ < StageSize::s_bottom)
        {
            rPosition.setY(StageSize::s_bottom - moveLimitBoundingBox_.min_.y_);
        }
        else if (rPosition.y() + moveLimitBoundingBox_.max_.y_ > StageSize::s_top)
        {
            rPosition.setY(StageSize::s_top - moveLimitBoundingBox_.max_.y_);
        }

        upRigidBody_->SetTransform(transform);
    }


    /*************************************************************//**
     *
     *  @brief  移動制限境界ボックスの更新を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::UpdateMoveLimitBoundingBox(C_BaseOption* pOption)
    {
        auto& rPlayerPosition = upRigidBody_->GetTransform().getOrigin();
        auto& rOptionPosition = pOption->GetRigidBody()->GetTransform().getOrigin();
        
        float optionRadius = pOption->GetRadius();

        if (rPlayerPosition.x() + moveLimitBoundingBox_.min_.x_ > rOptionPosition.x() - optionRadius)
        {
            moveLimitBoundingBox_.min_.x_ = rOptionPosition.x() - rPlayerPosition.x() - optionRadius;
        }
        else if (rPlayerPosition.x() + moveLimitBoundingBox_.max_.x_ < rOptionPosition.x() + optionRadius)
        {
            moveLimitBoundingBox_.max_.x_ = rOptionPosition.x() - rPlayerPosition.x() + optionRadius;
        }

        if (rPlayerPosition.y() + moveLimitBoundingBox_.min_.y_ > rOptionPosition.y() - optionRadius)
        {
            moveLimitBoundingBox_.min_.y_ = rOptionPosition.y() - rPlayerPosition.y() - optionRadius;
        }
        else if (rPlayerPosition.y() + moveLimitBoundingBox_.max_.y_ < rOptionPosition.y() + optionRadius)
        {
            moveLimitBoundingBox_.max_.y_ = rOptionPosition.y() - rPlayerPosition.y() + optionRadius;
        }
    }


    /*************************************************************//**
     *
     *  @brief  移動制限境界ボックスのリセットを行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::ResetMoveLimitBoundingBox()
    {
        moveLimitBoundingBox_.min_.Fill(-radius_);
        moveLimitBoundingBox_.max_.Fill(radius_);
    }


    /*************************************************************//**
     *
     *  @brief  移動速度のレベルを加算する
     *  @param  移動速度のレベル
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::AddMoveSpeedLevel(int32_t moveSpeedLevel)
    {
        moveSpeedLevel_ += moveSpeedLevel;
        assert(moveSpeedLevel_ >= 0);

        // TODO
        //C_Shooter::upMoveLogic_->SetMoveScale(1.0f + 0.2f * speedLevel_);
    }


    /*************************************************************//**
     *
     *  @brief  銃のレベルを加算する
     *  @param  銃のレベル
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::AddGunLevel(int32_t gunLevel)
    {
        gunLevel_ += gunLevel;
        assert(gunLevel_ >= 0);
    }


    /*************************************************************//**
     *
     *  @brief  オプションの数を加算する
     *  @param  オプションの数
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::AddOptionCount(int32_t optionCount)
    {
        optionCount_ += optionCount;
    }


    /*************************************************************//**
     *
     *  @brief  ステートマシーンを取得する
     *  @param  なし
     *  @return ステートマシーン
     *
     ****************************************************************/
    State::C_StateMachine<C_BasePlayer>* C_BasePlayer::GetStateMachine() const
    {
        return upStateMachine_.get();
    }


    /*************************************************************//**
     *
     *  @brief  銃のレベルを取得する
     *  @param  なし
     *  @return 銃のレベル
     *
     ****************************************************************/
    int32_t C_BasePlayer::GetGunLevel() const
    {
        return gunLevel_;
    }


    /*************************************************************//**
     *
     *  @brief  連結の硬直フレーム数を取得する
     *  @param  なし
     *  @return 連結の硬直フレーム数
     *
     ****************************************************************/
    int32_t C_BasePlayer::GetConnectPetrifyFrame() const
    {
        return connectPetrifyFrame_;
    }


    /*************************************************************//**
     *
     *  @brief  ボムのチャージフレーム数を取得する
     *  @param  なし
     *  @return ボムのチャージフレーム数
     *
     ****************************************************************/
    int32_t C_BasePlayer::GetBombChargeFrame() const
    {
        return bombChargeFrame_;
    }


    /*************************************************************//**
     *
     *  @brief  ボムの無敵フレーム数を取得する
     *  @param  なし
     *  @return ボムの無敵フレーム数
     *
     ****************************************************************/
    int32_t C_BasePlayer::GetBombInvincibleFrame() const
    {
        return bombInvincibleFrame_;
    }


    /*************************************************************//**
     *
     *  @brief  ボムのチャージフラグを取得する
     *  @param  なし
     *  @return ボムのチャージフラグ
     *
     ****************************************************************/
    bool C_BasePlayer::IsBombChargeFlag() const
    {
        return bombChargeFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  オプションの数を取得する
     *  @param  なし
     *  @return オプションの数
     *
     ****************************************************************/
    int32_t C_BasePlayer::GetOptionCount() const
    {
        return optionCount_;
    }


    /*************************************************************//**
     *
     *  @brief  ボムのチャージフラグを設定する
     *  @param  ボムのチャージフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::SetBombChargeFlag(bool bombChargeFlag)
    {
        bombChargeFlag_ = bombChargeFlag;
    }


    /*************************************************************//**
     *
     *  @brief  非公開の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::DoUpdate()
    {
        //upStateMachine_->Update();
        //ResetConnect();

        upMoveLogic_->Move(upRigidBody_.get());
        MoveLimitCheck();
    }


    /*************************************************************//**
     *
     *  @brief  非公開の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::DoDraw()
    {
        pGlslObject_->BeginWithUnifomBuffer(pUniformBuffer_->GetHandle(), uniformBlockIndex_);

        upRigidBody_->GetTransform().getOpenGLMatrix(modelMatrix_.a_);
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
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_BasePlayer::DoMessageProcess(const Telegram& rTelegram)
    {
        return (upStateMachine_->MessageProcess(rTelegram) == true);
    }
}