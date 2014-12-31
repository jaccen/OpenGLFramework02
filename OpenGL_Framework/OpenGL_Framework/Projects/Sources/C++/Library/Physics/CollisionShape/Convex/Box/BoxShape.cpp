/* �w�b�_�t�@�C�� */
#include "BoxShape.h"
#include "../../../PhysicsDefine.h"


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
     *  @param  ���̔���
     *  @param  �����̔���
     *  @param  ���s�̔���
     *
     ****************************************************************/
    C_BoxShape::C_BoxShape(float halfWidth, float halfHeight, float halfDepth)
    {
        upCollisionShape_ = std::make_unique<btBoxShape>(Vector3(halfWidth, halfHeight, halfDepth));
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BoxShape::~C_BoxShape()
    {
    }
}