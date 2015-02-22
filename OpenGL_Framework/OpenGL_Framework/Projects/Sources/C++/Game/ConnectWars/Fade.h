/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectWarsDefine.h"
#include "../../Library/GameObject/GameObject.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"


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
    //! @brief フェード
    //! @brief フェードイン・アウトをするためのクラス
    //!
    //-------------------------------------------------------------
    class C_Fade : public GameObject::C_GameObject
    {
    public:
        C_Fade(const std::string& rId,                                  // コンストラクタ
               int32_t type,    
               int32_t fadeFrame = 60,
               bool createFadeInFlag = true);           
        ~C_Fade() override;                                             // デストラクタ
        bool Update() override;                                         // 更新処理
        void Draw() override;                                           // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override;        // メッセージ処理
        void FadeIn();                                                  // フェードイン
        void FadeOut();                                                 // フェードアウト
        void ResetFlag();                                               // フラグをリセット
        void SetFadeFrame(int32_t fadeFrame);                           // フェードフレームを設定
        bool IsFinishFadeInFlag() const;                                // フェードイン完了フラグを取得
        bool IsFinishFadeOutFlag() const;                               // フェードアウト完了フラグを取得
    private:
        bool fadeInFlag_ = false;                                       ///< @brief フェードインフラグ
        bool finishFadeInFlag_ = false;                                 ///< @brief フェードイン完了フラグ
        bool fadeOutFlag_ = false;                                      ///< @brief フェードアウトフラグ
        bool finishFadeOutFlag_ = false;                                ///< @brief フェードアウト完了フラグ
        int32_t elapsedFadeFrame_ = 0;                                  ///< @brief 経過フェードフレーム
        int32_t fadeFrame_ = 0;                                         ///< @brief フェードフレーム
        Sprite::SpriteCreaterWeakPtr wpSpriteCreater_;                  ///< @brief スプライトクリエイター
        Vector4 color_;                                                 ///< @brief 色
    };
}