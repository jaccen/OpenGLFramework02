/* 二重インクルード防止 */
#pragma once


//-------------------------------------------------------------
//!
//! @brief タイマー
//! @brief タイマー関連の名前空間
//!
//-------------------------------------------------------------
namespace Timer
{
    //-------------------------------------------------------------
    //!
    //! @brief フレームカウンター
    //! @brief フレーム数をカウントするクラス
    //!
    //-------------------------------------------------------------
    class C_FrameCounter
    {
    public:
        explicit C_FrameCounter(int32_t startCount = 0) ;           // コンストラクタ
        ~C_FrameCounter();                                          // デストラクタ
        void CountUp();                                             // カウントアップ
        void CountDown();                                           // カウントダウン
        void Reset();                                               // リセット
        void EnableAutoReset(bool validFlag = true);                // 自動リセットを有効化
        int32_t GetCount() const;                                   // カウント数を取得
        int32_t GetAutoResetCount() const;                          // 自動リセットカウント数を取得
        void SetCount(int32_t count);                               // カウント数を設定
        void SetAutoResetCount(int32_t autoResetCount);             // 自動リセットカウント数を設定
    private:
        int32_t count_ = 0;                                         ///< @brief カウント数
        int32_t autoResetCount_ = 0;                                ///< @brief 自動リセットカウント数
        bool autoResetFlag_ = false;                                ///< @brief 自動リセットを判断するフラグ
    };
}
