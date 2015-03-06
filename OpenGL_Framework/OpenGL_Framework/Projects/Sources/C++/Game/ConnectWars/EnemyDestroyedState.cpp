/* �w�b�_�t�@�C�� */
#include "EnemyDestroyedState.h"
#include "BaseEnemy.h"


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
    C_EnemyDestroyedState::C_EnemyDestroyedState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_EnemyDestroyedState::~C_EnemyDestroyedState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�n�������s��
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EnemyDestroyedState::Enter(C_BaseEnemy* pEnemy)
    {
    }


    /*************************************************************//**
     *
     *  @brief  ���s�������s��
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EnemyDestroyedState::Execute(C_BaseEnemy* pEnemy)
    {
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EnemyDestroyedState::Exit(C_BaseEnemy* pEnemy)
    {
    }


    /*************************************************************//**
     *
     *  @brief  ���b�Z�[�W�������s��
     *  @param  �G
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_EnemyDestroyedState::MessageProcess(C_BaseEnemy* pEnemy, const Telegram& rTelegram)
    {
        return true;
    }
}