/* �w�b�_�t�@�C�� */
#include "keyboardManagerImpl.h"


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
    C_KeyboardManager::C_KeyboardManager() :

        // �������
        upImpl_(std::make_unique<C_KeyboardManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_KeyboardManager::~C_KeyboardManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_KeyboardManager::Initialize()
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
    void C_KeyboardManager::Update()
    {
        upImpl_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  �����Ă���t���[�������擾����
     *  @param  �X�L�����R�[�h
     *  @return �����Ă���t���[����
     *
     ****************************************************************/
    int32_t C_KeyboardManager::GetPressingCount(KeyCode keycode) const
    {
        return upImpl_->GetPressingCount(keycode);
    }


    /*************************************************************//**
     *
     *  @brief  �����Ă���t���[�������擾����
     *  @param  �X�L�����R�[�h
     *  @return �����Ă���t���[����
     *
     ****************************************************************/
    int32_t C_KeyboardManager::GetReleasingCount(KeyCode keycode) const
    {
        return upImpl_->GetReleasingCount(keycode);
    }


    /*************************************************************//**
     *
     *  @brief  ���͂����������擾����
     *  @param  �Ȃ�
     *  @return ���͂�������
     *
     ****************************************************************/
    const std::string& C_KeyboardManager::GetInputCharacter() const
    {
        return upImpl_->GetInputCharacter();
    }


    /*************************************************************//**
     *
     *  @brief  ���͂���������ݒ肷��
     *  @param  ���͂�������
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_KeyboardManager::SetInputCharacter(const std::string& rInputCharacter)
    {
        upImpl_->SetInputCharacter(rInputCharacter);
    }
}