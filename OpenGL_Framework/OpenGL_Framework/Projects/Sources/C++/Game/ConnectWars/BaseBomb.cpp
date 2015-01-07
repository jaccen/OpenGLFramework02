/* �w�b�_�t�@�C�� */
#include "BaseBomb.h"
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
    C_BaseBomb::C_BaseBomb(const std::string& rId, int32_t type) : C_CollisionObject(rId, type)
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BaseBomb::~C_BaseBomb()
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
    bool C_BaseBomb::Update()
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
    void C_BaseBomb::Draw()
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
    bool C_BaseBomb::MessageProcess(const Telegram& rTelegram)
    {
        return DoMessageProcess(rTelegram);
    }


    /*************************************************************//**
     *
     *  @brief  �Փˌ��m�𔭑�����
     *  @param  �Փ˃I�u�W�F�N�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBomb::DispatchCollision(C_CollisionObject* pCollisionObject)
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
    void C_BaseBomb::CollisionProcess(C_BasePlayer* pPlayer)
    {
        C_CollisionProcess::s_PlayerAndBomb(pPlayer, this);
    }


    /*************************************************************//**
     *
     *  @brief  �I�v�V�����Ƃ̏Փˎ��������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBomb::CollisionProcess(C_BaseOption* pOption)
    {
        C_CollisionProcess::s_OptionAndBomb(pOption, this);
    }


    /*************************************************************//**
     *
     *  @brief  �G�Ƃ̏Փˎ��������s��
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBomb::CollisionProcess(C_BaseEnemy* pEnemy)
    {
        C_CollisionProcess::s_EnemyAndBomb(pEnemy, this);
    }


    /*************************************************************//**
     *
     *  @brief  �e�Ƃ̏Փˎ��������s��
     *  @param  �e
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBomb::CollisionProcess(C_BaseBullet* pBullet)
    {
        C_CollisionProcess::s_BulletAndBomb(pBullet, this);
    }


    /*************************************************************//**
     *
     *  @brief  ��Q���Ƃ̏Փˎ��������s��
     *  @param  ��Q��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBomb::CollisionProcess(C_BaseObstacle* pObstacle)
    {
        C_CollisionProcess::s_ObstacleAndBomb(pObstacle, this);
    }


    /*************************************************************//**
     *
     *  @brief  �{���Ƃ̏Փˎ��������s��
     *  @param  �{��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBomb::CollisionProcess(C_BaseBomb* pBomb)
    {
        C_CollisionProcess::s_BombAndBomb(this, pBomb);
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseBomb::DoDraw()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̃��b�Z�[�W�������s��
     *  @param  �e���O����
     *  @return �Ȃ�
     *
     ****************************************************************/
    bool C_BaseBomb::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }
}