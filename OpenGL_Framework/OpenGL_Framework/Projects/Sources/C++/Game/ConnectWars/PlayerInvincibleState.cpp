/* ヘッダファイル */
#include "PlayerInvincibleState.h"
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
    C_PlayerInvincibleState::C_PlayerInvincibleState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PlayerInvincibleState::~C_PlayerInvincibleState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  開始処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerInvincibleState::Enter(C_BasePlayer* pPlayer)
    {
        if (pPlayer->IsInvincibleFlag() == false)
        {
            pPlayer->SetInvincibleFlag(true);
        }
    }


    /*************************************************************//**
     *
     *  @brief  実行処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerInvincibleState::Execute(C_BasePlayer* pPlayer)
    {
        frameCounter_.CountUp();

        pPlayer->Move();
        pPlayer->MoveLimitCheck();
        pPlayer->ResetMoveLimitBoundingBox();
        pPlayer->Shot();

        if (pPlayer->GetBombInvincibleFrame() <= frameCounter_.GetCount())
        {
            pPlayer->SetInvincibleFlag(false);

            pPlayer->GetStateMachine()->ChangeState(C_PlayerCombatState ::s_GetInstance());

            frameCounter_.Reset();
        }
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerInvincibleState::Exit(C_BasePlayer* pPlayer)
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
    bool C_PlayerInvincibleState::MessageProcess(C_BasePlayer* pPlayer, const Telegram& rTelegram)
    {
        if (rTelegram.message_ == Message::s_pCONNECT_CHECK)
        {
            pPlayer->ConnectCheck();
        }

        return true;
    }
}