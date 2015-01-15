/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "BaseGun.h"
#include "../../Library/Debug/Helper/DebugHelper.h"


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
    //! @brief ガンファクトリー( インターフェース )
    //! @brief 順の生成を行うクラスのインターフェース
    //!
    //-------------------------------------------------------------
    class IC_GunFactory
    {
    public:
        IC_GunFactory() = default;                                                                      // コンストラクタ
        virtual ~IC_GunFactory() = default;                                                             // デストラクタ
        virtual C_BaseGun* Create(C_Shooter* pShooter, int32_t index, void* pData = nullptr) = 0;       // 生成処理
    };
}