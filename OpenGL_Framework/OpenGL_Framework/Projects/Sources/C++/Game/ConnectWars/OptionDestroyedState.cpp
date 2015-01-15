/* �w�b�_�t�@�C�� */
#include "OptionDestroyedState.h"
#include "BaseOption.h"
#include "../../Library/GameObject/Manager/GameObjectManager.h"


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
    C_OptionDestroyedState::C_OptionDestroyedState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_OptionDestroyedState::~C_OptionDestroyedState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�n�������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionDestroyedState::Enter(C_BaseOption* pOption)
    {
        pOption->SetDefeatedFlag(true);
    }


    /*************************************************************//**
     *
     *  @brief  ���s�������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionDestroyedState::Execute(C_BaseOption* pOption)
    {
        // ���ʂ����Z�b�g
        pOption->ResetEffect();

        GameObject::C_GameObjectManager::s_GetInstance()->Remove(pOption->GetId());
        pOption->SetExistanceFlag(false);
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionDestroyedState::Exit(C_BaseOption* pOption)
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
    bool C_OptionDestroyedState::MessageProcess(C_BaseOption* pOption, const Telegram& rTelegram)
    {
        return true;
    }
}