/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../State.h"
#include "../../GameObject/Message/Telegram/Telegram.h"


//-------------------------------------------------------------
//!
//! @brief ステート
//! @brief 状態関連の名前空間
//!
//-------------------------------------------------------------
namespace State
{
    //-------------------------------------------------------------
    //!
    //! @brief ステートマシーン
    //! @brief 状態遷移を管理するクラス
    //!
    //-------------------------------------------------------------
    template<typename T>
    class C_StateMachine
    {
    public:
         /* 別名 */
        using State = IC_State<T>;                                                                      // State型

        C_StateMachine(T* pOwner, State* pCurrentState = nullptr, State* pGlobalState = nullptr);       // コンストラクタ
        virtual ~C_StateMachine();                                                                      // デストラクタ
        void Update() const;                                                                            // 更新処理
        bool MessageProcess(const GameObject::Message::S_Telegram& rTelegram) const;                    // メッセージ処理
        void ChangeState(State* pNewState);                                                             // 新しいステートに変更
        void RevertToPreviousState();                                                                   // 以前のステートに変更
        bool CheckCurrentState(const State& rState) const;                                              // 現在のステートを確認
        State* GetCurrentState() const;                                                                 // 現在のステートを取得
        State* GetPreviousState() const;                                                                // 以前のステートを取得
        State* GetGlobalState() const;                                                                  // グローバルステートを取得
        void SetCurrentState(State* pCurrentState);                                                     // 現在のステートを設定
        void SetPreviousState(State* pPreviousState);                                                   // 以前のステートを設定
        void SetGlobalState(State* pGlobalState);                                                       // グローバルステートを設定
    private:
        T* pOwner_ = nullptr;                                                                           ///< @brief オーナー
        State* pCurrentState_ = nullptr;                                                                ///< @brief 現在のステート
        State* pPreviousState_ = nullptr;                                                               ///< @brief 以前のステート
        State* pGlobalState_ = nullptr;                                                                 ///< @brief グローバルステート
    };
}


/* 実装 */
#include "StateMachineImpl.h"
