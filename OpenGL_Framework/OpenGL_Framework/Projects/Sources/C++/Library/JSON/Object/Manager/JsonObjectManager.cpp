/* �w�b�_�t�@�C�� */
#include "JsonObjectManagerImpl.h"


//-------------------------------------------------------------
///
/// @brief JSON
/// @brief JSON�֘A�̃N���X��֐��Ȃǂɕt���閼�O���
///
//-------------------------------------------------------------
namespace JSON
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_JsonObjectManager::C_JsonObjectManager() :

        // �������
        upImpl_(std::make_unique<C_JsonObjectManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_JsonObjectManager::~C_JsonObjectManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  JSON�I�u�W�F�N�g�̓o�^���s��
     *  @param  JSON�I�u�W�F�N�g
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_JsonObjectManager::Entry(const JsonObjectPtr& prLight, const std::string& rId)
    {
        upImpl_->Entry(prLight, rId);
    }


    /*************************************************************//**
     *
     *  @brief  JSON�I�u�W�F�N�g�̏������s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_JsonObjectManager::Remove(const std::string& rId)
    {
        upImpl_->Remove(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �S�Ă�JSON�I�u�W�F�N�g�̏������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_JsonObjectManager::AllRemove()
    {
        upImpl_->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  JSON�I�u�W�F�N�g���擾����
     *  @param  ID
     *  @return �擾�ł����ꍇ      �FJSON�I�u�W�F�N�g
     *  @return �擾�ł��Ȃ������ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const JsonObjectPtr&> C_JsonObjectManager::GetJsonObject(const std::string& rId) const
    {
        return upImpl_->GetJsonObject(rId);
    }
}