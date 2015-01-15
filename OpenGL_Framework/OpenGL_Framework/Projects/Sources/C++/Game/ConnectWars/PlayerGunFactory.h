/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "GunFactory.h"


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
    //! @brief プレイヤービームガンファクトリー
    //! @brief プレイヤーのビーム銃を作成するクラス
    //!
    //-------------------------------------------------------------
    class C_PlayerBeamGunFactory : public IC_GunFactory
    {
    public:
        C_PlayerBeamGunFactory();                                                                       // コンストラクタ
        ~C_PlayerBeamGunFactory() override;                                                             // デストラクタ
        C_BaseGun* Create(C_Shooter* pShooter, int32_t index, void* pData = nullptr) override;          // 生成処理
    };
}