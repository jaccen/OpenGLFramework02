/* �w�b�_�t�@�C�� */
#include "UniformBufferManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief �V�F�[�_�[
//! @brief �V�F�[�_�[�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Shader
{
    //-------------------------------------------------------------
    //!
    //! @brief GLSL
    //! @brief GLSL�֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace GLSL
    {
        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_UniformBufferManager::C_UniformBufferManager() :

            // �������
            upImpl_(std::make_unique<C_UniformBufferManagerImpl>())

        {
        }


        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_UniformBufferManager::~C_UniformBufferManager()
        {
        }


        /*************************************************************//**
         *
         *  @brief  ���j�t�H�[���o�b�t�@�̓o�^���s��
         *  @param  ���j�t�H�[���o�b�t�@
         *  @param  ID
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_UniformBufferManager::Entry(const UniformBufferPtr& prUniformBuffer, const std::string& rId)
        {
            upImpl_->Entry(prUniformBuffer, rId);
        }


        /*************************************************************//**
         *
         *  @brief  ���j�t�H�[���o�b�t�@�̏������s��
         *  @param  ID
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_UniformBufferManager::Remove(const std::string& rId)
        {
            upImpl_->Remove(rId);
        }


        /*************************************************************//**
         *
         *  @brief  �S�Ẵ��j�t�H�[���o�b�t�@�̏������s��
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_UniformBufferManager::AllRemove()
        {
            upImpl_->AllRemove();
        }


        /*************************************************************//**
         *
         *  @brief  ���j�t�H�[���o�b�t�@���擾����
         *  @param  ID
         *  @return �擾�ł����ꍇ      �F���j�t�H�[���o�b�t�@
         *  @return �擾�ł��Ȃ������ꍇ�Fnone
         *
         ****************************************************************/
        boost::optional<const UniformBufferPtr&> C_UniformBufferManager::GetUniformBuffer(const std::string& rId) const
        {
            return upImpl_->GetUniformBuffer(rId);
        }
    }
}