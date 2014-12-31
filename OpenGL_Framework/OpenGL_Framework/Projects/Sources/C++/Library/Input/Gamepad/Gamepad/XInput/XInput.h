/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Gamepad.h"


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
    //! @brief XInput
    //! @brief XInputの情報を管理するクラス
    //!
    //-------------------------------------------------------------
    class C_XInput : public C_Gamepad
    {
    public:
        /** ボタン */
        enum eButton
        {
            BUTTON_CROSS_UP,                                                ///< @brief 十字ボタン・上
            BUTTON_CROSS_DOWN,                                              ///< @brief 十字ボタン・下
            BUTTON_CROSS_LEFT,                                              ///< @brief 十字ボタン・左
            BUTTON_CROSS_RIGHT,                                             ///< @brief 十字ボタン・右
            BUTTON_START,                                                   ///< @brief スタートボタン
            BUTTON_BACK,                                                    ///< @brief バックボタン
    
            BUTTON_SHOULDER_LEFT = 8,                                       ///< @brief Lボタン
            BUTTON_SHOULDER_RIGHT,                                          ///< @brief Rボタン
            BUTTON_B,                                                       ///< @brief Bボタン
            BUTTON_A,                                                       ///< @brief Aボタン
            BUTTON_X,                                                       ///< @brief Xボタン
            BUTTON_Y,                                                       ///< @brief Yボタン
            BUTTON_HOME,                                                    ///< @brief ホームボタン
        };
    
        /** スティック */
        enum eStick
        {
            STICK_LEFT_X,                                                   ///< @brief 左スティックのX成分
            STICK_LEFT_Y,                                                   ///< @brief 左スティックのY成分
            STICK_RIGHT_X,                                                  ///< @brief 右スティックのX成分
            STICK_RIGHT_Y,                                                  ///< @brief 右スティックのY成分
            STICK_LEFT_TRIGGER,                                             ///< @brief 左トリガーボタン
            STICK_RIGHT_TRIGGER,                                            ///< @brief 右トリガーボタン
        };

        /* 定数 */
        static const char* s_pNAME;                                         ///< @brief 名前

        C_XInput(GamepadData* pGamepad);                                    // コンストラクタ
        ~C_XInput() override;                                               // デストラクタ
        void Update() override;                                             // 更新処理
    private:
        void ButtonUpdate();                                                // ボタンの更新処理
        void TriggerButtonUpdate(eStick trigger,                            // トリガーボタンの更新処理
                                 C_Gamepad::eButton updateButton);
        void StickUpdate();                                                 // スティックの更新処理
        void RepairStickComponent(int32_t* pStickComponent);                // スティックの成分を適切な値に修正
    };
}