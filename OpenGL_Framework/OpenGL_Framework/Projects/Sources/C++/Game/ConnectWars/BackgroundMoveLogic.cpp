/* ヘッダファイル */
#include "BackgroundMoveLogic.h"


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
     *  @brief  処理を行う
     *  @param  剛体
     *  @return なし
     *
     ****************************************************************/
    void C_BackgroundMoveLogic::Process(Background* pBackground)
    {
        DoProcess(pBackground);
    }


    /*************************************************************//**
     *
     *  @brief  速度の設定をする
     *  @param  速度
     *  @return なし
     *
     ****************************************************************/
    void C_BackgroundMoveLogic::SetVelocity(const Vector3& rVelocity)
    {
        velocity_ = rVelocity;
    }


    /*************************************************************//**
     *
     *  @brief  加速度の設定をする
     *  @param  加速度
     *  @return なし
     *
     ****************************************************************/
    void C_BackgroundMoveLogic::SetAccelaration(const Vector3& rAccelaration)
    {
        accelaration_ = rAccelaration;
    }


    /*************************************************************//**
     *
     *  @brief  回転速度の設定をする
     *  @param  回転速度
     *  @return なし
     *
     ****************************************************************/
    void C_BackgroundMoveLogic::SetRotationVelocity(const Vector3& rRotationVelocity)
    {
        rotationVelocity_ = rRotationVelocity;
    }


    /*************************************************************//**
     *
     *  @brief  回転加速度の設定をする
     *  @param  回転加速度
     *  @return なし
     *
     ****************************************************************/
    void C_BackgroundMoveLogic::SetRotationAccelaration(const Vector3& rRotationAccelaration)
    {
        rotationAccelaration_ = rRotationAccelaration;
    }
}