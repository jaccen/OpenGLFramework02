/* �w�b�_�t�@�C�� */
#include "OptionConnectState.h"
#include "BaseOption.h"
#include "BasePlayer.h"
#include "OptionWaitOwnCrashState.h"
#include "OptionCombatState.h"


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
    C_OptionConnectState::C_OptionConnectState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_OptionConnectState::~C_OptionConnectState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�n�������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionConnectState::Enter(C_BaseOption* pOption)
    {
        if (auto pPlayer = pOption->GetPlayer())
        {
            if (pPlayer->IsBombChargeFlag() == true)
            {
                pOption->GetStateMachine()->ChangeState(C_OptionWaitOwnCrashState::s_GetInstance());
            }
            else
            {
                pOption->GetStateMachine()->ChangeState(C_OptionCombatState::s_GetInstance());
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  ���s�������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionConnectState::Execute(C_BaseOption* pOption)
    {
        pOption->ResetConnect();
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionConnectState::Exit(C_BaseOption* pOption)
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
    bool C_OptionConnectState::MessageProcess(C_BaseOption* pOption, const Telegram& rTelegram)
    {
        return true;
    }
}