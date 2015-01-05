/* �w�b�_�t�@�C�� */
#include "MaterialManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief �}�e���A��
//! @brief �}�e���A���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Material
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_MaterialManager::C_MaterialManager() :

        // �������
        upImpl_(std::make_unique<C_MaterialManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_MaterialManager::~C_MaterialManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �}�e���A���̓o�^���s��
     *  @param  �}�e���A��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_MaterialManager::Entry(const MaterialPtr& prMaterial, const std::string& rId)
    {
        upImpl_->Entry(prMaterial, rId);
    }


    /*************************************************************//**
     *
     *  @brief  �}�e���A���̏������s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_MaterialManager::Remove(const std::string& rId)
    {
        upImpl_->Remove(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �S�Ẵ}�e���A���̏������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_MaterialManager::AllRemove()
    {
        upImpl_->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  �}�e���A�����擾����
     *  @param  ID
     *  @return �擾�ł����ꍇ      �F�}�e���A��
     *  @return �擾�ł��Ȃ������ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const MaterialPtr&> C_MaterialManager::GetMaterial(const std::string& rId) const
    {
        return upImpl_->GetMaterial(rId);
    }
}