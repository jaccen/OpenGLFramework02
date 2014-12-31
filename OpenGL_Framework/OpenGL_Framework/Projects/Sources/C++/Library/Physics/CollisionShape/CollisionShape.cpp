/* ��d�C���N���[�h�h�~ */
#include "CollisionShape.h"


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
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_CollisionShape::C_CollisionShape()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_CollisionShape::~C_CollisionShape()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �Փˌ`����擾����
     *  @param  �Ȃ�
     *  @return �Փˌ`��
     *
     ****************************************************************/
    btCollisionShape* C_CollisionShape::GetCollisionShape() const
    {
        return upCollisionShape_.get();
    }


    /*************************************************************//**
     *
     *  @brief  �`��̎�ނ��擾����
     *  @param  �Ȃ�
     *  @return �`��̎��
     *
     ****************************************************************/
    int32_t C_CollisionShape::GetShapeType() const
    {
        return upCollisionShape_->getShapeType();
    }


    /*************************************************************//**
     *
     *  @brief  �Փ˃}�[�W�����擾����
     *  @param  �Ȃ�
     *  @return �Փ˃}�[�W��
     *
     ****************************************************************/
    float C_CollisionShape::GetCollisionMargin() const
    {
        return upCollisionShape_->getMargin();
    }


    /*************************************************************//**
     *
     *  @brief  �Փ˃}�[�W����ݒ肷��
     *  @param  �Փ˃}�[�W��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionShape::SetCollisionMargin(float collisionMargin)
    {
        upCollisionShape_->setMargin(collisionMargin);
    }
}