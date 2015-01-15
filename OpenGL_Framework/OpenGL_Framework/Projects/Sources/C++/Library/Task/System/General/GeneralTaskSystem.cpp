/* ヘッダファイル */
#include "GeneralTaskSystem.h"
#include "../../FunctionObject/TaskFunctionObject.h"


//-------------------------------------------------------------
//!
//! @brief タスク
//! @brief タスク関連の名前空間
//!
//-------------------------------------------------------------
namespace Task
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_GeneralTaskSystem::C_GeneralTaskSystem()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_GeneralTaskSystem::~C_GeneralTaskSystem()
    {
        if (pUpdateTaskList_.empty() == false) AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  タスクの更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_GeneralTaskSystem::Update()
    {
        // 予約タスクのマージ処理
        MergeReserveTask();

        // ループカウンタ
        int32_t loopCount = 0;

        // イテレータ
        auto iterator = pUpdateTaskList_.begin();

        // 全てのタスクを更新
        while (iterator != pUpdateTaskList_.end())
        {
            // 更新後、そのタスクが終了すべき場合はリストから除去する
            if ((*iterator)->Update() == false)
            {
                iterator = pUpdateTaskList_.erase_after(std::next(pUpdateTaskList_.before_begin(), loopCount));
                continue;
            }

            ++iterator;
            ++loopCount;
        }
    }


    /*************************************************************//**
     *
     *  @brief  タスクの描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_GeneralTaskSystem::Draw()
    {
        // ループカウンタ
        int32_t loopCount = 0;

        // イテレータ
        auto iterator = wpDrawTaskList_.begin();

        // 全てのタスクを描画
        while (iterator != wpDrawTaskList_.end())
        {
            // 監視しているタスクを取得できた場合は描画、できない場合はそのタスクを除去する
            if ((*iterator).expired() == false)
            {
                auto pTask = (*iterator).lock();
                pTask->Draw();

                ++iterator;
                ++loopCount;
            }
            else
            {
                iterator = wpDrawTaskList_.erase_after(std::next(wpDrawTaskList_.before_begin(), loopCount));
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  全てのタスクを除去する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_GeneralTaskSystem::AllRemove()
    {
        pUpdateTaskList_.clear();
        pReserveTasks_.clear();
        wpDrawTaskList_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  更新優先度でのソートを有効化する
     *  @param  有効化を判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_GeneralTaskSystem::EnableUpdatePrioritySort(bool validFlag)
    {
        updatePrioritySortFlag_ = validFlag;
    }


    /*************************************************************//**
     *
     *  @brief  描画優先度でのソートを有効化する
     *  @param  有効化を判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_GeneralTaskSystem::EnableDrawPrioritySort(bool validFlag)
    {
        drawPrioritySortFlag_ = validFlag;
    }


    /*************************************************************//**
     *
     *  @brief  予約タスクのマージを行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_GeneralTaskSystem::MergeReserveTask()
    {
        if (pReserveTasks_.empty() == false)
        {
            // 予約タスクを各タスクリストにマージ
            for (auto& prReserveTask : pReserveTasks_)
            {
                pUpdateTaskList_.push_front(prReserveTask);
                wpDrawTaskList_.emplace_front(prReserveTask);
            }

            // 各タスクリストを優先度でソート
            if (updatePrioritySortFlag_ == true) pUpdateTaskList_.sort(C_UpdateTaskSortObject());
            if (drawPrioritySortFlag_ == true) wpDrawTaskList_.sort(C_DrawTaskSortObject());

            pReserveTasks_.clear();
        }
    }
}