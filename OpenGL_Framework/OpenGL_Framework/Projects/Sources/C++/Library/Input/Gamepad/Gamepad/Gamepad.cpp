/* �w�b�_�t�@�C�� */
#include "Gamepad.h"


//-------------------------------------------------------------
//!
//! @brief �C���v�b�g
//! @brief ���͊֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Input
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_Gamepad::C_Gamepad(SDL_Joystick* pGamepad) :

        // �Q�[���p�b�h
        pGamepad_(pGamepad)

    {
        // �{�^���̃t���[�����̃J�E���^��������
        buttonPressingCounts_.fill(0);
        buttonReleasingCounts_.fill(0);

        // �X�e�B�b�N�̃t���[�����̃J�E���^�Ɗe������������
        stickComponentX_.fill(0);
        stickComponentY_.fill(0);
        stickPushingCounts_.fill(0);
        stickReleasingCounts_.fill(0);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_Gamepad::~C_Gamepad()
    {
        if (pGamepad_ == nullptr) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_Gamepad::Finalize()
    {
        // �Q�[���p�b�h�����
        if (::SDL_JoystickGetAttached(pGamepad_) == SDL_TRUE)
        {
            ::SDL_JoystickClose(pGamepad_);
            pGamepad_ = nullptr;
        }
    }


    /*************************************************************//**
     *
     *  @brief  �{�^���������Ă���t���[�������擾����
     *  @param  �{�^��
     *  @return �{�^���������Ă���t���[����
     *
     ****************************************************************/
    int C_Gamepad::GetButtonPressingCount(eButton button) const
    {
        return buttonPressingCounts_.at(button);
    }


    /*************************************************************//**
     *
     *  @brief  �{�^���𗣂��Ă���t���[�������擾����
     *  @param  �{�^��
     *  @return �{�^���𗣂��Ă���t���[����
     *
     ****************************************************************/
    int C_Gamepad::GetButtonReleasingCount(eButton button) const
    {
        return buttonReleasingCounts_.at(button);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�B�b�N��X�������擾����
     *  @param  �X�e�B�b�N
     *  @return �X�e�B�b�N��X����
     *
     ****************************************************************/
    int C_Gamepad::GetStickXComponent(eStick stick) const
    {
        return stickComponentX_.at(stick);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�B�b�N��Y�������擾����
     *  @param  �X�e�B�b�N
     *  @return �X�e�B�b�N��Y����
     *
     ****************************************************************/
    int C_Gamepad::GetStickYComponent(eStick stick) const
    {
        return stickComponentY_.at(stick);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�B�b�N��|���Ă���t���[�������擾����
     *  @param  �X�e�B�b�N
     *  @return �X�e�B�b�N��|���Ă���t���[����
     *
     ****************************************************************/
    int C_Gamepad::GetStickPushingCount(eStick stick) const
    {
        return stickPushingCounts_.at(stick);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�B�b�N�𗣂��Ă���t���[�������擾����
     *  @param  �X�e�B�b�N
     *  @return �X�e�B�b�N�𗣂��Ă���t���[����
     *
     ****************************************************************/
    int C_Gamepad::GetStickReleasingCount(eStick stick) const
    {
        return stickReleasingCounts_.at(stick);
    }
}