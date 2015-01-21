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
    //! @brief オプションスモールビームガンファクトリー
    //! @brief オプションの小さいビーム銃を作成するクラス
    //!
    //-------------------------------------------------------------
    class C_OptionSmallBeamGunFactory : public IC_GunFactory
    {
    public:
        C_OptionSmallBeamGunFactory();                                                                  // コンストラクタ
        ~C_OptionSmallBeamGunFactory() override;                                                        // デストラクタ
        C_BaseGun* Create(C_Shooter* pShooter, int32_t index, void* pData = nullptr) override;          // 生成処理
    };
}