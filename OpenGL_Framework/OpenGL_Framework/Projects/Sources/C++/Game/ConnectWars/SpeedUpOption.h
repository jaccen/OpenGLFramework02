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
    //! @brief スピードアップオプション
    //! @brief 移動速度を上げるオプションを表すクラス
    //!
    //-------------------------------------------------------------
    class C_SpeedUpOption : public C_BaseOption
    {
    public:
        C_SpeedUpOption(const std::string& rId, int32_t type);          // コンストラクタ
        virtual ~C_SpeedUpOption() override;                            // デストラクタ
        void ConnectEffect() override;                                  // 連結時の効果
        void ResetEffect() override;                                    // 効果をリセット
    private:
        void DoDraw() override;                                         // 非公開の描画処理
    };
}