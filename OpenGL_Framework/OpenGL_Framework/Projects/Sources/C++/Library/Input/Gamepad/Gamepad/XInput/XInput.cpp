/* �w�b�_�t�@�C�� */
#include "XInput.h"


//-------------------------------------------------------------
//!
//! @brief �C���v�b�g
//! @brief ���͊֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Input
{

#pragma region �ÓI�����o�ϐ��̏�����


    /* ���O */
    const char* C_XInput::s_pNAME = "XInput Controller #1";


#pragma endregion


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_XInput::C_XInput(GamepadData* pGamepad) : C_Gamepad(pGamepad)
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_XInput::~C_XInput()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_XInput::Update()
    {
        assert(pGamepad_);

        // �{�^���̍X�V����
        ButtonUpdate();

        // �X�e�B�b�N�̍X�V����
        StickUpdate();
    }


    /*************************************************************//**
     *
     *  @brief  �{�^���̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_XInput::ButtonUpdate()
    {
        // �{�^���̏�Ԃ̎擾���ɗ��p�������
        static const eButton s_PARAMETERS[] =
        {
            BUTTON_Y,
            BUTTON_B,
            BUTTON_X,
            BUTTON_A,
            BUTTON_CROSS_UP,
            BUTTON_CROSS_DOWN,
            BUTTON_CROSS_LEFT,
            BUTTON_CROSS_RIGHT,
            BUTTON_START,
            BUTTON_BACK,
            BUTTON_SHOULDER_LEFT,
            BUTTON_SHOULDER_RIGHT,
        };

        // �����̑���
        static const int s_PARAMETER_TOTAL_NUMBER = 12;

        for (size_t i = 0; i < s_PARAMETER_TOTAL_NUMBER; ++i)
        {
            // ������Ă���ꍇ
            if (::SDL_JoystickGetButton(pGamepad_, s_PARAMETERS[i]) == 1)
            {
                // �����Ă���t���[���������Z�b�g���A
                // �����Ă���t���[����1����
                if (buttonReleasingCounts_[i] > 0) buttonReleasingCounts_[i] = 0;

                ++buttonPressingCounts_[i];
            }
            else
            {
                // �����Ă���t���[���������Z�b�g���A
                // �����Ă���t���[������1����
                if (buttonPressingCounts_[i] > 0) buttonPressingCounts_[i] = 0;

                ++buttonReleasingCounts_[i];
            }
        }


        // L2�{�^�����X�V
        TriggerButtonUpdate(STICK_LEFT_TRIGGER, BUTTON_SHOULDER_2_LEFT);

        // R2�{�^�����X�V
        TriggerButtonUpdate(STICK_RIGHT_TRIGGER, BUTTON_SHOULDER_2_RIGHT);
    }


    /*************************************************************//**
     *
     *  @brief  �g���K�[�{�^���̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_XInput::TriggerButtonUpdate(eStick trigger,
                                       C_Gamepad::eButton updateButton)
    {
        // �g���K�[�̌��m�l
        static const int32_t s_TRIGGET_DETECTION = 20000;


        // ������Ă���ꍇ
        if (::SDL_JoystickGetAxis(pGamepad_, trigger) > s_TRIGGET_DETECTION)
        {
            // �����Ă���t���[���������Z�b�g���A
            // �����Ă���t���[����1����
            if (buttonReleasingCounts_[updateButton] > 0) buttonReleasingCounts_[updateButton] = 0;

            ++buttonPressingCounts_[updateButton];
        }
        else
        {
            // �����Ă���t���[���������Z�b�g���A
            // �����Ă���t���[������1����
            if (buttonPressingCounts_[updateButton] > 0) buttonPressingCounts_[updateButton] = 0;

            ++buttonReleasingCounts_[updateButton];
        }
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�B�b�N�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_XInput::StickUpdate()
    {
        // ���̐�
        static const int32_t s_AXIS_COUNT = 4;

        for (int i = 0; i < s_AXIS_COUNT; ++i)
        {
            // �Y���������߂�
            int index = i / 2;

            // i�������̏ꍇ��X�������X�V
            if (i % 2 == 0)
            {
                // X�������擾���A�K�؂Ȓl�ɏC��
                stickComponentX_[index] = ::SDL_JoystickGetAxis(pGamepad_, i);
                RepairStickComponent(&stickComponentX_[index]);
            }
            else
            {
                // Y�������擾���A�K�؂Ȓl�ɏC��
                stickComponentY_[index] = ::SDL_JoystickGetAxis(pGamepad_, i);
                RepairStickComponent(&stickComponentY_[index]);

                // �X�e�B�b�N��|���Ă���ꍇ
                if (stickComponentX_[index] != 0 || stickComponentY_[index] != 0)
                {
                    // �|���Ă��Ȃ��t���[���������Z�b�g���A
                    // �|���Ă���t���[������1����
                    if (stickReleasingCounts_[index] > 0) stickReleasingCounts_[index] = 0;

                    ++stickPushingCounts_[index];
                }
                else
                {
                    // �|���Ă���t���[���������Z�b�g���A
                    // �|���Ă��Ȃ��t���[������1����
                    if (stickPushingCounts_[index] > 0) stickPushingCounts_[index] = 0;

                    ++stickReleasingCounts_[index];
                }
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�B�b�N�̐�����K�؂Ȓl�ɏC������
     *  @param  �X�e�B�b�N�̐���
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_XInput::RepairStickComponent(int32_t* pStickComponent)
    {
        assert(pStickComponent);

        // �X�e�B�b�N���V�ђl�ȓ��̏ꍇ
        if (abs(*pStickComponent) < Stick::s_DEAD_ZONE)
        {
            (*pStickComponent) = 0;
        }
        else
        {
            // �X�e�B�b�N���ő�l���߁A
            // �܂��͍ŏ��l�����������ꍇ�͏C��
            if ((*pStickComponent) > Stick::s_PUSH_MAXIMUM)
            {
                (*pStickComponent) = Stick::s_PUSH_MAXIMUM;
            }
            else if ((*pStickComponent) < Stick::s_PUSH_MINIMUM)
            {
                (*pStickComponent) = Stick::s_PUSH_MINIMUM;
            }
        }
    }
}