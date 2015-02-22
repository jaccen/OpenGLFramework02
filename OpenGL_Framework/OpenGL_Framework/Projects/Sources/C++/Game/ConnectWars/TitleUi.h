/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "BaseUi.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /** コンフィグデータ */
    struct S_ConfigData
    {
        int32_t playerLife_ = 3;                                                    ///< @brief プレイヤーの残機
        int32_t SE_ = 5;                                                            ///< @brief SE
        int32_t BGM_ = 5;                                                           ///< @brief BGM
        int32_t shotButton_ = 1;                                                    ///< @brief ショットボタン
        int32_t bombButton_ = 3;                                                    ///< @brief ボムボタン
    };


    //-------------------------------------------------------------
    //!
    //! @brief タイトルUI
    //! @brief タイトルUIを表示するクラス
    //!
    //-------------------------------------------------------------
    class C_TitleUi : public C_BaseUi
    {
    public:
        C_TitleUi(const std::string& rId, int32_t type);                            // コンストラクタ
        ~C_TitleUi() override;                                                      // デストラクタ
    private:
        S_ImageUiData imageUis_[2];                                                 ///< @brief 画像UI
        S_WordUiData initialItems_[3];                                              ///< @brief 初期項目
        S_WordUiData stageSelectItems_[4];                                          ///< @brief ステージセレクト項目
        S_WordUiData configItems_[7];                                               ///< @brief コンフィグ項目
        Sprite::SpriteCreaterWeakPtr wpUiSpriteCreater_;                            ///< @brief タイトルスプライトクリエイター
        Sprite::SpriteCreaterWeakPtr wpBackgroundSpriteCreater_;                    ///< @brief 背景スプライトクリエイター    
        bool drawStageSelectItemFlag_ = false;                                      ///< @brief ステージセレクト項目の描画フラグ
        bool drawConfigItemFlag_ = false;                                           ///< @brief コンフィグ項目の描画フラグ
        int32_t initialItemNumber_ = 0;                                             ///< @brief 初期項目番号
        int32_t stageSelectItemNumber_ = 0;                                         ///< @brief ステージセレクト項目番号
        int32_t configItemNumber_ = 0;                                              ///< @brief コンフィグ項目番号
        S_ConfigData configData_;                                                   ///< @brief コンフィグデータ


        void DoUpdate() override;                                                   // 非公開の更新処理
        void DoDraw() override;                                                     // 非公開の描画処理
        bool DoMessageProcess(const Telegram& rTelegram) override;                  // 非公開のメッセージ処理
        void LoadImageUis(JSON::JsonObject* pData);                                 // 画像UIのロード処理
        void LoadInitialItems(JSON::JsonObject* pData);                             // 初期項目のロード処理
        void LoadStaeSelectItems(JSON::JsonObject* pData);                          // ステージセレクト項目のロード処理
        void LoadConfigItems(JSON::JsonObject* pData);                              // コンフィグ項目のロード処理
        void LoadConfigData();                                                      // コンフィグデータのロード処理
        void SaveConfigData();                                                      // コンフィグデータのセーブ処理
        void DrawImageUiAndBackground();                                            // 画像UIと背景の描画
        void DrawInitialItems();                                                    // 初期項目の描画処理
        void DrawStageSelectItems();                                                // ステージセレクト項目の描画
        void DrawConfigItems();                                                     // コンフィグ項目の描画
    };
}