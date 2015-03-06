/* �w�b�_�t�@�C�� */
#include "GameController.h"
#include "PauseScene.h"
#include "../../Library/Input/Keyboard/KeyboardManager.h"
#include "../../Library/Input/Gamepad/Manager/GamepadManager.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"
#include "../../Library/Debug//String/DebugString.h"
#include "../../Library/Particle/System/Manager/ParticleSystemManager.h"


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
     *  @param  ID
     *  @param  ���
     *
     ****************************************************************/
    C_GameController::C_GameController(const std::string& rId, int32_t type) : C_SceneController(rId, type)
    {
        upFade_ = std::make_unique<C_Fade>(ID::GameObject::s_pFADE, eGameObjectType::TYPE_FADE, 30, true);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_GameController::~C_GameController()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameController::DoUpdate()
    {
        static auto isPauseButtonFunction = [&]()
        {
            if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_C) == 1
             || Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_START) == 1)
            {
                return true;
            }

            return false;
        };

        if (isPauseButtonFunction() == true)
        {
            assert(pSceneChanger_);
            pSceneChanger_->PushScene(newEx C_PauseScene);
            
            // �����G���W���̍X�V���~
            Physics::C_PhysicsEngine::s_GetInstance()->EnableActive(false);

            // �p�[�e�B�N���V�X�e���̍X�V���~
            Particle::C_ParticleSystemManager::s_GetInstance()->EnableActive(false);
        }

        pBackgroundGenerator_->AutoCreate(frameCounter_.GetCount());

        upFade_->Update();
    }
    

    /*************************************************************//**
     *
     *  @brief  ����J�̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameController::DoDraw()
    {
        upFade_->Draw();

        std::cout << frameCounter_.GetCount() << std::endl;
    }


    /*************************************************************//**
     *
     *  @brief  ���b�Z�[�W�������s��
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_GameController::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �o�b�N�O���E���h�W�F�l���[�^��ݒ肷��
     *  @param  �o�b�N�O���E���h�W�F�l���[�^
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameController::SetBackgroundGenerator(C_BackgroundGenerator* pBackgroundGenerator)
    {
        pBackgroundGenerator_ = pBackgroundGenerator;
    }


    /*************************************************************//**
     *
     *  @brief  �G�l�~�[�W�F�l���[�^��ݒ肷��
     *  @param  �G�l�~�[�W�F�l���[�^
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameController::SetEnemyGenerator(C_EnemyGenerator* pEnemyGenerator)
    {
        pEnemyGenerator_ = pEnemyGenerator;
    }
}