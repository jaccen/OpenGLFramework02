/* ヘッダファイル */
#include "Stage01Scene.h"
#include "LoadScene.h"
#include "LoadFunction.h"
#include "ConnectWarsDefine.h"
#include "SpeedUpOption.h"
#include "SmallBeamOption.h"
#include "PlayerBullet.h"
#include "OptionBullet.h"
#include "BombChargeEffect.h"
#include "../../Library/Particle/System/Manager/ParticleSystemManager.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "../../Library/Math/Define/MathDefine.h"
#include "../../Library/Figure/FigureDrawer.h"
#include "../../Library/OpenGL/Manager/OpenGlManager.h"
#include "../../Library/View/ViewHelper.h"
#include "../../Library/Camera/Camera/Perspective/Test/TestCamera.h"
#include "../../Library/Model/SelfMade/Loader/Manager/ModelLoaderManager.h"
#include "../../Library/Camera/Manager/CameraManager.h"
#include "../../Library/OpenGL/Buffer/Primitive/PrimitiveDefine.h"
#include "../../Library/GameObject/Manager/GameObjectManager.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "../../Library/GameObject/Message/Dispatcher/MessageDispatcher.h"



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
        // 残りのロード処理
        if (RemainLoadProcess() == false) return Scene::ecSceneReturn::ERROR_TERMINATION;

        // プレイヤーを生成
        playerGenerator_.Create(ID::Generator::Player::s_pNORMAL);

        // オプションを生成
        optionGenerator_.Create(ID::Generator::Option::s_pSPEED_UP, Physics::Vector3(0.0f, 2.0f, 0.0f));
        optionGenerator_.Create(ID::Generator::Option::s_pSPEED_UP, Physics::Vector3(2.0f, 4.0f, 0.0f));
        optionGenerator_.Create(ID::Generator::Option::s_pSPEED_UP, Physics::Vector3(4.0f, 6.0f, 0.0f));
        optionGenerator_.Create(ID::Generator::Option::s_pSPEED_UP, Physics::Vector3(6.0f, 8.0f, 0.0f));
        
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
        // 衝突確認メッセージを送信
		GameObject::Message::C_MessageDispatcher::s_GetInstance()->Send("Messanger", ID::GameObject::s_pPLAYER, Message::s_pCONNECT_CHECK);

        taskSystem_.Update();

