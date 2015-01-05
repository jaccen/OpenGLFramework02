/* �w�b�_�t�@�C�� */
#include "FrameBufferManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace OpenGL
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_FrameBufferManager::C_FrameBufferManager() :

        // �������
        upImpl_(std::make_unique<C_FrameBufferManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_FrameBufferManager::~C_FrameBufferManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �t���[���o�b�t�@�̓o�^���s��
     *  @param  �t���[���o�b�t�@
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FrameBufferManager::Entry(const FrameBufferPtr& prFrameBuffer, const std::string& rId)
    {
        upImpl_->Entry(prFrameBuffer, rId);
    }


    /*************************************************************//**
     *
     *  @brief  �t���[���o�b�t�@�̏������s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FrameBufferManager::Remove(const std::string& rId)
    {
        upImpl_->Remove(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �S�Ẵt���[���o�b�t�@�̏������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_FrameBufferManager::AllRemove()
    {
        upImpl_->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  �t���[���o�b�t�@���擾����
     *  @param  ID
     *  @return �擾�ł����ꍇ      �F�t���[���o�b�t�@
     *  @return �擾�ł��Ȃ������ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const FrameBufferPtr&> C_FrameBufferManager::GetFrameBuffer(const std::string& rId) const
    {
        return upImpl_->GetFrameBuffer(rId);
    }
}