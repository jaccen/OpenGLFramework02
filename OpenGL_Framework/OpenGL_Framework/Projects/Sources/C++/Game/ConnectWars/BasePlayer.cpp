/* �w�b�_�t�@�C�� */
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
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  ID
     *  @param  ���
     *
     ****************************************************************/
    C_BasePlayer::C_BasePlayer(const std::string& rId, int32_t type) : C_ConnectMachine(rId, type),

        // �X�e�[�g�}�V�[��
        upStateMachine_(std::make_unique<State::C_StateMachine<C_BasePlayer>>(this))

    {
        // ���`��𐫐���
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

        // �ړ��������E�{�b�N�X�����Z�b�g
        //ResetMoveLimitBoundingBox();
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BasePlayer::~C_BasePlayer()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �^�X�N���s�Ftrue
     *  @return �^�X�N�I���Ffalse
     *
     ****************************************************************/
    bool C_BasePlayer::Update()
    {
        DoUpdate();

        return existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::Draw()
    {
        DoDraw();
    }


    /*************************************************************//**
     *
     *  @brief  ���b�Z�[�W�������s��
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_BasePlayer::MessageProcess(const Telegram& rTelegram)
    {
        if (DoMessageProcess(rTelegram) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �Փˌ��o�̔��s���s��
     *  @param  �Փ˃I�u�W�F�N�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::DispatchCollision(C_CollisionObject* pCollisionObject)
    {
        pCollisionObject->CollisionProcess(this);
    }


    /*************************************************************//**
     *
     *  @brief  �v���C���[�Ƃ̏Փˎ��������s��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BasePlayer* pPlayer)
    {
        C_CollisionProcess::s_PlayerAndPlayer(this, pPlayer);
    }


    /*************************************************************//**
     *
     *  @brief  �I�v�V�����Ƃ̏Փˎ��������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BaseOption* pOption)
    {
        C_CollisionProcess::s_PlayerAndOption(this, pOption);
    }


    /*************************************************************//**
     *
     *  @brief  �G�Ƃ̏Փˎ��������s��
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BaseEnemy* pEnemy)
    {
        C_CollisionProcess::s_PlayerAndEnemy(this, pEnemy);
    }


    /*************************************************************//**
     *
     *  @brief  �e�Ƃ̏Փˎ��������s��
     *  @param  �e
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BaseBullet* pBullet)
    {
        C_CollisionProcess::s_PlayerAndBullet(this, pBullet);
    }


    /*************************************************************//**
     *
     *  @brief  ��Q���Ƃ̏Փˎ��������s��
     *  @param  ��Q��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BaseObstacle* pObstacle)
    {
        C_CollisionProcess::s_PlayerAndObstacle(this, pObstacle);
    }


    /*************************************************************//**
     *
     *  @brief  �{���Ƃ̏Փˎ��������s��
     *  @param  �{��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BaseBomb* pBomb)
    {
        C_CollisionProcess::s_PlayerAndBomb(this, pBomb);
    }


    /*************************************************************//**
     *
     *  @brief  �ړ��������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::Move()
    {
        upMoveLogic_->Move(upRigidBody_.get());
    }


    /*************************************************************//**
     *
     *  @brief  �ˌ��������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::Shot()
    {
        //for (auto& pGun : upGuns_) pGun->Shot();
    }


    /*************************************************************//**
     *
     *  @brief  �{���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::Bomb()
    {
        /*
        if (bombEnableFlag_ == true && C_KeyboardManager::s_GetInstance()->GetPressingCount(KeyCode::SDL_SCANCODE_X) == 1)
        {
            upStateMachine_->ChangeState(C_PlayerBombChargeState::s_GetInstance());
            bombEnableFlag_ = false;

            // �I�v�V���������ׂđҋ@��Ԃɂ���
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
     *  @brief  �A�����Ă���I�v�V������ID��ǉ�����
     *  @param  �A�����Ă���I�v�V������ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::AddConnectOption(C_BaseOption* pOption)
    {
        pConnectOptionList_.push_back(pOption);
    }


    /*************************************************************//**
     *
     *  @brief  �A���̃��Z�b�g���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::ResetConnect()
    {
        pConnectOptionList_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �A���̊m�F���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::ConnectCheck()
    {
        for (auto pOption : pConnectOptionList_)
        {
            // �I�v�V�������X�g�́A�ړ��������E�{�b�N�X�̍X�V�ƘA���̊m�F
            UpdateMoveLimitBoundingBox(pOption);
            ConnectCheck(pOption);
        }
    }


    /*************************************************************//**
     *
     *  @brief  �A���̊m�F���s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::ConnectCheck(C_BaseOption* pOption)
    {
        for (auto pAnotherOption : *pOption->GetConnectOptionList())
        {
            if (pAnotherOption->IsConnectFlag() == false)
            {
                // �A���t���O��ݒ�
                pAnotherOption->SetConnectFlag(true);

                if (pAnotherOption->IsOnceConnectFlag() == false)
                {
                    // ��x�A�����������f����t���O
                    pAnotherOption->SetOnceConnectFlag(true);


                    // �v���C���[����̃I�t�Z�b�g�����߂�
                    auto anotherOptionTransform = pAnotherOption->GetRigidBody()->GetTransform();

                    Physics::Vector3 anotherOptionOffsetFromPlayer = anotherOptionTransform.getOrigin() - pOption->GetRigidBody()->GetTransform().getOrigin();
                    anotherOptionOffsetFromPlayer = anotherOptionOffsetFromPlayer.normalize();
                    anotherOptionOffsetFromPlayer = pOption->GetOffsetFromPlayer()
                                                  + (anotherOptionOffsetFromPlayer * pOption->GetRadius())
                                                  + (anotherOptionOffsetFromPlayer * pAnotherOption->GetRadius());
                    anotherOptionOffsetFromPlayer *= Connect::s_OffsetFactor;
                    pAnotherOption->SetOffsetFromPlayer(anotherOptionOffsetFromPlayer);

                    // �I�v�V�����̍��W��ݒ�
                    anotherOptionTransform.setOrigin(upRigidBody_->GetTransform().getOrigin() + anotherOptionOffsetFromPlayer);
                    pAnotherOption->GetRigidBody()->SetTransform(anotherOptionTransform);

                    // �V�K�A���������s��
                    NewConnect();
                    pAnotherOption->NewConnect();

                    // �I�v�V��������1����
                    AddOptionCount(1);

                    // �A���̌��ʂ�����
                    pAnotherOption->ConnectEffect();

                    // �ړ��������E�{�b�N�X�̍X�V
                    UpdateMoveLimitBoundingBox(pAnotherOption);
                }

                // ���̃I�v�V�����̘A���̊m�F
                ConnectCheck(pAnotherOption);
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  �V�K�A�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::NewConnect()
    {
        // �{����L����
        if (bombEnableFlag_ == false) bombEnableFlag_ = true;

        // �X�e�[�g��A����ԂɕύX
        //upStateMachine_->ChangeState(C_PlayerConnectionState::s_GetInstance());
    }


    /*************************************************************//**
     *
     *  @brief  �ړ������̊m�F���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
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
     *  @brief  �ړ��������E�{�b�N�X�̍X�V���s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
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
     *  @brief  �ړ��������E�{�b�N�X�̃��Z�b�g���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::ResetMoveLimitBoundingBox()
    {
        moveLimitBoundingBox_.min_.Fill(-radius_);
        moveLimitBoundingBox_.max_.Fill(radius_);
    }


    /*************************************************************//**
     *
     *  @brief  �ړ����x�̃��x�������Z����
     *  @param  �ړ����x�̃��x��
     *  @return �Ȃ�
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
     *  @brief  �e�̃��x�������Z����
     *  @param  �e�̃��x��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::AddGunLevel(int32_t gunLevel)
    {
        gunLevel_ += gunLevel;
        assert(gunLevel_ >= 0);
    }


    /*************************************************************//**
     *
     *  @brief  �I�v�V�����̐������Z����
     *  @param  �I�v�V�����̐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::AddOptionCount(int32_t optionCount)
    {
        optionCount_ += optionCount;
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�[�g�}�V�[�����擾����
     *  @param  �Ȃ�
     *  @return �X�e�[�g�}�V�[��
     *
     ****************************************************************/
    State::C_StateMachine<C_BasePlayer>* C_BasePlayer::GetStateMachine() const
    {
        return upStateMachine_.get();
    }


    /*************************************************************//**
     *
     *  @brief  �e�̃��x�����擾����
     *  @param  �Ȃ�
     *  @return �e�̃��x��
     *
     ****************************************************************/
    int32_t C_BasePlayer::GetGunLevel() const
    {
        return gunLevel_;
    }


    /*************************************************************//**
     *
     *  @brief  �A���̍d���t���[�������擾����
     *  @param  �Ȃ�
     *  @return �A���̍d���t���[����
     *
     ****************************************************************/
    int32_t C_BasePlayer::GetConnectPetrifyFrame() const
    {
        return connectPetrifyFrame_;
    }


    /*************************************************************//**
     *
     *  @brief  �{���̃`���[�W�t���[�������擾����
     *  @param  �Ȃ�
     *  @return �{���̃`���[�W�t���[����
     *
     ****************************************************************/
    int32_t C_BasePlayer::GetBombChargeFrame() const
    {
        return bombChargeFrame_;
    }


    /*************************************************************//**
     *
     *  @brief  �{���̖��G�t���[�������擾����
     *  @param  �Ȃ�
     *  @return �{���̖��G�t���[����
     *
     ****************************************************************/
    int32_t C_BasePlayer::GetBombInvincibleFrame() const
    {
        return bombInvincibleFrame_;
    }


    /*************************************************************//**
     *
     *  @brief  �{���̃`���[�W�t���O���擾����
     *  @param  �Ȃ�
     *  @return �{���̃`���[�W�t���O
     *
     ****************************************************************/
    bool C_BasePlayer::IsBombChargeFlag() const
    {
        return bombChargeFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  �I�v�V�����̐����擾����
     *  @param  �Ȃ�
     *  @return �I�v�V�����̐�
     *
     ****************************************************************/
    int32_t C_BasePlayer::GetOptionCount() const
    {
        return optionCount_;
    }


    /*************************************************************//**
     *
     *  @brief  �{���̃`���[�W�t���O��ݒ肷��
     *  @param  �{���̃`���[�W�t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::SetBombChargeFlag(bool bombChargeFlag)
    {
        bombChargeFlag_ = bombChargeFlag;
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
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
     *  @brief  ����J�̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
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
     *  @brief  ����J�̃��b�Z�[�W�������s��
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_BasePlayer::DoMessageProcess(const Telegram& rTelegram)
    {
        return (upStateMachine_->MessageProcess(rTelegram) == true);
    }
}