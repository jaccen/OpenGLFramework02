/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ShotLogic.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief イーブンインターバルショットロジック
    //! @brief 等間隔の射撃のロジック
    //!
    //-------------------------------------------------------------
    class C_EvenIntervalShotLogic : public C_ShotLogic
    {
    public:
        /* 定数 */
        static const int32_t s_INFINITE_SHOT_COUNT;             ///< @brief 無限回の射撃数

        C_EvenIntervalShotLogic(int32_t shotInterval,           // コンストラクタ
                                int32_t shotStartDelay,
                                int32_t maxShotCount);
        ~C_EvenIntervalShotLogic() override;                    // デストラクタ
    private:
        int32_t shotStartDelay_ = 0;                            ///< @brief 射撃開始の遅延フレーム数
        int32_t shotCount_ = 0;                                 ///< @brief 射撃回数
        int32_t maxShotCount_ = 1;                              ///< @brief 最大射撃回数
        Timer::C_FrameCounter frameCounter_;                    ///< @brief フレームカウンター

        bool DoProcess() override;                              // 非公開の処理
    };
}