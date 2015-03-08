/* ヘッダファイル */
#include "Stage01Scene.h"
#include "LoadScene.h"
#include "RootScene.h"
#include "LoadFunction.h"
#include "ConnectWarsDefine.h"
#include "SpeedUpOption.h"
#include "SmallBeamOption.h"
#include "PlayerBullet.h"
#include "OptionBullet.h"
#include "NormalBombChargeEffect.h"
#include "BoxEnemy.h"
#include "Space.h"
#include "Shelter.h"
#include "CameraController.h"
#include "ExitRing.h"
#include "Earth.h"
#include "BackgroundMeteor.h"
#include "GameUi.h"
#include "BoxEnemy.h"
#include "PlayerFlarebackEffect.h"
#include "ConnectEffect.h"
#include "PlayerExplosionEffect.h"
#include "OptionExplosionEffect.h"
#include "PlayerBeamCollisionEffect.h"
#include "OptionSmallBeamCollisionEffect.h"
#include "NormalBombEffect.h"
#include "NormalBomb.h"
#include "OptionOwnCrashEffect01.h"
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

        // ジェネレータの設定
        SetupGenerator();

        // ゲームコントローラを生成
        auto pGameController = std::make_shared<C_GameController>(ID::GameObject::s_pSCENE_CONTROLLER, TYPE_SCENE_CONTROLLER);
        taskSystem_.Entry(pGameController, Priority::Task::Update::s_sceneController, Priority::Task::Draw::s_sceneController);
        pGameController->SetSceneChanger(GetSceneChanger());
        GameObject::C_GameObjectManager::s_GetInstance()->Entry(pGameController);
        pGameController->SetBackgroundGenerator(&backgroundGenerator_);

        // カメラコントローラを生成
        auto pCameraController = taskSystem_.Entry(std::make_shared<C_CameraController>(ID::GameObject::s_pCAMERA_CONTROLLER, TYPE_CAMERA_CONTROLLER), Priority::Task::Update::s_cameraController, Priority::Task::Draw::s_cameraController);

        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSTAGE_01_CAMERAWORK_DATA));
        pCameraController->SetCameraData(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSTAGE_01_CAMERAWORK_DATA).get());
        // pCameraController->SetNowFrame(1349);
        // pCameraController->SetIndex(7, ecCameraDataType::BACKGROUND_EYE_POINT);
        // pCameraController->SetIndex(10, ecCameraDataType::BACKGROUND_TARGET_POINT);
        pCameraController->Update();

        // ゲームUIの生成
        auto pGameUi = std::make_shared<C_GameUi>(ID::GameObject::s_pUI, TYPE_UI);
        taskSystem_.Entry(pGameUi, Priority::Task::Update::s_ui, Priority::Task::Draw::s_ui);
        GameObject::C_GameObjectManager::s_GetInstance()->Entry(pGameUi);


        // プレイヤーを生成
        playerGenerator_.Create(ID::Generator::Player::s_pNORMAL);

        // オプションを生成
        optionGenerator_.Create(ID::Generator::Option::s_pSPEED_UP, Physics::Vector3(2.0f, 4.0f, 0.0f));
        optionGenerator_.Create(ID::Generator::Option::s_pSPEED_UP, Physics::Vector3(4.0f, 6.0f, 0.0f));
        optionGenerator_.Create(ID::Generator::Option::s_pSPEED_UP, Physics::Vector3(6.0f, 8.0f, 0.0f));

        optionGenerator_.Create(ID::Generator::Option::s_pSMALL_BEAM, Physics::Vector3(-5.0f, 0.0f, 0.0f));
        optionGenerator_.Create(ID::Generator::Option::s_pSMALL_BEAM, Physics::Vector3(-10.0f, 0.0f, 0.0f));
        optionGenerator_.Create(ID::Generator::Option::s_pSMALL_BEAM, Physics::Vector3(-5.0f, 20.0f, 0.0f));
        optionGenerator_.Create(ID::Generator::Option::s_pSMALL_BEAM, Physics::Vector3(-5.0f, 30.0f, 0.0f));
        optionGenerator_.Create(ID::Generator::Option::s_pSMALL_BEAM, Physics::Vector3(-5.0f, 40.0f, 0.0f));
        optionGenerator_.Create(ID::Generator::Option::s_pSMALL_BEAM, Physics::Vector3(5.0f, 0.0f, 0.0f));
        optionGenerator_.Create(ID::Generator::Option::s_pSMALL_BEAM, Physics::Vector3(10.0f, 0.0f, 0.0f));
        optionGenerator_.Create(ID::Generator::Option::s_pSMALL_BEAM, Physics::Vector3(-5.0f, 5.0f, 0.0f));
        optionGenerator_.Create(ID::Generator::Option::s_pSMALL_BEAM, Physics::Vector3(-5.0f,10.0f, 0.0f));
        optionGenerator_.Create(ID::Generator::Option::s_pSMALL_BEAM, Physics::Vector3(-5.0f,15.0f, 0.0f));

        // enemyGenerator_.Create(ID::Generator::Enemy::s_pBOX);
        
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
            auto pNextScene = newEx C_RootScene;

            GetSceneChanger()->PopScene();
            GetSceneChanger()->ReplaceScene(pNextScene);
        }


