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
    class C_BaseEffect;


    /* �ʖ� */
    using EffectPtr = std::shared_ptr<C_BaseEffect>;                                        // EffectPtr�^


    //-------------------------------------------------------------
    //!
    //! @brief �G�t�F�N�g�W�F�l���[�^�[
    //! @brief �G�t�F�N�g�̐������s���N���X
    //!
    //-------------------------------------------------------------
    class C_EffectGenerator : public Singleton::C_AssertSingleton<C_EffectGenerator>
    {
    public:
        /* �ʖ� */
        using CreateFunction = C_BaseEffect*(*)();                                          // CreateFunction�^

        C_EffectGenerator();                                                                // �R���X�g���N�^
        ~C_EffectGenerator() override;                                                      // �f�X�g���N�^
        EffectPtr Create(const std::string& rId, const Vector3& rPosition);                 // ��������
        void RegistFunction(const std::string& rId, CreateFunction pCreateFunction);        // �֐��̓o�^
        void SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem);                         // �^�X�N�V�X�e����ݒ�
    private:
        std::unordered_map<std::string, CreateFunction> pCreateFunctions_;                  ///< @brief �����֐�
        Task::C_GeneralTaskSystem* pTaskSystem_ = nullptr;                                  ///< @brief �^�X�N�V�X�e��
        int32_t number = 0;                                                                 ///< @brief �ԍ�
    };
}