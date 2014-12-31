/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Singleton/Singleton.h"
#include "../Window/BaseWindowEvent.h"


/* 前方宣言 */
namespace Window
{
    class C_BaseWindow;
}


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
    //! @brief イベントマネージャー
    //! @brief イベントを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_EventManager : public Singleton::C_Singleton<C_EventManager>
    {
        friend C_Singleton<C_EventManager>;                                         // シングルトンをフレンド化
    public:
        void Initialize(const Window::C_BaseWindow& rMainWindow);                   // 初期化処理
        void Update();                                                              // 更新処理
        void EntryWindowEvent(C_BaseWindowEvent* pWindowEvent);                     // ウィンドウのイベントを登録
        void EnableTextInput(bool validFlag = true);                                // テキスト入力のイベントを有効化
        bool IsFinishFlag() const;                                                  // 終了フラグを取得
    private:
        /* 前方宣言 */
        class C_EventManagerImpl;

        std::unique_ptr<C_EventManagerImpl> upImpl_;                                /// <@brief 実装情報

        C_EventManager();                                                           // コンストラクタ
        ~C_EventManager() override;                                                 // デストラクタ
    };
}