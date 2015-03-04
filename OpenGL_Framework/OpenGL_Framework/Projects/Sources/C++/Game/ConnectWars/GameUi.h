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
    /** プレイヤーUIデータ */
    struct S_PlayerUiData
    {
        int32_t remainLife_ = 5;                ///< @brief 残機
        int32_t hp_ = 1000;                     ///< @brief 体力
        int32_t maxHp_ = 1000;                  ///< @brief 最大体力
        int32_t score_ = 10;                    ///< @brief スコア
    };


    //-------------------------------------------------------------
    //!
    //! @brief ゲームUI
    //! @brief ゲームUIを表示するクラス
    //!
    //-------------------------------------------------------------
    class C_GameUi : public C_BaseUi
    {
    public:
        C_GameUi(const std::string& rId, int32_t type);                     // コンストラクタ
        ~C_GameUi() override;                                               // デストラクタ
    private:
        S_WordUiData uiWords_[2];                                           ///< @brief UI文字
        S_ImageUiData imageUis_[3];                                         ///< @brief 画像UIデータ
        Sprite::SpriteCreaterWeakPtr wpUiSpriteCreater_;                    ///< @brief UIスプライトクリエイター
        S_PlayerUiData playerUiData_;                                       ///< @brief プレイヤーUIデータ
        bool toNextStageFlag_ = false;                                      ///< @brief 次のステージへ移行フラグ
        bool toRankingFlag_ = false;                                        ///< @brief ランキングへ移行フラグ

        void DoUpdate() override;                                           // 非公開の更新処理
        void DoDraw() override;                                             // 非公開の描画処理
        bool DoMessageProcess(const Telegram& rTelegram) override;          // 非公開のメッセージ処理
        void LoadUiWords(JSON::JsonObject* pData);                          // UI文字のロード処理
        void LoadUiSpriteData(JSON::JsonObject* pData);                     // UIスプライトデータのロード処理
        void UpdateUiWords();                                               // UI文字の更新処理
        void UpdateUiSprite();                                              // UIスプライトの更新処理
        void DrawUiWords();                                                 // UI文字の描画処理
        void DrawUiSprite();                                                // UIスプライトの描画処理
    };
}