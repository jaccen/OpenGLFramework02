/* ヘッダファイル */
#include "OptionOwnCrashState.h"
#include "BaseOption.h"
#include "EffectGenerator.h"
#include "../../Library/GameObject/Manager/GameObjectManager.h"


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
    C_OptionOwnCrashState::C_OptionOwnCrashState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_OptionOwnCrashState::~C_OptionOwnCrashState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  開始処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_OptionOwnCrashState::Enter(C_BaseOption* pOption)
    {
        // 撃破フラグを立てる
        pOption->SetDefeatedFlag(true);
    }


    /*************************************************************//**
     *
     *  @brief  実行処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_OptionOwnCrashState::Execute(C_BaseOption* pOption)
    {
        pOption->GetOwnCrashFrameCounter()->CountUp();

        if (pOption->GetOwnCrashFrameCounter()->GetCount() == pOption->GetDefeatedFrame())
        {
            // カウンタをリセット
            pOption->GetOwnCrashFrameCounter()->Reset();

            // 効果をリセット
            pOption->ResetEffect();

            // オプションを破棄
            pOption->SetExistanceFlag(false);

            // ゲームオブジェクトマネージャーから除去
            GameObject::C_GameObjectManager::s_GetInstance()->Remove(pOption->GetId());
        }
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_OptionOwnCrashState::Exit(C_BaseOption* pOption)
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
    bool C_OptionOwnCrashState::MessageProcess(C_BaseOption* pOption, const Telegram& rTelegram)
    {
        return true;
    }
}