/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../../Singleton/Assert/AssertSingleton.h"
#include "../../../Texture/TextureDefine.h"
#include "../ParticleSystem.h"


//-------------------------------------------------------------
//!
//! @brief パーティクル
//! @brief パーティクル関連の名前空間
//!
//-------------------------------------------------------------
namespace Particle
{
    //-------------------------------------------------------------
    //!
    //! @brief パーティクルシステムマネージャー
    //! @brief パーティクルシステムを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_ParticleSystemManager : public Singleton::C_AssertSingleton<C_ParticleSystemManager>
    {
    public:
        C_ParticleSystemManager();                                                                              // コンストラクタ
        ~C_ParticleSystemManager() override;                                                                    // デストラクタ
        void Update();                                                                                          // 更新処理
        void Draw();                                                                                            // 描画処理
        bool Create(const std::string& rId,                                                                     // パーティクスシステムを作成
                    const Camera::CameraPtr& prCamera,
                    Texture::TextureHandle textureHandle,
                    uint32_t maxParticleCount = 10000);
        void Destroy(const std::string& rId);                                                                   // パーティクルシステムを破棄
        void AllDestroy();                                                                                      // パーティクルシステムを全て破棄
        boost::optional<ParticleSystemWeakPtr> GetParticleSystem(const std::string& rId);                       // パーティクルシステムを取得
    private:
        /* 前方宣言 */
        class C_ParticleSystemManagerImpl;

        std::unique_ptr<C_ParticleSystemManagerImpl> upImpl_;                                                   ///< @brief 実装情報
    };
}
