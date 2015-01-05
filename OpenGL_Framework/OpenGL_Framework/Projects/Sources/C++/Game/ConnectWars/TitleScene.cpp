/* �w�b�_�t�@�C�� */
#include "TitleScene.h"
#include "../../Library/Particle/System/Manager/ParticleSystemManager.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "../../Library/Math/Define/MathDefine.h"
#include "../../Library/Figure/FigureDrawer.h"
#include "../../Library/OpenGL/Manager/OpenGlManager.h"
#include "../../Library/View/ViewHelper.h"
#include "../../Library/Camera/Camera/Perspective/Test/TestCamera.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_TitleScene::C_TitleScene()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_TitleScene::~C_TitleScene()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �Ȃ�
     *  @return ����I���FSUCCESSFUL
     *  @return �ُ�I���FERROR_TERTINATION
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

        Texture::C_TextureManager::s_GetInstance()->Create2DFromFile("Projects/Images/Test/Marisa.png", "Test");
        Particle::C_ParticleSystemManager::s_GetInstance()->Create("Test", spCamera_, Texture::C_TextureManager::s_GetInstance()->GetTextureData("Test").get()->textureHandle_);

        return Scene::ecSceneReturn::SUCCESSFUL;
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return ���s    �FCONTINUATIOIN
     *  @return ����I���FSUCCESSFUL
     *  @return �ُ�I���FERROR_TERTINATION
     *
     ****************************************************************/
    Scene::ecSceneReturn C_TitleScene::Update()
    {
        spCamera_->Update();

        return Scene::ecSceneReturn::CONTINUATIOIN;
    }



    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
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
                
                pParticleSystem->Entry(600, Particle::Vector3(1.0f, 1.0f, 0.0f),  Particle::Vector3(0.0f, 0.05f, 0.0f),  Particle::Vector3(),  Particle::Vector3());
                // pParticleSystem->SetExternalPower(Particle::Vector3(0.001f, 0.0f, 0.0f));
            }
        }
        
        View::C_ViewHelper::s_DrawGrid(5.0f, 1.0f, 11, View::Vector4(1.0f, 1.0f, 1.0f, 0.1f), spCamera_->GetViewProjectionMatrix());
        View::C_ViewHelper::s_DrawAxis(50.0f, spCamera_->GetViewProjectionMatrix());
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TitleScene::Finalize()
    {
    }
}