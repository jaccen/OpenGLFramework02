/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Library/Scene/BaseScene.h"
#include "../../Library/Camera/Camera/Perspective/PerspectiveCamera.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"
#include "../../Library/OpenGL/Buffer/Frame/FrameBuffer.h"
#include "BasePlayer.h"


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
    //! @brief ステージ01シーン
    //! @brief ステージ01を表すクラス
    //!
    //-------------------------------------------------------------
    class C_Stage01Scene : public Scene::C_BaseScene
    {
    public:
        C_Stage01Scene();                                                           // コンストラクタ
        ~C_Stage01Scene() override;                                                 // デストラクタ
        Scene::ecSceneReturn Initialize() override;                                 // 初期化処理
        Scene::ecSceneReturn Update() override;                                     // 更新処理
        void Draw() override;                                                       // 描画処理
        void Finalize() override;                                                   // 終了処理
    private:
        std::unique_ptr<Task::C_GeneralTaskSystem> upTaskSystem_;                   ///< @brief タスクシステム

        std::shared_ptr<Camera::C_PerspectiveCamera> spCamera_;                     // カメラ
        OpenGL::FrameBufferPtr pFrameBuffer_;                                       // フレームバッファ
        std::unique_ptr<C_BasePlayer> upPlayer_;
    };
}