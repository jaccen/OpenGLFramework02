/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Task.h"
#include <forward_list>


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
    //! @brief ジェネラルタスクシステム
    //! @brief 汎用タスクの実行を管理するためのクラス
    //!
    //-------------------------------------------------------------
    class C_GeneralTaskSystem
    {
    public:
        C_GeneralTaskSystem();                                          // コンストラクタ
        virtual ~C_GeneralTaskSystem();                                 // デストラクタ

        /*************************************************************//**
         *
         *  @brief  タスクの追加処理を行う
         *  @param  描画優先度
         *  @param  追加するタスクのコンストラクタの引数
         *  @return なし
         *
         ****************************************************************/
        template<typename T>
        T* Entry(const std::shared_ptr<T>& sprTask, float updatePriority, float drawPriority)
        {
            // 新しいタスクを作成し、追加
            std::shared_ptr<C_Task<T>> spNewTask = std::make_shared<C_Task<T>>(sprTask, updatePriority, drawPriority);
            pReserveTasks_.push_front(spNewTask);

            return sprTask.get();
        }

        virtual void Update();                                          // 更新処理
        virtual void Draw();                                            // 描画処理
        void AllRemove();                                               // 全てのタスクを除去
        void EnableUpdatePrioritySort(bool validFlag = true);           // 更新優先度でのソートを有効化
        void EnableDrawPrioritySort(bool validFlag = true);             // 描画優先度でのソートを有効化
    private:
        std::forward_list<TaskPtr> pUpdateTaskList_;                    ///< @brief 更新タスクリスト
        std::forward_list<TaskWeakPtr> wpDrawTaskList_;                 ///< @brief 描画タスクリスト
        std::forward_list<TaskPtr> pReserveTasks_;                      ///< @brief 予約タスク
        bool updatePrioritySortFlag_ = true;                            ///< @brief 更新優先度でのソートを行うか判断するフラグ
        bool drawPrioritySortFlag_ = true;                              ///< @brief 描画優先度でのソートを行うか判断するフラグ

        virtual void MergeReserveTask();                                // 予約タスクのマージ処理
    };
}
