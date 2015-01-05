/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../../Singleton/Singleton.h"
#include "../Gamepad/Gamepad.h"


//-------------------------------------------------------------
//!
//! @brief �C���v�b�g
//! @brief ���͊֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Input
{
    /** �Q�[���p�b�h�̔ԍ� */
    enum eGamepadNumber
    {
        GAMEPAD_01,
        GAMEPAD_02,
        GAMEPAD_03,
        GAMEPAD_04,
    };


    //-------------------------------------------------------------
    //!
    //! @brief �Q�[���p�b�h�}�l�[�W���[
    //! @brief �Q�[���p�b�h���Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_GamepadManager : public Singleton::C_Singleton<C_GamepadManager>
    {
        friend C_Singleton<C_GamepadManager>;                                                                       // �V���O���g���N���X���t�����h��
    public:
        void Initialize();                                                                                          // ����������
        void Update();                                                                                              // �X�V����
        void Finalize();                                                                                            // �I������

        /* �Q�b�^�[ */
        int32_t GetButtonPressingCount(C_Gamepad::eButton button, eGamepadNumber number = GAMEPAD_01) const;        // �{�^���������Ă���t���[�������擾
        int32_t GetButtonReleasingCount(C_Gamepad::eButton button, eGamepadNumber number = GAMEPAD_01) const;       // �{�^���𗣂��Ă���t���[�������擾
        int32_t GetStickXComponent(C_Gamepad::eStick stick, eGamepadNumber number = GAMEPAD_01) const;              // �X�e�B�b�N��X�������擾
        int32_t GetStickYComponent(C_Gamepad::eStick stick, eGamepadNumber number = GAMEPAD_01) const;              // �X�e�B�b�N��Y�������擾
        int32_t GetStickPushingCount(C_Gamepad::eStick stick, eGamepadNumber number = GAMEPAD_01) const;            // �X�e�B�b�N��|���Ă���t���[�������擾
        int32_t GetStickReleasingCount(C_Gamepad::eStick stick, eGamepadNumber number = GAMEPAD_01) const;          // �X�e�B�b�N��|���Ă��Ȃ��t���[�������擾
    private:
        /* �O���錾 */
        class C_GamepadManagerImpl;

        std::unique_ptr<C_GamepadManagerImpl> upImpl_;                                                              ///< @brief �������

        C_GamepadManager();                                                                                         // �R���X�g���N�^
        ~C_GamepadManager() override;                                                                               // �f�X�g���N�^
    };
}