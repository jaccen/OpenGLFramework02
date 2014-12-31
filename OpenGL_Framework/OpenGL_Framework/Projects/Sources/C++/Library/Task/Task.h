/* 二重インクルード防止 */
#pragma once


//-------------------------------------------------------------
//!
//! @brief タスク
//! @brief タスク関連の名前空間
//!
//-------------------------------------------------------------
namespace Task
{
    /* 前方宣言 */
    class IC_Task;


    /* 別名 */
    using TaskPtr = std::shared_ptr<IC_Task>;                                   // TaskPtr型
    using TaskWeakPtr = std::weak_ptr<IC_Task>;                                 // TaskWeakPtr型


    //-------------------------------------------------------------
    //!
    //! @brief タスク( インターフェース )
    //! @brief タスクのインターフェース
    //!
    //-------------------------------------------------------------
    class IC_Task
    {
    public:
        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        IC_Task(float updatePriority, float drawPriority) :

            // 更新優先度
            updatePriority_(updatePriority),

            // 描画優先度
            drawPriority_(drawPriority)

        {
        }

        virtual ~IC_Task() = default;                                           //!< @brief デフォルトデストラクタ
        virtual bool Update() = 0;                                              //!< @brief 更新処理
        virtual void Draw() = 0;                                                //!< @brief 描画処理

        /*************************************************************//**
         *
         *  @brief  更新優先度を取得する
         *  @param  なし
         *  @return 更新優先度
         *
         ****************************************************************/
        float GetUpdatePriority() const
        {
            return updatePriority_;
        }

        /*************************************************************//**
         *
         *  @brief  描画優先度を取得する
         *  @param  なし
         *  @return 描画優先度
         *
         ****************************************************************/
        float GetDrawPriority() const
        {
            return drawPriority_;
        }
    private:
        float updatePriority_ = 0.0f;                                           ///< @brief 更新優先度
        float drawPriority_ = 0.0f;                                             ///< @brief 描画優先度
    };


    //-------------------------------------------------------------
    //!
    //! @brief タスク
    //! @brief タスクを表すクラス
    //!
    //-------------------------------------------------------------
    template<typename T>
    class C_Task : public IC_Task
    {
    public:

        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  優先度
         *
         ****************************************************************/
        C_Task(const std::shared_ptr<T>& sprTask, float updatePriority, float drawPriority) : IC_Task(updatePriority, drawPriority),

            // タスク
            spTask_(sprTask)

        {
        }

        ~C_Task() override = default;                                   //!< @brief デフォルトデストラクタ

        /*************************************************************//**
         *
         *  @brief  更新処理を行う
         *  @param  なし
         *  @return タスクを続行：true
         *  @return タスクを終了：false
         *
         ****************************************************************/
        bool Update()
        {
            return spTask_->Update();
        }

        /*************************************************************//**
         *
         *  @brief  描画処理を行う
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void Draw()
        {
            spTask_->Draw();
        }

        /*************************************************************//**
         *
         *  @brief  タスクを取得する
         *  @param  なし
         *  @return タスク
         *
         ****************************************************************/
        T* GetTask() const
        {
            return spTask_.get();
        }
    private:
        std::shared_ptr<T> spTask_;                                     ///< @brief タスク
    };
}