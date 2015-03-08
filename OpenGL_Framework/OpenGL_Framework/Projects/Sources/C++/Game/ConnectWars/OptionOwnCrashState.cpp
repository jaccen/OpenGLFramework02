/* �w�b�_�t�@�C�� */
#include "OptionOwnCrashState.h"
#include "BaseOption.h"
#include "EffectGenerator.h"
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
    C_OptionOwnCrashState::C_OptionOwnCrashState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_OptionOwnCrashState::~C_OptionOwnCrashState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�n�������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionOwnCrashState::Enter(C_BaseOption* pOption)
    {
        // ���j�t���O�𗧂Ă�
        pOption->SetDefeatedFlag(true);
    }


    /*************************************************************//**
     *
     *  @brief  ���s�������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionOwnCrashState::Execute(C_BaseOption* pOption)
    {
        pOption->GetOwnCrashFrameCounter()->CountUp();

        if (pOption->GetOwnCrashFrameCounter()->GetCount() == pOption->GetDefeatedFrame())
        {
            // �J�E���^�����Z�b�g
            pOption->GetOwnCrashFrameCounter()->Reset();

            // ���ʂ����Z�b�g
            pOption->ResetEffect();

            // �I�v�V������j��
            pOption->SetExistanceFlag(false);

            // �Q�[���I�u�W�F�N�g�}�l�[�W���[���珜��
            GameObject::C_GameObjectManager::s_GetInstance()->Remove(pOption->GetId());
        }
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �I�v�V����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionOwnCrashState::Exit(C_BaseOption* pOption)
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
    bool C_OptionOwnCrashState::MessageProcess(C_BaseOption* pOption, const Telegram& rTelegram)
    {
        return true;
    }
}