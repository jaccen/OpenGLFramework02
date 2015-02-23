/* ヘッダファイル */
#include "PauseScene.h"
#include "RootScene.h"
#include "ConnectWarsDefine.h"
#include "PauseUi.h"
#include "PauseController.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "../../Library/Sprite/Creater/SpriteCreater.h"
#include "../../Library/Common/CommonHelper.h"
#include "../../Library/Input/Keyboard/KeyboardManager.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/GameObject/Manager/GameObjectManager.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"


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
    C_PauseScene::C_PauseScene()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PauseScene::~C_PauseScene()
    {
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  なし
     *  @return 正常終了：SUCCESSFUL
     *  @return 異常終了：ERROR_TERTINATION
     *
     ****************************************************************/
    Scene::ecSceneReturn C_PauseScene::Initialize()
    {
        if (RemainLoadProcess() == false) return Scene::ecSceneReturn::ERROR_TERMINATION;

        taskSystem_.Entry(std::make_shared<C_PauseUi>(ID::GameObject::s_pPAUSE_UI, TYPE_UI), Priority::Task::Update::s_ui, Priority::Task::Draw::s_ui);
        
        auto pPauseController = std::make_shared<C_PauseController>(ID::GameObject::s_pPAUSE_CONTROLLER, TYPE_SCENE_CONTROLLER);
        taskSystem_.Entry(pPauseController, Priority::Task::Update::s_sceneController, Priority::Task::Draw::s_sceneController);
        pPauseController->SetSceneChanger(GetSceneChanger());
        GameObject::C_GameObjectManager::s_GetInstance()->Entry(pPauseController);
        pPauseController->SetSceneChanger(GetSceneChanger());

        return Scene::ecSceneReturn::SUCCESSFUL;
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return 続行    ：CONTINUATIOIN
     *  @return 正常終了：SUCCESSFUL
     *  @return 異常終了：ERROR_TERTINATION
     *
     ****************************************************************/
    Scene::ecSceneReturn C_PauseScene::Update()
    {
        taskSystem_.Update();

#ifdef _DEBUG


        if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_R) == 1)
        {
            auto pNextScene = newEx C_RootScene;

            GetSceneChanger()->PopScene();
            GetSceneChanger()->PopScene();
            GetSceneChanger()->ReplaceScene(pNextScene);

            Physics::C_PhysicsEngine::s_GetInstance()->EnableActive(true);
        }


#endif

        return Scene::ecSceneReturn::CONTINUATIOIN;
    }



    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PauseScene::Draw()
    {
        taskSystem_.Draw();
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PauseScene::Finalize()
    {
        GameObject::C_GameObjectManager::s_GetInstance()->Remove(ID::GameObject::s_pPAUSE_CONTROLLER);
    }


    /*************************************************************//**
     *
     *  @brief  残りのロード処理を行う
     *  @param  なし
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_PauseScene::RemainLoadProcess()
    {
        // UI用カメラを取得
        assert(Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pUI));
        pUiCamera_ = Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pUI).get();

        // 各テクスチャの作成
        const char* pTexturePathList[] =
        {
            Path::Texture::s_pPAUSE_BACKGROUND,
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pTexturePathList); i < arraySize; ++i)
        {
            if (!Texture::C_TextureManager::s_GetInstance()->GetTextureData(pTexturePathList[i]))
            {
                if (Texture::C_TextureManager::s_GetInstance()->Create2DFromFile(pTexturePathList[i]) == false) return false;
            }
        }

        // 各スプライトクリエイターを作成
        const char* pSpriteIdList[] = 
        {
            ID::Sprite::s_pPAUSE_BACKGROUND,
        };

        const char* pSpriteTextureDataIdList[] =
        {
            Path::Texture::s_pPAUSE_BACKGROUND,
        };

        const float spritePriorityList[] =
        {
            Priority::Sprite::s_BACKGROUND,
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pSpriteIdList); i < arraySize; ++i)
        {
            if (!Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(pSpriteIdList[i]))
            {
                auto pTextureData = Texture::C_TextureManager::s_GetInstance()->GetTextureData(pSpriteTextureDataIdList[i]);
                assert(pTextureData);

                if (Sprite::C_SpriteCreaterManager::s_GetInstance()->Create(pSpriteIdList[i], pUiCamera_, pTextureData.get(), 3, spritePriorityList[i]) == false) return false;
               
                // カメラのタイプを正投影に設定
                auto pSpriteCreater = Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(pSpriteIdList[i]).get().lock();
                pSpriteCreater->SetCameraType(Camera::ORTHOGRAPHIC);
            }
        }

        Sprite::C_SpriteCreaterManager::s_GetInstance()->Sort();

        return true;
    }
}