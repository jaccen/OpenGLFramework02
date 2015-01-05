/* �w�b�_�t�@�C�� */
#include "LightManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief ���C�g
//! @brief ���C�g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Light
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_LightManager::C_LightManager() :

        // �������
        upImpl_(std::make_unique<C_LightManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_LightManager::~C_LightManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ���C�g�̓o�^���s��
     *  @param  ���C�g
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LightManager::Entry(const LightPtr& prLight, const std::string& rId)
    {
        upImpl_->Entry(prLight, rId);
    }


    /*************************************************************//**
     *
     *  @brief  ���C�g�̏������s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LightManager::Remove(const std::string& rId)
    {
        upImpl_->Remove(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �S�Ẵ��C�g�̏������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_LightManager::AllRemove()
    {
        upImpl_->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  ���C�g���擾����
     *  @param  ID
     *  @return �擾�ł����ꍇ      �F���C�g
     *  @return �擾�ł��Ȃ������ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const LightPtr&> C_LightManager::GetLight(const std::string& rId) const
    {
        return upImpl_->GetLight(rId);
    }
}