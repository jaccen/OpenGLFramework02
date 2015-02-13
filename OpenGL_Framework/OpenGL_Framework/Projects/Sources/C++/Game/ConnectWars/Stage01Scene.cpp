/* �w�b�_�t�@�C�� */
#include "Stage01Scene.h"
#include "LoadScene.h"
#include "RootScene.h"
#include "LoadFunction.h"
#include "ConnectWarsDefine.h"
#include "SpeedUpOption.h"
#include "SmallBeamOption.h"
#include "PlayerBullet.h"
#include "OptionBullet.h"
#include "BombChargeEffect.h"
#include "BoxEnemy.h"
#include "Space.h"
#include "CameraController.h"
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
    C_Stage01Scene::C_Stage01Scene()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_Stage01Scene::~C_Stage01Scene()
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
    Scene::ecSceneReturn C_Stage01Scene::Initialize()
    {
        // �c��̃��[�h����
        if (RemainLoadProcess() == false) return Scene::ecSceneReturn::ERROR_TERMINATION;

        // �Q�[���R���g���[���𐶐�
        taskSystem_.Entry(std::make_shared<C_GameController>(ID::GameObject::s_pGAME_CONTROLLER, TYPE_GAME_CONTROLLER), Priority::Task::Update::s_gameController, Priority::Task::Draw::s_gameController);

        // �J�����R���g���[���𐶐�
        auto pCameraController = taskSystem_.Entry(std::make_shared<C_CameraController>(ID::GameObject::s_pCAMERA_CONTROLLER, TYPE_CAMERA_CONTROLLER), Priority::Task::Update::s_cameraController, Priority::Task::Draw::s_cameraController);

        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSTAGE_01_CAMERAWORK_DATA));
        pCameraController->SetCameraData(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSTAGE_01_CAMERAWORK_DATA).get());

        // �v���C���[�𐶐�
        playerGenerator_.Create(ID::Generator::Player::s_pNORMAL);

        // �I�v�V�����𐶐�
        optionGenerator_.Create(ID::Generator::Option::s_pSPEED_UP, Physics::Vector3(0.0f, 2.0f, 0.0f));
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

        // �w�i�𐶐�
        auto pSpace = taskSystem_.Entry(std::make_shared<C_Space>(ID::GameObject::s_pBACKGROUND, TYPE_BACKGROUND), Priority::Task::Update::s_background, Priority::Task::Draw::s_background);
        pSpace->SetLifeFrame(-1);

        //enemyGenerator_.Create(ID::Generator::Enemy::s_pBOX);
        
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
    Scene::ecSceneReturn C_Stage01Scene::Update()
    {
        // �Փˊm�F���b�Z�[�W�𑗐M
		GameObject::Message::C_MessageDispatcher::s_GetInstance()->Send("Messanger", ID::GameObject::s_pPLAYER, Message::s_pCONNECT_CHECK);

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


        if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_E) == 1)
        {
            effectGenerator_.Create(ID::Generator::Effect::Bomb::s_pCHARGE, Vector3(0.0f, 0.0f, 0.0f));
        }

