/* ヘッダファイル */
#include "Gamepad.h"


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
    C_Gamepad::C_Gamepad(SDL_Joystick* pGamepad) :

        // ゲームパッド
        pGamepad_(pGamepad)

    {
        // ボタンのフレーム数のカウンタを初期化
        buttonPressingCounts_.fill(0);
        buttonReleasingCounts_.fill(0);

        // スティックのフレーム数のカウンタと各成分を初期化
        stickComponentX_.fill(0);
        stickComponentY_.fill(0);
        stickPushingCounts_.fill(0);
        stickReleasingCounts_.fill(0);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_Gamepad::~C_Gamepad()
    {
        if (pGamepad_ == nullptr) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_Gamepad::Finalize()
    {
        // ゲームパッドを閉じる
        if (::SDL_JoystickGetAttached(pGamepad_) == SDL_TRUE)
        {
            ::SDL_JoystickClose(pGamepad_);
            pGamepad_ = nullptr;
        }
    }


    /*************************************************************//**
     *
     *  @brief  ボタンを押しているフレーム数を取得する
     *  @param  ボタン
     *  @return ボタンを押しているフレーム数
     *
     ****************************************************************/
    int C_Gamepad::GetButtonPressingCount(eButton button) const
    {
        return buttonPressingCounts_.at(button);
    }


    /*************************************************************//**
     *
     *  @brief  ボタンを離しているフレーム数を取得する
     *  @param  ボタン
     *  @return ボタンを離しているフレーム数
     *
     ****************************************************************/
    int C_Gamepad::GetButtonReleasingCount(eButton button) const
    {
        return buttonReleasingCounts_.at(button);
    }


    /*************************************************************//**
     *
     *  @brief  スティックのX成分を取得する
     *  @param  スティック
     *  @return スティックのX成分
     *
     ****************************************************************/
    int C_Gamepad::GetStickXComponent(eStick stick) const
    {
        return stickComponentX_.at(stick);
    }


    /*************************************************************//**
     *
     *  @brief  スティックのY成分を取得する
     *  @param  スティック
     *  @return スティックのY成分
     *
     ****************************************************************/
    int C_Gamepad::GetStickYComponent(eStick stick) const
    {
        return stickComponentY_.at(stick);
    }


    /*************************************************************//**
     *
     *  @brief  スティックを倒しているフレーム数を取得する
     *  @param  スティック
     *  @return スティックを倒しているフレーム数
     *
     ****************************************************************/
    int C_Gamepad::GetStickPushingCount(eStick stick) const
    {
        return stickPushingCounts_.at(stick);
    }


    /*************************************************************//**
     *
     *  @brief  スティックを離しているフレーム数を取得する
     *  @param  スティック
     *  @return スティックを離しているフレーム数
     *
     ****************************************************************/
    int C_Gamepad::GetStickReleasingCount(eStick stick) const
    {
        return stickReleasingCounts_.at(stick);
    }
}