/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectWarsDefine.h"
#include "BasePlayer.h"
#include "../../Library/Singleton/Assert/AssertSingleton.h"
#include <deque>


/* 前方宣言 */
namespace Task
{
    class C_GeneralTaskSystem;
}


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* 別名 */
    using PlayerPtr = std::shared_ptr<C_BasePlayer>;                            // PlayerPtr型


    //-------------------------------------------------------------
    //!
    //! @brief プレイヤージェネレーター
    //! @brief プレイヤーの生成を行うクラス
    //!
    //-------------------------------------------------------------
    class C_PlayerGenerator : public Singleton::C_AssertSingleton<C_PlayerGenerator>
    {
    public:
        C_PlayerGenerator();                                                    // コンストラクタ
        ~C_PlayerGenerator() override;                                          // デストラクタ
        PlayerPtr Create(const std::string& rId);                               // 生成処理
        void SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem);             // タスクシステムを設定
    private:
        Task::C_GeneralTaskSystem* pTaskSystem_ = nullptr;                      ///< @brief タスクシステム
    };
}