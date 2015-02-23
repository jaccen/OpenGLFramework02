/* �w�b�_�t�@�C�� */
#include "GameController.h"
#include "PauseScene.h"
#include "../../Library/Input/Keyboard/KeyboardManager.h"
#include "../../Library/Input/Gamepad/Manager/GamepadManager.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
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
     *  @param  ID
     *  @param  ���
     *
     ****************************************************************/
    C_GameController::C_GameController(const std::string& rId, int32_t type) : C_SceneController(rId, type)
    {
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
        }
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
}