/* �w�b�_�t�@�C�� */
#include "MouseManagerImpl.h"


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
    C_MouseManager::C_MouseManager() :

        // �������
        upImpl_(std::make_unique<C_MouseManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_MouseManager::~C_MouseManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_MouseManager::Update()
    {
        // �J�[�\���ƃ{�^���̍X�V����
        upImpl_->CursorAndButtonUpdate();

        // �z�C�[���̍X�V����
        upImpl_->WheelUpdate();
    }


    /*************************************************************//**
     *
     *  @brief  �J�[�\����X���W���擾����
     *  @param  �Ȃ�
     *  @return �J�[�\����X���W
     *
     ****************************************************************/
    int32_t C_MouseManager::GetCursorPositionX() const
    {
        return upImpl_->GetCursorPositionX();
    }


    /*************************************************************//**
     *
     *  @brief  �J�[�\����Y���W���擾����
     *  @param  �Ȃ�
     *  @return �J�[�\����Y���W
     *
     ****************************************************************/
    int32_t C_MouseManager::GetCursorPositionY() const
    {
        return upImpl_->GetCursorPositionY();
    }


    /*************************************************************//**
     *
     *  @brief  �{�^���������Ă���t���[�������擾����
     *  @param  �{�^��
     *  @return �{�^���������Ă���t���[����
     *
     ****************************************************************/
    int32_t C_MouseManager::GetButtonPressingCount(eButton button) const
    {
        return upImpl_->GetButtonPressingCount(button);
    }


    /*************************************************************//**
     *
     *  @brief  �{�^���𗣂��Ă���t���[�������擾����
     *  @param  �{�^��
     *  @return �{�^���𗣂��Ă���t���[����
     *
     ****************************************************************/
    int32_t C_MouseManager::GetButtonReleasingCount(eButton button) const
    {
        return upImpl_->GetButtonReleasingCount(button);
    }


    /*************************************************************//**
     *
     *  @brief  �z�C�[������]���Ă���t���[�������擾����
     *  @param  �z�C�[���̉�]����
     *  @return �z�C�[������]���Ă���t���[����
     *
     ****************************************************************/
    int32_t C_MouseManager::GetWheelScrollingCount(eWheelScroll wheelScroll) const
    {
        return upImpl_->GetWheelScrollingCount(wheelScroll);
    }


    /*************************************************************//**
     *
     *  @brief  �z�C�[������]���Ă��Ȃ��t���[�������擾����
     *  @param  �z�C�[���̉�]����
     *  @return �z�C�[������]���Ă��Ȃ��t���[����
     *
     ****************************************************************/
    int C_MouseManager::GetWheelReleasingCount(eWheelScroll wheelScroll) const
    {
        return upImpl_->GetWheelReleasingCount(wheelScroll);
    }


    /*************************************************************//**
     *
     *  @brief  �z�C�[���𐂒������̉�]��ݒ肷��
     *  @param  �z�C�[���̐��������̉�]
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_MouseManager::SetWheelScrollVertical(int32_t wheelScrollVertical)
    {
        upImpl_->SetWheelScrollVertical(wheelScrollVertical);
    }
}