/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../CollisionShape.h"
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
    //! @brief �C���t�B�j�b�g�v���C���V�F�C�v
    //! @brief �������ʌ`���\���N���X
    //!
    //-------------------------------------------------------------
    class C_InfinitePlaneShape : public C_CollisionShape
    {
    public:
        C_InfinitePlaneShape(const Vector3& rNormal, float thickness);          // �R���X�g���N�^
        ~C_InfinitePlaneShape() override;                                       // �f�X�g���N�^
    };
}