/* ヘッダファイル */
#include "TitleScene.h"
#include "../../Library/Particle/System/Manager/ParticleSystemManager.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "../../Library/Math/Define/MathDefine.h"
#include "../../Library/Figure/FigureDrawer.h"
#include "../../Library/OpenGL/Manager/OpenGlManager.h"
#include "../../Library/View/ViewHelper.h"
#include "../../Library/Camera/Camera/Perspective/Test/TestCamera.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "../../Library/Debug/String/DebugString.h"
#include "ConnectWarsDefine.h"
#include "../../Library/Camera/Camera/Orthographic/OrthographicCamera.h"


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
        spCamera_ = std::make_shared<Camera::C_TestCamera>();
        spCamera_->SetEyePoint(Camera::Vector3(0.0f, 0.0f, 10.0f));
        spCamera_->SetTargetPoint(Camera::Vector3(0.0f, 0.0f, 0.0f));
        spCamera_->SetFieldOfViewY(static_cast<float>(Math::s_PI_DIVISION4));
        spCamera_->SetNearClippingPlane(1.0f);
        spCamera_->SetFarClippingPlane(1000.0f);
        spCamera_->SetUpVector(Camera::Vector3::s_UP_DIRECTION);
        spCamera_->SetAspectRatio(1024.0f / 768.0f);
        spCamera_->Update();

        auto pOrthograhicCamera = std::make_shared<Camera::C_OrthographicCamera>();
        pOrthograhicCamera->SetClipSpace(0.0f, static_cast<float>(1024), static_cast<float>(768), 0.0f);
        pOrthograhicCamera->Update();

        Camera::C_CameraManager::s_GetInstance()->Entry(spCamera_, ID::Camera::s_pMAIN);

        Texture::C_TextureManager::s_GetInstance()->Create2DFromFile("Projects/Images/Test/Marisa.png", "Test");

        Sprite::C_SpriteCreaterManager::s_GetInstance()->Create("Test", pOrthograhicCamera, Texture::C_TextureManager::s_GetInstance()->GetTextureData("Test").get());

        Particle::C_ParticleSystemManager::s_GetInstance()->Create("Test", spCamera_, Texture::C_TextureManager::s_GetInstance()->GetTextureData("Test").get()->handle_);


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
        spCamera_->Update();

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
        static int32_t count = 0;

        auto pSpriteCreater = Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater("Test").get();
        auto p = pSpriteCreater.lock();
        
        p->SetCameraType(Camera::ORTHOGRAPHIC);
        p->Entry(Sprite::Vector3(100.0f, 100.0f, 0.0f), Sprite::Vector2(100.0f), 0.0f, Sprite::Vector4(1.0f), Sprite::Vector2(0.0f), Sprite::Vector2(128.0f));

        if (count++ % 10 == 0)
        {
            auto wpParticleSystem = Particle::C_ParticleSystemManager::s_GetInstance()->GetParticleSystem("Test").get();

            if (wpParticleSystem.expired() == false)
            {
                auto pParticleSystem = wpParticleSystem.lock();
                
                pParticleSystem->Entry(600, Particle::Vector3(1.0f, 1.0f, 0.0f),  Particle::Vector3(0.0f, 0.05f, 0.0f),  Particle::Vector3(),  Particle::Vector3());
                // pParticleSystem->SetExternalPower(Particle::Vector3(0.001f, 0.0f, 0.0f));
            }
        }
        
        View::C_ViewHelper::s_DrawGrid(5.0f, 1.0f, 11, View::Vector4(1.0f, 1.0f, 1.0f, 0.1f), spCamera_->GetViewProjectionMatrix());
        View::C_ViewHelper::s_DrawAxis(50.0f, spCamera_->GetViewProjectionMatrix());
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
    }
}