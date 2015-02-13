/* �w�b�_�t�@�C�� */
#include "OptionCombatState.h"
#include "BaseOption.h"
#include "BaseHitPoint.h"
#include "OptionDestroyedState.h"


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
    C_OptionCombatState::C_OptionCombatState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_OptionCombatState::~C_OptionCombatState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�n�������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionCombatState::Enter(C_BaseOption* pOption)
    {
    }


    /*************************************************************//**
     *
     *  @brief  ���s�������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionCombatState::Execute(C_BaseOption* pOption)
    {
        if (pOption->GetHitPoint()->CheckRemainValue() == false || pOption->IsConnectFlag() == false)
        {
            pOption->GetStateMachine()->ChangeState(C_OptionDestroyedState::s_GetInstance());
        }

        pOption->Shot();
        pOption->Move();
        pOption->ResetConnect();
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionCombatState::Exit(C_BaseOption* pOption)
    {
    }
	

    /*************************************************************//**
     *
     *  @brief  ���b�Z�[�W�������s��
     *  @param  �I�v�V����
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_OptionCombatState::MessageProcess(C_BaseOption* pOption, const Telegram& rTelegram)
    {
        return true;
    }
}