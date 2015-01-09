#include "RigidBodyStraightMoveLogic.h"


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
     *  @param  加える力
     *
     ****************************************************************/
    C_RigidBodyStraightMoveLogic::C_RigidBodyStraightMoveLogic(const Physics::Vector3& rApplyForce) :

        // 加える力
        applyForce_(rApplyForce)

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
     *  @brief  非公開の処理を行う
     *  @param  剛体
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBodyStraightMoveLogic::DoProcess(RigidBody* pRigidBody)
    {
        pRigidBody->ApplyForce(applyForce_);
    }
}