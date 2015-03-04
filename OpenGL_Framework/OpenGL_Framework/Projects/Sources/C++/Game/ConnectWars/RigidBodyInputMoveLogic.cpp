/* �w�b�_�t�@�C�� */
#include "RigidBodyInputMoveLogic.h"
#include "../../Library/Input/Keyboard/KeyboardManager.h"
#include "../../Library/Input/Gamepad/Manager/GamepadManager.h"
#include "../../Library/Math/Define/MathDefine.h"
#include "../../Library/Debug/Helper/DebugHelper.h"


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
     *  @param  �ړ���
     *  @param  �ړ��ʂ̃X�P�[��
     *
     ****************************************************************/
    C_RigidBodyInputMoveLogic::C_RigidBodyInputMoveLogic(float movement, float movementScale) :

        // �ړ��ʂƈړ��ʂ̃X�P�[��
        movement_(movement),
        movementScale_(movementScale),

        // �e���͂̃}�l�[�W��
        pKeyboardManager_(Input::C_KeyboardManager::s_GetInstance()),
        pGamepadManager_(Input::C_GamepadManager::s_GetInstance())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_RigidBodyInputMoveLogic::~C_RigidBodyInputMoveLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �ړ��ʂ�ݒ肷��
     *  @param  �ړ���
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBodyInputMoveLogic::SetMovement(float movement)
    {
        movement_ = movement;
    }


    /*************************************************************//**
     *
     *  @brief  �f�B�[�v�R�s�[���s��
     *  @param  �Ȃ�
     *  @return ���g�̃R�s�[
     *
     ****************************************************************/
    C_RigidBodyMoveLogic* C_RigidBodyInputMoveLogic::DeepCopy()
    {
        return newEx C_RigidBodyInputMoveLogic(movement_, movementScale_);
    }


    /*************************************************************//**
     *
     *  @brief  �ړ��ʂ̃X�P�[���̐ݒ肷��
     *  @param  �ړ��ʂ̃X�P�[��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBodyInputMoveLogic::SetMovementScale(float movementScale)
    {
        movementScale_ = movementScale;
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̏������s��
     *  @param  ����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBodyInputMoveLogic::DoProcess(RigidBody* pRigidBody)
    {
        static const int32_t s_GAMEPAD_ENABLE_PUT_STICK = 18000;

        // �e�����ɓ��͂����邩���f����t���O
        bool inputHorizontalFlag = false, inputVerticalFlag = false;

        // ��������W�ƈړ���
        Physics::Vector3 addPosition = Physics::Vector3(0.0f, 0.0f, 0.0f);
        float movement = movement_ * movementScale_;

        if ((pKeyboardManager_->GetPressingCount(Input::KeyCode::SDL_SCANCODE_LEFT) > 0)
         || (pGamepadManager_->GetButtonPressingCount(Input::C_Gamepad::BUTTON_CROSS_LEFT) > 0)
         || (pGamepadManager_->GetStickXComponent(Input::C_Gamepad::STICK_LEFT) < -s_GAMEPAD_ENABLE_PUT_STICK))
        {
            
            addPosition.setX(-movement);
            inputHorizontalFlag = true;
        }

        if ((pKeyboardManager_->GetPressingCount(Input::KeyCode::SDL_SCANCODE_RIGHT) > 0)
         || (pGamepadManager_->GetButtonPressingCount(Input::C_Gamepad::BUTTON_CROSS_RIGHT) > 0)
         || (pGamepadManager_->GetStickXComponent(Input::C_Gamepad::STICK_LEFT) > s_GAMEPAD_ENABLE_PUT_STICK))
        {

            if (inputHorizontalFlag == false)
            {
                addPosition.setX(movement);
                inputHorizontalFlag = true;
            }
            else
            {
                addPosition.setX(0.0f);
                inputHorizontalFlag = false;
            }
        }

        if ((pKeyboardManager_->GetPressingCount(Input::KeyCode::SDL_SCANCODE_UP) > 0)
         || (pGamepadManager_->GetButtonPressingCount(Input::C_Gamepad::BUTTON_CROSS_UP) > 0)
         || (pGamepadManager_->GetStickYComponent(Input::C_Gamepad::eStick::STICK_LEFT) < -s_GAMEPAD_ENABLE_PUT_STICK))
        {
            addPosition.setY(movement);
            inputVerticalFlag = true;
        }

        if ((pKeyboardManager_->GetPressingCount(Input::KeyCode::SDL_SCANCODE_DOWN) > 0)
         || (pGamepadManager_->GetButtonPressingCount(Input::C_Gamepad::BUTTON_CROSS_DOWN) > 0)
         || (pGamepadManager_->GetStickYComponent(Input::C_Gamepad::STICK_LEFT) > s_GAMEPAD_ENABLE_PUT_STICK))
        {

            if (inputVerticalFlag == false)
            {
                addPosition.setY(-movement);
                inputVerticalFlag = true;
            }
            else
            {
                addPosition.setY(0.0f);
                inputVerticalFlag = false;
            }
        }

        // �΂߈ړ����ɂ͈ړ��ʂ���2�Ŋ���
        if (inputHorizontalFlag == true && inputVerticalFlag == true)
        {
            addPosition.setX(addPosition.x() / static_cast<float>(Math::s_ROOT2));
            addPosition.setY(addPosition.y() / static_cast<float>(Math::s_ROOT2));
        }

        // ���W��������
        pRigidBody->AddPosition(addPosition);
    }
}