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
    //! @brief タイトルコントローラー
    //! @brief タイトルを制御するためのクラス
    //!
    //-------------------------------------------------------------
    class C_TitleController : public C_SceneController
    {
    public:
        C_TitleController(const std::string& rId, int32_t type);                // コンストラクタ
        virtual ~C_TitleController() override;                                  // デストラクタ
    private:
        bool toRankingFlag_ = false;                                            ///< @brief ランキングへ移行フラグ
        bool toStage01Flag_ = false;                                            ///< @brief ステージ01へ移行フラグ

        void DoUpdate() override;                                               // 非公開の更新処理
        void DoDraw() override;                                                 // 非公開の描画処理
        bool DoMessageProcess(const Telegram& rTelegram) override;              // 非公開のメッセージ処理
    };
}
