#include "RigidBodyForceMoveLogic.h"
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
     *  @param  �ŏ��ɉ������
     *  @param  �ŏ��ɉ�����g���N
     *
     ****************************************************************/
    C_RigidBodyForceMoveLogic::C_RigidBodyForceMoveLogic(const Physics::Vector3& rFirstAddForce,
                                                         const Physics::Vector3& rFirstAddTorque) :

        // �ŏ��ɉ������
        upFirstAddForce_(std::make_unique<Physics::Vector3>(rFirstAddForce)),

        // �ŏ��ɉ�����g���N
        upFirstAddTorque_(std::make_unique<Physics::Vector3>(rFirstAddTorque))

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_RigidBodyForceMoveLogic::~C_RigidBodyForceMoveLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�B�[�v�R�s�[���s��
     *  @param  �Ȃ�
     *  @return ���g�̃R�s�[
     *
     ****************************************************************/
    C_RigidBodyMoveLogic* C_RigidBodyForceMoveLogic::DeepCopy()
    {
        auto pRigidBodyMoveLogic = newEx C_RigidBodyForceMoveLogic(*upFirstAddForce_, *upAddTorque_);

        pRigidBodyMoveLogic->SetAddForce(*upAddForce_);
        pRigidBodyMoveLogic->SetAddTorque(*upAddTorque_);

        return pRigidBodyMoveLogic;
    }


    /*************************************************************//**
     *
     *  @brief  ������͂�ݒ肷��
     *  @param  �������
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBodyForceMoveLogic::SetAddForce(const Physics::Vector3& rAddForce)
    {
        *upAddForce_ = rAddForce;
    }


    /*************************************************************//**
     *
     *  @brief  ������͂�ݒ肷��
     *  @param  �������
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBodyForceMoveLogic::SetAddTorque(const Physics::Vector3& rAddTorque)
    {
        *upAddTorque_ = rAddTorque;
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̏������s��
     *  @param  ����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBodyForceMoveLogic::DoProcess(RigidBody* pRigidBody)
    {
        if (firstAddForceFlag_ == false)
        {
            pRigidBody->ApplyForce(*upFirstAddForce_);
            firstAddForceFlag_ = true;
        }

        if (firstAddTorqueFlag_ == false)
        {
            pRigidBody->ApplayTorque(*upAddTorque_);
            firstAddTorqueFlag_ = true;
        }

        pRigidBody->ApplyForce(*upAddForce_);
        pRigidBody->ApplayTorque(*upAddTorque_);
    }
}