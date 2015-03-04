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
    using RigidBody = Physics::C_RigidBody;                                     // RigidBody�^


    //-------------------------------------------------------------
    //!
    //! @brief ���M�b�h�{�f�B���[�u���W�b�N
    //! @brief ���̂̈ړ��̃��W�b�N�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_RigidBodyMoveLogic : public IC_MoveLogic<RigidBody>
    {
    public:
        C_RigidBodyMoveLogic() = default;                                       // �R���X�g���N�^
        virtual ~C_RigidBodyMoveLogic() override = default;                     // �f�X�g���N�^
        virtual void Process(RigidBody* pRigidBody) override final;             // ����
        virtual void SetDirection(const Physics::Vector3& rDirection) = 0;      //!< @brief ������ݒ�
        virtual void SetMovement(float movement) = 0;                           //!< @brief �ړ��ʂ�ݒ�   
        virtual C_RigidBodyMoveLogic* DeepCopy() = 0;                           //!< @brief �f�B�[�v�R�s�[
    private:
        virtual void DoProcess(RigidBody* pRigidBody) = 0;                      //!< @brief ����J�̏���
    };
}