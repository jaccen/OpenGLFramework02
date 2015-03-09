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
    class C_CollisionObject;
    class C_BaseShield;
    class C_RigidBodyMoveLogic;


    /* �ʖ� */
    using ShieldPtr = std::shared_ptr<C_BaseShield>;                                                // ShieldPtr�^


    //-------------------------------------------------------------
    //!
    //! @brief �V�[���h�W�F�l���[�^�[
    //! @brief �V�[���h�̐������s���N���X
    //!
    //-------------------------------------------------------------
    class C_ShieldGenerator : public Singleton::C_AssertSingleton<C_ShieldGenerator>
    {
    public:
        /* �ʖ� */
        using CreateFunction = C_BaseShield*(*)(int32_t shooterType, C_CollisionObject* pTarget);   // CreateFunction�^

        C_ShieldGenerator();                                                                        // �R���X�g���N�^
        ~C_ShieldGenerator() override;                                                              // �f�X�g���N�^
        ShieldPtr Create(const std::string& rId,                                                    // ��������
                         const Physics::Vector3& rPosition,
                         int32_t shooterType,
                         C_CollisionObject* pTarget);
        void RegistFunction(const std::string& rId, CreateFunction pCreateFunction);                // �֐��̓o�^
        void SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem);                                 // �^�X�N�V�X�e����ݒ�
    private:
        std::unordered_map<std::string, CreateFunction> pCreateFunctions_;                          ///< @brief �����֐�
        Task::C_GeneralTaskSystem* pTaskSystem_ = nullptr;                                          ///< @brief �^�X�N�V�X�e��
        int32_t number = 0;                                                                         ///< @brief �ԍ�
    };
}