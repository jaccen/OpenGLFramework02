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
    //! @brief �{�b�N�X�V�F�C�v
    //! @brief �{�b�N�X�`���\���N���X
    //!
    //-------------------------------------------------------------
    class C_BoxShape : public C_CollisionShape
    {
    public:
        C_BoxShape(float halfWidth, float halfHeight, float halfDepth);     //!< @brief �R���X�g���N�^
        ~C_BoxShape() override;                                             //!< @brief �f�X�g���N�^
    };
}