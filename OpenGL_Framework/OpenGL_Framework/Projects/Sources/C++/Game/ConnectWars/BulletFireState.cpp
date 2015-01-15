/* �w�b�_�t�@�C�� */
#include "BulletFireState.h"
#include "BaseBullet.h"
#include "BaseHitPoint.h"
#include "BulletDestroyedState.h"


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
    C_BulletFireState::C_BulletFireState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BulletFireState::~C_BulletFireState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�n�������s��
     *  @param  �e
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BulletFireState::Enter(C_BaseBullet* pBullet)
    {
    }


    /*************************************************************//**
     *
     *  @brief  ���s�������s��
     *  @param  �e
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BulletFireState::Execute(C_BaseBullet* pBullet)
    {
        if (pBullet->GetHitPoint()->CheckRemainValue() == false)
        {
            pBullet->GetStateMachine()->ChangeState(C_BulletDestroyedState::s_GetInstance());
        }

        pBullet->Move();
        pBullet->MoveLimitCheck();
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �e
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BulletFireState::Exit(C_BaseBullet* pBullet)
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
    bool C_BulletFireState::MessageProcess(C_BaseBullet* pBullet, const Telegram& rTelegram)
    {
        return true;
    }
}