#endif

        if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_E) == 1)
        {
            effectGenerator_.Create(ID::Generator::Effect::s_pOPTION_OWN_CRASH_01, Vector3());
        }

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
        taskSystem_.Draw();
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

        JSON::C_JsonObjectManager::s_GetInstance()->AllRemove();
        Model::SelfMade::C_ModelLoaderManager::s_GetInstance()->AllRemove();

        Light::C_LightManager::s_GetInstance()->AllRemove();
        Material::C_MaterialManager::s_GetInstance()->AllRemove();
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
        // 各ユニフォームバッファを作成
        const char* pCameraIdList[] =
        {
            ID::Camera::s_pMAIN,
            ID::Camera::s_pBACKGROUND,
        };

        const char* pUniformBufferIdList[] =
        {
            ID::UniformBuffer::s_pMAIN_CAMERA,
            ID::UniformBuffer::s_pBACKGROUND_CAMERA,
        };

        const char* pUniformBlockNameList[] =
        {
            "MainCameraData",
            "BackgroundCamera"
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pCameraIdList); i < arraySize; ++i)
        {
            if (!Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(pUniformBufferIdList[i]))
            {
                assert(Camera::C_CameraManager::s_GetInstance()->GetCamera(pCameraIdList[i]));
                auto pCamera = Camera::C_CameraManager::s_GetInstance()->GetCamera(pCameraIdList[i]).get();

                 S_CameraData cameraData;

                cameraData.viewMatrix_ = pCamera->GetViewMatrix();
                cameraData.projectionMatrix_ = pCamera->GetProjectionMatrix();
                cameraData.viewProjectionMatrix_ = pCamera->GetViewProjectionMatrix();

                auto pUniformBuffer = Shader::GLSL::C_UniformBuffer::s_Create(&cameraData, sizeof(S_CameraData), pUniformBlockNameList[i], OpenGL::Modify::s_DYNAMIC);
                Shader::GLSL::C_UniformBufferManager::s_GetInstance()->Entry(pUniformBuffer, pUniformBufferIdList[i]);
            }
        }

        // メインカメラを取得
        assert(Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pMAIN));
        pMainCamera_ = Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pMAIN).get();

        // UI用カメラを取得
        assert(Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pUI));
        pUiCamera_ = Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pUI).get();

        // 各モデルのバッファを作成
        const char* pPrimitiveIdList[] =
        {
            ID::Primitive::s_pNORMAL_PLAYER,
            ID::Primitive::s_pBOX_ENEMY,
            ID::Primitive::s_pSPACE,
            ID::Primitive::s_pSHELTER,
            ID::Primitive::s_pSPEED_UP_OPTION,
            ID::Primitive::s_pSMALL_BEAM_OPTION,
            ID::Primitive::s_pEXIT_RING,
            ID::Primitive::s_pMETEOR,
            ID::Primitive::s_pROCK,
            ID::Primitive::s_pBACKGROUND_METEOR,
        };

        const char* pModelIdList[] = 
        {
            ID::Model::s_pNORMAL_PLAYER,
            ID::Model::s_pBOX_ENEMY,
            ID::Model::s_pSPACE,
            ID::Model::s_pSHELTER,
            ID::Model::s_pSPPED_UP_OPTION,
            ID::Model::s_pSMALL_BEAM_OPTION,
            ID::Model::s_pEXIT_RING,
            ID::Model::s_pMETEOR,
            ID::Model::s_pROCK,
            ID::Model::s_pMETEOR,
        };

        bool vertexTransferFlagList[][7] =
        {
            { true, true, true, false, false, false, false },       // ノーマルプレイヤー
            { true, true, false, false, false, false, false },      // ボックスエネミー
            { true, false, true, false, false, false, false },      // 宇宙
            { true, true, true, false, true, false, false },        // シェルター
            { true, true, true, false, false, false, false },       // スピードアップオプション
            { true, true, true, false, false, false, false },       // スモールビームオプション
            { true, true, false, false, false, false, false },      // エグジットリング
            { true, true, true, false, true, false, false },        // 隕石
            { true, true, true, false, true, false, false },        // 岩
            { true, true, true, false, false, false, false },       // 背景隕石
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pPrimitiveIdList); i < arraySize; ++i)
        {
            if (!OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(pPrimitiveIdList[i]))
            {
                assert(Model::SelfMade::C_ModelLoaderManager::s_GetInstance()->GetModelLoader(pModelIdList[i]));
                auto pModelData = Model::SelfMade::C_ModelLoaderManager::s_GetInstance()->GetModelLoader(pModelIdList[i]).get();

                // シングルメッシュ前提とする
                auto& rMesh = pModelData->GetMesh(0);

                uint32_t vertexAttributeElementCountList[] = { 3, 3, 2, 4, 4, 4, 4 };
                uint32_t vertexByteOffsetFlag[] = { 4, 4, 4, 4, 4, 1, 4 };

                OpenGL::DataEnum vertexAttributeDataTypeList[] =
                {
                    OpenGL::DataType::s_FLOAT,
                    OpenGL::DataType::s_FLOAT,
                    OpenGL::DataType::s_FLOAT,
                    OpenGL::DataType::s_FLOAT,
                    OpenGL::DataType::s_FLOAT,
                    OpenGL::DataType::s_INT,
                    OpenGL::DataType::s_FLOAT,
                };

                auto pModelBuffer = OpenGL::C_PrimitiveBuffer::s_Create(rMesh.vertices_.data(),
                                                                        rMesh.vertices_.size(),
                                                                        7,
                                                                        vertexAttributeElementCountList,
                                                                        vertexAttributeDataTypeList,
                                                                        OpenGL::Modify::s_STATIC,
                                                                        vertexByteOffsetFlag,
                                                                        vertexTransferFlagList[i],
                                                                        rMesh.indices_.data(),
                                                                        rMesh.indices_.size(),
                                                                        OpenGL::Modify::s_STATIC);

                OpenGL::C_PrimitiveBufferManager::s_GetInstance()->Entry(pModelBuffer, pPrimitiveIdList[i]);
            }
        }

        // 各GLSLオブジェクトを作成
        const char* pGlslObjectIdList[] =
        {
            ID::Shader::s_pPHONG,
            ID::Shader::s_pPHONG_TEXTURE,
            ID::Shader::s_pCELESTIAL_SPHERE,
            ID::Shader::s_pPHONG_NORMAL_TEXTURE,
        };

        const char* pVertexShaderPathList[] = 
        {
            Path::Shader::Vertex::s_pPHONG,
            Path::Shader::Vertex::s_pPHONG_TEXTURE,
            Path::Shader::Vertex::s_pCELESTINAL_SPHERE,
            Path::Shader::Vertex::s_pPHONG_NORMAL_TEXTURE,
        };


        const char* pFragmentShaderPathList[] =
        {
            Path::Shader::Fragment::s_pPHONG,
            Path::Shader::Fragment::s_pPHONG_TEXTURE,
            Path::Shader::Fragment::s_pCELESTINAL_SPHERE,
            Path::Shader::Fragment::s_pPHONG_NORMAL_TEXTURE,
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pGlslObjectIdList); i < arraySize; ++i)
        {
            if (!Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(pGlslObjectIdList[i]))
            {
                auto pGlslObject = Shader::GLSL::C_GlslObject::s_Create();

                if (pGlslObject->CompileFromFile(pVertexShaderPathList[i], Shader::GLSL::Type::s_VERTEX) == false) return false;
                if (pGlslObject->CompileFromFile(pFragmentShaderPathList[i], Shader::GLSL::Type::s_FRAGMENT) == false) return false;
                if (pGlslObject->Link() == false) return false;

                Shader::GLSL::C_GlslObjectManager::s_GetInstance()->Entry(pGlslObject, pGlslObjectIdList[i]);
            }
        }

        // 各テクスチャの作成
        const char* pTexturePathList[] =
        {
            Path::Texture::s_pNORMAL_PLAYER,
            Path::Texture::s_pSPRITE_BULLET,
            Path::Texture::s_pCIRCLE_01,
            Path::Texture::s_pCIRCLE_02,
            Path::Texture::s_pRING_01,
            Path::Texture::s_pSPACE,
            Path::Texture::s_pSHELTER,
            Path::Texture::s_pSHALTER_NORMAL,
            Path::Texture::s_pSPPED_UP_OPTION,
            Path::Texture::s_pSMALL_BEAM_OPTION,
            Path::Texture::s_pPAUSE_BACKGROUND,
            Path::Texture::s_pEARTH,
            Path::Texture::s_pBACKGROND_METEOR,
            Path::Texture::s_pGAME_UI,
            Path::Texture::s_pSMOKE_01,
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pTexturePathList); i < arraySize; ++i)
        {
            if (!Texture::C_TextureManager::s_GetInstance()->GetTextureData(pTexturePathList[i]))
            {
                if (Texture::C_TextureManager::s_GetInstance()->Create2DFromFile(pTexturePathList[i]) == false) return false;
            }
        }

        // 各スプライトクリエイターを作成
        const char* pBillboardSpriteIdList[] = 
        {
            ID::Sprite::s_pBULLET,
        };

        const char* pBillboardSpriteTextureDataIdList[] =
        {
            Path::Texture::s_pSPRITE_BULLET,
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pBillboardSpriteIdList); i < arraySize; ++i)
        {
            if (!Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(pBillboardSpriteIdList[i]))
            {
                auto pTextureData = Texture::C_TextureManager::s_GetInstance()->GetTextureData(pBillboardSpriteTextureDataIdList[i]);
                assert(pTextureData);

                if (Sprite::C_SpriteCreaterManager::s_GetInstance()->Create(pBillboardSpriteIdList[i], pMainCamera_, pTextureData.get(), 100, Priority::Sprite::s_BILLBOARD) == false) return false;
            }
        }

        const char* pUiSpriteIdList[] = 
        {
            ID::Sprite::s_pPAUSE_BACKGROUND,
            ID::Sprite::s_pGAME_UI,
        };

        const char* pUiSpriteTextureDataIdList[] =
        {
            Path::Texture::s_pPAUSE_BACKGROUND,
            Path::Texture::s_pGAME_UI,
        };

        const float uiSpritePriorityList[] =
        {
            Priority::Sprite::s_BACKGROUND,
            Priority::Sprite::s_IMAGE_UI,
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pUiSpriteIdList); i < arraySize; ++i)
        {
            if (!Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(pUiSpriteIdList[i]))
            {
                auto pTextureData = Texture::C_TextureManager::s_GetInstance()->GetTextureData(pUiSpriteTextureDataIdList[i]);
                assert(pTextureData);

                if (Sprite::C_SpriteCreaterManager::s_GetInstance()->Create(pUiSpriteIdList[i], pUiCamera_, pTextureData.get(), 100, uiSpritePriorityList[i]) == false) return false;
               
                // カメラのタイプを正投影に設定
                auto pSpriteCreater = Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(pUiSpriteIdList[i]).get().lock();
                pSpriteCreater->SetCameraType(Camera::ORTHOGRAPHIC);
            }
        }

        // 各パーティクルシステムを作成
        const char* pParticleTextureDataIdList[] =
        {
            Path::Texture::s_pCIRCLE_01,
            Path::Texture::s_pCIRCLE_02,
            Path::Texture::s_pRING_01,
            Path::Texture::s_pSMOKE_01,
        };

        const char* pParticleIdList[] = 
        {
            ID::Particle::s_pCIRCLE_01,
            ID::Particle::s_pCIRCLE_02,
            ID::Particle::s_pRING_01,
            ID::Particle::s_pSMOKE_01,
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pParticleIdList); i < arraySize; ++i)
        {
            if (!Particle::C_ParticleSystemManager::s_GetInstance()->GetParticleSystem(pParticleIdList[i]))
            {
                auto pTextureData = Texture::C_TextureManager::s_GetInstance()->GetTextureData(pParticleTextureDataIdList[i]);
                assert(pTextureData);

                if (Particle::C_ParticleSystemManager::s_GetInstance()->Create(pParticleIdList[i], pMainCamera_, pTextureData.get()->handle_) == false) return false;
            }
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  ジェネレーターの設定を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_Stage01Scene::SetupGenerator()
    {
        // プレイヤーの生成機の設定
        playerGenerator_.SetTaskSystem(&taskSystem_);

        // オプション生成機の設定
        optionGenerator_.SetTaskSystem(&taskSystem_);
        optionGenerator_.RegistFunction(ID::Generator::Option::s_pSPEED_UP, []()->C_BaseOption*{ return newEx C_SpeedUpOption(ID::GameObject::s_pOPTION, TYPE_OPTION); });
        optionGenerator_.RegistFunction(ID::Generator::Option::s_pSMALL_BEAM, []()->C_BaseOption*{ return newEx C_SmallBeamOption(ID::GameObject::s_pOPTION, TYPE_OPTION); });

        // 敵生成機の設定
        enemyGenerator_.SetTaskSystem(&taskSystem_);

        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSTAGE_01_ENEMY_DATA));
        enemyGenerator_.SetEnemyData(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSTAGE_01_ENEMY_DATA).get());
        enemyGenerator_.RegistFunction(ID::Generator::Enemy::s_pBOX, []()->C_BaseEnemy*{ return newEx C_BoxEnemy(ID::GameObject::s_pENEMY, TYPE_ENEMY); });

        // 弾生成機の設定
        bulletGenerator_.SetTaskSystem(&taskSystem_);
        bulletGenerator_.RegistFunction(ID::Generator::Bullet::Player::s_pBEAM, [](int32_t shooterType)->C_BaseBullet*{ return newEx C_PlayerBeamBullet(ID::GameObject::s_pBULLET, TYPE_BULLET, shooterType); });
        bulletGenerator_.RegistFunction(ID::Generator::Bullet::Option::s_pSMALL_BEAM, [](int32_t shooterType)->C_BaseBullet*{ return newEx C_OptionSmallBeamBullet(ID::GameObject::s_pBULLET, TYPE_BULLET, shooterType); });

        // エフェクト生成機の設定
        effectGenerator_.SetTaskSystem(&taskSystem_);
        effectGenerator_.RegistFunction(ID::Generator::Effect::s_pPLAYER_FLAREBACK, []()->C_BaseEffect*{ return newEx C_PlayerFlarebackEffect(ID::GameObject::s_pEFFECT, TYPE_EFFECT); });
        effectGenerator_.RegistFunction(ID::Generator::Effect::s_pCONNECT, []()->C_BaseEffect*{ return newEx C_ConnectEffect(ID::GameObject::s_pEFFECT, TYPE_EFFECT); });
        effectGenerator_.RegistFunction(ID::Generator::Effect::s_pPLAYER_EXPLOSION, []()->C_BaseEffect*{ return newEx C_PlayerExplosionEffect(ID::GameObject::s_pEFFECT, TYPE_EFFECT); });
        effectGenerator_.RegistFunction(ID::Generator::Effect::s_pPLAYER_BEAM_COLLISION, []()->C_BaseEffect*{ return newEx C_PlayerBeamCollisionEffect(ID::GameObject::s_pEFFECT, TYPE_EFFECT); });
        effectGenerator_.RegistFunction(ID::Generator::Effect::s_pOPTION_SMALL_BEAM_COLLISION, []()->C_BaseEffect*{ return newEx C_OptionSmallBeamCollisionEffect(ID::GameObject::s_pEFFECT, TYPE_EFFECT); });
        effectGenerator_.RegistFunction(ID::Generator::Effect::s_pNORMAL_BOMB_CHARGE, []()->C_BaseEffect*{ return newEx C_NormalBombChargeEffect(ID::GameObject::s_pEFFECT, TYPE_EFFECT); });
        effectGenerator_.RegistFunction(ID::Generator::Effect::s_pNORMAL_BOMB, []()->C_BaseEffect*{ return newEx C_NormalBombEffect(ID::GameObject::s_pEFFECT, TYPE_EFFECT); });
        effectGenerator_.RegistFunction(ID::Generator::Effect::s_pOPTION_OWN_CRASH_01, []()->C_BaseEffect*{ return newEx C_OptionOwnCrashEffect01(ID::GameObject::s_pEFFECT, TYPE_EFFECT); });
        effectGenerator_.RegistFunction(ID::Generator::Effect::s_pOPTION_EXPLOSION, []()->C_BaseEffect*{ return newEx C_OptionExplosionEffect(ID::GameObject::s_pEFFECT, TYPE_EFFECT); });

        // 背景生成機の設定
        backgroundGenerator_.SetTaskSystem(&taskSystem_);
        backgroundGenerator_.RegistFunction(ID::Generator::Background::s_pSPACE, []()->C_BaseBackground*{ return newEx C_Space(ID::GameObject::s_pBACKGROUND, TYPE_BACKGROUND); });
        backgroundGenerator_.RegistFunction(ID::Generator::Background::s_pSHELTER, []()->C_BaseBackground*{ return newEx C_Shelter(ID::GameObject::s_pBACKGROUND, TYPE_BACKGROUND); });
        backgroundGenerator_.RegistFunction(ID::Generator::Background::s_pEXIT_RING, []()->C_BaseBackground*{ return newEx C_ExitRing(ID::GameObject::s_pBACKGROUND, TYPE_BACKGROUND); });
        backgroundGenerator_.RegistFunction(ID::Generator::Background::s_pEARTH, []()->C_BaseBackground*{ return newEx C_Earth(ID::GameObject::s_pBACKGROUND, TYPE_BACKGROUND); });
        backgroundGenerator_.RegistFunction(ID::Generator::Background::s_pBACKGROUND_METEOR, []()->C_BaseBackground*{ return newEx C_BackgroundMeteor(ID::GameObject::s_pBACKGROUND, TYPE_BACKGROUND); });

        // ボム生成機の設定
        bombGenerator_.SetTaskSystem(&taskSystem_);
        bombGenerator_.RegistFunction(ID::Generator::Bomb::s_pNORMAL, [](int32_t level)->C_BaseBomb*{ return newEx C_NormalBomb(ID::GameObject::s_pBOMB, TYPE_BOMB, level); });

        // 背景生成機の設定
        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSTAGE_01_BACKGROUND_DATA));
        auto pBackgroundData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSTAGE_01_BACKGROUND_DATA).get();
        
        backgroundGenerator_.SetBackgroundData(&(*pBackgroundData)["Stage01BackgroundData"]);
        backgroundGenerator_.SetAutoCreateMaxCount((*pBackgroundData)["DataCount"].GetValue<JSON::Integer>());
    }
}