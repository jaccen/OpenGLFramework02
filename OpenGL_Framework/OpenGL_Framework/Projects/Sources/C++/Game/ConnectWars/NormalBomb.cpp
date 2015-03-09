/* ヘッダファイル */
#include "NormalBomb.h"
#include "BasePower.h"
#include "BaseOption.h"
#include "EffectGenerator.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"
#include "../../Library/Physics/CollisionShape/Convex/Box/BoxShape.h"
#include "../../Library/GameObject/Manager/GameObjectManager.h"
#include "../../Library/GameObject/Message/Dispatcher/MessageDispatcher.h"


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
     *  @param  レベル
     *
     ****************************************************************/
    C_NormalBomb::C_NormalBomb(const std::string& rId, int32_t type, int32_t level) : C_BaseBomb(rId, type, level)
    {
        // 剛体を作成し、物理エンジンに追加
        Physics::Transform transform;
        transform.setIdentity();

        int32_t collisionMask = C_CollisionObject::FILTER_TYPE_ENEMY
                              | C_CollisionObject::FILTER_TYPE_ENEMY_BULLET
                              | C_CollisionObject::FILTER_TYPE_OBSTACLE;

        upRigidBody_ = std::make_unique<Physics::C_RigidBody>(newEx Physics::C_BoxShape(std::abs(StageSize::s_left) + 2.0f, std::abs(StageSize::s_top) + 2.0f, 1.0f), transform, 0.0f);
        upRigidBody_->EnableCollisionResponse(false);

        Physics::C_PhysicsEngine::s_GetInstance()->AddRigidBody(upRigidBody_.get(),
                                                                C_CollisionObject::FILTER_TYPE_BOMB,
                                                                collisionMask);
        
        // レベルを0～2へクランプ
        level = level > 2 ? 2 : level;
        upPower_ = std::make_unique<C_BasePower>(level * 250 + 200);

        // エフェクトを生成(1, 3, 5)
        C_EffectGenerator::s_GetInstance()->Create(ID::Generator::Effect::s_pNORMAL_BOMB, Vector3());

        for (int32_t i = 0; i < level; ++i)
        {
            C_EffectGenerator::s_GetInstance()->Create(ID::Generator::Effect::s_pNORMAL_BOMB, Vector3());
            C_EffectGenerator::s_GetInstance()->Create(ID::Generator::Effect::s_pNORMAL_BOMB, Vector3());
        }

        auto pGameObjectManager = GameObject::C_GameObjectManager::s_GetInstance();
        auto gameObjectList =  pGameObjectManager->GetGameObjectsWithType(TYPE_OPTION);

        int32_t crashDelay = 1;
        int32_t addDelay = 19 - level * 7;

        for (auto pGameObject : gameObjectList)
        {
            auto pOption = std::dynamic_pointer_cast<C_BaseOption>(pGameObject);

            if (pOption->IsWaitOwnCrashFlag() == true)
            {
                GameObject::Message::C_MessageDispatcher::s_GetInstance()->Send(id_, pOption->GetId(), Message::s_pOWN_CRASH, crashDelay);
                crashDelay += addDelay;
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_NormalBomb::~C_NormalBomb()
    {
        // 剛体を物理エンジンから除く
        Physics::C_PhysicsEngine::s_GetInstance()->RemoveRigidBody(upRigidBody_.get());
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