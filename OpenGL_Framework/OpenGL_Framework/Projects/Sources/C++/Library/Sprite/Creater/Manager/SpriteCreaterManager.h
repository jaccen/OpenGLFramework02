/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../../Singleton/Assert/AssertSingleton.h"
#include "../../../Texture/TextureDefine.h"
#include "../SpriteCreater.h"


//-------------------------------------------------------------
//!
//! @brief スプライト
//! @brief スプライト関連の名前空間
//!
//-------------------------------------------------------------
namespace Sprite
{
    /* 別名 */
    using SpriteCreaterWeakPtr = std::weak_ptr<IC_SpriteCreater>;                                                   // SpriteCreaterWeakPtr型


    //-------------------------------------------------------------
    //!
    //! @brief スプライトクリエイターマネージャー
    //! @brief スプライトクリエイターを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_SpriteCreaterManager : public Singleton::C_AssertSingleton<C_SpriteCreaterManager>
    {
    public:
        C_SpriteCreaterManager();                                                                                   // コンストラクタ
        ~C_SpriteCreaterManager() override;                                                                         // デストラクタ
        void Draw();                                                                                                // 描画処理
        bool Create(const std::string& rId,                                                                         // スプライトクリエイターを作成
                    const Camera::CameraPtr& prCamera,
                    const Texture::TextureDataPtr pTextureData,
                    uint32_t maxSpriteCount = 100);
        void Destroy(const std::string& rId);                                                                       // スプライトクリエイターを破棄
        void AllDestroy();                                                                                          // スプライトクリエイターを全て破棄
        boost::optional<SpriteCreaterWeakPtr> GetSpriteCreater(const std::string& rId);                             // スプライトクリエイターを取得
    private:
        /* 前方宣言 */
        class C_SpriteCreaterManagerImpl;

        std::unique_ptr<C_SpriteCreaterManagerImpl> upImpl_;                                                        ///< @brief 実装情報
    };
}