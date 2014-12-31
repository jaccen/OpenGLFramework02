/* �w�b�_�t�@�C�� */
#include "ConvexHullShape.h"


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
     *  @param  ���_���W
     *  @param  ���_��
     *
     ****************************************************************/
    C_ConvexHullShape::C_ConvexHullShape(Vector3 vertexPositions[], int32_t vertexCount)
    {
        upCollisionShape_ = std::make_unique<btConvexHullShape>(reinterpret_cast<btScalar*>(vertexPositions), vertexCount);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_ConvexHullShape::~C_ConvexHullShape()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �_��ǉ�����
     *  @param  �_
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ConvexHullShape::AddVertexPosition(const Vector3& rVertexPosition)
    {
        dynamic_cast<btConvexHullShape*>(upCollisionShape_.get())->addPoint(rVertexPosition);
    }
}