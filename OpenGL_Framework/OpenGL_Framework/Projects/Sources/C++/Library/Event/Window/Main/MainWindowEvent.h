/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../BaseWindowEvent.h"


//-------------------------------------------------------------
//!
//! @brief イベント
//! @brief イベント関連の名前空間
//!
//-------------------------------------------------------------
namespace Event
{
    //-------------------------------------------------------------
    //!
    //! @brief メインウィンドウイベント
    //! @brief メインウィンドウのイベントの処理をまとめたクラス
    //!
    //-------------------------------------------------------------
    class C_MainWindowEvent : public C_BaseWindowEvent
    {
    public:
        C_MainWindowEvent(uint32_t windowId);               // コンストラクタ
        ~C_MainWindowEvent() override;                      // デストラクタ
        bool Process(EventData& rEvent) override;           // イベントの処理
    };
}