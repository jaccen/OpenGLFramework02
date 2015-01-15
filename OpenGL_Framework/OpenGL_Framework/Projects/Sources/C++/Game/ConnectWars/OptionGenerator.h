/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectWarsDefine.h"
#include "../../Library/Singleton/Assert/AssertSingleton.h"
#include "../../Library/Physics/PhysicsDefine.h"
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
    class C_BaseOption;
    class C_RigidBodyMoveLogic;


    /* �ʖ� */
    using OptionPtr = std::shared_ptr<C_BaseOption>;                                                // OptionPtr�^


    //-------------------------------------------------------------
    //!
    //! @brief �I�v�V�����W�F�l���[�^�[
    //! @brief �I�v�V�����̐������s���N���X
    //!
    //-------------------------------------------------------------
    class C_OptionGenerator : public Singleton::C_AssertSingleton<C_OptionGenerator>
    {
    public:
        /* �ʖ� */
        using CreateFunction = C_BaseOption*(*)();                                                  // CreateFunction�^

        C_OptionGenerator();                                                                        // �R���X�g���N�^
        ~C_OptionGenerator() override;                                                              // �f�X�g���N�^
        OptionPtr Create(const std::string& rId, const Physics::Vector3& rPosition);                // ��������
        void RegistFunction(const std::string& rId, CreateFunction pCreateFunction);                // �֐��̓o�^
        void SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem);                                 // �^�X�N�V�X�e����ݒ�
    private:
        std::unordered_map<std::string, CreateFunction> pCreateFunctions_;                          ///< @brief �����֐�
        Task::C_GeneralTaskSystem* pTaskSystem_ = nullptr;                                          ///< @brief �^�X�N�V�X�e��
        int32_t number = 0;                                                                         ///< @brief �ԍ�
    };
}