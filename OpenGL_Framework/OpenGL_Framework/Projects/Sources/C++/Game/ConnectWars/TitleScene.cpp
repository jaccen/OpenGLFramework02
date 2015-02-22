/* ヘッダファイル */
#include "TitleScene.h"
#include "RootScene.h"
#include "ConnectWarsDefine.h"
#include "TitleUi.h"
#include "TitleController.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "../../Library/Sprite/Creater/SpriteCreater.h"
#include "../../Library/Common/CommonHelper.h"
#include "../../Library/Input/Keyboard/KeyboardManager.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/GameObject/Manager/GameObjectManager.h"


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
    C_TitleScene::C_TitleScene()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_TitleScene::~C_TitleScene()
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
    Scene::ecSceneReturn C_TitleScene::Initialize()
    {
        if (RemainLoadProcess() == false) return Scene::ecSceneReturn::ERROR_TERMINATION;

        // タイトルUIを登録
        auto pTitleUi = std::make_shared<C_TitleUi>(ID::GameObject::s_pUI, TYPE_UI);
        taskSystem_.Entry(pTitleUi,  Priority::Task::Update::s_ui, Priority::Task::Draw::s_ui);
        GameObject::C_GameObjectManager::s_GetInstance()->Entry(pTitleUi);

        // タイトルコントローラを登録
        auto pTitleController = std::make_shared<C_TitleController>(ID::GameObject::s_pSCENE_CONTROLLER, TYPE_SCENE_CONTROLLER);
        taskSystem_.Entry(pTitleController, Priority::Task::Update::s_sceneController, Priority::Task::Draw::s_sceneController);
        pTitleController->SetSceneChanger(GetSceneChanger());
        GameObject::C_GameObjectManager::s_GetInstance()->Entry(pTitleController);

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
    Scene::ecSceneReturn C_TitleScene::Update()
    {
        taskSystem_.Update();

        #ifdef _DEBUG

        if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_R) == 1)
        {
            auto pNextScene = newEx C_RootScene;
            //pNextScene->SetLoadFunction(C_LoadFunction::s_LoadStage01Data);
            //pNextScene->SetNextSceneId(ID::Scene::s_pSTAGE01);

            GetSceneChanger()->PopScene();
            GetSceneChanger()->ReplaceScene(pNextScene);
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
    void C_TitleScene::Draw()
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
    void C_TitleScene::Finalize()
    {
        JSON::C_JsonObjectManager::s_GetInstance()->AllRemove();
        GameObject::C_GameObjectManager::s_GetInstance()->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  残りのロード処理を行う
     *  @param  なし
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_TitleScene::RemainLoadProcess()
    {
        // UI用カメラを取得
        assert(Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pUI));
        pUiCamera_ = Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pUI).get();

        // 各テクスチャの作成
        const char* pTexturePathList[] =
        {
            Path::Texture::s_pTITLE_BACKGROUND,
            Path::Texture::s_pTITLE_UI,
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
            ID::Sprite::s_pTITLE_BACKGROUND,
            ID::Sprite::s_pTITLE_UI,
        };

        const char* pSpriteTextureDataIdList[] =
        {
            Path::Texture::s_pTITLE_BACKGROUND,
            Path::Texture::s_pTITLE_UI,
        };

        const float spritePriorityList[] =
        {
            Priority::Sprite::s_BACKGROUND,
            Priority::Sprite::s_IMAGE_UI
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