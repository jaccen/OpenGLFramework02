/* �w�b�_�t�@�C�� */
#include "PlayerAdventState.h"
#include "BasePlayer.h"
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
    C_PlayerAdventState::C_PlayerAdventState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PlayerAdventState::~C_PlayerAdventState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�n�������s��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerAdventState::Enter(C_BasePlayer* pPlayer)
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
    void C_PlayerAdventState::Execute(C_BasePlayer* pPlayer)
    {
        pPlayer->Move();

        if (pPlayer->IsFinishAdvent() == true)
        {
            pPlayer->ChangeMove(C_BasePlayer::INPUT);
            pPlayer->GetStateMachine()->ChangeState(C_PlayerInvincibleState::s_GetInstance());
        }
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerAdventState::Exit(C_BasePlayer* pPlayer)
    {
        pPlayer->SetInvincibleFlag(false);
        pPlayer->SetEnableConnectFlag(true);
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
    bool C_PlayerAdventState::MessageProcess(C_BasePlayer* pPlayer, const Telegram& rTelegram)
    {
        return true;
    }
}