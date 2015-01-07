/* �w�b�_�t�@�C�� */
#include "BaseOption.h"
#include "BasePlayer.h"
#include "CollisionProcess.h"



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
    C_BaseOption::C_BaseOption(const std::string& rId, int32_t type) : C_ConnectMachine(rId, type)
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BaseOption::~C_BaseOption()
    {
        if (onceConnectFlag_ == true) pPlayer_->AddOptionCount(-1);
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
        assert(pPlayer_);

        DoUpdate();

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
        upMoveLogic_->Move(upRigidBody_.get());
    }


    /*************************************************************//**
     *
     *  @brief  �A�����̈ړ��������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::ConnectMove()
    {
        auto transform = upRigidBody_->GetTransform();
        auto position = transform.getOrigin();

        transform.setOrigin(pPlayer_->GetRigidBody()->GetTransform().getOrigin() + position);
        upRigidBody_->SetTransform(transform);
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
        // upStateMachine_->ChangeState(C_OptionConnectionState::s_GetInstance());
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
        /*
        if (position_.y_ < GameDefine::StageSize::s_BORDER_BOTTOM - 5.0f)
        {
            existenceFlag_ = false;
        }
        */
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
     *  @brief  �ҋ@�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::Wait()
    {
        //upStateMachine_->ChangeState(C_OptionWaitState::s_GetInstance());
    }


    /*************************************************************//**
     *
     *  @brief  �����������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::SelfCrash()
    {
        //upStateMachine_->ChangeState(C_OptionSelfCrashState::s_GetInstance());
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
        return offsetFromPlayer_;
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
    const std::string& C_BaseOption::GetBombSelfCrashEffectId() const
    {
        //return bombSelfCrashEffectId_;
        static std::string s;
        return s;
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
        offsetFromPlayer_ = rOffsetFromPlayer;
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
     *  @brief  ����J�̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseOption::DoDraw()
    {
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