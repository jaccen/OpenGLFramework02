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
    //! @brief �R�[���V�F�C�v
    //! @brief �R�[���`���\���N���X
    //!
    //-------------------------------------------------------------
    class C_ConeShape : public C_CollisionShape
    {
    public:
        C_ConeShape(float radius,                                   // �R���X�g���N�^
                    float height,
                    ecDirection direction = ecDirection::Y);
        ~C_ConeShape() override;                                    // �f�X�g���N�^
    };
}