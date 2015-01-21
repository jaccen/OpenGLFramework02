#include "RigidBodyConnectMoveLogic.h"
#include "CollisionObject.h"
#include "../../Library/Debug/Helper/DebugHelper.h"


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
     *  @param  ターゲット
     *  @param  ターゲットからのオフセット
     *
     ****************************************************************/
    C_RigidBodyConnectMoveLogic::C_RigidBodyConnectMoveLogic(C_CollisionObject* pTarget,
                                                             const Physics::Vector3& rOffsetFromTarget) :

        // ターゲットとターゲットからのオフセット
        pTarget_(pTarget),
        upOffsetFromTarget_(std::make_unique<Physics::Vector3>(rOffsetFromTarget))

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_RigidBodyConnectMoveLogic::~C_RigidBodyConnectMoveLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ディープコピーを行う
     *  @param  なし
     *  @return 自身のコピー
     *
     ****************************************************************/
    C_RigidBodyMoveLogic* C_RigidBodyConnectMoveLogic::DeepCopy()
    {
        return newEx C_RigidBodyConnectMoveLogic(pTarget_, *upOffsetFromTarget_);
    }


    /*************************************************************//**
     *
     *  @brief  非公開の処理を行う
     *  @param  剛体
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBodyConnectMoveLogic::DoProcess(RigidBody* pRigidBody)
    {
        auto transform = pRigidBody->GetTransform();

        transform.setOrigin(pTarget_->GetPosition() + (*upOffsetFromTarget_));
        pRigidBody->SetTransform(transform);
    }
}