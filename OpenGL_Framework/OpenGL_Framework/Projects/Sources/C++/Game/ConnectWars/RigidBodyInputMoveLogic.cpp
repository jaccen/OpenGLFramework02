/* ヘッダファイル */
#include "RigidBodyInputMoveLogic.h"
#include "../../Library/Input/Keyboard/KeyboardManager.h"
#include "../../Library/Input/Gamepad/Manager/GamepadManager.h"
#include "../../Library/Math/Define/MathDefine.h"


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
     *  @param  移動量
     *  @param  移動量のスケール
     *
     ****************************************************************/
    C_RigidBodyInputMoveLogic::C_RigidBodyInputMoveLogic(float movement, float movementScale) :

        // 移動量と移動量のスケール
        movement_(movement),
        movementScale_(movementScale),

        // 各入力のマネージャ
        pKeyboardManager_(Input::C_KeyboardManager::s_GetInstance()),
        pGamepadManager_(Input::C_GamepadManager::s_GetInstance())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_RigidBodyInputMoveLogic::~C_RigidBodyInputMoveLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  移動処理を行う
     *  @param  剛体
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBodyInputMoveLogic::Move(RigidBody* pRigidBody)
    {
        static const int32_t s_GAMEPAD_ENABLE_PUT_STICK = 18000;

        // 各方向に入力があるか判断するフラグ
        bool inputHorizontalFlag = false, inputVerticalFlag = false;

        // 加える座標と移動量
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
            addPosition.setX(movement);
            inputHorizontalFlag == false ? true : false;
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
            addPosition.setY(-movement);
            inputHorizontalFlag == false ? true : false;
        }

        // 斜め移動時には移動量を√2で割る
        if (inputHorizontalFlag == true && inputVerticalFlag == true)
        {
            addPosition.setX(addPosition.x() / static_cast<float>(Math::s_ROOT2));
            addPosition.setY(addPosition.y() / static_cast<float>(Math::s_ROOT2));
        }

        // 座標を加える
        pRigidBody->AddPosition(addPosition);
    }
}