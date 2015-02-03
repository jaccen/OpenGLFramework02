/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "RigidBodyMoveLogic.h"
#include "../../Library/Physics/PhysicsDefine.h"


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


    //-------------------------------------------------------------
    //!
    //! @brief ���M�b�h�{�f�B�R�l�N�g���[�u���W�b�N
    //! @brief ���̘̂A�����̈ړ��̃��W�b�N��\���N���X
    //!
    //-------------------------------------------------------------
    class C_RigidBodyConnectMoveLogic : public C_RigidBodyMoveLogic
    {
    public:
        C_RigidBodyConnectMoveLogic(C_CollisionObject* pTarget,                         // �R���X�g���N�^
                                    const Physics::Vector3& rOffsetFromTarget);             
        virtual ~C_RigidBodyConnectMoveLogic() override;                                // �f�X�g���N�^
        void SetDirection(const Physics::Vector3& rDirection) override {};              // ������ݒ�
        void SetMovement(float movement) override {};                                   // �ړ��ʂ�ݒ�
        C_RigidBodyMoveLogic* DeepCopy() override;                                      // �f�B�[�v�R�s�[
    private:
        C_CollisionObject* pTarget_ = nullptr;                                          ///< @brief �^�[�Q�b�g
        std::unique_ptr<Physics::Vector3> upOffsetFromTarget_;                          ///< @brief �^�[�Q�b�g����̃I�t�Z�b�g

        void DoProcess(RigidBody* pRigidBody) override;                                 // ����J�̏���
    };
}