/* �w�b�_�t�@�C�� */
#include "PlayerBullet.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"
#include "../../Library/Physics/CollisionShape/Convex/Box/BoxShape.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"


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
        // JSON�̃f�[�^���擾
        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pPLAYER_BULLET));
        auto pPlayerBulletData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pPLAYER_BULLET).get();
        auto& rPlayerBeamBulletData = (*pPlayerBulletData)["PlayerBulletDatas"]["Beam"];

        // �q�b�g�|�C���g�𐶐�
        C_BaseBullet::upHitPoint_ = std::make_unique<C_BaseHitPoint>(rPlayerBeamBulletData["HitPoint"].GetValue<JSON::Integer>());

        // ���̂��쐬���A�����G���W���ɒǉ�
        Physics::Transform transform;
        transform.setIdentity();

		upRigidBody_ = std::make_unique<Physics::C_RigidBody>(newEx Physics::C_BoxShape(static_cast<float>(rPlayerBeamBulletData["CollisionSize"][0].GetValue<JSON::Real>()),
                                                                                        static_cast<float>(rPlayerBeamBulletData["CollisionSize"][1].GetValue<JSON::Real>()),
                                                                                        static_cast<float>(rPlayerBeamBulletData["CollisionSize"][2].GetValue<JSON::Real>())),
                                                                                        transform,
                                                                                        static_cast<float>(rPlayerBeamBulletData["Mass"].GetValue<JSON::Real>()));

        shooterType_ = shooterType;

        // �Փ˔���̃}�X�N��������
        if (shooterType_ == TYPE_ENEMY)
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

        // ��]���t���[�Y���A���g��ݒ�
        upRigidBody_->EnableFreezeRotation(true, true, true);
        upRigidBody_->SetUserPointer(this);

        // �X�v���C�g�N���G�C�^�[���擾
        assert(Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pBULLET));
        wpSpriteCreater_ = Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pBULLET).get();

        // �X�v���C�g�̐�������ݒ�
        spriteCreateData_.size_.x_ = static_cast<float>(rPlayerBeamBulletData["SpriteData"]["Size"][0].GetValue<JSON::Real>());
        spriteCreateData_.size_.y_ = static_cast<float>(rPlayerBeamBulletData["SpriteData"]["Size"][1].GetValue<JSON::Real>());

        spriteCreateData_.angle_ = static_cast<float>(rPlayerBeamBulletData["SpriteData"]["Angle"].GetValue<JSON::Real>());

        spriteCreateData_.color_.red_ = static_cast<float>(rPlayerBeamBulletData["SpriteData"]["Color"][0].GetValue<JSON::Real>());
        spriteCreateData_.color_.green_ = static_cast<float>(rPlayerBeamBulletData["SpriteData"]["Color"][1].GetValue<JSON::Real>());
        spriteCreateData_.color_.blue_ = static_cast<float>(rPlayerBeamBulletData["SpriteData"]["Color"][2].GetValue<JSON::Real>());
        spriteCreateData_.color_.alpha_ = static_cast<float>(rPlayerBeamBulletData["SpriteData"]["Color"][3].GetValue<JSON::Real>());

        spriteCreateData_.textureUpperLeft_.x_ = static_cast<float>(rPlayerBeamBulletData["SpriteData"]["Texture"]["UpperLeft"][0].GetValue<JSON::Real>());
        spriteCreateData_.textureUpperLeft_.y_ = static_cast<float>(rPlayerBeamBulletData["SpriteData"]["Texture"]["UpperLeft"][1].GetValue<JSON::Real>());
        spriteCreateData_.textureLowerRight_.x_ = static_cast<float>(rPlayerBeamBulletData["SpriteData"]["Texture"]["LowerRight"][0].GetValue<JSON::Real>());
        spriteCreateData_.textureLowerRight_.y_ = static_cast<float>(rPlayerBeamBulletData["SpriteData"]["Texture"]["LowerRight"][1].GetValue<JSON::Real>());
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