#ifdef _DEBUG

        if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_R) == 1)
        {
            auto pNextScene = newEx C_LoadScene;
            pNextScene->SetLoadFunction(C_LoadFunction::s_LoadStage01Data);
            pNextScene->SetNextSceneId(ID::Scene::s_pSTAGE01);

            GetSceneChanger()->ReplaceScene(pNextScene);
        }


        if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_E) == 1)
        {
            effectGenerator_.Create(ID::Generator::Effect::Bomb::s_pCHARGE, Vector3(0.0f, 0.0f, 0.0f));
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
    void C_Stage01Scene::Draw()
    {
        S_CameraData cameraMatrix;

        cameraMatrix.viewMatrix_ = spMainCamera_->GetViewMatrix();
        cameraMatrix.projectionMatrix_ = spMainCamera_->GetProjectionMatrix();
        cameraMatrix.viewProjectionMatrix_ = spMainCamera_->GetViewProjectionMatrix();

        auto pUniform = Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pMAIN_CAMERA).get();
        pUniform->Rewrite(&cameraMatrix, sizeof(S_CameraData), OpenGL::Modify::s_DYNAMIC);

        taskSystem_.Draw();

        // View::C_ViewHelper::s_DrawGrid(5.0f, 1.0f, 11, View::Vector4(1.0f, 1.0f, 1.0f, 0.1f), spMainCamera_->GetViewProjectionMatrix());
        // View::C_ViewHelper::s_DrawAxis(50.0f, spMainCamera_->GetViewProjectionMatrix());
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
        taskSystem_.AllRemove();
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
    bool C_Stage01Scene::RemainLoadProcess()
    {
        // メインカメラを取得し、情報を設定
        assert(Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pMAIN));
        spMainCamera_ = Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pMAIN).get();

        mainCameraData_.viewMatrix_ = spMainCamera_->GetViewMatrix();
        mainCameraData_.projectionMatrix_ = spMainCamera_->GetProjectionMatrix();
        mainCameraData_.viewProjectionMatrix_ = spMainCamera_->GetViewProjectionMatrix();

        if (!Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pMAIN_CAMERA))
        {
            auto pUniformBuffer = Shader::GLSL::C_UniformBuffer::s_Create(&mainCameraData_, sizeof(S_CameraData), "CameraData", OpenGL::Modify::s_DYNAMIC);
            Shader::GLSL::C_UniformBufferManager::s_GetInstance()->Entry(pUniformBuffer, ID::UniformBuffer::s_pMAIN_CAMERA);
        }

        // 各モデルのバッファを作成
        if (!OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pNORMAL_PLAYER))
        {
            assert(Model::SelfMade::C_ModelLoaderManager::s_GetInstance()->GetModelLoader(ID::Model::s_pNORMAL_PLAYER));
            auto pPlayerModel = Model::SelfMade::C_ModelLoaderManager::s_GetInstance()->GetModelLoader(ID::Model::s_pNORMAL_PLAYER).get();

            // シングルメッシュ前提とする
            auto& rMesh = pPlayerModel->GetMesh(0);

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

            OpenGL::C_PrimitiveBufferManager::s_GetInstance()->Entry(ModelData, ID::Primitive::s_pNORMAL_PLAYER);
        }

        // 各GLSLオブジェクトを作成
        if (!Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pHALF_LAMBERT_PHONG))
        {
            auto pGlslObject = Shader::GLSL::C_GlslObject::s_Create();

            if (pGlslObject->CompileFromFile("Projects/Shaders/GLSL/HalfLambertPhong/HalfLambertPhong.vert", Shader::GLSL::Type::s_VERTEX) == false) return false;
            if (pGlslObject->CompileFromFile("Projects/Shaders/GLSL/HalfLambertPhong/HalfLambertPhong.frag", Shader::GLSL::Type::s_FRAGMENT) == false) return false;
            if (pGlslObject->Link() == false) return false;

            Shader::GLSL::C_GlslObjectManager::s_GetInstance()->Entry(pGlslObject, ID::Shader::s_pHALF_LAMBERT_PHONG);
        }

        // 各テクスチャの作成
        const char* pTexturePathList[] =
        {
            Path::Texture::s_pSPRITE_BULLET,
            Path::Texture::s_pCIRCLE_01,
            Path::Texture::s_pCIRCLE_02,
            Path::Texture::s_pRING_01,
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pTexturePathList); i < arraySize; ++i)
        {
            if (!Texture::C_TextureManager::s_GetInstance()->GetTextureData(pTexturePathList[i]))
            {
                if (Texture::C_TextureManager::s_GetInstance()->Create2DFromFile(pTexturePathList[i]) == false) return false;
            }
        }

        const char* pSpriteIdList[] = 
        {
            ID::Sprite::s_pBULLET,
        };

        const char* pSpriteTextureDataIdList[] =
        {
            Path::Texture::s_pSPRITE_BULLET,
        };

        const float spritePriorityList[] =
        {
            Priority::Sprite::s_BILLBOARD,
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pSpriteIdList); i < arraySize; ++i)
        {
            if (!Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(pSpriteIdList[i]))
            {
                auto pTextureData = Texture::C_TextureManager::s_GetInstance()->GetTextureData(pSpriteTextureDataIdList[i]);
                assert(pTextureData);

                if (Sprite::C_SpriteCreaterManager::s_GetInstance()->Create(pSpriteIdList[i], spMainCamera_, pTextureData.get(), 100, spritePriorityList[i]) == false) return false;
            }
        }

        const char* pParticleTextureDataIdList[] =
        {
            Path::Texture::s_pCIRCLE_01,
            Path::Texture::s_pCIRCLE_02,
            Path::Texture::s_pRING_01,
        };

        const char* pParticleIdList[] = 
        {
            ID::Particle::s_pCIRCLE_01,
            ID::Particle::s_pCIRCLE_02,
            ID::Particle::s_pRING_01,
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pParticleIdList); i < arraySize; ++i)
        {
            if (!Particle::C_ParticleSystemManager::s_GetInstance()->GetParticleSystem(pParticleIdList[i]))
            {
                auto pTextureData = Texture::C_TextureManager::s_GetInstance()->GetTextureData(pParticleTextureDataIdList[i]);
                assert(pTextureData);

                if (Particle::C_ParticleSystemManager::s_GetInstance()->Create(pParticleIdList[i], spMainCamera_, pTextureData.get()->handle_) == false) return false;
            }
        }

        // プレイヤーの生成機の設定
        playerGenerator_.SetTaskSystem(&taskSystem_);

        // オプション生成機の設定
        optionGenerator_.SetTaskSystem(&taskSystem_);
        optionGenerator_.RegistFunction(ID::Generator::Option::s_pSPEED_UP, []()->C_BaseOption*{ return newEx C_SpeedUpOption(ID::GameObject::s_pOPTION, TYPE_OPTION); });
        optionGenerator_.RegistFunction(ID::Generator::Option::s_pSMALL_BEAM, []()->C_BaseOption*{ return newEx C_SmallBeamOption(ID::GameObject::s_pOPTION, TYPE_OPTION); });

        // 弾生成機の設定
        bulletGenerator_.SetTaskSystem(&taskSystem_);
        bulletGenerator_.RegistFunction(ID::Generator::Bullet::Player::s_pBEAM, [](int32_t shooterType)->C_BaseBullet*{ return newEx C_PlayerBeamBullet(ID::GameObject::s_pBULLET, TYPE_BULLET, shooterType); });
        bulletGenerator_.RegistFunction(ID::Generator::Bullet::Option::s_pSMALL_BEAM, [](int32_t shooterType)->C_BaseBullet*{ return newEx C_PlayerBeamBullet(ID::GameObject::s_pBULLET, TYPE_BULLET, shooterType); });

        // エフェクト生成機の設定
        effectGenerator_.SetTaskSystem(&taskSystem_);
        effectGenerator_.RegistFunction(ID::Generator::Effect::Bomb::s_pCHARGE, []()->C_BaseEffect*{ return newEx C_BombChargeEffect(ID::GameObject::s_pEFFECT, TYPE_EFFECT); });

        return true;
    }
}