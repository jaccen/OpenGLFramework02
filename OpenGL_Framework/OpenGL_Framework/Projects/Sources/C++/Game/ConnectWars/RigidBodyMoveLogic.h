/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "MoveLogic.h"
#include "../../Library/Physics/Body/Rigid/Rigidbody.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* �ʖ� */
    using RigidBody = Physics::C_RigidBody;                                 // RIgidBody�^


    //-------------------------------------------------------------
    //!
    //! @brief ���M�b�h�{�f�B���[�u���W�b�N
    //! @brief ���̂̈ړ��̃��W�b�N�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_RigidBodyMoveLogic : public IC_MoveLogic<RigidBody>
    {
    public:
        C_RigidBodyMoveLogic() = default;                                   //!< @brief �R���X�g���N�^
        virtual ~C_RigidBodyMoveLogic() override = default;                 //!< @brief �f�X�g���N�^
        void Process(RigidBody* pRigidBody) override final;                 //!< @brief ����
    private:
        virtual void DoProcess(RigidBody* pRigidBody) = 0;                  // ����J�̏���
    };
}