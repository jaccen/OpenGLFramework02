/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectWarsDefine.h"
#include "../../Library/State/State.h"
#include "../../Library/Singleton/Singleton.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"


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
    //! @brief オプションオゥンクラッシュステート
    //! @brief オプションの自爆状態を表すクラス
    //!
    //-------------------------------------------------------------
    class C_OptionOwnCrashState : public State::IC_State<C_BaseOption>,
                                  public Singleton::C_Singleton<C_OptionOwnCrashState>
    {
        friend C_Singleton<C_OptionOwnCrashState>;                                          // シングルトンクラスをフレンド化
    public:
        void Enter(C_BaseOption* pOption) override;                                         // 開始処理
        void Execute(C_BaseOption* pOption) override;                                       // 実行処理
        void Exit(C_BaseOption* pOption) override;                                          // 終了処理
        bool MessageProcess(C_BaseOption* pOption, const Telegram& rTelegram) override;     // メッセージ処理
    private:
        C_OptionOwnCrashState();                                                            // コンストラクタ
        ~C_OptionOwnCrashState() override;                                                  // デストラクタ
    };
}