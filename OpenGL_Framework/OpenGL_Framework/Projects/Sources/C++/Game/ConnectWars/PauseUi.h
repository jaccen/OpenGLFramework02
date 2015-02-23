/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "BaseUi.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"


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
    //! @brief ポーズUI
    //! @brief ポーズUIを表示するクラス
    //!
    //-------------------------------------------------------------
    class C_PauseUi : public C_BaseUi
    {
    public:
        C_PauseUi(const std::string& rId, int32_t type);                    // コンストラクタ
        ~C_PauseUi() override;                                              // デストラクタ
    private:
        S_WordUiData uiWords_[3];                                           ///< @brief UI文字
        Sprite::SpriteCreaterWeakPtr wpBackgroundSpriteCreater_;            ///< @brief 背景スプライトクリエイター
        Timer::C_FrameCounter backgoundSizeFactor_;                         ///< @brief 背景のサイズ係数
        int32_t maxSizeCount_  = 15;                                        ///< @brief 最大サイズカウント数
        bool toTitleFlag_ = false;                                          ///< @brief タイトルシーンへ移行フラグ
        int32_t uiWordIndex_ = 0;                                           ///< @brief UI文字のインデックス

        void DoUpdate() override;                                           // 非公開の更新処理
        void DoDraw() override;                                             // 非公開の描画処理
        bool DoMessageProcess(const Telegram& rTelegram) override;          // 非公開のメッセージ処理
        void LoadUiWords(JSON::JsonObject* pData);                          // UI文字のロード処理
        void UpdateUiWords();                                               // UI文字の更新
        void DrawBackground();                                              // 背景の描画処理
        void DrawUiWords();                                                 // UI文字の描画処理
    };
}