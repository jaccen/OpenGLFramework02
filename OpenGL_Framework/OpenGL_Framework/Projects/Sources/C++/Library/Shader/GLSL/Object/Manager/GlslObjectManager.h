/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../../../Singleton/Singleton.h"
#include "../GlslObject.h"
#include <boost/optional.hpp>


//-------------------------------------------------------------
//!
//! @brief シェーダー
//! @brief シェーダー関連の名前空間
//!
//-------------------------------------------------------------
namespace Shader
{
    //-------------------------------------------------------------
    //!
    //! @brief GLSL
    //! @brief GLSL関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace GLSL
    {
        /* 別名 */
        using GlslObjectPtr = std::shared_ptr<C_GlslObject>;                                        // GlslObjectPtr型


        //-------------------------------------------------------------
        //!
        //! @brief GLSLオブジェクトマネージャー
        //! @brief GLSLオブジェクトを管理するクラス
        //!
        //-------------------------------------------------------------
        class C_GlslObjectManager : public Singleton::C_Singleton<C_GlslObjectManager>
        {
            friend C_Singleton<C_GlslObjectManager>;
        public:
            void Entry(const GlslObjectPtr& prGlslObject, const std::string& rId);                  // 登録処理
            void Remove(const std::string& rId);                                                    // 除去処理
            void AllRemove();                                                                       // 全てのGLSLオブジェクトを除去
            boost::optional<const GlslObjectPtr&> GetGlslObject(const std::string& rId) const;      // GLSLオブジェクトを取得
        private:
            /* 前方宣言 */
            class C_GlslObjectManagerImpl;

            std::unique_ptr<C_GlslObjectManagerImpl> upImpl_;                                       ///< @brief 実装情報

            C_GlslObjectManager();                                                                  // コンストラクタ
            ~C_GlslObjectManager() override;                                                        // デストラクタ
        };
    }
}
