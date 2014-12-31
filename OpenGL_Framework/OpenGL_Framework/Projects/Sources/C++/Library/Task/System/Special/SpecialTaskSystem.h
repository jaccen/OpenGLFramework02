/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Task.h"
#include "../../FunctionObject/TaskFunctionObject.h"
#include <forward_list>


//-------------------------------------------------------------
//!
//! @brief タスク
//! @brief タスク関連の名前空間
//!
//-------------------------------------------------------------
namespace Task
{
    /* 別名 */
    template<typename T>
    using SpecialTaskPtr = std::shared_ptr<C_Task<T>>;                                  // SpecialTaskPtr型

    template<typename T>
    using SpecialTaskWeakPtr = std::weak_ptr<C_Task<T>>;                                // SpecialTaskWeakPtr型


    //-------------------------------------------------------------
    //!
    //! @brief スペシャルタスクシステム
    //! @brief 一部に特化したタスクの実行を管理するためのクラス
    //!
    //-------------------------------------------------------------
    template<typename T>
    class C_SpecialTaskSystem
    {
    public:
        /* 別名 */
        using SpecialTaskPtr = SpecialTaskPtr<T>;                                       // SpecialTaskPtr型を省略
        using SpecialTaskWeakPtr = SpecialTaskWeakPtr<T>;                               // SpecialTaskWeakPtr型を省略


        C_SpecialTaskSystem();                                                          // コンストラクタ
        virtual ~C_SpecialTaskSystem();                                                 // デストラクタ

        /*************************************************************//**
         *
         *  @brief  タスクの追加処理を行う
         *  @param  描画優先度
         *  @param  追加するタスクのコンストラクタの引数
         *  @return なし
         *
         ****************************************************************/
        T* Entry(const std::shared_ptr<T>& sprTask, float updatePriority, float drawPriority)
        {
            // 新しいタスクを作成し、追加
            std::shared_ptr<C_Task<T>> spNewTask = std::make_shared<C_Task<T>>(sprTask, updatePriority, drawPriority);
            pReserveTasks_.push_front(spNewTask);

            return sprTask.get();
        }

        virtual void Update();                                                          // 更新処理
        virtual void Draw();                                                            // 描画処理
        void AllRemove();                                                               // 全てのタスクを除去
        void EnableUpdatePrioritySort(bool validFlag = true);                           // 更新優先度でのソートを有効化
        void EnableDrawPrioritySort(bool validFlag = true);                             // 描画優先度でのソートを有効化
        std::forward_list<SpecialTaskPtr>& GetTaskList();                               // タスクリストを取得
    private:
        std::forward_list<SpecialTaskPtr> pUpdateTaskList_;                             ///< @brief 更新タスクリスト
        std::forward_list<SpecialTaskWeakPtr> wpDrawTaskList_;                          ///< @brief 描画タスクリスト
        std::forward_list<SpecialTaskPtr> pReserveTasks_;                               ///< @brief 予約タスク
        bool updatePrioritySortFlag_ = true;                                            ///< @brief 更新優先度でのソートを行うか判断するフラグ
        bool drawPrioritySortFlag_ = true;                                              ///< @brief 描画優先度でのソートを行うか判断するフラグ

        virtual void MergeReserveTask();                                                // 予約タスクのマージ処理
    };
}


/* 実装 */
#include "SpecialTaskSystemImpl.h"