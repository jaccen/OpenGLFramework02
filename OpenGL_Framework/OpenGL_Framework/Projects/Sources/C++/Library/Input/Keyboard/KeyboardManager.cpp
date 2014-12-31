/* ヘッダファイル */
#include "keyboardManagerImpl.h"


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
    C_KeyboardManager::C_KeyboardManager() :

        // 実装情報
        upImpl_(std::make_unique<C_KeyboardManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_KeyboardManager::~C_KeyboardManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_KeyboardManager::Initialize()
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
    void C_KeyboardManager::Update()
    {
        upImpl_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  押しているフレーム数を取得する
     *  @param  スキャンコード
     *  @return 押しているフレーム数
     *
     ****************************************************************/
    int32_t C_KeyboardManager::GetPressingCount(KeyCode keycode) const
    {
        return upImpl_->GetPressingCount(keycode);
    }


    /*************************************************************//**
     *
     *  @brief  離しているフレーム数を取得する
     *  @param  スキャンコード
     *  @return 離しているフレーム数
     *
     ****************************************************************/
    int32_t C_KeyboardManager::GetReleasingCount(KeyCode keycode) const
    {
        return upImpl_->GetReleasingCount(keycode);
    }


    /*************************************************************//**
     *
     *  @brief  入力した文字を取得する
     *  @param  なし
     *  @return 入力した文字
     *
     ****************************************************************/
    const std::string& C_KeyboardManager::GetInputCharacter() const
    {
        return upImpl_->GetInputCharacter();
    }


    /*************************************************************//**
     *
     *  @brief  入力した文字を設定する
     *  @param  入力した文字
     *  @return なし
     *
     ****************************************************************/
    void C_KeyboardManager::SetInputCharacter(const std::string& rInputCharacter)
    {
        upImpl_->SetInputCharacter(rInputCharacter);
    }
}