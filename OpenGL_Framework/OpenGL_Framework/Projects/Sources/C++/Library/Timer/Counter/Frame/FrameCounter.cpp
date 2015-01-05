/* ヘッダファイル */
#include "FrameCounter.h"


//-------------------------------------------------------------
//!
//! @brief タイマー
//! @brief タイマー関連の名前空間
//!
//-------------------------------------------------------------
namespace Timer
{
    /* プロトタイプ宣言 */
    static void s_JudgeReset(int32_t* pCount, int32_t resetCount, bool resetFlag);


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  スタートカウント数
     *
     ****************************************************************/
    C_FrameCounter::C_FrameCounter(int32_t startCount) :

        // カウント数
        count_(startCount)

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_FrameCounter::~C_FrameCounter()
    {
    }


    /*************************************************************//**
     *
     *  @brief  カウントアップを行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_FrameCounter::CountUp()
    {
        ++count_;
        s_JudgeReset(&count_, autoResetCount_, autoResetFlag_);
    }


    /*************************************************************//**
     *
     *  @brief  カウントダウンを行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_FrameCounter::CountDown()
    {
        --count_;
        s_JudgeReset(&count_, autoResetCount_, autoResetFlag_);
    }


    /*************************************************************//**
     *
     *  @brief  カウント数のリセットを行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_FrameCounter::Reset()
    {
        count_ = 0;
    }


    /*************************************************************//**
     *
     *  @brief  自動リセットを有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_FrameCounter::EnableAutoReset(bool validFlag)
    {
        autoResetFlag_ = validFlag;
    }


    /*************************************************************//**
     *
     *  @brief  カウント数を取得する
     *  @param  なし
     *  @return カウント数
     *
     ****************************************************************/
    int32_t C_FrameCounter::GetCount() const
    {
        return count_;
    }


    /*************************************************************//**
     *
     *  @brief  自動リセットカウント数を取得する
     *  @param  なし
     *  @return 自動リセットカウント数
     *
     ****************************************************************/
    int32_t C_FrameCounter::GetAutoResetCount() const
    {
        return autoResetCount_;
    }


    /*************************************************************//**
     *
     *  @brief  カウント数を設定する
     *  @param  カウント数
     *  @return なし
     *
     ****************************************************************/
    void C_FrameCounter::SetCount(int32_t count)
    {
        count_ = count;
    }


    /*************************************************************//**
     *
     *  @brief  自動リセットカウント数を設定する
     *  @param  自動リセットカウント数
     *  @return なし
     *
     ****************************************************************/
    void C_FrameCounter::SetAutoResetCount(int32_t autoResetCount)
    {
        autoResetCount_ = autoResetCount;
    }


    /*************************************************************//**
     *
     *  @brief  リセットの判断を行う
     *  @param  カウント数
     *  @param  リセットカウント数
     *  @param  リセットするか判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void s_JudgeReset(int32_t* pCount, int32_t resetCount, bool resetFlag)
    {
        if (resetFlag == true)
        {
            if (*pCount == resetCount)
            {
                *pCount = 0;
            }
        }
    }
}