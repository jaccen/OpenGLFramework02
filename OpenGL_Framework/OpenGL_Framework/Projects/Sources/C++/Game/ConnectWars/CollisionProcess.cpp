/* ヘッダファイル */
#include "CollisionProcess.h"
#include "BasePlayer.h"
#include "BaseOption.h"
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
     *  @brief  プレイヤー同士の衝突時処理を行う
     *  @param  プレイヤー
     *  @param  もう一つのプレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_PlayerAndPlayer(C_BasePlayer* pPlayer, C_BasePlayer* pAnotherPlayer)
    {
        StrongAssert(false && "[ C_CollisionProcess::s_PlayerAndPlayer ] ゲーム内でプレイヤーが2体以上になることはありえません。\n");
    }


    /*************************************************************//**
     *
     *  @brief  プレイヤーとオプションの衝突時処理を行う
     *  @param  プレイヤー
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_PlayerAndOption(C_BasePlayer* pPlayer, C_BaseOption* pOption)
    {
        if (pOption->IsOnceConnectFlag() == false)
        {
            // 一度連結したか判断するフラグを設定
            pOption->SetOnceConnectFlag(true);
        
            // プレイヤーからのオフセットを求める
            auto playerPosition = pPlayer->GetRigidBody()->GetTransform().getOrigin();
            auto optionTransform = pOption->GetRigidBody()->GetTransform();

            Physics::Vector3 offsetFromPlayer = optionTransform.getOrigin() - playerPosition;
            offsetFromPlayer = offsetFromPlayer.normalize();

            offsetFromPlayer = offsetFromPlayer * pPlayer->GetRadius()
                             + offsetFromPlayer * pOption->GetRadius();
            offsetFromPlayer *= Connect::s_OffsetFactor;
            pOption->SetOffsetFromPlayer(offsetFromPlayer);

            // オプションの座標を設定
            optionTransform.setOrigin(playerPosition + offsetFromPlayer);
            pOption->GetRigidBody()->SetTransform(optionTransform);

            // 新規連結処理
            pPlayer->NewConnect();
            pOption->NewConnect();

            // 連結の効果を処理
            pOption->ConnectEffect();

            // オプション数を1増加
            pPlayer->AddOptionCount(1);
        }
    }


    /*************************************************************//**
     *
     *  @brief  プレイヤーと敵の衝突時処理を行う
     *  @param  プレイヤー
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_PlayerAndEnemy(C_BasePlayer* pPlayer, C_BaseEnemy* pEnemy)
    {

    }


    /*************************************************************//**
     *
     *  @brief  オプション同士の衝突時処理を行う
     *  @param  オプション
     *  @param  もう一つのオプション
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_OptionAndOption(C_BaseOption* pOption, C_BaseOption* pAnotherOption)
    {
        // どちらも一度も連結していない場合は何もしない
        if (pOption->IsOnceConnectFlag() == false && pAnotherOption->IsOnceConnectFlag() == false) return;

        // 各オプションを追加
        pOption->AddConnectOption(pAnotherOption);
        pAnotherOption->AddConnectOption(pOption);
    }
}