/* �w�b�_�t�@�C�� */
#include "BasePlayer.h"
#include "BaseOption.h"
#include "CollisionProcess.h"
#include "InputShotLogic.h"
#include "BaseGun.h"
#include "PlayerCombatState.h"
#include "PlayerConnectState.h"
#include "PlayerBombChargeState.h"
#include "RigidBodyInputMoveLogic.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/Model/SelfMade/Loader/ModelLoader.h"
#include "../../Library/OpenGL/Buffer/Primitive/PrimitiveDefine.h"


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
        upStateMachine_(std::make_unique<State::C_StateMachine<C_BasePlayer>>(this, C_PlayerCombatState::s_GetInstance()))

    {
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
        upMoveLogic_->Process(upRigidBody_.get());
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
        for (auto& uprGun : upGuns_) uprGun->Shot();
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
        if ((connectOptionCount_ > 0)
         && (upStateMachine_->CheckCurrentState(*C_PlayerCombatState::s_GetInstance()) == true)
         && ((Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(bombKeyCode_) == 1)
         ||  (Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(bombGamepadButton_) == 1)))
        {
            // �{���̃`���[�W��ԂɕύX
            upStateMachine_->ChangeState(C_PlayerBombChargeState::s_GetInstance());

            // �A�����Ă���I�v�V�����Ɏ����𔭑�
            for (auto pOption : pConnectOptionList_) pOption->DispatchOwnCrash();
        }
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
                    // �v���C���[��ݒ�
                    pAnotherOption->SetPlayer(this);

                    // ��x�A�����������f����t���O
                    pAnotherOption->SetOnceConnectFlag(true);

                    // �v���C���[����̃I�t�Z�b�g�����߂�
                    auto anotherOptionTransform = pAnotherOption->GetRigidBody()->GetTransform();

                    Physics::Vector3 anotherOptionOffsetFromPlayer = anotherOptionTransform.getOrigin() - pOption->GetRigidBody()->GetTransform().getOrigin();
                    anotherOptionOffsetFromPlayer = anotherOptionOffsetFromPlayer.normalize();
                    anotherOptionOffsetFromPlayer = pOption->GetOffsetFromPlayer()
                                                  + (anotherOptionOffsetFromPlayer * pOption->GetRadius())
                                                  + (anotherOptionOffsetFromPlayer * pAnotherOption->GetRadius());
                    anotherOptionOffsetFromPlayer *= Connect::s_offsetFactor;
                    pAnotherOption->SetOffsetFromPlayer(anotherOptionOffsetFromPlayer);

                    // �I�v�V�����̍��W��ݒ�
                    anotherOptionTransform.setOrigin(upRigidBody_->GetTransform().getOrigin() + anotherOptionOffsetFromPlayer);
                    pAnotherOption->GetRigidBody()->SetTransform(anotherOptionTransform);

                    // �V�K�A���������s��
                    NewConnect();
                    pAnotherOption->NewConnect();

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
        // �I�v�V��������1����
        AddConnectOptionCount(1);

        // �A����ԂɕύX
        upStateMachine_->ChangeState(C_PlayerConnectState::s_GetInstance());
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
        assert(dynamic_cast<C_RigidBodyInputMoveLogic*>(upMoveLogic_.get()));

        auto pInputMoveLogic = static_cast<C_RigidBodyInputMoveLogic*>(upMoveLogic_.get());

        if (moveSpeedLevel < s_MAX_MOVE_SPEED_LEVEL)
        {
            pInputMoveLogic->SetMovementScale(1.0f + moveSpeedUpInterval_ * moveSpeedLevel_);
        }
        else
        {
            pInputMoveLogic->SetMovementScale(1.0f + moveSpeedUpInterval_ * s_MAX_MOVE_SPEED_LEVEL);
        }
    }


    /*************************************************************//**
     *
     *  @brief  �A�������I�v�V�����̐������Z����
     *  @param  �A�������I�v�V�����̐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePlayer::AddConnectOptionCount(int32_t connectOptionCount)
    {
        connectOptionCount_ += connectOptionCount;
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
        upStateMachine_->Update();
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