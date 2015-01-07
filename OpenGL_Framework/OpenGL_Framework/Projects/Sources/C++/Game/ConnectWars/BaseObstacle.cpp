/* �w�b�_�t�@�C�� */
#include "BaseObstacle.h"
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
    C_BaseObstacle::C_BaseObstacle(const std::string& rId, int32_t type) : C_CollisionObject(rId, type)
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BaseObstacle::~C_BaseObstacle()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ��Q���̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �^�X�N���s�Ftrue
     *  @return �^�X�N�I���Ffalse
     *
     ****************************************************************/
    bool C_BaseObstacle::Update()
    {
        DoUpdate();

        return C_GameObject::existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  ��Q���̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseObstacle::Draw()
    {
        DoDraw();
    }


    /*************************************************************//**
     *
     *  @brief  ��Q���̃��b�Z�[�W�������s��
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_BaseObstacle::MessageProcess(const Telegram& rTelegram)
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
    void C_BaseObstacle::DispatchCollision(C_CollisionObject* pCollisionObject)
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
    void C_BaseObstacle::CollisionProcess(C_BasePlayer* pPlayer)
    {
        C_CollisionProcess::s_PlayerAndObstacle(pPlayer, this);
    }


    /*************************************************************//**
     *
     *  @brief  �I�v�V�����Ƃ̏Փˎ��������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseObstacle::CollisionProcess(C_BaseOption* pOption)
    {
        C_CollisionProcess::s_OptionAndObstacle(pOption, this);
    }


    /*************************************************************//**
     *
     *  @brief  �G�Ƃ̏Փˎ��������s��
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseObstacle::CollisionProcess(C_BaseEnemy* pEnemy)
    {
        C_CollisionProcess::s_EnemyAndObstacle(pEnemy, this);
    }


    /*************************************************************//**
     *
     *  @brief  �e�Ƃ̏Փˎ��������s��
     *  @param  �e
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseObstacle::CollisionProcess(C_BaseBullet* pBullet)
    {
        C_CollisionProcess::s_BulletAndObstale(pBullet, this);
    }


    /*************************************************************//**
     *
     *  @brief  ��Q���Ƃ̏Փˎ��������s��
     *  @param  ��Q��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseObstacle::CollisionProcess(C_BaseObstacle* pObstacle)
    {
        C_CollisionProcess::s_ObstacleAndObstacle(this, pObstacle);
    }


    /*************************************************************//**
     *
     *  @brief  �ړ��������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseObstacle::Move()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseObstacle::DoUpdate()
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
    void C_BaseObstacle::DoDraw()
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
    bool C_BaseObstacle::DoMessageProcess(const Telegram& rTelegram)
    {
        if (upStateMachine_->MessageProcess(rTelegram) == false) return false;

        return true;
    }
}