#endif

        return Scene::ecSceneReturn::CONTINUATIOIN;
    }



    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_Stage01Scene::Draw()
    {
        taskSystem_.Draw();

        View::C_ViewHelper::s_DrawGrid(5.0f, 1.0f, 11, View::Vector4(1.0f, 1.0f, 1.0f, 0.1f), pMainCamera_->GetViewProjectionMatrix());
        View::C_ViewHelper::s_DrawAxis(50.0f, pMainCamera_->GetViewProjectionMatrix());
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
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
     *  @brief  �c��̃��[�h�������s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_Stage01Scene::RemainLoadProcess()
    {
        // �e���j�t�H�[���o�b�t�@���쐬
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
            "BackgroundCameraData"
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

        // ���C���J������ێ�
        pMainCamera_ = Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pMAIN).get();

        // �e���f���̃o�b�t�@���쐬
        const char* pPrimitiveIdList[] =
        {
            ID::Primitive::s_pNORMAL_PLAYER,
            ID::Primitive::s_pBOX_ENEMY,
            ID::Primitive::s_pSPACE,
            ID::Primitive::s_pSHELTER,
            ID::Primitive::s_pSPEED_UP_OPTION,
            ID::Primitive::s_pSMALL_BEAM_OPTION,
        };

        const char* pModelIdList[] = 
        {
            ID::Model::s_pNORMAL_PLAYER,
            ID::Model::s_pBOX_ENEMY,
            ID::Model::s_pSPACE,
            ID::Model::s_pSHELTER,
            ID::Model::s_pSPPED_UP_OPTION,
            ID::Model::s_pSMALL_BEAM_OPTION,
        };

        bool vertexTransferFlagList[][7] =
        {
            { true, true, true, false, false, false, false },       // �m�[�}���v���C���[
            { true, true, false, false, false, false, false },      // �{�b�N�X�G�l�~�[
            { true, false, true, false, false, false, false },      // �F��
            { true, true, true, false, true, false, false },        // �V�F���^�[
            { true, true, true, false, false, false, false },       // �X�s�[�h�A�b�v�I�v�V����
            { true, true, true, false, false, false, false },       // �X���[���r�[���I�v�V����
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pPrimitiveIdList); i < arraySize; ++i)
        {
            if (!OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(pPrimitiveIdList[i]))
            {
                assert(Model::SelfMade::C_ModelLoaderManager::s_GetInstance()->GetModelLoader(pModelIdList[i]));
                auto pModelData = Model::SelfMade::C_ModelLoaderManager::s_GetInstance()->GetModelLoader(pModelIdList[i]).get();

                // �V���O�����b�V���O��Ƃ���
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

        // �eGLSL�I�u�W�F�N�g���쐬
        const char* pGlslObjectIdList[] =
        {
            ID::Shader::s_pPHONG,
            ID::Shader::s_pPHONG_TEXTURE,
            ID::Shader::s_pCELESTIAL_SPHERE,
        };

        const char* pVertexShaderPathList[] = 
        {
            Path::Shader::Vertex::s_pPHONG,
            Path::Shader::Vertex::s_pPHONG_TEXTURE,
            Path::Shader::Vertex::s_pCELESTINAL_SPHERE,
        };


        const char* pFragmentShaderPathList[] =
        {
            Path::Shader::Fragment::s_pPHONG,
            Path::Shader::Fragment::s_pPHONG_TEXTURE,
            Path::Shader::Fragment::s_pCELESTINAL_SPHERE,
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


        // �e�e�N�X�`���̍쐬
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
        };

        for (size_t i = 0, arraySize = Common::C_CommonHelper::s_ArraySize(pTexturePathList); i < arraySize; ++i)
        {
            if (!Texture::C_TextureManager::s_GetInstance()->GetTextureData(pTexturePathList[i]))
            {
                if (Texture::C_TextureManager::s_GetInstance()->Create2DFromFile(pTexturePathList[i]) == false) return false;
            }
        }

        // �e�X�v���C�g�N���G�C�^�[���쐬
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

                if (Sprite::C_SpriteCreaterManager::s_GetInstance()->Create(pSpriteIdList[i], pMainCamera_, pTextureData.get(), 100, spritePriorityList[i]) == false) return false;
            }
        }

        // �e�p�[�e�B�N���V�X�e�����쐬
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

                if (Particle::C_ParticleSystemManager::s_GetInstance()->Create(pParticleIdList[i], pMainCamera_, pTextureData.get()->handle_) == false) return false;
            }
        }

        // �v���C���[�̐����@�̐ݒ�
        playerGenerator_.SetTaskSystem(&taskSystem_);

        // �I�v�V���������@�̐ݒ�
        optionGenerator_.SetTaskSystem(&taskSystem_);
        optionGenerator_.RegistFunction(ID::Generator::Option::s_pSPEED_UP, []()->C_BaseOption*{ return newEx C_SpeedUpOption(ID::GameObject::s_pOPTION, TYPE_OPTION); });
        optionGenerator_.RegistFunction(ID::Generator::Option::s_pSMALL_BEAM, []()->C_BaseOption*{ return newEx C_SmallBeamOption(ID::GameObject::s_pOPTION, TYPE_OPTION); });

        // �G�����@�̐ݒ�
        /*
        enemyGenerator_.SetTaskSystem(&taskSystem_);

        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSTAGE_01_ENEMY_DATA));
        enemyGenerator_.SetEnemyData(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSTAGE_01_ENEMY_DATA).get());

        enemyGenerator_.RegistFunction(ID::Generator::Enemy::s_pBOX, []()->C_BaseEnemy*{ return newEx C_BoxEnemy(ID::GameObject::s_pENEMY, TYPE_ENEMY); });
        */

        // �e�����@�̐ݒ�
        bulletGenerator_.SetTaskSystem(&taskSystem_);
        bulletGenerator_.RegistFunction(ID::Generator::Bullet::Player::s_pBEAM, [](int32_t shooterType)->C_BaseBullet*{ return newEx C_PlayerBeamBullet(ID::GameObject::s_pBULLET, TYPE_BULLET, shooterType); });
        bulletGenerator_.RegistFunction(ID::Generator::Bullet::Option::s_pSMALL_BEAM, [](int32_t shooterType)->C_BaseBullet*{ return newEx C_OptionSmallBeamBullet(ID::GameObject::s_pBULLET, TYPE_BULLET, shooterType); });

        // �G�t�F�N�g�����@�̐ݒ�
        effectGenerator_.SetTaskSystem(&taskSystem_);
        effectGenerator_.RegistFunction(ID::Generator::Effect::Bomb::s_pCHARGE, []()->C_BaseEffect*{ return newEx C_BombChargeEffect(ID::GameObject::s_pEFFECT, TYPE_EFFECT); });

        return true;
    }
}