/* �w�b�_�t�@�C�� */
#include "NormalBomb.h"
#include "BasePower.h"
#include "BaseOption.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"
#include "../../Library/Physics/CollisionShape/Convex/Box/BoxShape.h"


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
    C_NormalBomb::C_NormalBomb(const std::string& rId, int32_t type) : C_BaseBomb(rId, type)
    {
        // ���̂��쐬���A�����G���W���ɒǉ�
        Physics::Transform transform;
        transform.setIdentity();

        int32_t collisionMask = C_CollisionObject::FILTER_TYPE_ENEMY
                              | C_CollisionObject::FILTER_TYPE_ENEMY_BULLET
                              | C_CollisionObject::FILTER_TYPE_OBSTACLE;

        upRigidBody_ = std::make_unique<Physics::C_RigidBody>(newEx Physics::C_BoxShape(std::abs(StageSize::s_left), std::abs(StageSize::s_top), 1.0f), transform, 0.0f);

        upRigidBody_->EnableCollisionResponse(false);

        Physics::C_PhysicsEngine::s_GetInstance()->AddRigidBody(upRigidBody_.get(),
                                                                C_CollisionObject::FILTER_TYPE_BOMB,
                                                                collisionMask);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_NormalBomb::~C_NormalBomb()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_NormalBomb::DoUpdate()
    {
        if (frameCounter_.GetCount() >= stayFrame_) existenceFlag_ = false;
    }
}