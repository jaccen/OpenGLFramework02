/* �w�b�_�t�@�C�� */
#include "GamepadManagerImpl.h"


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
    C_GamepadManager::C_GamepadManager() :

        // �������
        upImpl_(std::make_unique<C_GamepadManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_GamepadManager::~C_GamepadManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GamepadManager::Initialize()
    {
        upImpl_->Initialize();
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GamepadManager::Update()
    {
        upImpl_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GamepadManager::Finalize()
    {
        upImpl_->Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  �{�^���������Ă���t���[�������擾����
     *  @param  �{�^��
     *  @param  �Q�[���p�b�h�̔ԍ�
     *  @return �{�^���������Ă���t���[����
     *
     ****************************************************************/
    int32_t C_GamepadManager::GetButtonPressingCount(C_Gamepad::eButton button, eGamepadNumber number) const
    {
        return upImpl_->GetButtonPressingCount(button, number);
    }


    /*************************************************************//**
     *
     *  @brief  �{�^���𗣂��Ă���t���[�������擾����
     *  @param  �{�^��
     *  @param  �Q�[���p�b�h�̔ԍ�
     *  @return �{�^���𗣂��Ă���t���[����
     *
     ****************************************************************/
    int32_t C_GamepadManager::GetButtonReleasingCount(C_Gamepad::eButton button, eGamepadNumber number) const
    {
        return upImpl_->GetButtonReleasingCount(button, number);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�B�b�N��X�������擾����
     *  @param  �X�e�B�b�N
     *  @param  �Q�[���p�b�h�̔ԍ�
     *  @return �X�e�B�b�N��X����
     *
     ****************************************************************/
    int32_t C_GamepadManager::GetStickXComponent(C_Gamepad::eStick stick, eGamepadNumber number) const
    {
        return upImpl_->GetStickXComponent(stick, number);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�B�b�N��Y�������擾����
     *  @param  �X�e�B�b�N
     *  @param  �Q�[���p�b�h�̔ԍ�
     *  @return �X�e�B�b�N��Y����
     *
     ****************************************************************/
    int32_t C_GamepadManager::GetStickYComponent(C_Gamepad::eStick stick, eGamepadNumber number) const
    {
        return upImpl_->GetStickYComponent(stick, number);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�B�b�N��|���Ă���t���[�������擾����
     *  @param  �X�e�B�b�N
     *  @param  �Q�[���p�b�h�̔ԍ�
     *  @return �X�e�B�b�N��|���Ă���t���[����
     *
     ****************************************************************/
    int32_t C_GamepadManager::GetStickPushingCount(C_Gamepad::eStick stick, eGamepadNumber number) const
    {
        return upImpl_->GetStickPushingCount(stick, number);
    }


    /*************************************************************//**
     *
     *  @brief  �X�e�B�b�N��|���Ă��Ȃ��t���[�������擾����
     *  @param  �X�e�B�b�N
     *  @param  �Q�[���p�b�h�̔ԍ�
     *  @return �X�e�B�b�N��|���Ă��Ȃ��t���[����
     *
     ****************************************************************/
    int32_t C_GamepadManager::GetStickReleasingCount(C_Gamepad::eStick stick, eGamepadNumber number) const
    {
        return upImpl_->GetStickReleasingCount(stick, number);
    }
}