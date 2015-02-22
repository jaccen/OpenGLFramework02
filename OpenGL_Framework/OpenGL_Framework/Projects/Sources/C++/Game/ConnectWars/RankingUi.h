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
    /** スコアデータ */
    struct S_ScoreData
    {
        int32_t score_ = 0;
        S_WordUiData scoreStringData_;
    };

    /** ランキングデータ */
    struct S_RankingData
    {
        S_WordUiData nameData_;
        S_ScoreData scoreData_;
    };


    /** 新記録データ */
    struct S_NewRecordData
    {
        int32_t rank_ = -1;
        std::string rankWords_;
        int32_t score_ = 0;
        std::string name_;
        char newWord_ = 'A';
    };


    //-------------------------------------------------------------
    //!
    //! @brief ランキングUI
    //! @brief ランキングUIを表示するクラス
    //!
    //-------------------------------------------------------------
    class C_RankingUi : public C_BaseUi
    {
    public:
        C_RankingUi(const std::string& rId, int32_t type, bool rankingEntryFlag = false, int32_t newScore = 0);     // コンストラクタ
        ~C_RankingUi() override;                                                                                    // デストラクタ
    private:
        S_WordUiData rankingEntryWords_[1];                                                                         ///< @brief ランキング登録項目
        S_WordUiData rankingWords_[6];                                                                              ///< @brief ランキング項目
        S_RankingData rankingDatas_[5];                                                                             ///< @brief ランキングデータ
        Sprite::SpriteCreaterWeakPtr wpBackgroundSpriteCreater_;                                                    ///< @brief 背景スプライトクリエイター
        bool rankingEntryFlag_ = false;                                                                             ///< @brief ランキング登録フラグ
        Timer::C_FrameCounter rankingEntryCounter_;                                                                 ///< @brief ランキング登録カウンター
        Timer::C_FrameCounter rankingMoveCounter_;                                                                  ///< @brief ランキング移動のカウンター
        int32_t maxCount_ = 30;                                                                                     ///< @brief 最大カウント数
        S_NewRecordData newRecordData_;                                                                             ///< @brief 新記録データ
        bool toTitleFlag_ = false;                                                                                  ///< @brief タイトルシーンへ移行フラグ

        void DoUpdate() override;                                                                                   // 非公開の更新処理
        void DoDraw() override;                                                                                     // 非公開の描画処理
        bool DoMessageProcess(const Telegram& rTelegram) override;                                                  // 非公開のメッセージ処理
        void LoadRankingEntryWords(JSON::JsonObject* pData);                                                        // ランキング登録項目のロード処理
        void LoadRankingWords(JSON::JsonObject* pData);                                                             // ランキング項目のロード処理
        void LoadRankingData();                                                                                     // ランキングデータのロード処理
        void SaveRankingData();                                                                                     // ランキングデータのセーブ処理
        void UpdateRankingEntry();                                                                                  // ランキング登録の更新
        void UpdateRanking();                                                                                       // ランキングの更新
        void DrawBackground();                                                                                      // 背景の描画処理
        void DrawRankingEntry();                                                                                    // ランキング登録の描画処理
        void DrawRanking();                                                                                         // ランキングの描画処理
        void DrawNewEntryScore();                                                                                   // 新しいスコアの登録の描画
    };
}