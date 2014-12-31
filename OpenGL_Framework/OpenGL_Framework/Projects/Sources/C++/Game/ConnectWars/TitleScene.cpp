/* ヘッダファイル */
#include "TitleScene.h"
#include "../../Library/Particle/System/Manager/ParticleSystemManager.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "../../Library/Math/Define/MathDefine.h"

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
        spCamera_ = std::make_shared<Camera::C_PerspectiveCamera>();
        spCamera_->SetEyePoint(Camera::Vector3(0.0f, 0.0f, 10.0f));
        spCamera_->SetTargetPoint(Camera::Vector3(0.0f, 0.0f, 0.0f));
        spCamera_->SetFieldOfViewY(Math::s_PI_DIVISION4);
        spCamera_->SetNearClippingPlane(1.0f);
        spCamera_->SetFarClippingPlane(1000.0f);
        spCamera_->SetUpVector(Camera::Vector3::s_UP_DIRECTION);
        spCamera_->SetAspectRatio(1024.0f / 768.0f);
        spCamera_->Update();

        Texture::C_TextureManager::s_GetInstance()->Create2DFromFile("Projects/Images/Test/Marisa.png", "Test");
        Particle::C_ParticleSystemManager::s_GetInstance()->Create("Test", spCamera_, Texture::C_TextureManager::s_GetInstance()->GetTextureData("Test").get()->textureHandle_);

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

        if (count++ % 10 == 0)
        {
            auto wpParticleSystem = Particle::C_ParticleSystemManager::s_GetInstance()->GetParticleSystem("Test").get();

            if (wpParticleSystem.expired() == false)
            {
                auto pParticleSystem = wpParticleSystem.lock();
                pParticleSystem->Entry(60, Particle::Vector3(1.0f, 1.0f, 0.0f),  Particle::Vector3(0.0f, 0.05f, 0.0f),  Particle::Vector3(),  Particle::Vector3(), 1.57f, -1.57f);
                // pParticleSystem->SetExternalPower(Particle::Vector3(0.001f, 0.0f, 0.0f));
            }
        }
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