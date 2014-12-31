/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Gamepad.h"


//-------------------------------------------------------------
//!
//! @brief �C���v�b�g
//! @brief ���͊֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Input
{
    //-------------------------------------------------------------
    //!
    //! @brief XInput
    //! @brief XInput�̏����Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_XInput : public C_Gamepad
    {
    public:
        /** �{�^�� */
        enum eButton
        {
            BUTTON_CROSS_UP,                                                ///< @brief �\���{�^���E��
            BUTTON_CROSS_DOWN,                                              ///< @brief �\���{�^���E��
            BUTTON_CROSS_LEFT,                                              ///< @brief �\���{�^���E��
            BUTTON_CROSS_RIGHT,                                             ///< @brief �\���{�^���E�E
            BUTTON_START,                                                   ///< @brief �X�^�[�g�{�^��
            BUTTON_BACK,                                                    ///< @brief �o�b�N�{�^��
    
            BUTTON_SHOULDER_LEFT = 8,                                       ///< @brief L�{�^��
            BUTTON_SHOULDER_RIGHT,                                          ///< @brief R�{�^��
            BUTTON_B,                                                       ///< @brief B�{�^��
            BUTTON_A,                                                       ///< @brief A�{�^��
            BUTTON_X,                                                       ///< @brief X�{�^��
            BUTTON_Y,                                                       ///< @brief Y�{�^��
            BUTTON_HOME,                                                    ///< @brief �z�[���{�^��
        };
    
        /** �X�e�B�b�N */
        enum eStick
        {
            STICK_LEFT_X,                                                   ///< @brief ���X�e�B�b�N��X����
            STICK_LEFT_Y,                                                   ///< @brief ���X�e�B�b�N��Y����
            STICK_RIGHT_X,                                                  ///< @brief �E�X�e�B�b�N��X����
            STICK_RIGHT_Y,                                                  ///< @brief �E�X�e�B�b�N��Y����
            STICK_LEFT_TRIGGER,                                             ///< @brief ���g���K�[�{�^��
            STICK_RIGHT_TRIGGER,                                            ///< @brief �E�g���K�[�{�^��
        };

        /* �萔 */
        static const char* s_pNAME;                                         ///< @brief ���O

        C_XInput(GamepadData* pGamepad);                                    // �R���X�g���N�^
        ~C_XInput() override;                                               // �f�X�g���N�^
        void Update() override;                                             // �X�V����
    private:
        void ButtonUpdate();                                                // �{�^���̍X�V����
        void TriggerButtonUpdate(eStick trigger,                            // �g���K�[�{�^���̍X�V����
                                 C_Gamepad::eButton updateButton);
        void StickUpdate();                                                 // �X�e�B�b�N�̍X�V����
        void RepairStickComponent(int32_t* pStickComponent);                // �X�e�B�b�N�̐�����K�؂Ȓl�ɏC��
    };
}