/* �w�b�_�t�@�C�� */
#include "LinearJoint.h"


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
     *  @param  ���W
     *  @param  �S���͂̍���
     *  @param  �G���[�ጸ�p�����[�^
     *
     ****************************************************************/
    C_LinearJoint::C_LinearJoint(const Vector3& rPosition,
                                 float constraintForceMixing,
                                 float errorReductionParameter)
    {
        linearJointSpec_.cfm = constraintForceMixing;
        linearJointSpec_.erp = errorReductionParameter;
        linearJointSpec_.position = rPosition;
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_LinearJoint::~C_LinearJoint()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ���`�ڍ��̃X�y�b�N���擾����
     *  @param  �Ȃ�
     *  @result ���`�ڍ��̃X�y�b�N
     *
     ****************************************************************/
    C_LinearJoint::LinearJointSpec* C_LinearJoint::GetLinearJointSpec()
    {
        return &linearJointSpec_;
    }
}