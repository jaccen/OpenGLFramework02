/* �w�b�_�t�@�C�� */
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
    C_PauseScene::C_PauseScene()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PauseScene::~C_PauseScene()
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
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return ���s    �FCONTINUATIOIN
     *  @return ����I���FSUCCESSFUL
     *  @return �ُ�I���FERROR_TERTINATION
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
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PauseScene::Draw()
    {
        taskSystem_.Draw();
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PauseScene::Finalize()
    {
        GameObject::C_GameObjectManager::s_GetInstance()->Remove(ID::GameObject::s_pPAUSE_CONTROLLER);
    }


    /*************************************************************//**
     *
     *  @brief  �c��̃��[�h�������s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_PauseScene::RemainLoadProcess()
    {
        // UI�p�J�������擾
        assert(Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pUI));
        pUiCamera_ = Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pUI).get();

        // �e�e�N�X�`���̍쐬
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

        // �e�X�v���C�g�N���G�C�^�[���쐬
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
               
                // �J�����̃^�C�v�𐳓��e�ɐݒ�
                auto pSpriteCreater = Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(pSpriteIdList[i]).get().lock();
                pSpriteCreater->SetCameraType(Camera::ORTHOGRAPHIC);
            }
        }

        Sprite::C_SpriteCreaterManager::s_GetInstance()->Sort();

        return true;
    }
}