/* ヘッダファイル */
#include "OptionWaitOwnCrashState.h"
#include "BaseOption.h"


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
    C_OptionWaitOwnCrashState::C_OptionWaitOwnCrashState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_OptionWaitOwnCrashState::~C_OptionWaitOwnCrashState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  開始処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_OptionWaitOwnCrashState::Enter(C_BaseOption* pOption)
    {
        pOption->SetInvincibleFlag(true);
    }


    /*************************************************************//**
     *
     *  @brief  実行処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_OptionWaitOwnCrashState::Execute(C_BaseOption* pOption)
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
    void C_OptionWaitOwnCrashState::Exit(C_BaseOption* pOption)
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
    bool C_OptionWaitOwnCrashState::MessageProcess(C_BaseOption* pOption, const Telegram& rTelegram)
    {
        if (rTelegram.message_ == Message::s_pOWN_CRASH)
        {
            pOption->OwnCrash();
        }

        return true;
    }
}