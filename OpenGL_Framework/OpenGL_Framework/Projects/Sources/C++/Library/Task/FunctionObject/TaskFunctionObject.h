/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Task.h"


//-------------------------------------------------------------
//!
//! @brief タスク
//! @brief タスク関連の名前空間
//!
//-------------------------------------------------------------
namespace Task
{
    //-------------------------------------------------------------
    //!
    //! @brief アップデートタスクソートオブジェクト
    //! @brief 更新順序をソートする関数オブジェクト
    //!
    //-------------------------------------------------------------
    class C_UpdateTaskSortObject
    {
    public:
        /*************************************************************//**
         *
         *  @brief  関数呼び出し演算子のオーバーロード
         *  @param  タスク
         *  @param  もう一つのタスク
         *  @return なし
         *
         ****************************************************************/
        bool operator()(const TaskPtr& prTask, const TaskPtr& prAnotherTask)
        {
            return prTask->GetUpdatePriority() > prAnotherTask->GetUpdatePriority();
        }
    };



    //-------------------------------------------------------------
    //!
    //! @brief ドロータスクソートオブジェクト
    //! @brief 描画順序をソートする関数オブジェクト
    //!
    //-------------------------------------------------------------
    class C_DrawTaskSortObject
    {
    public:
        /*************************************************************//**
         *
         *  @brief  関数呼び出し演算子のオーバーロード
         *  @param  タスク
         *  @param  もう一つのタスク
         *  @return なし
         *
         ****************************************************************/
        bool operator()(const TaskWeakPtr& prTask, const TaskWeakPtr& prAnotherTask)
        {
            if (prTask.expired() == false && prAnotherTask.expired() == false)
            {
                auto pTask = prTask.lock();
                auto pAnotherTask = prAnotherTask.lock();

                return pTask->GetDrawPriority() > pAnotherTask->GetDrawPriority();
            }

            // ※ 注 フレームスキップを入れることでここに入る場合があるが動作上は問題はない

            return false;
        }
    };
}