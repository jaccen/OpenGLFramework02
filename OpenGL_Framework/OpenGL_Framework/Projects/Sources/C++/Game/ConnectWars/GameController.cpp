/* ヘッダファイル */
#include "GameController.h"
#include "PauseScene.h"
#include "../../Library/Input/Keyboard/KeyboardManager.h"
#include "../../Library/Input/Gamepad/Manager/GamepadManager.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"
#include "../../Library/Debug//String/DebugString.h"
#include "../../Library/Particle/System/Manager/ParticleSystemManager.h"


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
     *  @param  ID
     *  @param  種類
     *
     ****************************************************************/
    C_GameController::C_GameController(const std::string& rId, int32_t type) : C_SceneController(rId, type)
    {
        upFade_ = std::make_unique<C_Fade>(ID::GameObject::s_pFADE, eGameObjectType::TYPE_FADE, 30, true);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_GameController::~C_GameController()
    {
    }


    /*************************************************************//**
     *
     *  @brief  非公開の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_GameController::DoUpdate()
    {
        static auto isPauseButtonFunction = [&]()
        {
            if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_C) == 1
             || Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_START) == 1)
            {
                return true;
            }

            return false;
        };

        if (isPauseButtonFunction() == true)
        {
            assert(pSceneChanger_);
            pSceneChanger_->PushScene(newEx C_PauseScene);
            
            // 物理エンジンの更新を停止
            Physics::C_PhysicsEngine::s_GetInstance()->EnableActive(false);

            // パーティクルシステムの更新を停止
            Particle::C_ParticleSystemManager::s_GetInstance()->EnableActive(false);
        }

        pBackgroundGenerator_->AutoCreate(frameCounter_.GetCount());

        upFade_->Update();
    }
    

    /*************************************************************//**
     *
     *  @brief  非公開の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_GameController::DoDraw()
    {
        upFade_->Draw();

        std::cout << frameCounter_.GetCount() << std::endl;
    }


    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_GameController::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }


    /*************************************************************//**
     *
     *  @brief  バックグラウンドジェネレータを設定する
     *  @param  バックグラウンドジェネレータ
     *  @return なし
     *
     ****************************************************************/
    void C_GameController::SetBackgroundGenerator(C_BackgroundGenerator* pBackgroundGenerator)
    {
        pBackgroundGenerator_ = pBackgroundGenerator;
    }


    /*************************************************************//**
     *
     *  @brief  エネミージェネレータを設定する
     *  @param  エネミージェネレータ
     *  @return なし
     *
     ****************************************************************/
    void C_GameController::SetEnemyGenerator(C_EnemyGenerator* pEnemyGenerator)
    {
        pEnemyGenerator_ = pEnemyGenerator;
    }
}