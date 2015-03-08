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
    class C_BaseBomb;


    /* �ʖ� */
    using BombPtr = std::shared_ptr<C_BaseBomb>;                                                    // BombPtr�^


    //-------------------------------------------------------------
    //!
    //! @brief �{���W�F�l���[�^�[
    //! @brief �{���̐������s���N���X
    //!
    //-------------------------------------------------------------
    class C_BombGenerator : public Singleton::C_AssertSingleton<C_BombGenerator>
    {
    public:
        /* �ʖ� */
        using CreateFunction = C_BaseBomb*(*)(int32_t level);                                       // CreateFunction�^

        C_BombGenerator();                                                                          // �R���X�g���N�^
        ~C_BombGenerator() override;                                                                // �f�X�g���N�^
        BombPtr Create(const std::string& rId, const Physics::Vector3& rPosition, int32_t level);   // ��������
        void RegistFunction(const std::string& rId, CreateFunction pCreateFunction);                // �֐��̓o�^
        void SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem);                                 // �^�X�N�V�X�e����ݒ�
    private:
        std::unordered_map<std::string, CreateFunction> pCreateFunctions_;                          ///< @brief �����֐�
        Task::C_GeneralTaskSystem* pTaskSystem_ = nullptr;                                          ///< @brief �^�X�N�V�X�e��
        int32_t number = 0;                                                                         ///< @brief �ԍ�
    };
}