/* �w�b�_�t�@�C�� */
#include "PlayerInvincibleState.h"
#include "BasePlayer.h"
#include "PlayerCombatState.h"


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
    C_PlayerInvincibleState::C_PlayerInvincibleState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PlayerInvincibleState::~C_PlayerInvincibleState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�n�������s��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerInvincibleState::Enter(C_BasePlayer* pPlayer)
    {
        pPlayer->SetInvincibleFlag(true);
    }


    /*************************************************************//**
     *
     *  @brief  ���s�������s��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerInvincibleState::Execute(C_BasePlayer* pPlayer)
    {
        // �v���C���[��_�ł�����
        if (pPlayer->GetInvincibleFrameCounter()->GetCount() % 4 == 0) pPlayer->SetDrawFlag(!pPlayer->IsDrawFlag());

        pPlayer->GetInvincibleFrameCounter()->CountUp();
        pPlayer->Move();
        pPlayer->MoveLimitCheck();
        pPlayer->ResetMoveLimitBoundingBox();
        pPlayer->Shot();
        pPlayer->Bomb();
        pPlayer->ResetConnect();

        if (pPlayer->GetInvincibleFrameCounter()->GetCount() == pPlayer->GetBombInvincibleFrame())
        {
            pPlayer->GetStateMachine()->ChangeState(C_PlayerCombatState ::s_GetInstance());
            pPlayer->SetInvincibleFlag(false);
            pPlayer->GetInvincibleFrameCounter()->Reset();
        }
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerInvincibleState::Exit(C_BasePlayer* pPlayer)
    {
        pPlayer->SetDrawFlag(true);
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
    bool C_PlayerInvincibleState::MessageProcess(C_BasePlayer* pPlayer, const Telegram& rTelegram)
    {
        if (rTelegram.message_ == Message::s_pCONNECT_CHECK)
        {
            pPlayer->ConnectCheck();
        }

        return true;
    }
}