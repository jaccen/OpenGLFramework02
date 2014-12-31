/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../GameObject/Message/Telegram/Telegram.h"


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
    //! @brief ステート( インターフェース )
    //! @brief ステートのインターフェース
    //!
    //-------------------------------------------------------------
    template<class T>
    class IC_State
    {
    public:
        IC_State() = default;                                                                   //!< @brief コンストラクタ
        virtual ~IC_State() = default;                                                          //!< @brief デストラクタ
        virtual void Enter(T* pEntity) = 0;                                                     //!< @brief 開始処理
        virtual void Execute(T* pEntity) = 0;                                                   //!< @brief 実行処理
        virtual void Exit(T* pEntity) = 0;                                                      //!< @brief 終了処理
        virtual bool MessageProcess(T* pEntity,                                                 //!< @brief メッセージ処理
                                    const GameObject::Message::S_Telegram& rTelegram) = 0;
    };
}
