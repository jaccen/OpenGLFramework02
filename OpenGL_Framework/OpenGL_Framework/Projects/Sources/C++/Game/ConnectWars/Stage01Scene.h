/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Library/Scene/BaseScene.h"
#include "../../Library/Camera/Camera/Perspective/PerspectiveCamera.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"
#include "../../Library/OpenGL/Buffer/Frame/FrameBuffer.h"
#include "BasePlayer.h"
#include "PlayerGenerator.h"
#include "OptionGenerator.h"
#include "EnemyGenerator.h"
#include "BulletGenerator.h"
#include "EffectGenerator.h"
#include "BackgroundGenerator.h"
#include "BombGenerator.h"
#include "ShieldGenerator.h"
#include "GameController.h"


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
        C_Stage01Scene();                                               // コンストラクタ
        ~C_Stage01Scene() override;                                     // デストラクタ
        Scene::ecSceneReturn Initialize() override;                     // 初期化処理
        Scene::ecSceneReturn Update() override;                         // 更新処理
        void Draw() override;                                           // 描画処理
        void Finalize() override;                                       // 終了処理
    private:
        Task::C_GeneralTaskSystem taskSystem_;                          ///< @brief タスクシステム

        C_PlayerGenerator playerGenerator_;                             ///< @brief プレイヤー生成機
        C_OptionGenerator optionGenerator_;                             ///< @brief オプション生成機
        C_EnemyGenerator enemyGenerator_;                               ///< @brief エネミー生成機
        C_BulletGenerator bulletGenerator_;                             ///< @brief 弾生成機
        C_EffectGenerator effectGenerator_;                             ///< @brief エフェクト生成機
        C_BackgroundGenerator backgroundGenerator_;                     ///< @brief 背景生成機
        C_BombGenerator bombGenerator_;                                 ///< @brief ボム生成機
        C_ShieldGenerator shieldGenerator_;                             ///< @brief シールド生成機

        Camera::CameraPtr pMainCamera_;                                 ///< @brief メインカメラ
        Camera::CameraPtr pUiCamera_;                                   ///< @brief UI用カメラ
        Camera::CameraPtr pBackgroundCamera_;                           ///< @brief 背景用カメラ

        bool RemainLoadProcess();                                       // 残りのロード処理
        void SetupGenerator();                                          // ジェネレータの設定
    };
}