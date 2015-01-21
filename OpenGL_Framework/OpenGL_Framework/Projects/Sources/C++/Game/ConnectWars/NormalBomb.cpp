/* ヘッダファイル */
#include "NormalBomb.h"
#include "BasePower.h"
#include "BaseOption.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"
#include "../../Library/Physics/CollisionShape/Convex/Box/BoxShape.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ID
     *  @param  種類
     *
     ****************************************************************/
    C_NormalBomb::C_NormalBomb(const std::string& rId, int32_t type) : C_BaseBomb(rId, type)
    {
        // 剛体を作成し、物理エンジンに追加
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
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_NormalBomb::~C_NormalBomb()
    {
    }


    /*************************************************************//**
     *
     *  @brief  非公開の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_NormalBomb::DoUpdate()
    {
        if (frameCounter_.GetCount() >= stayFrame_) existenceFlag_ = false;
    }
}