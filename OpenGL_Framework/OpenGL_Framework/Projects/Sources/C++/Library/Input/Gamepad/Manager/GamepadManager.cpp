/* ヘッダファイル */
#include "GamepadManagerImpl.h"


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
    C_GamepadManager::C_GamepadManager() :

        // 実装情報
        upImpl_(std::make_unique<C_GamepadManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_GamepadManager::~C_GamepadManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_GamepadManager::Initialize()
    {
        upImpl_->Initialize();
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_GamepadManager::Update()
    {
        upImpl_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_GamepadManager::Finalize()
    {
        upImpl_->Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  ボタンを押しているフレーム数を取得する
     *  @param  ボタン
     *  @param  ゲームパッドの番号
     *  @return ボタンを押しているフレーム数
     *
     ****************************************************************/
    int32_t C_GamepadManager::GetButtonPressingCount(C_Gamepad::eButton button, eGamepadNumber number) const
    {
        return upImpl_->GetButtonPressingCount(button, number);
    }


    /*************************************************************//**
     *
     *  @brief  ボタンを離しているフレーム数を取得する
     *  @param  ボタン
     *  @param  ゲームパッドの番号
     *  @return ボタンを離しているフレーム数
     *
     ****************************************************************/
    int32_t C_GamepadManager::GetButtonReleasingCount(C_Gamepad::eButton button, eGamepadNumber number) const
    {
        return upImpl_->GetButtonReleasingCount(button, number);
    }


    /*************************************************************//**
     *
     *  @brief  スティックのX成分を取得する
     *  @param  スティック
     *  @param  ゲームパッドの番号
     *  @return スティックのX成分
     *
     ****************************************************************/
    int32_t C_GamepadManager::GetStickXComponent(C_Gamepad::eStick stick, eGamepadNumber number) const
    {
        return upImpl_->GetStickXComponent(stick, number);
    }


    /*************************************************************//**
     *
     *  @brief  スティックのY成分を取得する
     *  @param  スティック
     *  @param  ゲームパッドの番号
     *  @return スティックのY成分
     *
     ****************************************************************/
    int32_t C_GamepadManager::GetStickYComponent(C_Gamepad::eStick stick, eGamepadNumber number) const
    {
        return upImpl_->GetStickYComponent(stick, number);
    }


    /*************************************************************//**
     *
     *  @brief  スティックを倒しているフレーム数を取得する
     *  @param  スティック
     *  @param  ゲームパッドの番号
     *  @return スティックを倒しているフレーム数
     *
     ****************************************************************/
    int32_t C_GamepadManager::GetStickPushingCount(C_Gamepad::eStick stick, eGamepadNumber number) const
    {
        return upImpl_->GetStickPushingCount(stick, number);
    }


    /*************************************************************//**
     *
     *  @brief  スティックを倒していないフレーム数を取得する
     *  @param  スティック
     *  @param  ゲームパッドの番号
     *  @return スティックを倒していないフレーム数
     *
     ****************************************************************/
    int32_t C_GamepadManager::GetStickReleasingCount(C_Gamepad::eStick stick, eGamepadNumber number) const
    {
        return upImpl_->GetStickReleasingCount(stick, number);
    }
}