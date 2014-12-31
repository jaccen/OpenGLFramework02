/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Singleton/Singleton.h"
#include <SDL_ttf.h>


//-------------------------------------------------------------
//!
//! @brief フォント
//! @brief フォント関連の名前空間
//!
//-------------------------------------------------------------
namespace Font
{
    /* 別名 */
    using Font = TTF_Font;                                                                                  // Font型
    using FontPtr = std::shared_ptr<Font>;                                                                  // FontPtr型


    //-------------------------------------------------------------
    //!
    //! @brief フォントマネージャー
    //! @brief フォントを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_FontManager : public Singleton::C_Singleton<C_FontManager>
    {
        friend C_Singleton<C_FontManager>;                                                                  // シングルトンクラスをフレンド化
    public:
        bool Initialize();                                                                                  // 初期化処理
        void Finalize();                                                                                    // 終了処理
        bool Load(const std::string& rFilePath, int32_t size);                                              // ロード処理
        void Release(const std::string& rFilePath, int32_t size);                                           // 解放処理
        void AllRelease();                                                                                  // 全て解放
        boost::optional<const FontPtr&> GetFont(const std::string& rFilePath, int32_t size) const;          // フォントを取得
    private:
        /* 前方宣言 */
        class C_FontManagerImpl;

        std::unique_ptr<C_FontManagerImpl> upImpl_;                                                         ///< @brief 実装情報

        C_FontManager();                                                                                    // コンストラクタ
        ~C_FontManager() override;                                                                          // デストラクタ
    };
}
