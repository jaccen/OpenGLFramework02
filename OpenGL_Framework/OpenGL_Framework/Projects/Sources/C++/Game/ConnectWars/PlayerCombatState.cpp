/* �w�b�_�t�@�C�� */
#include "PlayerCombatState.h"
#include "BasePlayer.h"
#include "ConnectWarsDefine.h"
#include "PlayerDestroyedState.h"


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
    C_PlayerCombatState::C_PlayerCombatState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PlayerCombatState::~C_PlayerCombatState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�n�������s��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerCombatState::Enter(C_BasePlayer* pPlayer)
    {
    }


    /*************************************************************//**
     *
     *  @brief  ���s�������s��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerCombatState::Execute(C_BasePlayer* pPlayer)
    {
        // �q�b�g�|�C���g���Ȃ��Ȃ����ꍇ�A�j�󂳂ꂽ��Ԃ֕ύX
        if (pPlayer->GetHitPoint()->CheckRemainValue() == false)
        {
            pPlayer->GetStateMachine()->ChangeState(C_PlayerDestroyedState::s_GetInstance());
        }

        pPlayer->Move();
        pPlayer->MoveLimitCheck();
        pPlayer->ResetMoveLimitBoundingBox();
        pPlayer->Shot();
        pPlayer->Bomb();
        pPlayer->ResetConnect();
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �v���C���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerCombatState::Exit(C_BasePlayer* pPlayer)
    {
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
    bool C_PlayerCombatState::MessageProcess(C_BasePlayer* pPlayer, const Telegram& rTelegram)
    {
        if (rTelegram.message_ == Message::s_pCONNECT_CHECK)
        {
            pPlayer->ConnectCheck();
        }

        return true;
    }
}