/* ヘッダファイル */
#include "ConnectWars.h"
#include "../../Library/Scene/Manager/SceneManager.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/Input/Keyboard/KeyboardManager.h"
#include "TitleScene.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_ConnectWars::C_ConnectWars() : C_Framework(this),

        // Luaステートマネージャー
        upLuaStateManager_(std::make_unique<Lua::C_LuaStateManager>()),

        // パーティクルシステムマネージャー
        upParticleSystemManager_(std::make_unique<Particle::C_ParticleSystemManager>()),

        // ゲームオブジェクトマネージャー
        upGameObjectManager_(std::make_unique<GameObject::C_GameObjectManager>()),

        // メッセージディスパッチャー
        upMessageDispatcher_(std::make_unique<GameObject::Message::C_MessageDispatcher>()),

        // フィジックスエンジン
        upPhysicsEngine_(std::make_unique<Physics::C_PhysicsEngine>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_ConnectWars::~C_ConnectWars()
    {
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  なし
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_ConnectWars::Initialize()
    {
        // ライブラリの初期化処理
        if (C_Framework::InitializeWithJsonFile("Projects/GameDatas/ConnectWars/JSON/Window/MainWindowData.json",
                                                "Projects/GameDatas/ConnectWars/JSON/OpenGL/OpenGLData.json") == false)
        {
            return false;
        }

        // シーンマネージャーの初期化処理
        upSceneManager_ = std::make_unique<Scene::C_SceneManager>(newEx C_TitleScene);
        if (upSceneManager_->Initialize() == Scene::ecSceneReturn::ERROR_TERMINATION) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return ゲーム続行：true
     *  @return ゲーム終了：false
     *
     ****************************************************************/
    bool C_ConnectWars::Update()
    {
        // ライブラリの更新処理
        if (C_Framework::Update() == false) return false;

        // パーティクルシステムマネージャーの更新処理
        upParticleSystemManager_->Update();

        // メッセージディスパッチャーの更新処理
        upMessageDispatcher_->Update();

        // シーンマネージャーの更新処理
        Scene::ecSceneReturn sceneReturnValue = upSceneManager_->Update();

        if (sceneReturnValue != Scene::ecSceneReturn::CONTINUATIOIN)
        {
            // エラー終了の場合はログを表示する
            if (sceneReturnValue == Scene::ecSceneReturn::ERROR_TERMINATION)
            {
                PrintLog("[ C_ConnectWars::Update ] : ゲームがエラー終了しました。\n");
            }

            return false;
        }

        /* デバッグ時 */
#ifdef _DEBUG

        // エスケープキー入力で強制終了
        if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_ESCAPE) == 1) return false;

#endif

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_ConnectWars::Draw()
    {
        // シーンマネージャーの描画処理
        upSceneManager_->Draw();

        // パーティクルシステムマネージャーの描画処理
        upParticleSystemManager_->Draw();

        // ライブラリの描画処理
        C_Framework::Draw();
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_ConnectWars::Finalize()
    {
        // シーンマネージャーの終了処理
        upSceneManager_->Finalize();

        // パーティクルシステムを全て破棄
        upParticleSystemManager_->AllDestroy();
        
        // ゲームオブジェクトを全て除去
        upGameObjectManager_->AllRemove();

        // Luaステートを全て破棄
        upLuaStateManager_->AllDestroy();

        // ライブラリの終了処理
        C_Framework::Finalize();
    }
}