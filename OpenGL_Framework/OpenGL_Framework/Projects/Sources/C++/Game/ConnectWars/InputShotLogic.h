/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ShotLogic.h"
#include "../../Library/Input/Keyboard/KeyboardManager.h"
#include "../../Library/Input/Gamepad/Manager/GamepadManager.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief インプットショットロジック
    //! @brief 入力による射撃のロジック
    //!
    //-------------------------------------------------------------
    class C_InputShotLogic : public C_ShotLogic
    {
    public:
        C_InputShotLogic(int32_t shotInterval,                                                              // コンストラクタ
                         Input::KeyCode keyCode = Input::KeyCode::SDL_SCANCODE_Z,
                         Input::C_Gamepad::eButton gamepadButton = Input::C_Gamepad::BUTTON_FOUR_DOWN);
        ~C_InputShotLogic() override;                                                                       // デストラクタ
    private:
        Input::KeyCode keyCode_ = Input::KeyCode::SDL_SCANCODE_Z;                                           ///< @brief キーコード
        Input::C_Gamepad::eButton gamepadButton_ = Input::C_Gamepad::BUTTON_FOUR_DOWN;                      ///< @brief ゲームパッドのボタン

        Input::C_KeyboardManager* pKeyboardManager_ = nullptr;                                              ///< @brief キーボードマネージャー
        Input::C_GamepadManager* pGamepadManager_ = nullptr;                                                ///< @brief ゲームパッドマネージャー

        bool DoProcess() override;                                                                          // 非公開の処理
    };
}