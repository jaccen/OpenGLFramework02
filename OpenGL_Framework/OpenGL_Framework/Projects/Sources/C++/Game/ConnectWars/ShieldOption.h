/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "BaseOption.h"


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
    //! @brief シールドオプション
    //! @brief シールドを張るオプションを表すクラス
    //!
    //-------------------------------------------------------------
    class C_ShieldOption : public C_BaseOption
    {
    public:
        C_ShieldOption(const std::string& rId, int32_t type);           // コンストラクタ
        virtual ~C_ShieldOption() override;                             // デストラクタ
        void ConnectEffect() override;                                  // 連結時の効果
    private:
        void DoDraw() override;                                         // 非公開の描画処理
    };
}