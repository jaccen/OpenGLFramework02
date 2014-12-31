/* �w�b�_�t�@�C�� */
#include "ConeShape.h"


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
     *  @param  ( ��ʂ� )���a
     *  @param  ����
     *  @param  ����
     *
     ****************************************************************/
    C_ConeShape::C_ConeShape(float radius, 
                             float height,
                             ecDirection direction)
    {
        if (direction == ecDirection::X)
        {
            upCollisionShape_ = std::make_unique<btCylinderShapeX>(Vector3(height, radius, radius));
        }
        else if (direction == ecDirection::Z)
        {
            upCollisionShape_ = std::make_unique<btCylinderShape>(Vector3(radius, radius, height));
        }
        else
        {
            upCollisionShape_ = std::make_unique<btCylinderShape>(Vector3(radius, height, radius));
        }
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_ConeShape::~C_ConeShape()
    {
    }
}