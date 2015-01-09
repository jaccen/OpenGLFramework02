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
        C_RigidBodyStraightMoveLogic(const Physics::Vector3& rApplyForce);          // �R���X�g���N�^
        virtual ~C_RigidBodyStraightMoveLogic() override;                           // �f�X�g���N�^
    private:
        Physics::Vector3 applyForce_;                                               ///< @brief �������

        void DoProcess(RigidBody* pRigidBody) override;                             // ����J�̏���
    };
}