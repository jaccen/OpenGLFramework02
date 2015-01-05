/* �w�b�_�t�@�C�� */
#include "ConnectWars.h"
#include "../../Library/Scene/Manager/SceneManager.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/Input/Keyboard/KeyboardManager.h"
#include "../../Library/Camera/Manager/CameraManager.h"
#include "../../Library/Timer/Manager/TimeManager.h"
#include "TitleScene.h"
#include "Stage01Scene.h"


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
    C_ConnectWars::C_ConnectWars() : C_Framework(this),

        // Lua�X�e�[�g�}�l�[�W���[
        upLuaStateManager_(std::make_unique<Lua::C_LuaStateManager>()),

        // �p�[�e�B�N���V�X�e���}�l�[�W���[
        upParticleSystemManager_(std::make_unique<Particle::C_ParticleSystemManager>()),

        // �Q�[���I�u�W�F�N�g�}�l�[�W���[
        upGameObjectManager_(std::make_unique<GameObject::C_GameObjectManager>()),

        // ���b�Z�[�W�f�B�X�p�b�`���[
        upMessageDispatcher_(std::make_unique<GameObject::Message::C_MessageDispatcher>()),

        // �t�B�W�b�N�X�G���W��
        upPhysicsEngine_(std::make_unique<Physics::C_PhysicsEngine>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_ConnectWars::~C_ConnectWars()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_ConnectWars::Initialize()
    {
        // ���C�u�����̏���������
        if (C_Framework::InitializeWithJsonFile("Projects/GameDatas/ConnectWars/JSON/Window/MainWindowData.json",
                                                "Projects/GameDatas/ConnectWars/JSON/OpenGL/OpenGLData.json") == false)
        {
            return false;
        }

        // �t�B�W�b�N�X�G���W���̏���������
        upPhysicsEngine_->Initialize(Physics::Vector3(0.0f, 0.0f, 0.0f), Physics::Default::s_AIR_DENSITY);

        // �V�[���}�l�[�W���[�̏���������
        upSceneManager_ = std::make_unique<Scene::C_SceneManager>(newEx C_Stage01Scene);
        if (upSceneManager_->Initialize() == Scene::ecSceneReturn::ERROR_TERMINATION) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �Q�[�����s�Ftrue
     *  @return �Q�[���I���Ffalse
     *
     ****************************************************************/
    bool C_ConnectWars::Update()
    {
        // ���C�u�����̍X�V����
        if (C_Framework::Update() == false) return false;

        // �p�[�e�B�N���V�X�e���}�l�[�W���[�̍X�V����
        upParticleSystemManager_->Update();

        // ���b�Z�[�W�f�B�X�p�b�`���[�̍X�V����
        upMessageDispatcher_->Update();

        // �J�����}�l�[�W���[�̍X�V����
        Camera::C_CameraManager::s_GetInstance()->Update();

        // �V�[���}�l�[�W���[�̍X�V����
        Scene::ecSceneReturn sceneReturnValue = upSceneManager_->Update();

        // �t�B�W�b�N�X�G���W���̍X�V����
        upPhysicsEngine_->Update(Timer::C_TimeManager::s_GetInstance()->GetDeltaTime());

        if (sceneReturnValue != Scene::ecSceneReturn::CONTINUATIOIN)
        {
            // �G���[�I���̏ꍇ�̓��O��\������
            if (sceneReturnValue == Scene::ecSceneReturn::ERROR_TERMINATION)
            {
                PrintLog("[ C_ConnectWars::Update ] : �Q�[�����G���[�I�����܂����B\n");
            }

            return false;
        }


/* �f�o�b�O�� */
#ifdef _DEBUG

        // �G�X�P�[�v�L�[���͂ŋ����I��
        if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_ESCAPE) == 1) return false;

#endif

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ConnectWars::Draw()
    {
        // �V�[���}�l�[�W���[�̕`�揈��
        upSceneManager_->Draw();

        // �p�[�e�B�N���V�X�e���}�l�[�W���[�̕`�揈��
        upParticleSystemManager_->Draw();

        // ���C�u�����̕`�揈��
        C_Framework::Draw();
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ConnectWars::Finalize()
    {
        // �t�B�W�b�N�X�G���W���̏I������
        upPhysicsEngine_->Finalize();

        // �V�[���}�l�[�W���[�̏I������
        upSceneManager_->Finalize();

        // �p�[�e�B�N���V�X�e����S�Ĕj��
        upParticleSystemManager_->AllDestroy();
        
        // �Q�[���I�u�W�F�N�g��S�ď���
        upGameObjectManager_->AllRemove();

        // Lua�X�e�[�g��S�Ĕj��
        upLuaStateManager_->AllDestroy();

        // ���C�u�����̏I������
        C_Framework::Finalize();
    }
}