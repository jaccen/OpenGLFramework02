/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "BaseGun.h"


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
    //! @brief ノーマルガン
    //! @brief 通常の銃を表すクラス
    //!
    //-------------------------------------------------------------
    class C_NormalGun : public C_BaseGun
    {
    public:
        C_NormalGun(C_Shooter* pShooter);       // コンストラクタ
        ~C_NormalGun() override;                // デストラクタ
    private:
        void DoShot() override;                 ///< @brief 非公開の射撃処理
    };
}