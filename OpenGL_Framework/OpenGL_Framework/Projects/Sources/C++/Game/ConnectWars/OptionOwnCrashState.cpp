/* �w�b�_�t�@�C�� */
#include "OptionOwnCrashState.h"
#include "BaseOption.h"


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

        // �G�t�F�N�g�𐶐�
        //C_EffectGenerator::s_GetManagementInstance().Create(pOption->GetBombSelfCrashEffectId(), pOption->GetPosition());
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
        frameCounter_.CountUp();

        //pOption->Defeated();

        if (pOption->GetDefeatedFrame() <= frameCounter_.GetCount())
        {
            // ���ʂ����Z�b�g
            pOption->ResetEffect();

            // �Q�[���I�u�W�F�N�g�}�l�[�W���[���珜��
            //C_GameObjectManager::s_GetManagementInstance().Remove(pOption->GetId());

            // �I�v�V������j��
            pOption->SetExistanceFlag(false);
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