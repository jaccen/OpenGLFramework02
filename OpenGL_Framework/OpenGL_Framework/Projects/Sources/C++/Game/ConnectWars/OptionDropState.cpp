/* �w�b�_�t�@�C�� */
#include "OptionDropState.h"
#include "BaseOption.h"
#include "BaseHitPoint.h"


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
    C_OptionDropState::C_OptionDropState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_OptionDropState::~C_OptionDropState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�n�������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionDropState::Enter(C_BaseOption* pOption)
    {
        pOption->SetInvincibleFlag(true);
    }


    /*************************************************************//**
     *
     *  @brief  ���s�������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionDropState::Execute(C_BaseOption* pOption)
    {
        pOption->Move();
        pOption->MoveLimitCheck();
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionDropState::Exit(C_BaseOption* pOption)
    {
        pOption->SetInvincibleFlag(false);
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
    bool C_OptionDropState::MessageProcess(C_BaseOption* pOption, const Telegram& rTelegram)
    {
        return true;
    }
}