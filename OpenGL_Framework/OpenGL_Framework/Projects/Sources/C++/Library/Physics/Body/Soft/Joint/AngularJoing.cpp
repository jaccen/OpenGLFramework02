/* �w�b�_�t�@�C�� */
#include "AngularJoint.h"


//-------------------------------------------------------------
///
/// @brief �t�B�W�b�N�X
/// @brief �����֘A�̖��O���
///
//-------------------------------------------------------------
namespace Physics
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  ��
     *  @param  �S���͂̍���
     *  @param  �G���[�ጸ�p�����[�^
     *
     ****************************************************************/
    C_AngularJoint::C_AngularJoint(const Vector3& rAxis,
                                   float constraintForceMixing,
                                   float errorReductionParameter)
    {
        angularJointSpec_.axis = rAxis;
        angularJointSpec_.cfm = constraintForceMixing;
        angularJointSpec_.erp = errorReductionParameter;
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_AngularJoint::~C_AngularJoint()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �p�ڍ��̃X�y�b�N���擾����
     *  @param  �Ȃ�
     *  @result �p�ڍ��̃X�y�b�N
     *
     ****************************************************************/
    C_AngularJoint::AngularJointSpec* C_AngularJoint::GetAngularJointSpec()
    {
        return &angularJointSpec_;
    }
}