/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "BackgroundMoveLogic.h"


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
    //! @brief バックグラウンドムーブロジック
    //! @brief 背景の移動のロジックの基底クラス
    //!
    //-------------------------------------------------------------
    class C_BackgroundStraightMoveLogic : public C_BackgroundMoveLogic
    {
    public:
        C_BackgroundStraightMoveLogic();                            // コンストラクタ
        ~C_BackgroundStraightMoveLogic() override;                  // デストラクタ
    private:
        void DoProcess(Background* pBackground) override;           ///< @brief 非公開の処理
    };
}