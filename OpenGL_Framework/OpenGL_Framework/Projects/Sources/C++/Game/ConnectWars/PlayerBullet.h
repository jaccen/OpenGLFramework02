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
    //! @brief プレイヤービームバレット
    //! @brief プレイヤーのビーム弾を表すクラス
    //!
    //-------------------------------------------------------------
    class C_PlayerBeamBullet : public C_BaseBullet
    {
    public:
        C_PlayerBeamBullet(const std::string& rId,                      // コンストラクタ
                           int32_t type,
                           int32_t shooterType);               
        ~C_PlayerBeamBullet() override;                                 // デストラクタ
    private:
        Sprite::SpriteCreaterWeakPtr wpSpriteCreater_;                  ///< @brief スプライトクリエイター
        Sprite::S_CreateData spriteCreateData_;                         ///< @brief スプライトの作成情報

        void DoDraw() override;                                         // 非公開の描画処理
    };
}