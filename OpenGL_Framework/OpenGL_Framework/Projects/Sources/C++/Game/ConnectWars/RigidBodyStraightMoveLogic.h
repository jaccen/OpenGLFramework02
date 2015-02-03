/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "RigidBodyMoveLogic.h"


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
    //! @brief ���M�b�h�{�f�B�X�g���[�g���[�u���W�b�N
    //! @brief ���̂̒����ړ��̃��W�b�N��\���N���X
    //!
    //-------------------------------------------------------------
    class C_RigidBodyStraightMoveLogic : public C_RigidBodyMoveLogic
    {
    public:
        C_RigidBodyStraightMoveLogic();                                             // �R���X�g���N�^
        virtual ~C_RigidBodyStraightMoveLogic() override;                           // �f�X�g���N�^
        void SetDirection(const Physics::Vector3& rDirection) override;             // ������ݒ�
        void SetMovement(float movement)  override;                                 // �ړ��ʂ�ݒ�   
        C_RigidBodyMoveLogic* DeepCopy() override;                                  // �f�B�[�v�R�s�[
    private:
        std::unique_ptr<Physics::Vector3> upDirection_;                             ///< @brief ���x
        float movement_ = 0.0f;                                                     ///< @brief �ړ���

        void DoProcess(RigidBody* pRigidBody) override;                             // ����J�̏���
    };
}