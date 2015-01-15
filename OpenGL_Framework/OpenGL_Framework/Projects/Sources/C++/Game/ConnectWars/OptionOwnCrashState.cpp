/* ヘッダファイル */
#include "OptionOwnCrashState.h"
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

        // エフェクトを生成
        //C_EffectGenerator::s_GetManagementInstance().Create(pOption->GetBombSelfCrashEffectId(), pOption->GetPosition());
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
        frameCounter_.CountUp();

        //pOption->Defeated();

        if (pOption->GetDefeatedFrame() <= frameCounter_.GetCount())
        {
            // 効果をリセット
            pOption->ResetEffect();

            // ゲームオブジェクトマネージャーから除去
            //C_GameObjectManager::s_GetManagementInstance().Remove(pOption->GetId());

            // オプションを破棄
            pOption->SetExistanceFlag(false);
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