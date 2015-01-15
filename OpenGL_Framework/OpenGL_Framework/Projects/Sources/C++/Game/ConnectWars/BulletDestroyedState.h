/*  /* 二重インクルード防止 */
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
    class C_BaseBullet;


    //-------------------------------------------------------------
    //!
    //! @brief バレットデストロイドステート
    //! @brief 弾の破壊された状態を表すクラス
    //!
    //-------------------------------------------------------------
    class C_BulletDestroyedState : public State::IC_State<C_BaseBullet>, 
                                   public Singleton::C_Singleton<C_BulletDestroyedState>
    {
        friend C_Singleton<C_BulletDestroyedState>;                                         // シングルトンクラスをフレンド化
    public:
        void Enter(C_BaseBullet* pBullet) override;                                         // 開始処理
        void Execute(C_BaseBullet* pBullet) override;                                       // 実行処理
        void Exit(C_BaseBullet* pBullet) override;                                          // 終了処理
        bool MessageProcess(C_BaseBullet* pBullet, const Telegram& rTelegram) override;     // メッセージ処理
    private:
        C_BulletDestroyedState();                                                           // コンストラクタ
        ~C_BulletDestroyedState() override;                                                 // デストラクタ
    };
}