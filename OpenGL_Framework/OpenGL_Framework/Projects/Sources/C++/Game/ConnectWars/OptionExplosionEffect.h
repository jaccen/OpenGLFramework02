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
    //! @brief オプションエクスプローションエフェクト
    //! @brief オプションの爆発のエフェクト
    //!
    //-------------------------------------------------------------
    class C_OptionExplosionEffect : public C_BaseEffect
    {
    public:
        C_OptionExplosionEffect(const std::string& rId, int32_t type);              // コンストラクタ
        virtual ~C_OptionExplosionEffect() override;                                // デストラクタ
    private:
        Particle::ParticleSystemWeakPtr wpCircleParticleSystem_;                    ///< @brief 円のパーティクルシステム
        Particle::ParticleSystemWeakPtr wpSmokeParticleSystem_;                     ///< @brief 煙のパーティクルシステム

        void DoUpdate() override;                                                   // 非公開の更新処理
        void DoDraw() override;                                                     // 非公開の描画処理
        bool DoMessageProcess(const Telegram& rTelegram) override;                  // 非公開のメッセージ処理
    };
}