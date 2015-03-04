/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "BaseEffect.h"
#include "../../Library/Particle/System/ParticleSystem.h"


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
    //! @brief プレイヤーフレーヤーバック
    //! @brief プレイヤーの噴射炎のエフェクト
    //!
    //-------------------------------------------------------------
    class C_PlayerFlarebackEffect : public C_BaseEffect
    {
    public:
        C_PlayerFlarebackEffect(const std::string& rId, int32_t type);              // コンストラクタ
        virtual ~C_PlayerFlarebackEffect() override;                                // デストラクタ
    private:
        Particle::ParticleSystemWeakPtr wpCircleParticleSystem_;                    ///< @brief 円のパーティクルシステム
        Particle::ParticleSystemWeakPtr wpSmokeParticleSystem_;                     ///< @brief 煙のパーティクルシステム

        void DoUpdate() override;                                                   // 非公開の更新処理
        void DoDraw() override;                                                     // 非公開の描画処理
        bool DoMessageProcess(const Telegram& rTelegram) override;                  // 非公開のメッセージ処理
    };
}