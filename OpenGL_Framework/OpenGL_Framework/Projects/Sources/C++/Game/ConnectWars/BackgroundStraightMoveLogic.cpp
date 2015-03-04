#include "BackgroundStraightMoveLogic.h"


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
     *  @param  なし
     *
     ****************************************************************/
    C_BackgroundStraightMoveLogic::C_BackgroundStraightMoveLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BackgroundStraightMoveLogic::~C_BackgroundStraightMoveLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  非公開の処理を行う
     *  @param  剛体
     *  @return なし
     *
     ****************************************************************/
    void C_BackgroundStraightMoveLogic::DoProcess(C_BaseBackground* pBackground)
    {
        rotationVelocity_ += rotationAccelaration_;
        velocity_ += accelaration_;

        pBackground->SetPosition(pBackground->GetPosition() + velocity_);
        pBackground->SetRotation(pBackground->GetRotation() + rotationVelocity_);
    }
}