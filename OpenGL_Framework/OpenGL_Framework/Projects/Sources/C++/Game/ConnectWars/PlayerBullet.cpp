/* �w�b�_�t�@�C�� */
#include "PlayerBullet.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"
#include "../../Library/Physics/CollisionShape/Convex/Box/BoxShape.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "../../Library/Debug/Helper/DebugHelper.h"


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
     *  @param  �ˌ��҂̎��
     *
     ****************************************************************/
    C_PlayerBeamBullet::C_PlayerBeamBullet(const std::string& rId,
                                           int32_t type,
                                           int32_t shooterType) : C_BaseBullet(rId, type)
    {
        // �q�b�g�|�C���g�𐶐�
        C_BaseBullet::upHitPoint_ = std::make_unique<C_BaseHitPoint>(1);

        // ���̂��쐬���A�����G���W���ɒǉ�
        Physics::Transform transform;
        transform.setIdentity();

		upRigidBody_ = std::make_unique<Physics::C_RigidBody>(newEx Physics::C_BoxShape(0.2f, 0.5f, 0.1f), transform, 1.0f);

        if (shooterType == TYPE_ENEMY)
        {
            int32_t collisionMask = C_CollisionObject::FILTER_TYPE_PLAYER
                                  | C_CollisionObject::FILTER_TYPE_OPTION 
                                  | C_CollisionObject::FILTER_TYPE_OBSTACLE;

			Physics::C_PhysicsEngine::s_GetInstance()->AddRigidBody(upRigidBody_.get(), FILTER_TYPE_ENEMY_BULLET, collisionMask);
        }
        else
        {
            int32_t collisionMask = C_CollisionObject::FILTER_TYPE_ENEMY
                                  | C_CollisionObject::FILTER_TYPE_OBSTACLE;
        
            Physics::C_PhysicsEngine::s_GetInstance()->AddRigidBody(upRigidBody_.get(), FILTER_TYPE_CONNECTMACHINE_BULLET, collisionMask);
        }

        upRigidBody_->EnableCollisionResponse(false);
        upRigidBody_->EnableFreezeRotation(true, true, true);

        // ���g��ݒ�
        upRigidBody_->SetUserPointer(this);

        // �X�v���C�g�N���G�C�^�[���擾
        assert(Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pBULLET));
        wpSpriteCreater_ = Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pBULLET).get();

        spriteCreateData_.size_.x_ = 0.4f;
        spriteCreateData_.size_.y_ = 0.9f;
        spriteCreateData_.color_.Fill(1.0f);
        spriteCreateData_.textureLowerRight_.x_ = 16.0f;
        spriteCreateData_.textureLowerRight_.y_ = 48.0f;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PlayerBeamBullet::~C_PlayerBeamBullet()
    {
        // ���̂𕨗��G���W�����珜��
        Physics::C_PhysicsEngine::s_GetInstance()->RemoveRigidBody(upRigidBody_.get());
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PlayerBeamBullet::DoDraw()
    {
        if (wpSpriteCreater_.expired() == false)
        {
            auto pSpriteCreater = wpSpriteCreater_.lock();

            spriteCreateData_.position_.x_ = upRigidBody_->GetTransform().getOrigin().x();
            spriteCreateData_.position_.y_ = upRigidBody_->GetTransform().getOrigin().y();
            spriteCreateData_.position_.z_ = upRigidBody_->GetTransform().getOrigin().z();

            pSpriteCreater->Entry(spriteCreateData_);
        }
    }
}
