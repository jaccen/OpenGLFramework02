/* �w�b�_�t�@�C�� */
#include "GameObjectManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief �Q�[���I�u�W�F�N�g
//! @brief �Q�[���ɑ��݂���I�u�W�F�N�g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace GameObject
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_GameObjectManager::C_GameObjectManager() :

        // �������
        upImpl_(std::make_unique<C_GameObjectManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_GameObjectManager::~C_GameObjectManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �Q�[���I�u�W�F�N�g�̓o�^�������s��
     *  @param  �Q�[���I�u�W�F�N�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameObjectManager::Entry(const GameObjectPtr& prGameObject)
    {
        upImpl_->Entry(prGameObject);
    }


    /*************************************************************//**
     *
     *  @brief  �Q�[���I�u�W�F�N�g�̏������s��
     *  @param  �Q�[���I�u�W�F�N�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameObjectManager::Remove(const GameObjectPtr& prGameObject)
    {
        upImpl_->Remove(prGameObject);
    }


    /*************************************************************//**
     *
     *  @brief  �Q�[���I�u�W�F�N�g�̏������s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameObjectManager::Remove(const std::string& rId)
    {
        upImpl_->Remove(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �Q�[���I�u�W�F�N�g�̏������s��
     *  @param  ���
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameObjectManager::Remove(int32_t type)
    {
        upImpl_->Remove(type);
    }


    /*************************************************************//**
     *
     *  @brief  �S�ăQ�[���I�u�W�F�N�g�̏������s��
     *  @param  �Q�[���I�u�W�F�N�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameObjectManager::AllRemove()
    {
        upImpl_->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  ID����Q�[���I�u�W�F�N�g���擾����
     *  @param  ID
     *  @return �Q�[���I�u�W�F�N�g
     *
     ****************************************************************/
    boost::optional<const GameObjectPtr&> C_GameObjectManager::GetGameObjectWithId(const std::string& rId)
    {
        return upImpl_->FindGameObjectWithId(rId);
    }


    /*************************************************************//**
     *
     *  @brief  ��ނ���Q�[���I�u�W�F�N�g���擾����
     *  @param  ���
     *  @return �Q�[���I�u�W�F�N�g
     *
     ****************************************************************/
    GameObjectList C_GameObjectManager::GetGameObjectsWithType(int32_t type)
    {
        return upImpl_->FindGameObjectsWithType(type);
    }
}