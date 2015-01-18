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
        using StatePtr = IC_State<T>*;                                                                  // StatePtr型

        C_StateMachine(T* pOwner);																		// コンストラクタ
        virtual ~C_StateMachine();                                                                      // デストラクタ
        void Update() const;                                                                            // 更新処理
        bool MessageProcess(const GameObject::Message::S_Telegram& rTelegram) const;                    // メッセージ処理
        void ChangeState(StatePtr pNewState);															// 新しいステートに変更
        void RevertToPreviousState();                                                                   // 以前のステートに変更
		bool CheckCurrentState(StatePtr pState) const;													// 現在のステートを確認
        StatePtr GetCurrentState() const;																// 現在のステートを取得
        StatePtr GetPreviousState() const;																// 以前のステートを取得
        StatePtr GetGlobalState() const;																// グローバルステートを取得
        void SetCurrentState(StatePtr pCurrentState);													// 現在のステートを設定
        void SetPreviousState(StatePtr pPreviousState);													// 以前のステートを設定
        void SetGlobalState(StatePtr pGlobalState);														// グローバルステートを設定
    private:
        T* pOwner_ = nullptr;                                                                           ///< @brief オーナー
        StatePtr pCurrentState_ = nullptr;																///< @brief 現在のステート
        StatePtr pPreviousState_ = nullptr;																///< @brief 以前のステート
        StatePtr pGlobalState_ = nullptr;																///< @brief グローバルステート
    };
}


/* 実装 */
#include "StateMachineImpl.h"
