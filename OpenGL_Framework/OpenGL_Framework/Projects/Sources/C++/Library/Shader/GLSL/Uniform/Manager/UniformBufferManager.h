/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../../../Singleton/Singleton.h"
#include "../UniformBuffer.h"


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
        //-------------------------------------------------------------
        //!
        //! @brief ユニフォームバッファマネージャー
        //! @brief ユニフォームバッファを管理するクラス
        //!
        //-------------------------------------------------------------
        class C_UniformBufferManager : public Singleton::C_Singleton<C_UniformBufferManager>
        {
            friend C_Singleton<C_UniformBufferManager>;
        public:
            void Entry(const UniformBufferPtr& prUniformBuffer, const std::string& rId);                // 登録処理
            void Remove(const std::string& rId);                                                        // 除去処理
            void AllRemove();                                                                           // 全てのユニフォームバッファを除去
            boost::optional<const UniformBufferPtr&> GetUniformBuffer(const std::string& rId) const;    // ユニフォームバッファを取得
        private:
            /* 前方宣言 */
            class C_UniformBufferManagerImpl;

            std::unique_ptr<C_UniformBufferManagerImpl> upImpl_;                                        ///< @brief 実装情報

            C_UniformBufferManager();                                                                   // コンストラクタ
            ~C_UniformBufferManager() override;                                                         // デストラクタ
        };
    }
}
