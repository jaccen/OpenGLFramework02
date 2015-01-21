#include "RigidBodyConnectMoveLogic.h"
#include "CollisionObject.h"
#include "../../Library/Debug/Helper/DebugHelper.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �^�[�Q�b�g
     *  @param  �^�[�Q�b�g����̃I�t�Z�b�g
     *
     ****************************************************************/
    C_RigidBodyConnectMoveLogic::C_RigidBodyConnectMoveLogic(C_CollisionObject* pTarget,
                                                             const Physics::Vector3& rOffsetFromTarget) :

        // �^�[�Q�b�g�ƃ^�[�Q�b�g����̃I�t�Z�b�g
        pTarget_(pTarget),
        upOffsetFromTarget_(std::make_unique<Physics::Vector3>(rOffsetFromTarget))

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_RigidBodyConnectMoveLogic::~C_RigidBodyConnectMoveLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�B�[�v�R�s�[���s��
     *  @param  �Ȃ�
     *  @return ���g�̃R�s�[
     *
     ****************************************************************/
    C_RigidBodyMoveLogic* C_RigidBodyConnectMoveLogic::DeepCopy()
    {
        return newEx C_RigidBodyConnectMoveLogic(pTarget_, *upOffsetFromTarget_);
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̏������s��
     *  @param  ����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBodyConnectMoveLogic::DoProcess(RigidBody* pRigidBody)
    {
        auto transform = pRigidBody->GetTransform();

        transform.setOrigin(pTarget_->GetPosition() + (*upOffsetFromTarget_));
        pRigidBody->SetTransform(transform);
    }
}