/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include <SDL_joystick.h>
#include <array>


//-------------------------------------------------------------
//!
//! @brief インプット
//! @brief 入力関連の名前空間
//!
//-------------------------------------------------------------
namespace Input
{
    /* 別名 */
    using GamepadData = SDL_Joystick;                                       // GamepadData型

    
    namespace
    {
        /* スティック */
        namespace Stick
        {
            static const int32_t s_DEAD_ZONE = 8500;                        ///< @brief 遊び値
            static const int32_t s_PUSH_MAXIMUM = 32700;                    ///< @brief 倒し具合の最大数
            static const int32_t s_PUSH_MINIMUM = -32700;                   ///< @brief 倒し具合の最初値
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief ゲームパッド
    //! @brief ゲームパッドの基底クラス
    //!
    //-------------------------------------------------------------
    class C_Gamepad
    {
    public:
        /** ボタン */
        enum eButton
        {
            BUTTON_FOUR_UP,                                                 ///< @brief 4つボタン・上
            BUTTON_FOUR_DOWN,                                               ///< @brief 4つボタン・下
            BUTTON_FOUR_LEFT,                                               ///< @brief 4つボタン・左
            BUTTON_FOUR_RIGHT,                                              ///< @brief 4つボタン・右
            BUTTON_CROSS_UP,                                                ///< @brief 十字キー・上
            BUTTON_CROSS_DOWN,                                              ///< @brief 十字キー・下
            BUTTON_CROSS_LEFT,                                              ///< @brief 十字キー・左
            BUTTON_CROSS_RIGHT,                                             ///< @brief 十字キー・右
            BUTTON_START,                                                   ///< @brief スタートボタン
            BUTTON_SELECT,                                                  ///< @brief セレクトボタン
            BUTTON_SHOULDER_1_LEFT,                                         ///< @brief L1ボタン
            BUTTON_SHOULDER_1_RIGHT,                                        ///< @brief R1ボタン
            BUTTON_SHOULDER_2_LEFT,                                         ///< @brief L2ボタン
            BUTTON_SHOULDER_2_RIGHT,                                        ///< @brief R2ボタン

            BUTTON_TOTAL_NUMBER,                                            ///< @brief ボタンの総数
        };

        /** スティック */
        enum eStick
        {
            STICK_LEFT,                                                     ///< @brief 左スティック
            STICK_RIGHT,                                                    ///< @brief 右スティック

            STICK_TOTAL_NUMBER,                                             ///< @brief スティックの総数
        };


        C_Gamepad(GamepadData* pGamepad);                                   // コンストラクタ
        virtual ~C_Gamepad();                                               // デストラクタ
        virtual void Update() = 0;                                          // 更新処理
        void Finalize();                                                    // 終了処理
        int32_t GetButtonPressingCount(eButton button) const;               // ボタンの押しているフレーム数を取得
        int32_t GetButtonReleasingCount(eButton button) const;              // ボタンの離しているフレーム数を取得
        int32_t GetStickXComponent(eStick stick) const;                     // スティックのX成分を取得
        int32_t GetStickYComponent(eStick stick) const;                     // スティックのY成分を取得
        int32_t GetStickPushingCount(eStick stick) const;                   // スティックを倒しているフレーム数を取得
        int32_t GetStickReleasingCount(eStick stick) const;                 // スティックを倒していないフレーム数を取得
    protected:
        GamepadData* pGamepad_ = nullptr;                                   ///< @brief ゲームパッド
        std::array<int32_t, BUTTON_TOTAL_NUMBER> buttonPressingCounts_;     ///< @brief ボタンを押しているフレーム数のカウンタ
        std::array<int32_t, BUTTON_TOTAL_NUMBER> buttonReleasingCounts_;    ///< @brief ボタンを離しているフレーム数のカウンタ
        std::array<int32_t, STICK_TOTAL_NUMBER> stickComponentX_;           ///< @brief スティックのX成分
        std::array<int32_t, STICK_TOTAL_NUMBER> stickComponentY_;           ///< @brief スティックのY成分
        std::array<int32_t, STICK_TOTAL_NUMBER> stickPushingCounts_;        ///< @brief スティックを倒しているフレーム数のカウンタ
        std::array<int32_t, STICK_TOTAL_NUMBER> stickReleasingCounts_;      ///< @brief スティックを倒していないフレーム数のカウンタ
    };
}
