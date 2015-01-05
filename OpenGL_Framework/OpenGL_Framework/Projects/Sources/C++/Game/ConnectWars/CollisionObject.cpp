/* �w�b�_�t�@�C�� */
#include "CollisionObject.h"
#include <algorithm>


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  ID
     *  @param  ���
     *
     ****************************************************************/
    C_CollisionObject::C_CollisionObject(const std::string& rId, int32_t type)
    {
        // 4����ID�̃��������m��
        collidedObjectIdList_.reserve(4);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_CollisionObject::~C_CollisionObject()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �Փ˂����I�u�W�F�N�g��ID�����݂��邩�m�F���s��
     *  @param  ID
     *  @return ���݂���ꍇ  �Ftrue
     *  @return ���݂��Ȃ��ꍇ�Ffalse
     *
     ****************************************************************/
    bool C_CollisionObject::CheckCollidedObjectId(const std::string& rId)
    {
        auto iterator = std::find(collidedObjectIdList_.begin(), collidedObjectIdList_.end(), rId);
        if (iterator == collidedObjectIdList_.end()) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �Փ˂����I�u�W�F�N�g��ID�̓o�^���s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionObject::EntryCollidedObjectId(const std::string& rId)
    {
        collidedObjectIdList_.push_back(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �Փ˓_��ݒ肷��
     *  @param  �Փ˓_
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionObject::SetCollisionPoint(const Physics::Vector3& rCollisionPoint)
    {
        collisionPoint_ = rCollisionPoint;
    }


    /*************************************************************//**
     *
     *  @brief  �Փ˂����I�u�W�F�N�g��ID�̃��Z�b�g���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CollisionObject::ResetCollidedObjectId()
    {
        collidedObjectIdList_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  �Փ˓_���擾����
     *  @param  �Ȃ�
     *  @return �Փ˓_
     *
     ****************************************************************/
    const Physics::Vector3& C_CollisionObject::GetCollisionPoint() const
    {
        return collisionPoint_;
    }
}