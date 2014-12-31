/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../../PhysicsDefine.h"


//-------------------------------------------------------------
///
/// @brief �t�B�W�b�N�X
/// @brief �����֘A�̖��O���
///
//-------------------------------------------------------------
namespace Physics
{
    //-------------------------------------------------------------
    //!
    //! @brief �A���M�����[�W���C���g
    //! @brief �p�ڍ���\���N���X
    //!
    //-------------------------------------------------------------
    class C_AngularJoint
    {
    public:
        /* �^�ϊ� */
        using AngularJointSpec = btSoftBody::AJoint::Specs;         // AngularJointSpec�^��錾

        C_AngularJoint(const Vector3& rAxis,                        // �R���X�g���N�^
                       float constraintForceMixing = 1.0f,
                       float errorReductionParameter = 1.0f);
        ~C_AngularJoint();                                          // �f�X�g���N�^
        AngularJointSpec* GetAngularJointSpec();                    // �p�ڍ��̃X�y�b�N���擾
    private:
        AngularJointSpec angularJointSpec_;                         ///< @brief �p�ڍ��̃X�y�b�N
    };
}