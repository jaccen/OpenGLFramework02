/* �w�b�_�t�@�C�� */
#include "PrimitiveBufferManagerImpl.h"


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
    C_PrimitiveBufferManager::C_PrimitiveBufferManager() :

        // �������
        upImpl_(std::make_unique<C_PrimitiveBufferManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PrimitiveBufferManager::~C_PrimitiveBufferManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �v���~�e�B�u�o�b�t�@�̓o�^���s��
     *  @param  �v���~�e�B�u�o�b�t�@
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PrimitiveBufferManager::Entry(const PrimitiveBufferPtr& prPrimitiveBuffer, const std::string& rId)
    {
        upImpl_->Entry(prPrimitiveBuffer, rId);
    }


    /*************************************************************//**
     *
     *  @brief  �v���~�e�B�u�o�b�t�@�̏������s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PrimitiveBufferManager::Remove(const std::string& rId)
    {
        upImpl_->Remove(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �S�Ẵv���~�e�B�u�o�b�t�@�̏������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PrimitiveBufferManager::AllRemove()
    {
        upImpl_->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  �v���~�e�B�u�o�b�t�@���擾����
     *  @param  ID
     *  @return �擾�ł����ꍇ      �F�v���~�e�B�u�o�b�t�@
     *  @return �擾�ł��Ȃ������ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const PrimitiveBufferPtr&> C_PrimitiveBufferManager::GetPrimitiveBuffer(const std::string& rId) const
    {
        return upImpl_->GetPrimitiveBuffer(rId);
    }
}