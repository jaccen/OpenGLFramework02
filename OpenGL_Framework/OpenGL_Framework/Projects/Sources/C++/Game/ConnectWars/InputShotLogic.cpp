/* ヘッダファイル */
#include "InputShotLogic.h"


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
     *  @param  射撃の間隔
     *  @param  キーコード
     *  @param  ゲームパッドのボタン
     *
     ****************************************************************/
    C_InputShotLogic::C_InputShotLogic(int32_t shotInterval,
                                       Input::KeyCode keyCode,
                                       Input::C_Gamepad::eButton gamepadButton) : C_ShotLogic(shotInterval),

        // キーボードマネージャー
        pKeyboardManager_(Input::C_KeyboardManager::s_GetInstance()),

        // ゲームパッドマネージャー
        pGamepadManager_(Input::C_GamepadManager::s_GetInstance())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_InputShotLogic::~C_InputShotLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  非公開の処理を行う
     *  @param  なし
     *  @return 射撃準備完了：true
     *  @return 射撃準備中  ：false
     *
     ****************************************************************/
    bool C_InputShotLogic::DoProcess()
    {
        if (((pKeyboardManager_->GetPressingCount(keyCode_) > 0)   
          && (pKeyboardManager_->GetPressingCount(keyCode_) % shotInterval_ == 1))
         || ((pGamepadManager_->GetButtonPressingCount(gamepadButton_) > 0)
          && (pGamepadManager_->GetButtonPressingCount(gamepadButton_) % shotInterval_ == 1)))
        {
            return true;
        }

        return false;
    }
}