/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "SceneController.h"
#include "EnemyGenerator.h"
#include "BackgroundGenerator.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief ゲームコントローラー
    //! @brief ゲームを制御するためのクラス
    //!
    //-------------------------------------------------------------
    class C_GameController : public C_SceneController
    {
    public:
        C_GameController(const std::string& rId, int32_t type);                         // コンストラクタ
        virtual ~C_GameController() override;                                           // デストラクタ
        void SetBackgroundGenerator(C_BackgroundGenerator* pBackgroundGenerator);       // バックグラウンドジェネレータを設定
        void SetEnemyGenerator(C_EnemyGenerator* pEnemyGenerator);                      // エネミージェネレータを設定
    protected:
        C_BackgroundGenerator* pBackgroundGenerator_ = nullptr;                         ///< @brief バックグラウンドジェネレータ
        C_EnemyGenerator* pEnemyGenerator_ = nullptr;                                   ///< @brief エネミージェネレータ

        void DoUpdate() override;                                                       // 非公開の更新処理
        void DoDraw() override;                                                         // 非公開の描画処理
        bool DoMessageProcess(const Telegram& rTelegram) override;                      // 非公開のメッセージ処理
    };
}
