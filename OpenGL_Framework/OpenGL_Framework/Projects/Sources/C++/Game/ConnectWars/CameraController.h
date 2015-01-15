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
    //! @brief カメラコントローラー
    //! @brief カメラを制御するためのクラス
    //!
    //-------------------------------------------------------------
    class C_CameraController : public GameObject::C_GameObject
    {
    public:
        C_CameraController(const std::string& rId, int32_t type);               // コンストラクタ
        virtual ~C_CameraController() override;                                 // デストラクタ
        bool Update() override;                                                 // 更新処理
        void Draw() override;                                                   // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override;                // メッセージ処理
    protected:
    };
}
