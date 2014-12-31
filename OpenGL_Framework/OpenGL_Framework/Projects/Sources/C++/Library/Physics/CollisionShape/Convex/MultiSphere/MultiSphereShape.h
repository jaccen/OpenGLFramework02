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
    //! @brief �}���`�X�t�B�A�V�F�C�v
    //! @brief �������`���\���N���X
    //!
    //-------------------------------------------------------------
    class C_MultiSphereShape : public C_CollisionShape
    {
    public:
        C_MultiSphereShape(Vector3 centerPoints[],          // �R���X�g���N�^
                           float radii[],
                           int32_t count);
        ~C_MultiSphereShape() override;                     // �f�X�g���N�^
    };
}