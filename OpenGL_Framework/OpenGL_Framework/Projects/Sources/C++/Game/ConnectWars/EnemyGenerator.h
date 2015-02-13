/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectWarsDefine.h"
#include "../../Library/Singleton/Assert/AssertSingleton.h"
#include "../../Library/Physics/PhysicsDefine.h"
#include "../../Library/JSON/Object/JsonObject.h"
#include <unordered_map>


/* �O���錾 */
namespace Task
{
    class C_GeneralTaskSystem;
}


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* �O���錾 */
    class C_BaseEnemy;


    /* �ʖ� */
    using EnemyPtr = std::shared_ptr<C_BaseEnemy>;                                                  // EnemyPtr�^


    //-------------------------------------------------------------
    //!
    //! @brief �G�l�~�[�W�F�l���[�^�[
    //! @brief �G�̐������s���N���X
    //!
    //-------------------------------------------------------------
    class C_EnemyGenerator : public Singleton::C_AssertSingleton<C_EnemyGenerator>
    {
    public:
        /* �ʖ� */
        using CreateFunction = C_BaseEnemy*(*)();                                                   // CreateFunction�^

        C_EnemyGenerator();                                                                         // �R���X�g���N�^
        ~C_EnemyGenerator() override;                                                               // �f�X�g���N�^
        EnemyPtr Create(const std::string& rId);                                                    // ��������
        void AutoCreate(int32_t frame);                                                             // ������������
        void RegistFunction(const std::string& rId, CreateFunction pCreateFunction);                // �֐��̓o�^
        void SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem);                                 // �^�X�N�V�X�e����ݒ�
        void SetEnemyData(const JSON::JsonObjectPtr& prEnemyData);                                  // �G�f�[�^��ݒ�
    private:
        std::unordered_map<std::string, CreateFunction> pCreateFunctions_;                          ///< @brief �����֐�
        Task::C_GeneralTaskSystem* pTaskSystem_ = nullptr;                                          ///< @brief �^�X�N�V�X�e��
        int32_t number = 0;                                                                         ///< @brief �ԍ�
        JSON::JsonObjectPtr pEnemyData_;                                                            ///< @brief �G�f�[�^
    };
}