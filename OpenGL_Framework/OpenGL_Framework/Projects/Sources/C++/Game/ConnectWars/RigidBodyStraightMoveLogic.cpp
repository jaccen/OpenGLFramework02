#include "RigidBodyStraightMoveLogic.h"
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
     *  @param  ���x
     *
     ****************************************************************/
    C_RigidBodyStraightMoveLogic::C_RigidBodyStraightMoveLogic(const Physics::Vector3& rVelocity) :

        // ���x
        upVelocity_(std::make_unique<Physics::Vector3>(rVelocity))

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_RigidBodyStraightMoveLogic::~C_RigidBodyStraightMoveLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�B�[�v�R�s�[���s��
     *  @param  �Ȃ�
     *  @return ���g�̃R�s�[
     *
     ****************************************************************/
    C_RigidBodyMoveLogic* C_RigidBodyStraightMoveLogic::DeepCopy()
    {
        return newEx C_RigidBodyStraightMoveLogic(*upVelocity_);
    }


    /*************************************************************//**
     *
     *  @brief  ������͂�ݒ肷��
     *  @param  �������
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBodyStraightMoveLogic::SetVelocity(const Physics::Vector3& rVelocity)
    {
        *upVelocity_ = rVelocity;
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̏������s��
     *  @param  ����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBodyStraightMoveLogic::DoProcess(RigidBody* pRigidBody)
    {
        pRigidBody->SetLinearVelocity(*upVelocity_);
    }
}