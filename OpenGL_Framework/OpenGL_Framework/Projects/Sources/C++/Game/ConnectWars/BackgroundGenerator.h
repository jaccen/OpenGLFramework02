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
    using BackgroundPtr = std::shared_ptr<C_BaseBackground>;                                            // BackgroundPtr�^


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
        using CreateFunction = C_BaseBackground*(*)();                                          // CreateFunction�^

        C_BackgroundGenerator();                                                                // �R���X�g���N�^
        ~C_BackgroundGenerator() override;                                                      // �f�X�g���N�^
        BackgroundPtr Create(const std::string& rId,                                            // ��������
                             const Vector3& rPosition,
                             const Vector3& rRotation = Vector3::s_ZERO,
                             const Vector3& rScale = Vector3::s_ONE,
                             const Vector3& rVelocity = Vector3::s_ZERO,
                             const Vector3& rAccelaration = Vector3::s_ZERO,
                             const Vector3& rRotationVelocity = Vector3::s_ZERO,
                             const Vector3& rRotationAccelaration = Vector3::s_ZERO,
                             int32_t lifeFrame = -1);
        void AutoCreate(int32_t frame);                                                         // ������������
        void RegistFunction(const std::string& rId, CreateFunction pCreateFunction);            // �֐��̓o�^
        void SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem);                             // �^�X�N�V�X�e����ݒ�
        void SetBackgroundData(JSON::JsonObject* pBackgroundData);                              // �w�i�f�[�^��ݒ�
        void SetAutoCreateMaxCount(int32_t autoCreateMaxCount);                                 // ���������̍ő吔��ݒ�
    private:
        std::unordered_map<std::string, CreateFunction> pCreateFunctions_;                      ///< @brief �����֐�
        Task::C_GeneralTaskSystem* pTaskSystem_ = nullptr;                                      ///< @brief �^�X�N�V�X�e��
        int32_t number = 0;                                                                     ///< @brief �ԍ�
        JSON::JsonObject* pBackgroundData_;                                                     ///< @brief �w�i�f�[�^
        int32_t autoCreateIndex_ = 0;                                                           ///< @brief ���������̃C���f�b�N�X
        int32_t autoCreateMaxCount_ = 0;                                                        ///< @brief ���������̍ő吔
    };
}