/* ヘッダファイル */
#include "EventManagerImpl.h"
#include "../../Window/Window/BaseWindow.h"
#include "../../Debug/Helper/DebugHelper.h"
#include <SDL.h>


//-------------------------------------------------------------
//!
//! @brief イベント
//! @brief イベント関連の名前空間
//!
//-------------------------------------------------------------
namespace Event
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_EventManager::C_EventManager() :

        // 実装情報
        upImpl_(std::make_unique<C_EventManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_EventManager::~C_EventManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  メインウィンドウのID
     *  @return なし
     *
     ****************************************************************/
    void C_EventManager::Initialize(const Window::C_BaseWindow& rMainWindow)
    {
        // 初期化されていない場合、初期化する
        if (::SDL_WasInit(SDL_INIT_EVENTS) == 0) ::SDL_InitSubSystem(SDL_INIT_EVENTS);

        // メインウィンドウのイベントを登録
        upImpl_->EntryWindowEvent(newEx C_MainWindowEvent(rMainWindow.GetId()));

        // テキスト入力のイベントを無効化
        EnableTextInput(false);
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_EventManager::Update()
    {
        upImpl_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  ウィンドウのイベントを登録する
     *  @param  ウィンドウのイベント
     *  @return なし
     *
     ****************************************************************/
    void C_EventManager::EntryWindowEvent(C_BaseWindowEvent* pWindowEvent)
    {
        upImpl_->EntryWindowEvent(pWindowEvent);
    }


    /*************************************************************//**
     *
     *  @brief  テキスト入力のイベントを有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_EventManager::EnableTextInput(bool validFlag)
    {
        (validFlag == true) ? ::SDL_StartTextInput() : ::SDL_StopTextInput();
    }


    /*************************************************************//**
     *
     *  @brief  終了のイベント処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_EventManager::QuitEvent()
    {
        upImpl_->QuitEvent();
    }


    /*************************************************************//**
     *
     *  @brief  終了フラグを取得する
     *  @param  なし
     *  @return 終了フラグ
     *
     ****************************************************************/
    bool C_EventManager::IsFinishFlag() const
    {
        return upImpl_->IsFinishFlag();
    }
}