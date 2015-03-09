/* ヘッダファイル */
#include "PlayerBombChargeState.h"
#include "BasePlayer.h"


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
        pPlayer->BombCharge();
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
        pPlayer->GetBombChargeFrameCounter()->CountUp();

        if (pPlayer->GetBombChargeFrameCounter()->GetCount() >= pPlayer->GetBombChargeFrame())
        {
            pPlayer->FireBomb();
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
        pPlayer->GetBombChargeFrameCounter()->Reset();
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
        if (rTelegram.message_ == Message::s_pCONNECT_CHECK)
        {
            pPlayer->ConnectCheck();
        }

        return true;
    }
}