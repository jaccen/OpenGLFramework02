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
#include "BulletGenerator.h"
#include "EffectGenerator.h"


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
        C_BulletGenerator bulletGenerator_;                             ///< @brief 弾生成機
        C_EffectGenerator effectGenerator_;                             ///< @brief エフェクト生成機
        std::shared_ptr<Camera::IC_Camera> spMainCamera_;               ///< @brief メインカメラ
        S_CameraData mainCameraData_;                                   ///< @brief メインカメラの情報

        bool RemainLoadProcess();                                       // 残りのロード処理
    };
}