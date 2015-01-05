/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../CollisionShape/CollisionShape.h"
#include "../../PhysicsDefine.h"
#include <tuple>


//-------------------------------------------------------------
///
/// @brief �t�B�W�b�N�X
/// @brief �����֘A�̖��O���
///
//-------------------------------------------------------------
namespace Physics
{
    //-------------------------------------------------------------
    //!
    //! @brief ���W�b�h�{�f�B
    //! @brief ���̂�\���N���X
    //!
    //-------------------------------------------------------------
    class C_RigidBody
    {
    public:
        C_RigidBody(C_CollisionShape* pCollisionShape,                                                  // �R���X�g���N�^
                    const Transform& rTransform,
                    float mass = 0.0f,
                    const Vector3& rInertia = Vector3(0.0f, 0.0f, 0.0f));
        virtual ~C_RigidBody();                                                                         // �f�X�g���N�^
        void EnableActive(bool validFlag = true);                                                       // �A�N�e�B�u��Ԃ�L����
        void EnableCollisionResponse(bool validFlag = true);                                            // �Փˉ�����L����
        void EnableCollisionCallback(bool validFlag = true);                                            // �Փ˃R�[���o�b�N��L����
        void EnableFreezePosition(bool x = false, bool y = false, bool z = false);                      // ���W�̌Œ��L����
        void EnableFreezeRotation(bool x = false, bool y = false, bool z = false);                      // ��]�̌Œ��L����
        void ApplyForce(const Vector3& rForce,                                                          // �͂�������
                        const Vector3& rOffsetFromCenter = Vector3(0.0f, 0.0f, 0.0f));
        void ApplyImpulse(const Vector3& rImpulse,                                                      // ���͂�������
                          const Vector3& rOffsetFromCenter = Vector3(0.0f, 0.0f, 0.0f));
        void AddPosition(const Vector3& rPosition);                                                     // ���W��������
        void ResetVelocity();                                                                           // ���x�����Z�b�g
        btRigidBody* GetRigidBody() const;                                                              // ���̂��擾
        C_CollisionShape* GetCollisionShape() const;                                                    // �Փˌ`����擾
        const Transform& GetTransform() const;                                                          // �g�����X�t�H�[�����擾
        const Transform& GetCenterOfGravityTransform() const;                                           // �d�S�̃g�����X�t�H�[�����擾
        const Vector3& GetLinearVelocity() const;                                                       // �����x���擾
        const Vector3& GetAngularVelocity() const;                                                      // �p���x���擾
        float GetFriction() const;                                                                      // ���C�W�����擾
        float GetRollingFriction() const;                                                               // �]���薀�C�W�����擾
        float GetRestitution() const;                                                                   // �����W�����擾
        float GetLinearDamping() const;                                                                 // �ړ��������擾
        float GetAngularDamping() const;                                                                // ��]�������擾
        std::tuple<Vector3, Vector3> GetAabb() const;                                                   // AABB���擾
        int32_t GetActivationState() const;                                                             // �A�N�e�B�x�[�V�����X�e�[�g���擾
        int32_t GetUserIndex() const;                                                                   // �Ǝ��̃C���f�b�N�X���擾
        void* GetUserPointer() const;                                                                   // �Ǝ��̃|�C���^���擾
        void SetTransform(const Transform& rTransform);                                                 // �g�����X�t�H�[����ݒ�
        void SetCenterOfGravityTransform(const Transform& rTransform);                                  // �d�S�̃g�����X�t�H�[����ݒ�
        void SetLinearVelocity(const Vector3& rLinearVelocity = Vector3(0.0f, 0.0f, 0.0f));             // �����x��ݒ�
        void SetAngularVelocity(const Vector3& rAngularVelocity = Vector3(0.0f, 0.0f, 0.0f));           // �p���x��ݒ�
        void SetFriction(float friction = 1.0f);                                                        // ���C�W����ݒ�
        void SetRollingFriction(float rollingFriction = 1.0f);                                          // �]���薀�C�W����ݒ�
        void SetRestitution(float restitution = 0.0f);                                                  // �����W����ݒ�
        void SetLinearDamping(float linearDamping);                                                     // �ړ�������ݒ�
        void SetAngularDamping(float angularDamping);                                                   // ��]������ݒ�
        void SetActivationState(int32_t state);                                                         // �A�N�e�B�x�[�V�����X�e�[�g��ݒ�
        void SetUserIndex(int32_t index);                                                               // �Ǝ��̃C���f�b�N�X��ݒ�
        void SetUserPointer(void* pPointer);                                                            // �Ǝ��̃|�C���^��ݒ�
    private:
        std::unique_ptr<btRigidBody> upRigidBody_;                                                      ///< @brief ����
        std::unique_ptr<C_CollisionShape> upCollisionShape_;                                            ///< @brief �Փˌ`��
        std::unique_ptr<btDefaultMotionState> upMotionState_;                                           ///< @brief ���[�V�����X�e�[�g
    };
}