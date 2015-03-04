/* ヘッダファイル */
#include "PlayerAdventMoveLogic.h"
#include "../../Library/Math/Define/MathDefine.h"
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
     *  @param  なし
     *
     ****************************************************************/
    C_PlayerAdventMoveLogic::C_PlayerAdventMoveLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PlayerAdventMoveLogic::~C_PlayerAdventMoveLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  移動量を設定する
     *  @param  移動量
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerAdventMoveLogic::SetMovement(float movement)
    {
        movement_ = movement;
    }


    /*************************************************************//**
     *
     *  @brief  ディープコピーを行う
     *  @param  なし
     *  @return 自身のコピー
     *
     ****************************************************************/
    C_RigidBodyMoveLogic* C_PlayerAdventMoveLogic::DeepCopy()
    {
        return newEx C_PlayerAdventMoveLogic();
    }


    /*************************************************************//**
     *
     *  @brief  移動終了か確認する
     *  @param  なし
     *  @return 移動終了の場合    ：true
     *  @return 移動終了でない場合：false
     *
     ****************************************************************/
    bool C_PlayerAdventMoveLogic::IsMoveFinish() const
    {
        return (finishCount == frameCounter_.GetCount()) ? true : false;
    }


    /*************************************************************//**
     *
     *  @brief  非公開の処理を行う
     *  @param  剛体
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerAdventMoveLogic::DoProcess(RigidBody* pRigidBody)
    {
        if (finishCount == frameCounter_.GetCount()) return;
        
        // 加える座標と移動量
        Physics::Vector3 addPosition = Physics::Vector3(0.0f, 0.0f, 0.0f);

        if (frameCounter_.GetCount() < 10)
        {
            addPosition = Physics::Vector3(0.05f, 0.8f, 1.5f);
        }
        else if (frameCounter_.GetCount() < 20)
        {
            addPosition = Physics::Vector3(0.05f, 0.7f, 0.8f);
        }
        else if (frameCounter_.GetCount() < 30)
        {
            addPosition = Physics::Vector3(0.05f, 0.5f, 0.7f);
        }
        else
        {
            addPosition = Physics::Vector3(0.05f, 0.4f, 0.5f);
        }

        // 座標を加える
        pRigidBody->AddPosition(addPosition);
    
        frameCounter_.CountUp();
    }
}