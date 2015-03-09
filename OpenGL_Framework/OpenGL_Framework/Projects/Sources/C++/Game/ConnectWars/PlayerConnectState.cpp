/* ヘッダファイル */
#include "PlayerConnectState.h"
#include "BasePlayer.h"
#include "BaseHitPoint.h"
#include "PlayerCombatState.h"
#include "PlayerDestroyedState.h"
#include "PlayerBombChargeState.h"
#include "PlayerInvincibleState.h"


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
    C_PlayerConnectState::C_PlayerConnectState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PlayerConnectState::~C_PlayerConnectState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  開始処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerConnectState::Enter(C_BasePlayer* pPlayer)
    {
    }


    /*************************************************************//**
     *
     *  @brief  実行処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerConnectState::Execute(C_BasePlayer* pPlayer)
    {
        // カウントアップ
        pPlayer->GetConnectFrameCounter()->CountUp();

        if (pPlayer->GetHitPoint()->CheckRemainValue() == false)
        {
            // 破壊された状態へ変更
            pPlayer->GetStateMachine()->ChangeState(C_PlayerDestroyedState::s_GetInstance());
        }
        else if (pPlayer->IsBombChargeFlag() == true)
        {
            // ボムチャージ状態へ変更
            pPlayer->GetStateMachine()->ChangeState(C_PlayerBombChargeState::s_GetInstance());
        }
        else if (pPlayer->GetConnectFrameCounter()->GetCount() == pPlayer->GetConnectPetrifyFrame())
        {
            if (pPlayer->IsInvincibleFlag() == true)
            {
                // 無敵状態へ変更
                pPlayer->GetStateMachine()->ChangeState(C_PlayerInvincibleState::s_GetInstance());
            }
            else
            {
                // 戦闘状態へ変更
                pPlayer->GetStateMachine()->ChangeState(C_PlayerCombatState::s_GetInstance());
            }
        }

        // 移動制限の確認
        pPlayer->MoveLimitCheck();
        pPlayer->ResetConnect();
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerConnectState::Exit(C_BasePlayer* pPlayer)
    {
        // カウンターをリセット
        pPlayer->GetConnectFrameCounter()->Reset();
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
    bool C_PlayerConnectState::MessageProcess(C_BasePlayer* pPlayer, const Telegram& rTelegram)
    {
        if (rTelegram.message_ == Message::s_pCONNECT_CHECK)
        {
            pPlayer->ConnectCheck();
        }

        return true;
    }
}