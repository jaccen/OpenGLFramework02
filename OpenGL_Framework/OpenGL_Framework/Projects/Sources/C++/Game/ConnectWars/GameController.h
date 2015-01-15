/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectWarsDefine.h"
#include "../../Library/GameObject/GameObject.h"
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
    //! @brief ゲームコントローラー
    //! @brief ゲームを制御するためのクラス
    //!
    //-------------------------------------------------------------
    class C_GameController : public GameObject::C_GameObject
    {
    public:
        C_GameController(const std::string& rId, int32_t type);                 // コンストラクタ
        virtual ~C_GameController() override;                                   // デストラクタ
        bool Update() override;                                                 // 更新処理
        void Draw() override;                                                   // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override;                // メッセージ処理
        void EnableWait(bool validFlag = true);                                 // 待機を有効化
        int32_t GetNowFrame() const;                                            // 現在のフレーム数を取得
    protected:
        Timer::C_FrameCounter frameCounter_;                                    ///< @brief フレームカウンター
        bool waitFlag_ = false;                                                 ///< @brief 待機フラグ
    };
}
