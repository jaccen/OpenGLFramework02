/* �w�b�_�t�@�C�� */
#include "PlayerBombChargeState.h"
#include "BasePlayer.h"


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
    C_PlayerBombChargeState::C_PlayerBombChargeState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PlayerBombChargeState::~C_PlayerBombChargeState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�n�������s��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerBombChargeState::Enter(C_BasePlayer* pPlayer)
    {
        pPlayer->BombCharge();
    }


    /*************************************************************//**
     *
     *  @brief  ���s�������s��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerBombChargeState::Execute(C_BasePlayer* pPlayer)
    {
        // �J�E���g�A�b�v
        pPlayer->GetBombChargeFrameCounter()->CountUp();

        if (pPlayer->GetBombChargeFrameCounter()->GetCount() >= pPlayer->GetBombChargeFrame())
        {
            pPlayer->FireBomb();
        }
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerBombChargeState::Exit(C_BasePlayer* pPlayer)
    {
        pPlayer->GetBombChargeFrameCounter()->Reset();
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
    bool C_PlayerBombChargeState::MessageProcess(C_BasePlayer* pPlayer, const Telegram& rTelegram)
    {
        if (rTelegram.message_ == Message::s_pCONNECT_CHECK)
        {
            pPlayer->ConnectCheck();
        }

        return true;
    }
}