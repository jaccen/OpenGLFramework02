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
    class C_BaseBackground;


    /* �ʖ� */
    using BackgroundPtr = std::shared_ptr<C_BaseBackground>;                                // BackgroundPtr�^


    //-------------------------------------------------------------
    //!
    //! @brief �o�b�N�O���E���h�W�F�l���[�^�[
    //! @brief �o�b�N�O���E���h�̐������s���N���X
    //!
    //-------------------------------------------------------------
    class C_BackgroundGenerator : public Singleton::C_AssertSingleton<C_BackgroundGenerator>
    {
    public:
        /* �ʖ� */
        using CreateFunction = C_BaseBackground*(*)();                                      // CreateFunction�^

        C_BackgroundGenerator();                                                            // �R���X�g���N�^
        ~C_BackgroundGenerator() override;                                                  // �f�X�g���N�^
        BackgroundPtr Create(const std::string& rId, const Vector3& rPosition);             // ��������
        void AutoCreate(int32_t frame);                                                     // ������������
        void RegistFunction(const std::string& rId, CreateFunction pCreateFunction);        // �֐��̓o�^
        void SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem);                         // �^�X�N�V�X�e����ݒ�
        void SetBackgroundData(const JSON::JsonObjectPtr& prBackgroundData);                // �w�i�f�[�^��ݒ�
    private:
        std::unordered_map<std::string, CreateFunction> pCreateFunctions_;                  ///< @brief �����֐�
        Task::C_GeneralTaskSystem* pTaskSystem_ = nullptr;                                  ///< @brief �^�X�N�V�X�e��
        int32_t number = 0;                                                                 ///< @brief �ԍ�
        JSON::JsonObjectPtr pBackgroundData_;                                               ///< @brief �w�i�f�[�^
    };
}