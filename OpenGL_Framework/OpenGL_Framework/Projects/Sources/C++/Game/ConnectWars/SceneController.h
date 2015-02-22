/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectWarsDefine.h"
#include "Fade.h"
#include "../../Library/GameObject/GameObject.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"
#include "../../Library/Scene/Manager/SceneManager.h"


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
    //! @brief シーンコントローラー
    //! @brief シーンを制御するためのクラス
    //!
    //-------------------------------------------------------------
    class C_SceneController : public GameObject::C_GameObject
    {
    public:
        C_SceneController(const std::string& rId, int32_t type);                // コンストラクタ
        virtual ~C_SceneController() override;                                  // デストラクタ
        bool Update() override;                                                 // 更新処理
        void Draw() override;                                                   // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override;                // メッセージ処理
        void EnableWait(bool validFlag = true);                                 // 待機を有効化
        int32_t GetNowFrame() const;                                            // 現在のフレーム数を取得
        void SetSceneChanger(Scene::IC_SceneChanger* pSceneChanger);            // シーンチェンジャーを設定
    protected:
        Timer::C_FrameCounter frameCounter_;                                    ///< @brief フレームカウンター
        bool waitFlag_ = false;                                                 ///< @brief 待機フラグ
        Scene::IC_SceneChanger* pSceneChanger_ = nullptr;                       ///< @brief シーンチェンジャー
        std::unique_ptr<C_Fade> upFade_;                                        ///< @brief フェード

        virtual void DoUpdate() = 0;                                            // 非公開の更新処理
        virtual void DoDraw() = 0;                                              // 非公開の描画処理
        virtual bool DoMessageProcess(const Telegram& rTelegram) = 0;           // 非公開のメッセージ処理
    };
}
