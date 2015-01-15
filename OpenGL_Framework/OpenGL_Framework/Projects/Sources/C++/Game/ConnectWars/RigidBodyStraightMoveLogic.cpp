#include "RigidBodyStraightMoveLogic.h"
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
     *  @param  速度
     *
     ****************************************************************/
    C_RigidBodyStraightMoveLogic::C_RigidBodyStraightMoveLogic(const Physics::Vector3& rVelocity) :

        // 速度
        upVelocity_(std::make_unique<Physics::Vector3>(rVelocity))

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_RigidBodyStraightMoveLogic::~C_RigidBodyStraightMoveLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ディープコピーを行う
     *  @param  なし
     *  @return 自身のコピー
     *
     ****************************************************************/
    C_RigidBodyMoveLogic* C_RigidBodyStraightMoveLogic::DeepCopy()
    {
        return newEx C_RigidBodyStraightMoveLogic(*upVelocity_);
    }


    /*************************************************************//**
     *
     *  @brief  加える力を設定する
     *  @param  加える力
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBodyStraightMoveLogic::SetVelocity(const Physics::Vector3& rVelocity)
    {
        *upVelocity_ = rVelocity;
    }


    /*************************************************************//**
     *
     *  @brief  非公開の処理を行う
     *  @param  剛体
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBodyStraightMoveLogic::DoProcess(RigidBody* pRigidBody)
    {
        pRigidBody->SetLinearVelocity(*upVelocity_);
    }
}