/* �w�b�_�t�@�C�� */
#include "OptionBullet.h"
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
    C_OptionSmallBeamBullet::C_OptionSmallBeamBullet(const std::string& rId,
                                                     int32_t type,
                                                     int32_t shooterType) : C_BaseBullet(rId, type)
    {
         // JSON�̃f�[�^���擾
        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pOPTION_BULLET));
        auto pOptionBulletData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pOPTION_BULLET).get();
        auto& rOptionSmallBeamBulletData = (*pOptionBulletData)["OptionBulletDatas"]["SmallBeam"];

        // �q�b�g�|�C���g�𐶐�
        C_BaseBullet::upHitPoint_ = std::make_unique<C_BaseHitPoint>(rOptionSmallBeamBulletData["HitPoint"].GetValue<JSON::Integer>());

        // ���̂��쐬���A�����G���W���ɒǉ�
        Physics::Transform transform;
        transform.setIdentity();

		upRigidBody_ = std::make_unique<Physics::C_RigidBody>(newEx Physics::C_BoxShape(static_cast<float>(rOptionSmallBeamBulletData["CollisionSize"][0].GetValue<JSON::Real>()),
                                                                                        static_cast<float>(rOptionSmallBeamBulletData["CollisionSize"][1].GetValue<JSON::Real>()),
                                                                                        static_cast<float>(rOptionSmallBeamBulletData["CollisionSize"][2].GetValue<JSON::Real>())),
                                                                                        transform,
                                                                                        static_cast<float>(rOptionSmallBeamBulletData["Mass"].GetValue<JSON::Real>()));
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
        spriteCreateData_.size_.x_ = static_cast<float>(rOptionSmallBeamBulletData["SpriteData"]["Size"][0].GetValue<JSON::Real>());
        spriteCreateData_.size_.y_ = static_cast<float>(rOptionSmallBeamBulletData["SpriteData"]["Size"][1].GetValue<JSON::Real>());

        spriteCreateData_.angle_ = static_cast<float>(rOptionSmallBeamBulletData["SpriteData"]["Angle"].GetValue<JSON::Real>());

        spriteCreateData_.color_.red_ = static_cast<float>(rOptionSmallBeamBulletData["SpriteData"]["Color"][0].GetValue<JSON::Real>());
        spriteCreateData_.color_.green_ = static_cast<float>(rOptionSmallBeamBulletData["SpriteData"]["Color"][1].GetValue<JSON::Real>());
        spriteCreateData_.color_.blue_ = static_cast<float>(rOptionSmallBeamBulletData["SpriteData"]["Color"][2].GetValue<JSON::Real>());
        spriteCreateData_.color_.alpha_ = static_cast<float>(rOptionSmallBeamBulletData["SpriteData"]["Color"][3].GetValue<JSON::Real>());

        spriteCreateData_.textureUpperLeft_.x_ = static_cast<float>(rOptionSmallBeamBulletData["SpriteData"]["Texture"]["UpperLeft"][0].GetValue<JSON::Real>());
        spriteCreateData_.textureUpperLeft_.y_ = static_cast<float>(rOptionSmallBeamBulletData["SpriteData"]["Texture"]["UpperLeft"][1].GetValue<JSON::Real>());
        spriteCreateData_.textureLowerRight_.x_ = static_cast<float>(rOptionSmallBeamBulletData["SpriteData"]["Texture"]["LowerRight"][0].GetValue<JSON::Real>());
        spriteCreateData_.textureLowerRight_.y_ = static_cast<float>(rOptionSmallBeamBulletData["SpriteData"]["Texture"]["LowerRight"][1].GetValue<JSON::Real>());
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_OptionSmallBeamBullet::~C_OptionSmallBeamBullet()
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
    void C_OptionSmallBeamBullet::DoDraw()
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
