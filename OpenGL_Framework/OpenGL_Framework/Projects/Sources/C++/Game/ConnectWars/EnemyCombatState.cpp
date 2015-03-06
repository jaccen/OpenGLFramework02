/* �w�b�_�t�@�C�� */
#include "EnemyAdventState.h"
#include "EnemyCombatState.h"
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
    C_EnemyCombatState::C_EnemyCombatState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_EnemyCombatState::~C_EnemyCombatState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�n�������s��
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EnemyCombatState::Enter(C_BaseEnemy* pEnemy)
    {
    }


    /*************************************************************//**
     *
     *  @brief  ���s�������s��
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EnemyCombatState::Execute(C_BaseEnemy* pEnemy)
    {
        // �q�b�g�|�C���g���Ȃ��Ȃ����ꍇ�A�j�󂳂ꂽ��Ԃ֕ύX
        if (pEnemy->GetHitPoint()->CheckRemainValue() == false)
        {
            pEnemy->GetStateMachine()->ChangeState(C_EnemyDestroyedState::s_GetInstance());
        }

        pEnemy->Move();
        pEnemy->Shot();
        pEnemy->MoveLimitCheck();
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �G
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EnemyCombatState::Exit(C_BaseEnemy* pEnemy)
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
    bool C_EnemyCombatState::MessageProcess(C_BaseEnemy* pEnemy, const Telegram& rTelegram)
    {
        return true;
    }
}