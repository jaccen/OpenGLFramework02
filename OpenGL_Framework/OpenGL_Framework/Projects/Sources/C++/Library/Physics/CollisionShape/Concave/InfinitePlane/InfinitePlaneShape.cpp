/* �w�b�_�t�@�C�� */
#include "InfinitePlaneShape.h"


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
     *  @param  �@��
     *  @param  ����
     *
     ****************************************************************/
    C_InfinitePlaneShape::C_InfinitePlaneShape(const Vector3& rNormal, float thickness)
    {
        upCollisionShape_ = std::make_unique<btStaticPlaneShape>(rNormal, thickness);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_InfinitePlaneShape::~C_InfinitePlaneShape()
    {
    }
}