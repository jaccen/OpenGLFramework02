/* ヘッダファイル */
#include "GamepadFactory.h"
#include "../Gamepad/XInput/XInput.h"
#include "../../../Debug/Helper/DebugHelper.h"


//-------------------------------------------------------------
//!
//! @brief インプット
//! @brief 入力関連の名前空間
//!
//-------------------------------------------------------------
namespace Input
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_GamepadFactory::C_GamepadFactory()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_GamepadFactory::~C_GamepadFactory()
    {
    }


    /*************************************************************//**
     *
     *  @brief  各ゲームパッドを生成する
     *  @param  名前
     *  @param  ゲームパッドの情報
     *  @param  各ゲームパッド
     *
     ****************************************************************/
    C_Gamepad* C_GamepadFactory::Create(const std::string& rName, GamepadData* pGamepadData)
    {
        // XInputを生成
        if (rName == C_XInput::s_pNAME)
        {
            return newEx C_XInput(pGamepadData);
        }

        return nullptr;
    }
}