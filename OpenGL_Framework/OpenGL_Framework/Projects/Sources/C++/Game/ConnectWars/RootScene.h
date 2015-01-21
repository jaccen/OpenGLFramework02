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
    //! @brief ルートシーン
    //! @brief 最上位にあるシーンを表すクラス
    //!
    //-------------------------------------------------------------
    class C_RootScene : public Scene::C_BaseScene
    {
    public:
        C_RootScene();                                                  // コンストラクタ
        ~C_RootScene() override;                                        // デストラクタ
        Scene::ecSceneReturn Initialize() override;                     // 初期化処理
        Scene::ecSceneReturn Update() override;                         // 更新処理
        void Draw() override;                                           // 描画処理
        void Finalize() override;                                       // 終了処理
    private:
        void SetPhysicsEngine();                                        // 物理エンジンの設定
        bool BindToLua();                                               // Luaへのバインド処理
        void PushNextScene();                                           // 次のシーンを追加
    };
}