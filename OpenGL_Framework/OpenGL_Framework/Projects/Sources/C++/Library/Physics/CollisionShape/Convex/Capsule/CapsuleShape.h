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
    //! @brief �J�v�Z���V�F�C�v
    //! @brief �J�v�Z���`���\���N���X
    //!
    //-------------------------------------------------------------
    class C_CapsuleShape : public C_CollisionShape
    {
    public:
        C_CapsuleShape(float radius,                                    // �R���X�g���N�^
                       float height,
                       ecDirection direction = ecDirection::Y);
        ~C_CapsuleShape() override;                                     // �f�X�g���N�^
    private:

    };
}