/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectWarsDefine.h"
#include "../../Library/State/State.h"
#include "../../Library/Singleton/Singleton.h"
#include "../../Library/GameObject/Message/Telegram/Telegram.h"


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
    //! @brief プレイヤーコンバットステート
    //! @brief プレイヤーの戦闘状態を表すクラス
    //!
    //-------------------------------------------------------------
    class C_PlayerCombatState : public State::IC_State<C_BasePlayer>,
                                public Singleton::C_Singleton<C_PlayerCombatState>
    {
        friend C_Singleton<C_PlayerCombatState>;                                                        // シングルトンクラスをフレンド化
    public:
        void Enter(C_BasePlayer* pPlayer) override;                                                     //!< @brief 開始処理
        void Execute(C_BasePlayer* pPlayer) override;                                                   //!< @brief 実行処理
        void Exit(C_BasePlayer* pPlayer) override;                                                      //!< @brief 終了処理
        bool MessageProcess(C_BasePlayer* pPlayer, const Telegram& rTelegram) override;                 //!< @brief メッセージ処理
    private:
        C_PlayerCombatState();                                                                          // コンストラクタ
        ~C_PlayerCombatState() override;                                                                // デストラクタ
    };
}