/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../../Singleton/Singleton.h"
#include "../Gamepad/Gamepad.h"


//-------------------------------------------------------------
//!
//! @brief インプット
//! @brief 入力関連の名前空間
//!
//-------------------------------------------------------------
namespace Input
{
    /** ゲームパッドの番号 */
    enum eGamepadNumber
    {
        GAMEPAD_01,
        GAMEPAD_02,
        GAMEPAD_03,
        GAMEPAD_04,
    };


    //-------------------------------------------------------------
    //!
    //! @brief ゲームパッドマネージャー
    //! @brief ゲームパッドを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_GamepadManager : public Singleton::C_Singleton<C_GamepadManager>
    {
        friend C_Singleton<C_GamepadManager>;                                                                       // シングルトンクラスをフレンド化
    public:
        void Initialize();                                                                                          // 初期化処理
        void Update();                                                                                              // 更新処理
        void Finalize();                                                                                            // 終了処理

        /* ゲッター */
        int32_t GetButtonPressingCount(C_Gamepad::eButton button, eGamepadNumber number = GAMEPAD_01) const;        // ボタンを押しているフレーム数を取得
        int32_t GetButtonReleasingCount(C_Gamepad::eButton button, eGamepadNumber number = GAMEPAD_01) const;       // ボタンを離しているフレーム数を取得
        int32_t GetStickXComponent(C_Gamepad::eStick stick, eGamepadNumber number = GAMEPAD_01) const;              // スティックのX成分を取得
        int32_t GetStickYComponent(C_Gamepad::eStick stick, eGamepadNumber number = GAMEPAD_01) const;              // スティックのY成分を取得
        int32_t GetStickPushingCount(C_Gamepad::eStick stick, eGamepadNumber number = GAMEPAD_01) const;            // スティックを倒しているフレーム数を取得
        int32_t GetStickReleasingCount(C_Gamepad::eStick stick, eGamepadNumber number = GAMEPAD_01) const;          // スティックを倒していないフレーム数を取得
    private:
        /* 前方宣言 */
        class C_GamepadManagerImpl;

        std::unique_ptr<C_GamepadManagerImpl> upImpl_;                                                              ///< @brief 実装情報

        C_GamepadManager();                                                                                         // コンストラクタ
        ~C_GamepadManager() override;                                                                               // デストラクタ
    };
}