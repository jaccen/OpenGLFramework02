/* �w�b�_�t�@�C�� */
#include "GameObjectManager.h"
#include "../GameObject.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief �Q�[���I�u�W�F�N�g
//! @brief �Q�[���ɑ��݂���I�u�W�F�N�g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace GameObject
{
    //-------------------------------------------------------------
    //!
    //! @brief �Q�[���I�u�W�F�N�g�}�l�[�W���[�C���v�������g
    //! @brief �Q�[���I�u�W�F�N�g�}�l�[�W���[�̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_GameObjectManager::C_GameObjectManagerImpl
    {
    public:
        C_GameObjectManagerImpl();                                                                  // �R���X�g���N�^
        ~C_GameObjectManagerImpl();                                                                 // �f�X�g���N�^
        void Entry(const GameObjectPtr& prGameObject);                                              // �o�^����
        void Remove(const GameObjectPtr& prGameObject);                                             // ��������
        void Remove(const std::string& rId);                                                        // ��������
        void Remove(int32_t type);                                                                  // ��������
        void AllRemove();                                                                           // �S�ẴQ�[���I�u�W�F�N�g������
        boost::optional<const GameObjectPtr&> FindGameObjectWithId(const std::string& rId);         // ID����Q�[���I�u�W�F�N�g������
        GameObjectList FindGameObjectsWithType(int32_t type);                                       // ��ނ���Q�[���I�u�W�F�N�g������
    private:
        std::unordered_map<std::string, GameObjectPtr> pGameObjects_;                               // �Q�[���I�u�W�F�N�g
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_GameObjectManager::C_GameObjectManagerImpl::C_GameObjectManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_GameObjectManager::C_GameObjectManagerImpl::~C_GameObjectManagerImpl()
    {
        if (pGameObjects_.empty() == false) AllRemove();
    }



    /*************************************************************//**
     *
     *  @brief  �Q�[���I�u�W�F�N�g�̓o�^�������s��
     *  @param  �Q�[���I�u�W�F�N�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameObjectManager::C_GameObjectManagerImpl::Entry(const GameObjectPtr& prGameObject)
    {
        // ID���擾
        const std::string& rID = prGameObject->GetId();

        // �Q�[���I�u�W�F�N�g�����ɓo�^����Ă���ꍇ
        if (pGameObjects_.find(rID) != pGameObjects_.end())
        {
            std::cout << "[ C_GameObjectManagerImpl::Entry ] : �Q�[���I�u�W�F�N�g�����ɓo�^����Ă��܂��B" << std::endl;
            std::cout << "                                ID : " << rID << std::endl;

            return;
        }

        // �Q�[���I�u�W�F�N�g��ǉ�
        pGameObjects_.emplace(rID, prGameObject);
    }


    /*************************************************************//**
     *
     *  @brief  �Q�[���I�u�W�F�N�g�̏������s��
     *  @param  �Q�[���I�u�W�F�N�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameObjectManager::C_GameObjectManagerImpl::Remove(const GameObjectPtr& prGameObject)
    {
        Remove(prGameObject->GetId());
    }


    /*************************************************************//**
     *
     *  @brief  �Q�[���I�u�W�F�N�g�̏������s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameObjectManager::C_GameObjectManagerImpl::Remove(const std::string& rId)
    {
        // �Q�[���I�u�W�F�N�g���o�^����Ă��Ȃ��ꍇ
        if (pGameObjects_.find(rId) == pGameObjects_.end())
        {
            std::cout << "[ C_GameObjectManagerImpl::Remove ] : �Q�[���I�u�W�F�N�g��o�^���Ă��܂���B" << std::endl;
            std::cout << "                                 ID : " << rId << std::endl;

            return;
        }

        // �v�f���폜
        pGameObjects_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �Q�[���I�u�W�F�N�g�̏������s��
     *  @param  ���
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameObjectManager::C_GameObjectManagerImpl::Remove(int32_t type)
    {
        // �C�e���[�^�ő������A��ނƓ������̂��폜
        auto iterator = pGameObjects_.begin();

        while (iterator != pGameObjects_.end())
        {
            if ((*iterator).second->GetType() == type) pGameObjects_.erase(iterator);

            ++iterator;
        }
    }


    /*************************************************************//**
     *
     *  @brief  �S�ăQ�[���I�u�W�F�N�g�̏������s��
     *  @param  �Q�[���I�u�W�F�N�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameObjectManager::C_GameObjectManagerImpl::AllRemove()
    {
        pGameObjects_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  ID����Q�[���I�u�W�F�N�g����������
     *  @param  ID
     *  @return �Q�[���I�u�W�F�N�g
     *
     ****************************************************************/
    boost::optional<const GameObjectPtr&> C_GameObjectManager::C_GameObjectManagerImpl::FindGameObjectWithId(const std::string& rId)
    {
        auto iterator = pGameObjects_.find(rId);
        if (iterator == pGameObjects_.end()) return boost::none;

        return (*iterator).second;
    }


    /*************************************************************//**
     *
     *  @brief  ��ނ���Q�[���I�u�W�F�N�g����������
     *  @param  ���
     *  @return �Q�[���I�u�W�F�N�g
     *
     ****************************************************************/
    GameObjectList C_GameObjectManager::C_GameObjectManagerImpl::FindGameObjectsWithType(int32_t type)
    {
        std::deque<GameObjectPtr> pGameObjectList;

        for (auto& rGameObject : pGameObjects_)
        {
            if (rGameObject.second->GetType() == type) pGameObjectList.push_back(rGameObject.second);
        }

        return pGameObjectList;
    }
}