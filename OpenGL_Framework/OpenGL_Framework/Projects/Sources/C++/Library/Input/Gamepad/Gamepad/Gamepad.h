/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include <SDL_joystick.h>
#include <array>


//-------------------------------------------------------------
//!
//! @brief �C���v�b�g
//! @brief ���͊֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Input
{
    /* �ʖ� */
    using GamepadData = SDL_Joystick;                                       // GamepadData�^

    
    namespace
    {
        /* �X�e�B�b�N */
        namespace Stick
        {
            static const int32_t s_DEAD_ZONE = 8500;                        ///< @brief �V�ђl
            static const int32_t s_PUSH_MAXIMUM = 32700;                    ///< @brief �|����̍ő吔
            static const int32_t s_PUSH_MINIMUM = -32700;                   ///< @brief �|����̍ŏ��l
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief �Q�[���p�b�h
    //! @brief �Q�[���p�b�h�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_Gamepad
    {
    public:
        /** �{�^�� */
        enum eButton
        {
            BUTTON_FOUR_UP,                                                 ///< @brief 4�{�^���E��
            BUTTON_FOUR_DOWN,                                               ///< @brief 4�{�^���E��
            BUTTON_FOUR_LEFT,                                               ///< @brief 4�{�^���E��
            BUTTON_FOUR_RIGHT,                                              ///< @brief 4�{�^���E�E
            BUTTON_CROSS_UP,                                                ///< @brief �\���L�[�E��
            BUTTON_CROSS_DOWN,                                              ///< @brief �\���L�[�E��
            BUTTON_CROSS_LEFT,                                              ///< @brief �\���L�[�E��
            BUTTON_CROSS_RIGHT,                                             ///< @brief �\���L�[�E�E
            BUTTON_START,                                                   ///< @brief �X�^�[�g�{�^��
            BUTTON_SELECT,                                                  ///< @brief �Z���N�g�{�^��
            BUTTON_SHOULDER_1_LEFT,                                         ///< @brief L1�{�^��
            BUTTON_SHOULDER_1_RIGHT,                                        ///< @brief R1�{�^��
            BUTTON_SHOULDER_2_LEFT,                                         ///< @brief L2�{�^��
            BUTTON_SHOULDER_2_RIGHT,                                        ///< @brief R2�{�^��

            BUTTON_TOTAL_NUMBER,                                            ///< @brief �{�^���̑���
        };

        /** �X�e�B�b�N */
        enum eStick
        {
            STICK_LEFT,                                                     ///< @brief ���X�e�B�b�N
            STICK_RIGHT,                                                    ///< @brief �E�X�e�B�b�N

            STICK_TOTAL_NUMBER,                                             ///< @brief �X�e�B�b�N�̑���
        };


        C_Gamepad(GamepadData* pGamepad);                                   // �R���X�g���N�^
        virtual ~C_Gamepad();                                               // �f�X�g���N�^
        virtual void Update() = 0;                                          // �X�V����
        void Finalize();                                                    // �I������
        int32_t GetButtonPressingCount(eButton button) const;               // �{�^���̉����Ă���t���[�������擾
        int32_t GetButtonReleasingCount(eButton button) const;              // �{�^���̗����Ă���t���[�������擾
        int32_t GetStickXComponent(eStick stick) const;                     // �X�e�B�b�N��X�������擾
        int32_t GetStickYComponent(eStick stick) const;                     // �X�e�B�b�N��Y�������擾
        int32_t GetStickPushingCount(eStick stick) const;                   // �X�e�B�b�N��|���Ă���t���[�������擾
        int32_t GetStickReleasingCount(eStick stick) const;                 // �X�e�B�b�N��|���Ă��Ȃ��t���[�������擾
    protected:
        GamepadData* pGamepad_ = nullptr;                                   ///< @brief �Q�[���p�b�h
        std::array<int32_t, BUTTON_TOTAL_NUMBER> buttonPressingCounts_;     ///< @brief �{�^���������Ă���t���[�����̃J�E���^
        std::array<int32_t, BUTTON_TOTAL_NUMBER> buttonReleasingCounts_;    ///< @brief �{�^���𗣂��Ă���t���[�����̃J�E���^
        std::array<int32_t, STICK_TOTAL_NUMBER> stickComponentX_;           ///< @brief �X�e�B�b�N��X����
        std::array<int32_t, STICK_TOTAL_NUMBER> stickComponentY_;           ///< @brief �X�e�B�b�N��Y����
        std::array<int32_t, STICK_TOTAL_NUMBER> stickPushingCounts_;        ///< @brief �X�e�B�b�N��|���Ă���t���[�����̃J�E���^
        std::array<int32_t, STICK_TOTAL_NUMBER> stickReleasingCounts_;      ///< @brief �X�e�B�b�N��|���Ă��Ȃ��t���[�����̃J�E���^
    };
}
