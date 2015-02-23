/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Library/Scene/BaseScene.h"
#include "../../Library/Camera/Manager/CameraManager.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"


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
    //! @brief ポーズシーン
    //! @brief ポーズを表すクラス
    //!
    //-------------------------------------------------------------
    class C_PauseScene : public Scene::C_BaseScene
    {
    public:
        C_PauseScene();                                                 // コンストラクタ
        ~C_PauseScene() override;                                       // デストラクタ
        Scene::ecSceneReturn Initialize() override;                     // 初期化処理
        Scene::ecSceneReturn Update() override;                         // 更新処理
        void Draw() override;                                           // 描画処理
        void Finalize() override;                                       // 終了処理
    private:
        Task::C_GeneralTaskSystem taskSystem_;                          ///< @brief タスクシステム
        Camera::CameraPtr pUiCamera_;                                   ///< @brief UI用カメラ

        bool RemainLoadProcess();                                       // 残りのロード処理
    };
}