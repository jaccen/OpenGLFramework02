/* ヘッダファイル */
#include "Stage01Scene.h"
#include "ConnectWarsDefine.h"
#include "../../Library/Particle/System/Manager/ParticleSystemManager.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "../../Library/Math/Define/MathDefine.h"
#include "../../Library/Figure/FigureDrawer.h"
#include "../../Library/OpenGL/Manager/OpenGlManager.h"
#include "../../Library/View/ViewHelper.h"
#include "../../Library/Camera/Manager/CameraManager.h"
#include "../../Library/Camera/Camera/Perspective/Test/TestCamera.h"
#include "../../Library/Window/Manager/WindowManager.h"
#include "../../Library/Shader/GLSL/Uniform/Manager/UniformBufferManager.h"
#include "../../Library/Model/SelfMade/Loader/ModelLoader.h"
#include "../../Library/OpenGL/Buffer/Primitive/PrimitiveDefine.h"


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
    C_Stage01Scene::C_Stage01Scene()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_Stage01Scene::~C_Stage01Scene()
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
    Scene::ecSceneReturn C_Stage01Scene::Initialize()
    {
        if (!upTaskSystem_)
        {
            upTaskSystem_ = std::make_unique<Task::C_GeneralTaskSystem>();
        }

        spCamera_ = std::make_shared<Camera::C_PerspectiveCamera>();
        spCamera_->SetEyePoint(Camera::Vector3(0.0f, 0.0f, 28.0f));
        spCamera_->SetTargetPoint(Camera::Vector3(0.0f, 0.0f, 0.0f));
        spCamera_->SetFieldOfViewY(static_cast<float>(Math::s_PI_DIVISION4));
        spCamera_->SetNearClippingPlane(1.0f);
        spCamera_->SetFarClippingPlane(1000.0f);
        spCamera_->SetUpVector(Camera::Vector3::s_UP_DIRECTION);
        spCamera_->SetAspectRatio(1024.0f / 768.0f);
        spCamera_->Update();

        Camera::C_CameraManager::s_GetInstance()->Entry(spCamera_, "MainCamera");

        S_CameraData cameraMatrix;

        cameraMatrix.viewMatrix_ = spCamera_->GetViewMatrix();
        cameraMatrix.projectionMatrix_ = spCamera_->GetProjectionMatrix();
        cameraMatrix.viewProjectionMatrix_ = spCamera_->GetViewProjectionMatrix();
        
        auto pUniformBuffer = Shader::GLSL::C_UniformBuffer::s_Create(&cameraMatrix, sizeof(S_CameraData), "CameraData", OpenGL::Modify::s_DYNAMIC);
        Shader::GLSL::C_UniformBufferManager::s_GetInstance()->Entry(pUniformBuffer, "CameraData");

        // 球形状を性生成
        Model::SelfMade::C_ModelLoader modelLoader;
        modelLoader.LoadModel("Projects/Models/Test/Sphere/Sphere.model");
        auto& rMesh = modelLoader.GetMesh(0);

        uint32_t vertexCount = rMesh.vertices_.size();
        std::vector<OpenGL::S_VertexPNT> vertices(vertexCount);

        for (size_t i = 0; i < vertexCount; ++i)
        {
            vertices[i].position_ = rMesh.vertices_[i].position_;
            vertices[i].normal_ = rMesh.vertices_[i].normal_;
            vertices[i].textureCoord_ = rMesh.vertices_[i].textureCoord_;
        }

        uint32_t vertexAttributeElementCountList[] = { 3, 3, 2 };
        OpenGL::DataEnum vertexAttributeDataTypeList[] = { OpenGL::DataType::s_FLOAT, OpenGL::DataType::s_FLOAT, OpenGL::DataType::s_FLOAT };
        
        auto ModelData = OpenGL::C_PrimitiveBuffer::s_Create(vertices.data(),
                                                             vertexCount,
                                                             3,
                                                             vertexAttributeElementCountList,
                                                             vertexAttributeDataTypeList,
                                                             OpenGL::Modify::s_STATIC,
                                                             rMesh.indices_.data(),
                                                             rMesh.indices_.size(),
                                                             OpenGL::Modify::s_STATIC);

        OpenGL::C_PrimitiveBufferManager::s_GetInstance()->Entry(ModelData, "Sphere");

        auto pGlslObject = Shader::GLSL::C_GlslObject::s_Create();

        pGlslObject->CompileFromFile("Projects/Shaders/GLSL/HalfLambert/HalfLambert.vert", Shader::GLSL::Type::s_VERTEX);
        pGlslObject->CompileFromFile("Projects/Shaders/GLSL/HalfLambert/HalfLambert.frag", Shader::GLSL::Type::s_FRAGMENT);
        pGlslObject->Link();

        Shader::GLSL::C_GlslObjectManager::s_GetInstance()->Entry(pGlslObject, "HalfLambert");

        upPlayer_ = std::make_unique<C_BasePlayer>("Player", 0);

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
    Scene::ecSceneReturn C_Stage01Scene::Update()
    {
        upTaskSystem_->Update();
        upPlayer_->Update();

        return Scene::ecSceneReturn::CONTINUATIOIN;
    }



    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_Stage01Scene::Draw()
    {
        S_CameraData cameraMatrix;

        cameraMatrix.viewMatrix_ = spCamera_->GetViewMatrix();
        cameraMatrix.projectionMatrix_ = spCamera_->GetProjectionMatrix();
        cameraMatrix.viewProjectionMatrix_ = spCamera_->GetViewProjectionMatrix();

        auto pUniform = Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer("CameraData").get();
        pUniform->Rewrite(&cameraMatrix, sizeof(S_CameraData), OpenGL::Modify::s_DYNAMIC);

        upTaskSystem_->Draw();
        upPlayer_->Draw();

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
    void C_Stage01Scene::Finalize()
    {
    }
}