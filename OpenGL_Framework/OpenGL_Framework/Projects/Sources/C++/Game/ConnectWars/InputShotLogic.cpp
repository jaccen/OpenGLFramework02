/* �w�b�_�t�@�C�� */
#include "InputShotLogic.h"


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
     *  @param  �ˌ��̊Ԋu
     *  @param  �L�[�R�[�h
     *  @param  �Q�[���p�b�h�̃{�^��
     *
     ****************************************************************/
    C_InputShotLogic::C_InputShotLogic(int32_t shotInterval,
                                       Input::KeyCode keyCode,
                                       Input::C_Gamepad::eButton gamepadButton) : C_ShotLogic(shotInterval),

        // �L�[�{�[�h�}�l�[�W���[
        pKeyboardManager_(Input::C_KeyboardManager::s_GetInstance()),

        // �Q�[���p�b�h�}�l�[�W���[
        pGamepadManager_(Input::C_GamepadManager::s_GetInstance())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_InputShotLogic::~C_InputShotLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̏������s��
     *  @param  �Ȃ�
     *  @return �ˌ����������Ftrue
     *  @return �ˌ�������  �Ffalse
     *
     ****************************************************************/
    bool C_InputShotLogic::DoProcess()
    {
        if (((pKeyboardManager_->GetPressingCount(keyCode_) > 0)   
          && (pKeyboardManager_->GetPressingCount(keyCode_) % shotInterval_ == 1))
         || ((pGamepadManager_->GetButtonPressingCount(gamepadButton_) > 0)
          && (pGamepadManager_->GetButtonPressingCount(gamepadButton_) % shotInterval_ == 1)))
        {
            return true;
        }

        return false;
    }
}