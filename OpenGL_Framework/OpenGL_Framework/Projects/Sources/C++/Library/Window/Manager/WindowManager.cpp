/* �w�b�_�t�@�C�� */
#include "WindowManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief �E�B���h�E
//! @brief �E�B���h�E�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Window
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_WindowManager::C_WindowManager() :

        // �������
        upImpl_(std::make_unique<C_WindowManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_WindowManager::~C_WindowManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �o�^�������s��
     *  @param  �J����
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_WindowManager::Entry(const WindowPtr& pWindow,
                                const std::string& rId)
    {
        upImpl_->Entry(pWindow, rId);
    }


    /*************************************************************//**
     *
     *  @brief  �J�����̏����������s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_WindowManager::Remove(const std::string& rId)
    {
        upImpl_->Remove(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �S�ẴJ�����̏����������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_WindowManager::AllRemove()
    {
        upImpl_->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  �J�������擾����
     *  @param  ID
     *  @return �擾�ł����ꍇ      �F�J����
     *  @return �擾�ł��Ȃ������ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const WindowPtr&> C_WindowManager::GetWindow(const std::string& rId) const
    {
        return upImpl_->GetWindow(rId);
    }
}