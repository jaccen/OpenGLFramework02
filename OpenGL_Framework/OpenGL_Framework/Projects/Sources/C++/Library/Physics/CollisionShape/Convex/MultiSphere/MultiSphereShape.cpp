/* �w�b�_�t�@�C�� */
#include "MultiSphereShape.h"


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
     *  @param  ���S�_
     *  @param  ���a
     *  @param  ��
     *
     ****************************************************************/
    C_MultiSphereShape::C_MultiSphereShape(Vector3 centerPoints[],
                                           float radii[],
                                           int32_t count)
    {
        upCollisionShape_ = std::make_unique<btMultiSphereShape>(centerPoints, radii, count);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_MultiSphereShape::~C_MultiSphereShape()
    {
    }
}