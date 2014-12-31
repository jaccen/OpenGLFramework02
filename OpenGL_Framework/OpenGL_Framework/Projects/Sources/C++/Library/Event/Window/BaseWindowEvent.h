/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include <SDL_events.h>


//-------------------------------------------------------------
//!
//! @brief イベント
//! @brief イベント関連の名前空間
//!
//-------------------------------------------------------------
namespace Event
{
    /* 別名 */
    using EventData = SDL_Event;                                        // EventData型
    using WindowEventType = SDL_WindowEventID;                          // WindowEventType型

    //-------------------------------------------------------------
    //!
    //! @brief ベースウィンドウイベント
    //! @brief ウィンドウイベントの基底クラス
    //!
    //-------------------------------------------------------------
    class C_BaseWindowEvent
    {
    public:
        C_BaseWindowEvent(Uint32 windowId);                             // コンストラクタ
        virtual ~C_BaseWindowEvent() = 0;                               // デストラクタ
        virtual bool Process(EventData& rEvent) = 0;                    // イベントの処理

        /* ゲッター */
        uint32_t GetWindowId() const;                                   // ウィンドウのIDを取得
    protected:
        uint32_t windowId_ = 0;                                         ///< @brief ウィンドウのID
    };
}
