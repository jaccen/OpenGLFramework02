/* �w�b�_�t�@�C�� */
#include "RankingScene.h"
#include "RootScene.h"
#include "ConnectWarsDefine.h"
#include "RankingUi.h"
#include "RankingController.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "../../Library/Sprite/Creater/SpriteCreater.h"
#include "../../Library/Common/CommonHelper.h"
#include "../../Library/Input/Keyboard/KeyboardManager.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/GameObject/Manager/GameObjectManager.h"


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
    C_RankingScene::C_RankingScene()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_RankingScene::~C_RankingScene()
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
    Scene::ecSceneReturn C_RankingScene::Initialize()
    {
        if (RemainLoadProcess() == false) return Scene::ecSceneReturn::ERROR_TERMINATION;

        taskSystem_.Entry(std::make_shared<C_RankingUi>(ID::GameObject::s_pUI, TYPE_UI), Priority::Task::Update::s_ui, Priority::Task::Draw::s_ui);
        
        auto pRankingController = std::make_shared<C_RankingController>(ID::GameObject::s_pSCENE_CONTROLLER, TYPE_SCENE_CONTROLLER);
        taskSystem_.Entry(pRankingController, Priority::Task::Update::s_sceneController, Priority::Task::Draw::s_sceneController);
        pRankingController->SetSceneChanger(GetSceneChanger());
        GameObject::C_GameObjectManager::s_GetInstance()->Entry(pRankingController);


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
    Scene::ecSceneReturn C_RankingScene::Update()
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
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RankingScene::Draw()
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
    void C_RankingScene::Finalize()
    {
        JSON::C_JsonObjectManager::s_GetInstance()->AllRemove();
        GameObject::C_GameObjectManager::s_GetInstance()->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  �c��̃��[�h�������s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_RankingScene::RemainLoadProcess()
    {
        // UI�p�J�������擾
        assert(Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pUI));
        pUiCamera_ = Camera::C_CameraManager::s_GetInstance()->GetCamera(ID::Camera::s_pUI).get();

        // �e�e�N�X�`���̍쐬
        const char* pTexturePathList[] =
        {
            Path::Texture::s_pRANKING_BACKGROUND,
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
            ID::Sprite::s_pRANKING_BACKGROUND,
        };

        const char* pSpriteTextureDataIdList[] =
        {
            Path::Texture::s_pRANKING_BACKGROUND,
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