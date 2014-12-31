/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Library/Scene/BaseScene.h"
#include "../../Library/Camera/Camera/Perspective/PerspectiveCamera.h"


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
    //! @brief タイトルシーン
    //! @brief タイトルを表すクラス
    //!
    //-------------------------------------------------------------
    class C_TitleScene : public Scene::C_BaseScene
    {
    public:
        C_TitleScene();                                                 // コンストラクタ
        ~C_TitleScene() override;                                       // デストラクタ
        Scene::ecSceneReturn Initialize() override;                     // 初期化処理
        Scene::ecSceneReturn Update() override;                         // 更新処理
        void Draw() override;                                           // 描画処理
        void Finalize() override;                                       // 終了処理
    private:
        std::shared_ptr<Camera::C_PerspectiveCamera> spCamera_;         // カメラ
    };
}