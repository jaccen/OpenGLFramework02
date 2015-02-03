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
    /* 前方宣言 */
    class C_BaseGun;


    //-------------------------------------------------------------
    //!
    //! @brief スモールビームオプション
    //! @brief 小さいビーム弾を撃つオプションを表すクラス
    //!
    //-------------------------------------------------------------
    class C_SmallBeamOption : public C_BaseOption
    {
    public:
        C_SmallBeamOption(const std::string& rId, int32_t type);            // コンストラクタ
        virtual ~C_SmallBeamOption() override;                              // デストラクタ
        void ConnectEffect() override;                                      // 連結時の効果
    private:
        int32_t gunDataCount_ = 0;                                          ///< @brief 銃の情報の数

        void DoDraw() override;                                             // 非公開の描画処理
    };
}