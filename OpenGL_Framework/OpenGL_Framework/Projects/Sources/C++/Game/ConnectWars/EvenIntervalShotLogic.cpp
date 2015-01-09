/* ヘッダファイル */
#include "EvenIntervalShotLogic.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{


#pragma region 静的メンバ変数の初期化


    /* 無限回の射撃数 */
    const int32_t C_EvenIntervalShotLogic::s_INFINITE_SHOT_COUNT = -1;


#pragma endregion


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  射撃の間隔
     *
     ****************************************************************/
    C_EvenIntervalShotLogic::C_EvenIntervalShotLogic(int32_t shotInterval,
                                                     int32_t shotStartDelay,
                                                     int32_t maxShotCount) : C_ShotLogic(shotInterval),

        // 射撃開始の遅延フレーム数
        shotStartDelay_(shotStartDelay),

        // 最大射撃数
        maxShotCount_(maxShotCount)

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_EvenIntervalShotLogic::~C_EvenIntervalShotLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  非公開の処理を行う
     *  @param  なし
     *  @return 射撃準備完了：true
     *  @return 射撃準備中  ：false
     *
     ****************************************************************/
    bool C_EvenIntervalShotLogic::DoProcess()
    {
        bool shotReadyFlag = false;

        if ((frameCounter_.GetCount() >= shotStartDelay_)
         && (maxShotCount_ == s_INFINITE_SHOT_COUNT || shotCount_ < maxShotCount_))
        {
            if (frameCounter_.GetCount() % shotInterval_ == 0)
            {
                ++shotCount_;
                shotReadyFlag = true;
            }
        }

        // カウントアップ
        frameCounter_.CountUp();

        return shotReadyFlag;
    }
}