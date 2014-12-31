/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Gamepad/Gamepad.h"


//-------------------------------------------------------------
//!
//! @brief インプット
//! @brief 入力関連の名前空間
//!
//-------------------------------------------------------------
namespace Input
{
    //-------------------------------------------------------------
    //!
    //! @brief ゲームパッドファクトリ( インターフェース )
    //! @brief ゲームパッドファクトリのインターフェース
    //!
    //-------------------------------------------------------------
    class IC_GamepadFactory
    {
    public:
        IC_GamepadFactory(){};                                                  //!< @brief コンストラクタ
        virtual ~IC_GamepadFactory(){};                                         //!< @brief デストラクタ
        virtual C_Gamepad* Create(const std::string& rName,                     //!< @brief 生成処理
                                  GamepadData* pGamepadData) = 0;
    };


    //-------------------------------------------------------------
    //!
    //! @brief ゲームパッドファクトリ
    //! @brief 各ゲームパッドを生成するクラス
    //!
    //-------------------------------------------------------------
    class C_GamepadFactory : public IC_GamepadFactory
    {
    public:
        C_GamepadFactory();                                                     // コンストラクタ
        virtual ~C_GamepadFactory() override;                                   // デストラクタ
        virtual C_Gamepad* Create(const std::string& rName,                     // 生成処理
                                  GamepadData* pGamepadData) override;
    };
}