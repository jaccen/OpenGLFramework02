/* wb_t@C */
#include "TitleScene.h"
#include "../../Library/Particle/System/Manager/ParticleSystemManager.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "../../Library/Math/Define/MathDefine.h"
#include "../../Library/Figure/FigureDrawer.h"
#include "../../Library/OpenGL/Manager/OpenGlManager.h"
#include "../../Library/View/ViewHelper.h"
#include "../../Library/Camera/Camera/Perspective/Test/TestCamera.h"
<<<<<<< HEAD
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "../../Library/Debug/String/DebugString.h"
#include "ConnectWarsDefine.h"
#include "../../Library/Camera/Camera/Orthographic/OrthographicCamera.h"
=======
>>>>>>> parent of f268703... ã¹ãã©ã¤ãã¯ãªã¨ã¤ã¿ã¼ããã¼ã¸ã£ã¼ãã¹ãå®äº


//-------------------------------------------------------------
//!
//! @brief RlNgEH[Y
//! @brief RlNgEH[YÖAÌ¼OóÔ
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  RXgN^
     *  @param  Èµ
     *
     ****************************************************************/
    C_TitleScene::C_TitleScene()
    {
    }


    /*************************************************************//**
     *
     *  @brief  fXgN^
     *  @param  Èµ
     *
     ****************************************************************/
    C_TitleScene::~C_TitleScene()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ú»ðs¤
     *  @param  Èµ
     *  @return ³íI¹FSUCCESSFUL
     *  @return ÙíI¹FERROR_TERTINATION
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
<<<<<<< HEAD
        Sprite::C_SpriteCreaterManager::s_GetInstance()->Create("Test", pOrthograhicCamera, Texture::C_TextureManager::s_GetInstance()->GetTextureData("Test").get());
=======
        Particle::C_ParticleSystemManager::s_GetInstance()->Create("Test", spCamera_, Texture::C_TextureManager::s_GetInstance()->GetTextureData("Test").get()->handle_);
>>>>>>> parent of f268703... ã¹ãã©ã¤ãã¯ãªã¨ã¤ã¿ã¼ããã¼ã¸ã£ã¼ãã¹ãå®äº

        return Scene::ecSceneReturn::SUCCESSFUL;
    }


    /*************************************************************//**
     *
     *  @brief  XVðs¤
     *  @param  Èµ
     *  @return ±s    FCONTINUATIOIN
     *  @return ³íI¹FSUCCESSFUL
     *  @return ÙíI¹FERROR_TERTINATION
     *
     ****************************************************************/
    Scene::ecSceneReturn C_TitleScene::Update()
    {
        spCamera_->Update();

        return Scene::ecSceneReturn::CONTINUATIOIN;
    }



    /*************************************************************//**
     *
     *  @brief  XVðs¤
     *  @param  Èµ
     *  @return Èµ
     *
     ****************************************************************/
    void C_TitleScene::Draw()
    {
        static int32_t count = 0;

<<<<<<< HEAD
        auto pSpriteCreater = Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater("Test").get();
        auto p = pSpriteCreater.lock();
        
        p->SetCameraType(Camera::ORTHOGRAPHIC);
        p->Entry(Sprite::Vector3(100.0f, 100.0f, 0.0f), Sprite::Vector2(100.0f), 0.0f, Sprite::Vector4(1.0f), Sprite::Vector2(0.0f), Sprite::Vector2(128.0f));

=======
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
        
>>>>>>> parent of f268703... ã¹ãã©ã¤ãã¯ãªã¨ã¤ã¿ã¼ããã¼ã¸ã£ã¼ãã¹ãå®äº
        View::C_ViewHelper::s_DrawGrid(5.0f, 1.0f, 11, View::Vector4(1.0f, 1.0f, 1.0f, 0.1f), spCamera_->GetViewProjectionMatrix());
        View::C_ViewHelper::s_DrawAxis(50.0f, spCamera_->GetViewProjectionMatrix());
    }


    /*************************************************************//**
     *
     *  @brief  I¹ðs¤
     *  @param  Èµ
     *  @return Èµ
     *
     ****************************************************************/
    void C_TitleScene::Finalize()
    {
    }
}