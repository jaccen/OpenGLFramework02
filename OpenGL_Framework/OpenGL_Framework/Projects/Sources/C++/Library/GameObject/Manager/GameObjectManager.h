/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Singleton/Assert/AssertSingleton.h"
#include <deque>


//-------------------------------------------------------------
//!
//! @brief �Q�[���I�u�W�F�N�g
//! @brief �Q�[���ɑ��݂���I�u�W�F�N�g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace GameObject
{
    /* �O���錾 */
    class C_GameObject;


    /* �^�ϊ� */
    using GameObjectPtr = std::shared_ptr<C_GameObject>;                                        // GameObjectPtr�^��錾
    using GameObjectList = std::deque<GameObjectPtr>;                                           // GameObjectList�^��錾


    //-------------------------------------------------------------
    //!
    //! @brief �Q�[���I�u�W�F�N�g�}�l�[�W���[
    //! @brief �Q�[���I�u�W�F�N�g���Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    class C_GameObjectManager : public Singleton::C_AssertSingleton<C_GameObjectManager>
    {
    public:
        C_GameObjectManager();                                                                  // �R���X�g���N�^
        ~C_GameObjectManager() override;                                                        // �f�X�g���N�^
        void Entry(const GameObjectPtr& prGameObject);                                          // �o�^����
        void Remove(const GameObjectPtr& prGameObject);                                         // ��������
        void Remove(const std::string& rId);                                                    // ��������
        void Remove(int32_t type);                                                              // ��������
        void AllRemove();                                                                       // �S�ẴQ�[���I�u�W�F�N�g������
        boost::optional<const GameObjectPtr&> GetGameObjectWithId(const std::string& rId);      // ID����Q�[���I�u�W�F�N�g���擾
        GameObjectList GetGameObjectsWithType(int32_t type);                                    // ��ނ���Q�[���I�u�W�F�N�g���擾
    private:
        /* �O���錾 */
        class C_GameObjectManagerImpl;

        std::unique_ptr<C_GameObjectManagerImpl> upImpl_;                                       ///< @brief �������
    };
}