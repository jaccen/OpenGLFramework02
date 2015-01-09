/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "BaseGun.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* 前方宣言 */
    class C_Shooter;


    //-------------------------------------------------------------
    //!
    //! @brief ラピッドファイヤーガン
    //! @brief 連射銃を表すクラス
    //!
    //-------------------------------------------------------------
    class C_RapidFireGun : public C_BaseGun
    {
    public:
        C_RapidFireGun(C_Shooter* pShooter,                 // コンストラクタ
                       int32_t rapidFireCount,
                       int32_t rapidFireInterval = 0);
        ~C_RapidFireGun() override;                         // デストラクタ
    private:
        int32_t shotCount_ = 0;                             ///< @brief 射撃回数
        int32_t rapidFireCount_ = 1;                        ///< @brief 連射回数
        int32_t rapidFireInterval_ = 1;                     ///< @brief 連射間隔
        Timer::C_FrameCounter frameCounter_;                ///< @brief フレームカウンタ

        void DoShot() override;                             // 非公開の射撃処理
    };
}