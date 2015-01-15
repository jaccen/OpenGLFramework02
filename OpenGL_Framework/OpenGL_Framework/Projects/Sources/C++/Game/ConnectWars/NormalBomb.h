/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "BaseBomb.h"
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
    //! @brief ノーマルボム
    //! @brief 通常のボム
    //!
    //-------------------------------------------------------------
    class C_NormalBomb : public C_BaseBomb
    {
    public:
        C_NormalBomb(const std::string& rId, int32_t type);         // コンストラクタ
        ~C_NormalBomb() override;                                   // デストラクタ    
    private:
        int32_t stayFrame_ = 60;                                    ///< @brief ボムの残るフレーム数
        Timer::C_FrameCounter frameCounter_;                        ///< @brief フレームカウンター

        void DoUpdate() override;                                   // 非公開の更新処理
    };
}