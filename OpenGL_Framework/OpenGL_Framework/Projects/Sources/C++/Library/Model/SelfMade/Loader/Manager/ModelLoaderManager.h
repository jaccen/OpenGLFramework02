/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../ModelLoader.h"
#include "../../../../Singleton/Singleton.h"


//-------------------------------------------------------------
//!
//! @brief モデル
//! @brief モデル関連の名前空間
//!
//-------------------------------------------------------------
namespace Model
{
    //-------------------------------------------------------------
    //!
    //! @brief SelfMade
    //! @brief 自作関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace SelfMade
    {
        //-------------------------------------------------------------
        //!
        //! @brief モデルローダーマネージャー
        //! @brief モデルローダーを管理するクラス
        //!
        //-------------------------------------------------------------
        class C_ModelLoaderManager : public Singleton::C_Singleton<C_ModelLoaderManager>
        {
            friend C_Singleton<C_ModelLoaderManager>;
        public:
            void Entry(const ModelLoaderPtr& prModelLoader, const std::string& rId);                // 登録処理
            void Remove(const std::string& rId);                                                    // 除去処理
            void AllRemove();                                                                       // 全てのモデルローダーを除去
            boost::optional<const ModelLoaderPtr&> GetModelLoader(const std::string& rId) const;    // モデルローダーを取得
        private:
            /* 前方宣言 */
            class C_ModelLoaderManagerImpl;

            std::unique_ptr<C_ModelLoaderManagerImpl> upImpl_;                                      ///< @brief 実装情報

            C_ModelLoaderManager();                                                                 // コンストラクタ
            ~C_ModelLoaderManager() override;                                                       // デストラクタ
        };
    }
}