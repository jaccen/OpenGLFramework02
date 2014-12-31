/* ヘッダファイル */
#include "MainWindowEvent.h"
#include "../../../OpenGL/Manager/OpenGlManager.h"
#include "../../../Window/Manager/WindowManager.h"


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
     *  @param  ウィンドウのID
     *
     ****************************************************************/
    C_MainWindowEvent::C_MainWindowEvent(uint32_t windowId) : C_BaseWindowEvent(windowId)
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_MainWindowEvent::~C_MainWindowEvent()
    {
    }


    /*************************************************************//**
     *
     *  @brief  イベントの処理を行う
     *  @param  イベント
     *  @return イベント維持：true
     *  @return イベント破棄：false
     *
     ****************************************************************/
    bool C_MainWindowEvent::Process(EventData& rEvent)
    {
        switch (rEvent.window.event)
        {
        /* ウィンドウをリサイズ */
        case WindowEventType::SDL_WINDOWEVENT_RESIZED:
        {
            // 座標を取得
            int32_t positionX = 0, positionY = 0;
            ::SDL_GetWindowPosition(::SDL_GetWindowFromID(windowId_), &positionX, &positionY);

            // 幅と高さを設定し、ビューポートを再設定
            assert(Window::C_WindowManager::s_GetInstance()->GetWindow());

            auto pWindow = Window::C_WindowManager::s_GetInstance()->GetWindow().get();

            pWindow->SetWidth(rEvent.window.data1);
            pWindow->SetHeight(rEvent.window.data2);

            OpenGL::C_OpenGlManager::s_GetInstance()->SetViewport(positionX, positionY, rEvent.window.data1, rEvent.window.data2);
        }
            break;
        /* ウィンドウを閉じる */
        case WindowEventType::SDL_WINDOWEVENT_CLOSE:

            // イベントに終了させるイベントを設定する
            rEvent.type = SDL_QUIT;
            ::SDL_PushEvent(&rEvent);

            return false;

            break;
        }

        return true;
    }
}