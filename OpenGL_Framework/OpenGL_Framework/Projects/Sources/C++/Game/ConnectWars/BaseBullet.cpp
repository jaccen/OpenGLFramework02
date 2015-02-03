/* �w�b�_�t�@�C�� */
#include "BaseBullet.h"
#include "CollisionProcess.h"
#include "BulletFireState.h"


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
    C_BaseBullet::C_BaseBullet(const std::string& rId, int32_t type) : C_CollisionObject(rId, type),

        // �X�e�[�g�}�V�[��
        upStateMachine_(std::make_unique<State::C_StateMachine<C_BaseBullet>>(this))

    {
		upStateMachine_->SetCurrentState(C_BulletFireState::s_GetInstance());

        // �p���[�𐶐�
        upPower_ = std::make_unique<C_BasePower>();
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BaseBullet::~C_BaseBullet()
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
    bool C_BaseBullet::Update()
    {
        // ��ɃA�N�e�B�u��������
        upRigidBody_->EnableActive(true);

        // ����J�̍X�V����
        DoUpdate();

        // �Փ˃I�u�W�F�N�g��ID�����Z�b�g
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
    void C_BaseBullet::Draw()
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
    bool C_BaseBullet::MessageProcess(const Telegram& rTelegram)
    {
        if (DoMessageProcess(rTelegram) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �Փˌ��m�̔��s���s��
     *  @param  �Փ˃I�u�W�F�N�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBullet::DispatchCollision(C_CollisionObject* pCollisionObject)
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
    void C_BaseBullet::CollisionProcess(C_BasePlayer* pPlayer)
    {
        C_CollisionProcess::s_PlayerAndBullet(pPlayer, this);
    }


    /*************************************************************//**
     *
     *  @brief  �I�v�V�����Ƃ̏Փˎ��������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBullet::CollisionProcess(C_BaseOption* pOption)
    {
        C_CollisionProcess::s_OptionAndBullet(pOption, this);
    }


    /*************************************************************//**
     *
     *  @brief  �G�Ƃ̏Փˎ��������s��
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBullet::CollisionProcess(C_BaseEnemy* pEnemy)
    {
        C_CollisionProcess::s_EnemyAndBullet(pEnemy, this);
    }


    /*************************************************************//**
     *
     *  @brief  �e�Ƃ̏Փˎ��������s��
     *  @param  �e
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBullet::CollisionProcess(C_BaseBullet* pBullet)
    {
        C_CollisionProcess::s_BulletAndBullet(this, pBullet);
    }


    /*************************************************************//**
     *
     *  @brief  ��Q���Ƃ̏Փˎ��������s��
     *  @param  ��Q��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBullet::CollisionProcess(C_BaseObstacle* pObstacle)
    {
        C_CollisionProcess::s_BulletAndObstale(this, pObstacle);
    }


    /*************************************************************//**
     *
     *  @brief  �{���Ƃ̏Փˎ��������s��
     *  @param  �{��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBullet::CollisionProcess(C_BaseBomb* pBomb)
    {
        C_CollisionProcess::s_BulletAndBomb(this, pBomb);
    }


    /*************************************************************//**
     *
     *  @brief  �ړ��������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBullet::Move()
    {
        upMoveLogic_->Process(upRigidBody_.get());
    }


    /*************************************************************//**
     *
     *  @brief  �ړ������̊m�F���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBullet::MoveLimitCheck()
    {
        auto transform = upRigidBody_->GetTransform();
        auto& rPosition = transform.getOrigin();

        if (rPosition.x() < StageSize::s_left
         || rPosition.x() > StageSize::s_right
         || rPosition.y() < StageSize::s_bottom
         || rPosition.y() > StageSize::s_top)
        {
            existenceFlag_ = false;
        }
    }


    /*************************************************************//**
     *
     *  @brief  �ˌ��҂̎�ނ��擾����
     *  @param  �Ȃ�
     *  @return �ˌ��҂̎��
     *
     ****************************************************************/
    int32_t C_BaseBullet::GetShooterType() const
    {
        return shooterType_;
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�[�g�}�V�[�����擾����
     *  @param  �Ȃ�
     *  @return �X�e�[�g�}�V�[��
     *
     ****************************************************************/
    State::C_StateMachine<C_BaseBullet>* C_BaseBullet::GetStateMachine() const
    {
        return upStateMachine_.get();
    }


    /*************************************************************//**
     *
     *  @brief  ���W���擾����
     *  @param  �Ȃ�
     *  @return ���W
     *
     ****************************************************************/
    const Physics::Vector3& C_BaseBullet::GetPosition() const
    {
        return upRigidBody_->GetTransform().getOrigin();
    }


    /*************************************************************//**
     *
     *  @brief  �ˌ��҂̎�ނ�ݒ肷��
     *  @param  �ˌ��҂̎��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBullet::SetShooterType(int32_t shooterType)
    {
        shooterType_ = shooterType;
    }


    /*************************************************************//**
     *
     *  @brief  �ړ��̃��W�b�N��ݒ肷��
     *  @param  �ړ��̃��W�b�N
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBullet::SetMoveLogic(C_RigidBodyMoveLogic* pMoveLogic)
    {
        upMoveLogic_.reset(pMoveLogic);
    }


    /*************************************************************//**
     *
     *  @brief  ���W��ݒ肷��
     *  @param  ���W
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBullet::SetPosition(const Physics::Vector3& rPosition)
    {
        auto transform = upRigidBody_->GetTransform();
        transform.setOrigin(rPosition);
        upRigidBody_->SetTransform(transform);
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBullet::DoUpdate()
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
    bool C_BaseBullet::DoMessageProcess(const Telegram& rTelegram)
    {
        if (upStateMachine_->MessageProcess(rTelegram) == false) return false;

        return true;
    }
}