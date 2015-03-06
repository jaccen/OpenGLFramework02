/* �w�b�_�t�@�C�� */
#include "EnemyAdventState.h"
#include "EnemyCombatState.h"
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
    C_EnemyAdventState::C_EnemyAdventState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_EnemyAdventState::~C_EnemyAdventState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�n�������s��
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EnemyAdventState::Enter(C_BaseEnemy* pEnemy)
    {
    }


    /*************************************************************//**
     *
     *  @brief  ���s�������s��
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EnemyAdventState::Execute(C_BaseEnemy* pEnemy)
    {
        if (pEnemy->IsFinishAdvent() == true)
        {
            pEnemy->GetStateMachine()->ChangeState(C_EnemyCombatState::s_GetInstance());
        }
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EnemyAdventState::Exit(C_BaseEnemy* pEnemy)
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
    bool C_EnemyAdventState::MessageProcess(C_BaseEnemy* pEnemy, const Telegram& rTelegram)
    {
        return true;
    }
}