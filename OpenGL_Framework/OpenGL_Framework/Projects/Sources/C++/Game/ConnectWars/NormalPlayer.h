/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "BasePlayer.h"


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
    //! @brief ノーマルプレイヤー
    //! @brief 通常のプレイヤーを表すクラス
    //!
    //-------------------------------------------------------------
    class C_NormalPlayer : public C_BasePlayer
    {
    public:
        C_NormalPlayer(const std::string& rId, int32_t type);                   // コンストラクタ
        ~C_NormalPlayer() override;                                             // デストラクタ
    private:
    };
}