/* �w�b�_�t�@�C�� */
#include "PlayerConnectState.h"
#include "BasePlayer.h"
#include "BaseHitPoint.h"
#include "PlayerCombatState.h"
#include "PlayerDestroyedState.h"
#include "PlayerBombChargeState.h"
#include "PlayerInvincibleState.h"


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
    C_PlayerConnectState::C_PlayerConnectState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PlayerConnectState::~C_PlayerConnectState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�n�������s��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerConnectState::Enter(C_BasePlayer* pPlayer)
    {
    }


    /*************************************************************//**
     *
     *  @brief  ���s�������s��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerConnectState::Execute(C_BasePlayer* pPlayer)
    {
        // �J�E���g�A�b�v
        pPlayer->GetConnectFrameCounter()->CountUp();

        if (pPlayer->GetHitPoint()->CheckRemainValue() == false)
        {
            // �j�󂳂ꂽ��Ԃ֕ύX
            pPlayer->GetStateMachine()->ChangeState(C_PlayerDestroyedState::s_GetInstance());
        }
        else if (pPlayer->IsBombChargeFlag() == true)
        {
            // �{���`���[�W��Ԃ֕ύX
            pPlayer->GetStateMachine()->ChangeState(C_PlayerBombChargeState::s_GetInstance());
        }
        else if (pPlayer->GetConnectFrameCounter()->GetCount() == pPlayer->GetConnectPetrifyFrame())
        {
            if (pPlayer->IsInvincibleFlag() == true)
            {
                // ���G��Ԃ֕ύX
                pPlayer->GetStateMachine()->ChangeState(C_PlayerInvincibleState::s_GetInstance());
            }
            else
            {
                // �퓬��Ԃ֕ύX
                pPlayer->GetStateMachine()->ChangeState(C_PlayerCombatState::s_GetInstance());
            }
        }

        // �ړ������̊m�F
        pPlayer->MoveLimitCheck();
        pPlayer->ResetConnect();
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerConnectState::Exit(C_BasePlayer* pPlayer)
    {
        // �J�E���^�[�����Z�b�g
        pPlayer->GetConnectFrameCounter()->Reset();
    }


    /*************************************************************//**
     *
     *  @brief  ���b�Z�[�W�������s��
     *  @param  �v���C���[
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_PlayerConnectState::MessageProcess(C_BasePlayer* pPlayer, const Telegram& rTelegram)
    {
        if (rTelegram.message_ == Message::s_pCONNECT_CHECK)
        {
            pPlayer->ConnectCheck();
        }

        return true;
    }
}