/* �w�b�_�t�@�C�� */
#include "OptionWaitOwnCrashState.h"
#include "BaseOption.h"
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
    C_OptionWaitOwnCrashState::C_OptionWaitOwnCrashState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_OptionWaitOwnCrashState::~C_OptionWaitOwnCrashState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�n�������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionWaitOwnCrashState::Enter(C_BaseOption* pOption)
    {
        // ���G�t���O��ݒ�
        pOption->SetInvincibleFlag(true);

        // ���ʂ����Z�b�g
        pOption->ResetEffect();

        // �A�����Ă����ꍇ�͘A������Ă���I�v�V�����̐���1���炷
        if (pOption->IsOnceConnectFlag() == true)
        {
            assert(pOption->GetPlayer());
            pOption->GetPlayer()->AddConnectOptionCount(-1);
        }
    }


    /*************************************************************//**
     *
     *  @brief  ���s�������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionWaitOwnCrashState::Execute(C_BaseOption* pOption)
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
    void C_OptionWaitOwnCrashState::Exit(C_BaseOption* pOption)
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
    bool C_OptionWaitOwnCrashState::MessageProcess(C_BaseOption* pOption, const Telegram& rTelegram)
    {
        if (rTelegram.message_ == Message::s_pOWN_CRASH)
        {
            pOption->OwnCrash();
        }

        return true;
    }
}