#include "RigidBodyStraightMoveLogic.h"


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
     *  @param  �������
     *
     ****************************************************************/
    C_RigidBodyStraightMoveLogic::C_RigidBodyStraightMoveLogic(const Physics::Vector3& rApplyForce) :

        // �������
        applyForce_(rApplyForce)

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
     *  @brief  �ړ��������s��
     *  @param  ����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBodyStraightMoveLogic::Move(RigidBody* pRigidBody)
    {
        pRigidBody->ApplyForce(applyForce_);
    }
}