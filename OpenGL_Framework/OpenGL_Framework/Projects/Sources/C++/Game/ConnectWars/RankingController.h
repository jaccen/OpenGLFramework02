/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "SceneController.h"


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
    //! @brief ランキングコントローラー
    //! @brief ランキングを制御するためのクラス
    //!
    //-------------------------------------------------------------
    class C_RankingController : public C_SceneController
    {
    public:
        C_RankingController(const std::string& rId, int32_t type);              // コンストラクタ
        virtual ~C_RankingController() override;                                // デストラクタ
    private:
        bool toTitleFlag_ = false;                                              ///< @brief タイトルへ移行フラグ

        void DoUpdate() override;                                               // 非公開の更新処理
        void DoDraw() override;                                                 // 非公開の描画処理
        bool DoMessageProcess(const Telegram& rTelegram) override;              // 非公開のメッセージ処理
    };
}
