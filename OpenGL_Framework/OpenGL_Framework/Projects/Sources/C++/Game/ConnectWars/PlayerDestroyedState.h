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
    class C_BasePlayer;


    //-------------------------------------------------------------
    //!
    //! @brief プレイヤーデストロイドステート
    //! @brief プレイヤーの破壊された状態を表すクラス
    //!
    //-------------------------------------------------------------
    class C_PlayerDestroyedState : public State::IC_State<C_BasePlayer>,
                                   public Singleton::C_Singleton<C_PlayerDestroyedState>
    {
        friend C_Singleton<C_PlayerDestroyedState>;                                             // シングルトンクラスをフレンド化
    public:
        void Enter(C_BasePlayer* pPlayer) override;                                             // 開始処理
        void Execute(C_BasePlayer* pPlayer) override;                                           // 実行処理
        void Exit(C_BasePlayer* pPlayer) override;                                              // 終了処理
        bool MessageProcess(C_BasePlayer* pPlayer, const Telegram& rTelegram) override;         // メッセージ処理
    private:
        C_PlayerDestroyedState();                                                               // コンストラクタ
        ~C_PlayerDestroyedState() override;                                                     // デストラクタ
    };
}