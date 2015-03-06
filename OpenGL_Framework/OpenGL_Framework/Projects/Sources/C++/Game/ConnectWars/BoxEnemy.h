/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "BaseEnemy.h"
#include "RigidBodyMoveLogic.h"
#include "../../Library/Physics/Body/Rigid/Rigidbody.h"
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief �{�b�N�X�G�l�~�[
    //! @brief ����̓G��\���N���X
    //!
    //-------------------------------------------------------------
    class C_BoxEnemy : public C_BaseEnemy
    {
    public:
        C_BoxEnemy(const std::string& rId, int32_t type);                                   // �R���X�g���N�^
        virtual ~C_BoxEnemy() override;                                                     // �f�X�g���N�^
        void Move() override;                                                               // �ړ�����
        void MoveLimitCheck() override;                                                     // �ړ������̊m�F
        void SetCreateDataWithJson(JSON::JsonObject* pJsonObject);                          // JSON�I�u�W�F�N�g����f�[�^��ݒ�
        const Physics::Vector3& GetPosition() const override;                               // ���W���擾
        void SetPosition(const Physics::Vector3& rPosition);                                // ���W��ݒ�
        const Physics::Matrix3x3& GetRotation() const override;                             // ��]�ʂ��擾
    protected:
        std::unique_ptr<Physics::C_RigidBody> upRigidBody_;                                 ///< @brief ����
        std::unique_ptr<C_RigidBodyMoveLogic> upMoveLogic_;                                 ///< @brief �ړ����W�b�N
        OpenGL::PrimitiveBufferPtr pModelData_;                                             ///< @brief ���f�����
        Vector3 size_;                                                                      ///< @brief �T�C�Y

        void DoUpdate() override;                                                           // ����J�̍X�V����
        void DoDraw() override;                                                             // ����J�̕`�揈��
        bool DoMessageProcess(const Telegram& rTelegram) override;                          // ����J�̃��b�Z�[�W����
    };
}