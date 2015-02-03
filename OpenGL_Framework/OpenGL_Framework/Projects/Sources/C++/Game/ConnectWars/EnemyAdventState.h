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
    class C_BaseEnemy;


    //-------------------------------------------------------------
    //!
    //! @brief エネミーアドベントステート
    //! @brief エネミーの出現状態を表すクラス
    //!
    //-------------------------------------------------------------
    class C_EnemyAdventState : public State::IC_State<C_BaseEnemy>,
                               public Singleton::C_Singleton<C_EnemyAdventState>
    {
        friend C_Singleton<C_EnemyAdventState>;                                                         // シングルトンクラスをフレンド化
    public:
        void Enter(C_BaseEnemy* pEnemy) override;                                                       // 開始処理
        void Execute(C_BaseEnemy* pEnemy) override;                                                     // 実行処理
        void Exit(C_BaseEnemy* pEnemy) override;                                                        // 終了処理
        bool MessageProcess(C_BaseEnemy* pEnemy, const Telegram& rTelegram) override;                   // メッセージ処理
    private:
        C_EnemyAdventState();                                                                           // コンストラクタ
        ~C_EnemyAdventState() override;                                                                 // デストラクタ
    };
}