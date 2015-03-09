/* �w�b�_�t�@�C�� */
#include "NormalShield.h"
#include "RigidBodyConnectMoveLogic.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"
#include "../../Library/Physics/CollisionShape/Convex/Sphere/SphereShape.h"
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
     *  @param  �^�[�Q�b�g
     *
     ****************************************************************/
    C_NormalShield::C_NormalShield(const std::string& rId,
                                   int32_t type,  
                                   int32_t shooterType,
                                   C_CollisionObject* pTarget) : C_BaseShield(rId, type, shooterType, pTarget)
    {
        // JSON�̃f�[�^���擾
        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pPLAYER_BULLET));
        auto pShiledData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSHIELD_DATA).get();
        auto& rPlayerBeamBulletData = (*pShiledData)["ShieldData"]["Normal"];

        // �q�b�g�|�C���g�𐶐�
        upHitPoint_ = std::make_unique<C_BaseHitPoint>(rPlayerBeamBulletData["HitPoint"].GetValue<JSON::Integer>());

        // ���̂��쐬���A�����G���W���ɒǉ�
        Physics::Transform transform;
        transform.setIdentity();

		upRigidBody_ = std::make_unique<Physics::C_RigidBody>(newEx Physics::C_SphereShape(static_cast<float>(rPlayerBeamBulletData["Radius"].GetValue<JSON::Real>())),
                                                                                           transform,
                                                                                           static_cast<float>(rPlayerBeamBulletData["Mass"].GetValue<JSON::Real>()));

        shooterType_ = shooterType;

        // �Փ˔���̃}�X�N��������
        if (shooterType_ == TYPE_ENEMY)
        {
            int32_t collisionMask = C_CollisionObject::FILTER_TYPE_OBSTACLE
                                  | C_CollisionObject::FILTER_TYPE_CONNECTMACHINE_BULLET
                                  | C_CollisionObject::FILTER_TYPE_BOMB;

			Physics::C_PhysicsEngine::s_GetInstance()->AddRigidBody(upRigidBody_.get(), FILTER_TYPE_SHIELD, collisionMask);
        }
        else
        {
            int32_t collisionMask = C_CollisionObject::FILTER_TYPE_ENEMY
                                  | C_CollisionObject::FILTER_TYPE_OBSTACLE
                                  | C_CollisionObject::FILTER_TYPE_ENEMY_BULLET;
        
            Physics::C_PhysicsEngine::s_GetInstance()->AddRigidBody(upRigidBody_.get(), FILTER_TYPE_SHIELD, collisionMask);
        }

        // ��]���t���[�Y���A���g��ݒ�
        upRigidBody_->EnableFreezeRotation(true, true, true);
        upRigidBody_->SetUserPointer(this);

        // �X�v���C�g�N���G�C�^�[���擾
        assert(Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pSHIELD));
        wpSpriteCreater_ = Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pSHIELD).get();

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
    
        // �ړ����W�b�N���쐬
        upMoveLogic_ = std::make_unique<C_RigidBodyConnectMoveLogic>(pTarget, Physics::Vector3(0.0f, 0.0f, 1.0f));
    }
    
    
    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_NormalShield::~C_NormalShield()
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
    void C_NormalShield::DoDraw()
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
