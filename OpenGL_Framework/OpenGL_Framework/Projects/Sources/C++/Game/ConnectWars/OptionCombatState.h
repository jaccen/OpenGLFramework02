/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectWarsDefine.h"
#include "../../Library/State/State.h"
#include "../../Library/Singleton/Singleton.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* 前方宣言 */
    class C_BaseOption;


    //-------------------------------------------------------------
    //!
    //! @brief オプションノーマルステート
    //! @brief オプションの戦闘状態を表すクラス
    //!
    //-------------------------------------------------------------
    class C_OptionCombatState : public State::IC_State<C_BaseOption>, 
                                public Singleton::C_Singleton<C_OptionCombatState>
    {
        friend C_Singleton<C_OptionCombatState>;                                                // シングルトンクラスをフレンド化
    public:
        void Enter(C_BaseOption* pOption) override;                                             // 開始処理
        void Execute(C_BaseOption* pOption) override;                                           // 実行処理
        void Exit(C_BaseOption* pOption) override;                                              // 終了処理
        bool MessageProcess(C_BaseOption* pOption, const Telegram& rTelegram) override;         // メッセージ処理
    private:
        C_OptionCombatState();                                                                  // コンストラクタ
        ~C_OptionCombatState() override;                                                        // デストラクタ
    };
}