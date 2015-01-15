/* ヘッダファイル */
#include "PlayerBombChargeState.h"
#include "BasePlayer.h"
#include "PlayerInvincibleState.h"
//#include "EffectGenerator.h"
//#include "BombGenerator.h"


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
    C_PlayerBombChargeState::C_PlayerBombChargeState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PlayerBombChargeState::~C_PlayerBombChargeState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  開始処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerBombChargeState::Enter(C_BasePlayer* pPlayer)
    {
        if (pPlayer->IsBombChargeFlag() == false)
        {
            // 各フラグを設定
            pPlayer->SetBombChargeFlag(true);
            pPlayer->SetInvincibleFlag(true);

            // チャージエフェクトを生成
            //C_EffectGenerator::s_GetManagementInstance().Create(pPlayer->GetBombChargeEffectId(), pPlayer->GetPosition());
        }
    }


    /*************************************************************//**
     *
     *  @brief  実行処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerBombChargeState::Execute(C_BasePlayer* pPlayer)
    {
        // カウントアップ
        frameCounter_.CountUp();

        if (frameCounter_.GetCount() >= pPlayer->GetBombChargeFrame())
        {
            // 各フラグを設定
            pPlayer->SetBombChargeFlag(false);
            pPlayer->SetInvincibleFlag(false);

            // 無敵状態に変更
            pPlayer->GetStateMachine()->ChangeState(C_PlayerInvincibleState::s_GetInstance());

            // ボムを生成
            //C_BombGenerator::s_GetManagementInstance().Create(pPlayer->GetBombId(), pPlayer->GetPosition(), 1 + pPlayer->GetOptionCount() / 5);
        }
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerBombChargeState::Exit(C_BasePlayer* pPlayer)
    {
        // カウンターをリセット
        frameCounter_.Reset();
    }


    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  プレイヤー
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_PlayerBombChargeState::MessageProcess(C_BasePlayer* pPlayer, const Telegram& rTelegram)
    {
        return true;
    }
}