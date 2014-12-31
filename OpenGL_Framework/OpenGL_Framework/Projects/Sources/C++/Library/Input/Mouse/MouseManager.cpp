/* ヘッダファイル */
#include "MouseManagerImpl.h"


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
    C_MouseManager::C_MouseManager() :

        // 実装情報
        upImpl_(std::make_unique<C_MouseManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_MouseManager::~C_MouseManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_MouseManager::Update()
    {
        // カーソルとボタンの更新処理
        upImpl_->CursorAndButtonUpdate();

        // ホイールの更新処理
        upImpl_->WheelUpdate();
    }


    /*************************************************************//**
     *
     *  @brief  カーソルのX座標を取得する
     *  @param  なし
     *  @return カーソルのX座標
     *
     ****************************************************************/
    int32_t C_MouseManager::GetCursorPositionX() const
    {
        return upImpl_->GetCursorPositionX();
    }


    /*************************************************************//**
     *
     *  @brief  カーソルのY座標を取得する
     *  @param  なし
     *  @return カーソルのY座標
     *
     ****************************************************************/
    int32_t C_MouseManager::GetCursorPositionY() const
    {
        return upImpl_->GetCursorPositionY();
    }


    /*************************************************************//**
     *
     *  @brief  ボタンを押しているフレーム数を取得する
     *  @param  ボタン
     *  @return ボタンを押しているフレーム数
     *
     ****************************************************************/
    int32_t C_MouseManager::GetButtonPressingCount(eButton button) const
    {
        return upImpl_->GetButtonPressingCount(button);
    }


    /*************************************************************//**
     *
     *  @brief  ボタンを離しているフレーム数を取得する
     *  @param  ボタン
     *  @return ボタンを離しているフレーム数
     *
     ****************************************************************/
    int32_t C_MouseManager::GetButtonReleasingCount(eButton button) const
    {
        return upImpl_->GetButtonReleasingCount(button);
    }


    /*************************************************************//**
     *
     *  @brief  ホイールを回転しているフレーム数を取得する
     *  @param  ホイールの回転方向
     *  @return ホイールを回転しているフレーム数
     *
     ****************************************************************/
    int32_t C_MouseManager::GetWheelScrollingCount(eWheelScroll wheelScroll) const
    {
        return upImpl_->GetWheelScrollingCount(wheelScroll);
    }


    /*************************************************************//**
     *
     *  @brief  ホイールを回転していないフレーム数を取得する
     *  @param  ホイールの回転方向
     *  @return ホイールを回転していないフレーム数
     *
     ****************************************************************/
    int C_MouseManager::GetWheelReleasingCount(eWheelScroll wheelScroll) const
    {
        return upImpl_->GetWheelReleasingCount(wheelScroll);
    }


    /*************************************************************//**
     *
     *  @brief  ホイールを垂直方向の回転を設定する
     *  @param  ホイールの垂直方向の回転
     *  @return なし
     *
     ****************************************************************/
    void C_MouseManager::SetWheelScrollVertical(int32_t wheelScrollVertical)
    {
        upImpl_->SetWheelScrollVertical(wheelScrollVertical);
    }
}