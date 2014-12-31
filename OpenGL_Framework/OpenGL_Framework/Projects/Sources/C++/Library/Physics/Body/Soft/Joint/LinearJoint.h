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
    //! @brief ���j�A�W���C���g
    //! @brief �����ڍ���\���N���X
    //!
    //-------------------------------------------------------------
    class C_LinearJoint
    {
    public:
        /* �^�ϊ� */
        using LinearJointSpec = btSoftBody::LJoint::Specs;      // LinearJointSpec�^��錾

        C_LinearJoint(const Vector3& rPosition,                 // �R���X�g���N�^
                      float constraintForceMixing = 1.0f,
                      float errorReductionParameter = 1.0f);                
        ~C_LinearJoint();                                       // �f�X�g���N�^
        LinearJointSpec* GetLinearJointSpec();                  // ���`�ڍ��̃X�y�b�N���擾
    private:
        LinearJointSpec linearJointSpec_;                       ///< @brief ���`�ڍ�
    };
}