/* �w�b�_�t�@�C�� */
#include "CapsuleShape.h"


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
     *  @param  ( �������� )���a
     *  @param  ( �~�������� )����
     *  @param  ����
     *
     ****************************************************************/
    C_CapsuleShape::C_CapsuleShape(float radius,
                                   float height,
                                   ecDirection direction)
    {
        if (direction == ecDirection::X)
        {
            upCollisionShape_ = std::make_unique<btCapsuleShapeX>(radius, height);
        }
        else if (direction == ecDirection::Z)
        {
            upCollisionShape_ = std::make_unique<btCapsuleShapeZ>(radius, height);
        }
        else
        {
            upCollisionShape_ = std::make_unique<btCapsuleShape>(radius, height);
        }
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_CapsuleShape::~C_CapsuleShape()
    {
    }
}