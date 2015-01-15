/* �w�b�_�t�@�C�� */
#include "PlayerBombChargeState.h"
#include "BasePlayer.h"
#include "PlayerInvincibleState.h"
//#include "EffectGenerator.h"
//#include "BombGenerator.h"


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
        if (pPlayer->IsBombChargeFlag() == false)
        {
            // �e�t���O��ݒ�
            pPlayer->SetBombChargeFlag(true);
            pPlayer->SetInvincibleFlag(true);

            // �`���[�W�G�t�F�N�g�𐶐�
            //C_EffectGenerator::s_GetManagementInstance().Create(pPlayer->GetBombChargeEffectId(), pPlayer->GetPosition());
        }
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
        frameCounter_.CountUp();

        if (frameCounter_.GetCount() >= pPlayer->GetBombChargeFrame())
        {
            // �e�t���O��ݒ�
            pPlayer->SetBombChargeFlag(false);
            pPlayer->SetInvincibleFlag(false);

            // ���G��ԂɕύX
            pPlayer->GetStateMachine()->ChangeState(C_PlayerInvincibleState::s_GetInstance());

            // �{���𐶐�
            //C_BombGenerator::s_GetManagementInstance().Create(pPlayer->GetBombId(), pPlayer->GetPosition(), 1 + pPlayer->GetOptionCount() / 5);
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
        // �J�E���^�[�����Z�b�g
        frameCounter_.Reset();
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
        return true;
    }
}