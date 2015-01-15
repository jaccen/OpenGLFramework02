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
    class C_BaseBullet;
    class C_RigidBodyMoveLogic;


    /* �ʖ� */
    using BulletPtr = std::shared_ptr<C_BaseBullet>;                                                // BulletPtr�^


    //-------------------------------------------------------------
    //!
    //! @brief �o���b�g�W�F�l���[�^�[
    //! @brief �o���b�g�̐������s���N���X
    //!
    //-------------------------------------------------------------
    class C_BulletGenerator : public Singleton::C_AssertSingleton<C_BulletGenerator>
    {
    public:
        /* �ʖ� */
        using CreateFunction = C_BaseBullet*(*)(int32_t shooterType);                               // CreateFunction�^

        C_BulletGenerator();                                                                        // �R���X�g���N�^
        ~C_BulletGenerator() override;                                                              // �f�X�g���N�^
        BulletPtr Create(const std::string& rId,                                                    // ��������
                         const Physics::Vector3& rPosition,
                         int32_t power,
                         C_RigidBodyMoveLogic* pMoveLogic,
                         int32_t shooterType);
        void RegistFunction(const std::string& rId, CreateFunction pCreateFunction);                // �֐��̓o�^
        void SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem);                                 // �^�X�N�V�X�e����ݒ�
    private:
        std::unordered_map<std::string, CreateFunction> pCreateFunctions_;                          ///< @brief �����֐�
        Task::C_GeneralTaskSystem* pTaskSystem_ = nullptr;                                          ///< @brief �^�X�N�V�X�e��
        int32_t number = 0;                                                                         ///< @brief �ԍ�
    };
}