/* �w�b�_�t�@�C�� */
#include "BaseOption.h"
#include "BasePlayer.h"
#include "CollisionProcess.h"
#include "OptionDropState.h"
#include "OptionConnectState.h"
#include "OptionWaitOwnCrashState.h"
#include "OptionOwnCrashState.h"
#include "BaseGun.h"
#include "RigidBodyConnectMoveLogic.h"
#include "EffectGenerator.h"


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
    C_BaseOption::C_BaseOption(const std::string& rId, int32_t type) : C_ConnectMachine(rId, type),

        // �X�e�[�g�}�V�[��
        upStateMachine_(std::make_unique<State::C_StateMachine<C_BaseOption>>(this))

    {
        // ���݂̃X�e�[�g��ݒ�
		upStateMachine_->ChangeState(C_OptionDropState::s_GetInstance());
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BaseOption::~C_BaseOption()
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
    bool C_BaseOption::Update()
    {
        // ��ɍ��̂��A�N�e�B�u��ԂƂ���
        upRigidBody_->EnableActive(true);

        // ����J�̍X�V����
        DoUpdate();

        // �Փ˂����I�u�W�F�N�g��ID��S�ă��Z�b�g
        ResetCollidedObjectId();

        return C_GameObject::existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::Draw()
    {
        if (pPlayer_ == nullptr 
         || waitOwnCrashFlag_ == true
         || pPlayer_->IsDrawFlag() == true)
        {
            DoDraw();
        }
    }


    /*************************************************************//**
     *
     *  @brief  ���b�Z�[�W�������s��
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_BaseOption::MessageProcess(const Telegram& rTelegram)
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
    void C_BaseOption::DispatchCollision(C_CollisionObject* pCollisionObject)
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
    void C_BaseOption::CollisionProcess(C_BasePlayer* pPlayer)
    {
        C_CollisionProcess::s_PlayerAndOption(pPlayer, this);
    }


    /*************************************************************//**
     *
     *  @brief  �I�v�V�����Ƃ̏Փˎ��������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::CollisionProcess(C_BaseOption* pOption)
    {
        C_CollisionProcess::s_OptionAndOption(this, pOption);
    }


    /*************************************************************//**
     *
     *  @brief  �G�Ƃ̏Փˎ��������s��
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::CollisionProcess(C_BaseEnemy* pEnemy)
    {
        C_CollisionProcess::s_OptionAndEnemy(this, pEnemy);
    }


    /*************************************************************//**
     *
     *  @brief  �e�Ƃ̏Փˎ��������s��
     *  @param  �e
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::CollisionProcess(C_BaseBullet* pBullet)
    {
        C_CollisionProcess::s_OptionAndBullet(this, pBullet);
    }


    /*************************************************************//**
     *
     *  @brief  ��Q���Ƃ̏Փˎ��������s��
     *  @param  ��Q��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::CollisionProcess(C_BaseObstacle* pObstacle)
    {
        C_CollisionProcess::s_OptionAndObstacle(this, pObstacle);
    }


    /*************************************************************//**
     *
     *  @brief  �{���Ƃ̏Փˎ��������s��
     *  @param  �{��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::CollisionProcess(C_BaseBomb* pBomb)
    {
        C_CollisionProcess::s_OptionAndBomb(this, pBomb);
    }


    /*************************************************************//**
     *
     *  @brief  �V�[���h�Ƃ̏Փˎ��������s��
     *  @param  �V�[���h
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::CollisionProcess(C_BaseShield* pShield)
    {
        C_CollisionProcess::s_OptionAndShield(this, pShield);
    }


    /*************************************************************//**
     *
     *  @brief  �ړ��������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::Move()
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
    void C_BaseOption::Shot()
    {
        for (auto& uprGun : upGuns_) uprGun->Shot();
    }


    /*************************************************************//**
     *
     *  @brief  ���ʂ����Z�b�g����
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::ResetEffect()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �A�����Ă���I�v�V������ǉ�����
     *  @param  �A�����Ă���I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::AddConnectOption(C_BaseOption* pOption)
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
    void C_BaseOption::ResetConnect()
    {
        connectFlag_ = false;
        pConnectOptionList_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �V�K�A�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::NewConnect()
    {
        // �A����Ԃ֕ύX
        upStateMachine_->ChangeState(C_OptionConnectState::s_GetInstance());

        C_EffectGenerator::s_GetInstance()->Create(ID::Generator::Effect::s_pCONNECT,
                                                   Vector3(upRigidBody_->GetTransform().getOrigin().x(),
                                                           upRigidBody_->GetTransform().getOrigin().y(),
                                                           upRigidBody_->GetTransform().getOrigin().z()));

        // ���̂ɉ������Ă���͂����Z�b�g
        upRigidBody_->EnableActive(true);
        upRigidBody_->SetLinearVelocity();
        upRigidBody_->SetAngularVelocity();
        upRigidBody_->ResetVelocity();

        // �A�����̈ړ����W�b�N�ɕύX
        assert(pPlayer_);
        upMoveLogic_ = std::make_unique<C_RigidBodyConnectMoveLogic>(pPlayer_, *upOffsetFromPlayer_);
    }


    /*************************************************************//**
     *
     *  @brief  �ړ������̊m�F���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::MoveLimitCheck()
    {
        if (upRigidBody_->GetTransform().getOrigin().y() < StageSize::s_bottom - 10.0f)
        {
            existenceFlag_ = false;
        }
    }



    /*************************************************************//**
     *
     *  @brief  �A�����̌��ʂ���������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::ConnectEffect()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �����̔������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::DispatchOwnCrash()
    {
        if (upStateMachine_->CheckCurrentState(C_OptionWaitOwnCrashState::s_GetInstance()) == false)
        {
            upStateMachine_->ChangeState(C_OptionWaitOwnCrashState::s_GetInstance());
            waitOwnCrashFlag_ = true;

            for (auto& prOption : pConnectOptionList_)
            {
                prOption->DispatchOwnCrash();
            }

            ResetConnect();
        }
    }


    /*************************************************************//**
     *
     *  @brief  �����������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::OwnCrash()
    {
        upStateMachine_->ChangeState(C_OptionOwnCrashState::s_GetInstance());

        // �G�t�F�N�g�𐶐�
        auto& rPosition = GetPosition();
        C_EffectGenerator::s_GetInstance()->Create(GetBombOwnCrashEffectId(),
                                                   Vector3(rPosition.x(), rPosition.y(), rPosition.z()));
    }


    /*************************************************************//**
     *
     *  @brief  �A���̖�����������
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::DisableConnect()
    {
        if (enableConnectFlag_ == true)
        {
            enableConnectFlag_ = false;

            for (auto& prOption : pConnectOptionList_) prOption->DisableConnect();
        }
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�[�g�}�V�[�����擾����
     *  @param  �Ȃ�
     *  @return �X�e�[�g�}�V�[��
     *
     ****************************************************************/
    State::C_StateMachine<C_BaseOption>* C_BaseOption::GetStateMachine() const
    {
        return upStateMachine_.get();
    }


    /*************************************************************//**
     *
     *  @brief  �v���C���[����̃I�t�Z�b�g���擾����
     *  @param  �Ȃ�
     *  @return �v���C���[����̃I�t�Z�b�g
     *
     ****************************************************************/
    const Physics::Vector3& C_BaseOption::GetOffsetFromPlayer() const
    {
        return *upOffsetFromPlayer_;
    }


    /*************************************************************//**
     *
     *  @brief  �v���C���[���擾����
     *  @param  �Ȃ�
     *  @return �v���C���[
     *
     ****************************************************************/
    C_BasePlayer* C_BaseOption::GetPlayer() const
    {
        return pPlayer_;
    }


    /*************************************************************//**
     *
     *  @brief  ��x�A�����������f����t���O���擾
     *  @param  �Ȃ�
     *  @return ��x�A�����������f����t���O
     *
     ****************************************************************/
    bool C_BaseOption::IsOnceConnectFlag() const
    {
        return onceConnectFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  �A���t���O���擾
     *  @param  �Ȃ�
     *  @return �A���t���O
     *
     ****************************************************************/
    bool C_BaseOption::IsConnectFlag() const
    {
        return connectFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  ���j�t���O���擾
     *  @param  �Ȃ�
     *  @return ���j�t���O
     *
     ****************************************************************/
    bool C_BaseOption::IsDefeatedFlag() const
    {
        return defeatedFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  ���j��Ԃ̃t���[�������擾
     *  @param  �Ȃ�
     *  @return ���j��Ԃ̃t���[����
     *
     ****************************************************************/
    int32_t C_BaseOption::GetDefeatedFrame() const
    {
        return defeatedFrame_;
    }


    /*************************************************************//**
     *
     *  @brief  �{���̎����G�t�F�N�g��ID���擾
     *  @param  �Ȃ�
     *  @return �{���̎����G�t�F�N�g��ID
     *
     ****************************************************************/
    const std::string& C_BaseOption::GetBombOwnCrashEffectId() const
    {
        return bombOwnCrashEffectId_;
    }


    /*************************************************************//**
     *
     *  @brief  ��x�A�����������f����t���O��ݒ肷��
     *  @param  ��x�A�����������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::SetOnceConnectFlag(bool onceConnectFlag)
    {
        onceConnectFlag_ = onceConnectFlag;
    }


    /*************************************************************//**
     *
     *  @brief  �A���t���O��ݒ肷��
     *  @param  �A���t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::SetConnectFlag(bool connectFlag)
    {
        connectFlag_ = connectFlag;
    }


    /*************************************************************//**
     *
     *  @brief  �v���C���[����̃I�t�Z�b�g��ݒ肷��
     *  @param  �v���C���[����̃I�t�Z�b�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::SetOffsetFromPlayer(const Physics::Vector3& rOffsetFromPlayer)
    {
        upOffsetFromPlayer_ = std::make_unique<Physics::Vector3>(rOffsetFromPlayer);
    }


    /*************************************************************//**
     *
     *  @brief  �v���C���[��ݒ肷��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::SetPlayer(C_BasePlayer* pPlayer)
    {
        pPlayer_ = pPlayer;
    }


    /*************************************************************//**
     *
     *  @brief  ���j�t���O��ݒ肷��
     *  @param  ���j�t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::SetDefeatedFlag(bool defeatedFlag)
    {
        defeatedFlag_ = defeatedFlag;
    }


    /*************************************************************//**
     *
     *  @brief  ���j�t���O��ݒ肷��
     *  @param  ���j�t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    bool C_BaseOption::IsWaitOwnCrashFlag() const
    {
        return waitOwnCrashFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  ���j�t���O��ݒ肷��
     *  @param  ���j�t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::SetWaitOwnCrashFlag(bool waitOwnCrashFlag)
    {
        waitOwnCrashFlag_ = waitOwnCrashFlag;
    }


    /*************************************************************//**
     *
     *  @brief  �����t���[���J�E���^���擾����
     *  @param  �Ȃ�
     *  @return �����t���[���J�E���^
     *
     ****************************************************************/
    Timer::C_FrameCounter* C_BaseOption::GetOwnCrashFrameCounter()
    {
        return &ownCrashFrameCounter_;
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::DoUpdate()
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
    bool C_BaseOption::DoMessageProcess(const Telegram& rTelegram)
    {
        return (upStateMachine_->MessageProcess(rTelegram) == true);
    }
}