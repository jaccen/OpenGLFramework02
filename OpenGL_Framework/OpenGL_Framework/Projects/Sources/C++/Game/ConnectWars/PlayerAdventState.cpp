/* ヘッダファイル */
#include "PlayerAdventState.h"
#include "BasePlayer.h"
#include "PlayerCombatState.h"


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
    C_PlayerAdventState::C_PlayerAdventState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PlayerAdventState::~C_PlayerAdventState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  開始処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerAdventState::Enter(C_BasePlayer* pPlayer)
    {
    }


    /*************************************************************//**
     *
     *  @brief  実行処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerAdventState::Execute(C_BasePlayer* pPlayer)
    {
        pPlayer->Move();

        if (pPlayer->IsFinishAdvent() == true)
        {
            pPlayer->ChangeMove(C_BasePlayer::INPUT);
            pPlayer->GetStateMachine()->ChangeState(C_PlayerCombatState::s_GetInstance());
        }
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerAdventState::Exit(C_BasePlayer* pPlayer)
    {
            pPlayer->SetEnableConnectFlag(true);
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
    bool C_PlayerAdventState::MessageProcess(C_BasePlayer* pPlayer, const Telegram& rTelegram)
    {
        return true;
    }
}