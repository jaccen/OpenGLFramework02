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
    C_RigidBodyStraightMoveLogic::C_RigidBodyStraightMoveLogic() :

        // 向き
        upDirection_(std::make_unique<Physics::Vector3>())

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
        auto pMoveLogic = newEx C_RigidBodyStraightMoveLogic();

        pMoveLogic->SetDirection(*upDirection_);
        pMoveLogic->SetMovement(movement_);

        return pMoveLogic;
    }


    /*************************************************************//**
     *
     *  @brief  向きを設定する
     *  @param  向き
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBodyStraightMoveLogic::SetDirection(const Physics::Vector3& rDirection)
    {
        *upDirection_ = rDirection;
    }


    /*************************************************************//**
     *
     *  @brief  移動量を設定する
     *  @param  移動量
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBodyStraightMoveLogic::SetMovement(float movement)
    {
        movement_ = movement;
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
        pRigidBody->SetLinearVelocity((*upDirection_) * movement_);
    }
}