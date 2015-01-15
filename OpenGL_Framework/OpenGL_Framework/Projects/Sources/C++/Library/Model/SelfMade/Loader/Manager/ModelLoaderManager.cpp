/* �w�b�_�t�@�C�� */
#include "ModelLoaderManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief ���f��
//! @brief ���f���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Model
{
    //-------------------------------------------------------------
    //!
    //! @brief SelfMade
    //! @brief ����֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace SelfMade
    {
        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_ModelLoaderManager::C_ModelLoaderManager() :

            // �������
            upImpl_(std::make_unique<C_ModelLoaderManagerImpl>())

        {
        }


        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_ModelLoaderManager::~C_ModelLoaderManager()
        {
        }


        /*************************************************************//**
         *
         *  @brief  ���f�����[�_�[�̓o�^���s��
         *  @param  ���f�����[�_�[
         *  @param  ID
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ModelLoaderManager::Entry(const ModelLoaderPtr& prMaterial, const std::string& rId)
        {
            upImpl_->Entry(prMaterial, rId);
        }


        /*************************************************************//**
         *
         *  @brief  ���f�����[�_�[�̏������s��
         *  @param  ID
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ModelLoaderManager::Remove(const std::string& rId)
        {
            upImpl_->Remove(rId);
        }


        /*************************************************************//**
         *
         *  @brief  �S�Ẵ��f�����[�_�[�̏������s��
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void C_ModelLoaderManager::AllRemove()
        {
            upImpl_->AllRemove();
        }


        /*************************************************************//**
         *
         *  @brief  ���f�����[�_�[���擾����
         *  @param  ID
         *  @return �擾�ł����ꍇ      �F���f�����[�_�[
         *  @return �擾�ł��Ȃ������ꍇ�Fnone
         *
         ****************************************************************/
        boost::optional<const ModelLoaderPtr&> C_ModelLoaderManager::GetModelLoader(const std::string& rId) const
        {
            return upImpl_->GetModelLoader(rId);
        }
    }
}