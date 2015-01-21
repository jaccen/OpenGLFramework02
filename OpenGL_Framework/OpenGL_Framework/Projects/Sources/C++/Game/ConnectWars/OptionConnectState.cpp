/* ヘッダファイル */
#include "OptionConnectState.h"
#include "BaseOption.h"
#include "BasePlayer.h"
#include "OptionWaitOwnCrashState.h"
#include "OptionCombatState.h"


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
    C_OptionConnectState::C_OptionConnectState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_OptionConnectState::~C_OptionConnectState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  開始処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_OptionConnectState::Enter(C_BaseOption* pOption)
    {
        if (auto pPlayer = pOption->GetPlayer())
        {
            if (pPlayer->IsBombChargeFlag() == true)
            {
                pOption->GetStateMachine()->ChangeState(C_OptionWaitOwnCrashState::s_GetInstance());
            }
            else
            {
                pOption->GetStateMachine()->ChangeState(C_OptionCombatState::s_GetInstance());
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  実行処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_OptionConnectState::Execute(C_BaseOption* pOption)
    {
        pOption->ResetConnect();
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_OptionConnectState::Exit(C_BaseOption* pOption)
    {
    }


    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  オプション
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_OptionConnectState::MessageProcess(C_BaseOption* pOption, const Telegram& rTelegram)
    {
        return true;
    }
}