/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../CollisionShape.h"


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
    //! @brief �X�t�B�A�V�F�C�v
    //! @brief ���`���\���N���X
    //!
    //-------------------------------------------------------------
    class C_SphereShape : public C_CollisionShape
    {
    public:
        C_SphereShape(float radius);            // �R���X�g���N�^
        ~C_SphereShape() override;              // �f�X�g���N�^
    };
}