/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ShotLogic.h"
#include "../../Library/Input/Keyboard/KeyboardManager.h"
#include "../../Library/Input/Gamepad/Manager/GamepadManager.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief �C���v�b�g�V���b�g���W�b�N
    //! @brief ���͂ɂ��ˌ��̃��W�b�N
    //!
    //-------------------------------------------------------------
    class C_InputShotLogic : public C_ShotLogic
    {
    public:
        C_InputShotLogic(int32_t shotInterval,                                                              // �R���X�g���N�^
                         Input::KeyCode keyCode = Input::KeyCode::SDL_SCANCODE_Z,
                         Input::C_Gamepad::eButton gamepadButton = Input::C_Gamepad::BUTTON_FOUR_DOWN);
        ~C_InputShotLogic() override;                                                                       // �f�X�g���N�^
    private:
        Input::KeyCode keyCode_ = Input::KeyCode::SDL_SCANCODE_Z;                                           ///< @brief �L�[�R�[�h
        Input::C_Gamepad::eButton gamepadButton_ = Input::C_Gamepad::BUTTON_FOUR_DOWN;                      ///< @brief �Q�[���p�b�h�̃{�^��

        Input::C_KeyboardManager* pKeyboardManager_ = nullptr;                                              ///< @brief �L�[�{�[�h�}�l�[�W���[
        Input::C_GamepadManager* pGamepadManager_ = nullptr;                                                ///< @brief �Q�[���p�b�h�}�l�[�W���[

        bool DoProcess() override;                                                                          // ����J�̏���
    };
}