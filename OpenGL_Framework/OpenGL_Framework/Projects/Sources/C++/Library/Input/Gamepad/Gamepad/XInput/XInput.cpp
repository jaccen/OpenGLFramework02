/* ヘッダファイル */
#include "XInput.h"


//-------------------------------------------------------------
//!
//! @brief インプット
//! @brief 入力関連の名前空間
//!
//-------------------------------------------------------------
namespace Input
{

#pragma region 静的メンバ変数の初期化


    /* 名前 */
    const char* C_XInput::s_pNAME = "XInput Controller #1";


#pragma endregion


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_XInput::C_XInput(GamepadData* pGamepad) : C_Gamepad(pGamepad)
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_XInput::~C_XInput()
    {
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_XInput::Update()
    {
        assert(pGamepad_);

        // ボタンの更新処理
        ButtonUpdate();

        // スティックの更新処理
        StickUpdate();
    }


    /*************************************************************//**
     *
     *  @brief  ボタンの更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_XInput::ButtonUpdate()
    {
        // ボタンの状態の取得時に利用する引数
        static const eButton s_PARAMETERS[] =
        {
            BUTTON_Y,
            BUTTON_B,
            BUTTON_X,
            BUTTON_A,
            BUTTON_CROSS_UP,
            BUTTON_CROSS_DOWN,
            BUTTON_CROSS_LEFT,
            BUTTON_CROSS_RIGHT,
            BUTTON_START,
            BUTTON_BACK,
            BUTTON_SHOULDER_LEFT,
            BUTTON_SHOULDER_RIGHT,
        };

        // 引数の総数
        static const int s_PARAMETER_TOTAL_NUMBER = 12;

        for (size_t i = 0; i < s_PARAMETER_TOTAL_NUMBER; ++i)
        {
            // 押されている場合
            if (::SDL_JoystickGetButton(pGamepad_, s_PARAMETERS[i]) == 1)
            {
                // 離しているフレーム数をリセットし、
                // 押しているフレームを1増加
                if (buttonReleasingCounts_[i] > 0) buttonReleasingCounts_[i] = 0;

                ++buttonPressingCounts_[i];
            }
            else
            {
                // 押しているフレーム数をリセットし、
                // 離しているフレーム数を1増加
                if (buttonPressingCounts_[i] > 0) buttonPressingCounts_[i] = 0;

                ++buttonReleasingCounts_[i];
            }
        }


        // L2ボタンを更新
        TriggerButtonUpdate(STICK_LEFT_TRIGGER, BUTTON_SHOULDER_2_LEFT);

        // R2ボタンを更新
        TriggerButtonUpdate(STICK_RIGHT_TRIGGER, BUTTON_SHOULDER_2_RIGHT);
    }


    /*************************************************************//**
     *
     *  @brief  トリガーボタンの更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_XInput::TriggerButtonUpdate(eStick trigger,
                                       C_Gamepad::eButton updateButton)
    {
        // トリガーの検知値
        static const int32_t s_TRIGGET_DETECTION = 20000;


        // 押されている場合
        if (::SDL_JoystickGetAxis(pGamepad_, trigger) > s_TRIGGET_DETECTION)
        {
            // 離しているフレーム数をリセットし、
            // 押しているフレームを1増加
            if (buttonReleasingCounts_[updateButton] > 0) buttonReleasingCounts_[updateButton] = 0;

            ++buttonPressingCounts_[updateButton];
        }
        else
        {
            // 押しているフレーム数をリセットし、
            // 離しているフレーム数を1増加
            if (buttonPressingCounts_[updateButton] > 0) buttonPressingCounts_[updateButton] = 0;

            ++buttonReleasingCounts_[updateButton];
        }
    }


    /*************************************************************//**
     *
     *  @brief  スティックの更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_XInput::StickUpdate()
    {
        // 軸の数
        static const int32_t s_AXIS_COUNT = 4;

        for (int i = 0; i < s_AXIS_COUNT; ++i)
        {
            // 添え字を求める
            int index = i / 2;

            // iが偶数の場合はX成分を更新
            if (i % 2 == 0)
            {
                // X成分を取得し、適切な値に修正
                stickComponentX_[index] = ::SDL_JoystickGetAxis(pGamepad_, i);
                RepairStickComponent(&stickComponentX_[index]);
            }
            else
            {
                // Y成分を取得し、適切な値に修正
                stickComponentY_[index] = ::SDL_JoystickGetAxis(pGamepad_, i);
                RepairStickComponent(&stickComponentY_[index]);

                // スティックを倒している場合
                if (stickComponentX_[index] != 0 || stickComponentY_[index] != 0)
                {
                    // 倒していないフレーム数をリセットし、
                    // 倒しているフレーム数を1増加
                    if (stickReleasingCounts_[index] > 0) stickReleasingCounts_[index] = 0;

                    ++stickPushingCounts_[index];
                }
                else
                {
                    // 倒しているフレーム数をリセットし、
                    // 倒していないフレーム数を1増加
                    if (stickPushingCounts_[index] > 0) stickPushingCounts_[index] = 0;

                    ++stickReleasingCounts_[index];
                }
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  スティックの成分を適切な値に修正する
     *  @param  スティックの成分
     *  @return なし
     *
     ****************************************************************/
    void C_XInput::RepairStickComponent(int32_t* pStickComponent)
    {
        assert(pStickComponent);

        // スティックが遊び値以内の場合
        if (abs(*pStickComponent) < Stick::s_DEAD_ZONE)
        {
            (*pStickComponent) = 0;
        }
        else
        {
            // スティックが最大値超過、
            // または最小値未満だった場合は修正
            if ((*pStickComponent) > Stick::s_PUSH_MAXIMUM)
            {
                (*pStickComponent) = Stick::s_PUSH_MAXIMUM;
            }
            else if ((*pStickComponent) < Stick::s_PUSH_MINIMUM)
            {
                (*pStickComponent) = Stick::s_PUSH_MINIMUM;
            }
        }
    }
}