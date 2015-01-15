/* �w�b�_�t�@�C�� */
#include "BulletDestroyedState.h"
#include "BaseBullet.h"
#include "BaseHitPoint.h"


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
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BulletDestroyedState::C_BulletDestroyedState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BulletDestroyedState::~C_BulletDestroyedState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�n�������s��
     *  @param  �e
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BulletDestroyedState::Enter(C_BaseBullet* pBullet)
    {
        pBullet->SetExistanceFlag(false);
    }


    /*************************************************************//**
     *
     *  @brief  ���s�������s��
     *  @param  �e
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BulletDestroyedState::Execute(C_BaseBullet* pBullet)
    {
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �e
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BulletDestroyedState::Exit(C_BaseBullet* pBullet)
    {
    }


    /*************************************************************//**
     *
     *  @brief  ���b�Z�[�W�������s��
     *  @param  �e
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_BulletDestroyedState::MessageProcess(C_BaseBullet* pBullet, const Telegram& rTelegram)
    {
        return true;
    }
}