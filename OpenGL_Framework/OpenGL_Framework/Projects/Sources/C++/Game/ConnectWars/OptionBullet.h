/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "BaseBullet.h"
#include "../../Library/Sprite/Creater/SpriteCreater.h"


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
    //! @brief オプションスモールビームバレット
    //! @brief オプションの小さいビーム弾を表すクラス
    //!
    //-------------------------------------------------------------
    class C_OptionSmallBeamBullet : public C_BaseBullet
    {
    public:
        C_OptionSmallBeamBullet(const std::string& rId,                 // コンストラクタ
                                int32_t type,
                                int32_t shooterType);               
        ~C_OptionSmallBeamBullet() override;                            // デストラクタ
    private:
        Sprite::SpriteCreaterWeakPtr wpSpriteCreater_;                  ///< @brief スプライトクリエイター
        Sprite::S_CreateData spriteCreateData_;                         ///< @brief スプライトの作成情報

        void DoDraw() override;                                         // 非公開の描画処理
    };
}