/* �w�b�_�t�@�C�� */
#include "GlslObjectManagerImpl.h"


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
        C_GlslObjectManager::C_GlslObjectManager() :

            // �������
            upImpl_(std::make_unique<C_GlslObjectManagerImpl>())

        {
        }


        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_GlslObjectManager::~C_GlslObjectManager()
        {
        }


        /*************************************************************//**
         *
         *  @brief  GLSL�I�u�W�F�N�g�̓o�^���s��
         *  @param  GLSL�I�u�W�F�N�g
         *  @param  ID
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_GlslObjectManager::Entry(const GlslObjectPtr& prGlslObject, const std::string& rId)
        {
            upImpl_->Entry(prGlslObject, rId);
        }


        /*************************************************************//**
         *
         *  @brief  GLSL�I�u�W�F�N�g�̏������s��
         *  @param  ID
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_GlslObjectManager::Remove(const std::string& rId)
        {
            upImpl_->Remove(rId);
        }


        /*************************************************************//**
         *
         *  @brief  �S�Ă�GLSL�I�u�W�F�N�g�̏������s��
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_GlslObjectManager::AllRemove()
        {
            upImpl_->AllRemove();
        }


        /*************************************************************//**
         *
         *  @brief  GLSL�I�u�W�F�N�g���擾����
         *  @param  ID
         *  @return �擾�ł����ꍇ      �FGLSL�I�u�W�F�N�g
         *  @return �擾�ł��Ȃ������ꍇ�Fnone
         *
         ****************************************************************/
        boost::optional<const GlslObjectPtr&> C_GlslObjectManager::GetGlslObject(const std::string& rId) const
        {
            return upImpl_->GetGlslObject(rId);
        }
    }
}