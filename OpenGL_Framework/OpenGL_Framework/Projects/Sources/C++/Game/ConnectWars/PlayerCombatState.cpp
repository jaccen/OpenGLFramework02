/* ヘッダファイル */
#include "PlayerCombatState.h"
#include "BasePlayer.h"
#include "ConnectWarsDefine.h"
#include "PlayerDestroyedState.h"


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
    C_PlayerCombatState::C_PlayerCombatState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PlayerCombatState::~C_PlayerCombatState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  開始処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerCombatState::Enter(C_BasePlayer* pPlayer)
    {
    }


    /*************************************************************//**
     *
     *  @brief  実行処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerCombatState::Execute(C_BasePlayer* pPlayer)
    {
        // ヒットポイントがなくなった場合、破壊された状態へ変更
        if (pPlayer->GetHitPoint()->CheckRemainValue() == false)
        {
            pPlayer->GetStateMachine()->ChangeState(C_PlayerDestroyedState::s_GetInstance());
        }

        pPlayer->Move();
        pPlayer->MoveLimitCheck();
        pPlayer->ResetMoveLimitBoundingBox();
        pPlayer->Shot();
        pPlayer->Bomb();
        pPlayer->ResetConnect();
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerCombatState::Exit(C_BasePlayer* pPlayer)
    {
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
    bool C_PlayerCombatState::MessageProcess(C_BasePlayer* pPlayer, const Telegram& rTelegram)
    {
        if (rTelegram.message_ == Message::s_pCONNECT_CHECK)
        {
            pPlayer->ConnectCheck();
        }

        return true;
    }
}