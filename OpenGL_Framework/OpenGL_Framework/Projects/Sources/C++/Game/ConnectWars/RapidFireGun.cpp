/* ヘッダファイル */
#include "RapidFireGun.h"
#include "ShotLogic.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  射撃者
     *  @param  連射回数
     *  @param  連射間隔
     *
     ****************************************************************/
    C_RapidFireGun::C_RapidFireGun(C_Shooter* pShooter,
                                   int32_t rapidFireCount,
                                   int32_t rapidFireInterval) : C_BaseGun(pShooter),

        // 連射回数
        rapidFireCount_(rapidFireCount),

        // 連射間隔
        rapidFireInterval_(rapidFireInterval)

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_RapidFireGun::~C_RapidFireGun()
    {
    }


    /*************************************************************//**
     *
     *  @brief  非公開の射撃処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RapidFireGun::DoShot()
    {
        if (upShotLogic_->Process() == true) shotCount_ = 0;

        if (shotCount_ < rapidFireCount_)
        {
            if (frameCounter_.GetCount() == rapidFireInterval_ || shotCount_ == 0)
            {
                ++shotCount_;

                // リセット
                frameCounter_.Reset();
            }
            else
            {
                // カウントアップ
                frameCounter_.CountUp();
            }
        }
    }
}