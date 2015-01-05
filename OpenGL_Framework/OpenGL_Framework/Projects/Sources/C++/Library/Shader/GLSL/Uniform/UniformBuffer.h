/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../GlslDefine.h"
#include "../../../OpenGL/OpenGlDefine.h"


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
        /* 前方宣言 */
        class C_UniformBuffer;


        /* 別名 */
        using UniformBufferPtr = std::shared_ptr<C_UniformBuffer>;                      // UniformBufferPtr型


        //-------------------------------------------------------------
        //!
        //! @brief ユニフォームバッファー
        //! @brief ユニフォームバッファのラッパークラス
        //! @brief ※ std140レイアウト前提の作りになっていることに注意
        //!
        //-------------------------------------------------------------
        class C_UniformBuffer
        {
        public:
            C_UniformBuffer(void* pBuffer,                                                                          // コンストラクタ
                            uint32_t bufferSize,
                            const std::string& rBlockName,
                            OpenGL::ModifyEnum modifyType);
            ~C_UniformBuffer();                                                                                     // デストラクタ
            void Rewrite(void* pBuffer,                                                                             // 書き換え処理
                         uint32_t bufferSize,
                         OpenGL::ModifyEnum modifyType);
            UniformBlockIndex GetBlockIndexFromProgramObject(ProgramObjectHandle programObjectHandle) const;        // プログラムオブジェクトからブロックのインデックスを取得
            UniformBufferObjectHandle GetHandle() const;                                                            // ハンドルを取得
            static UniformBufferPtr s_Create(void* pBuffer,                                                         // 生成処理
                                             uint32_t bufferSize,
                                             const std::string& rBlockName,
                                             OpenGL::ModifyEnum modifyType);
        private:
            UniformBufferObjectHandle handle_ = 0;                                                                  ///< @brief ハンドル
            std::string blockName_;                                                                                 ///< @brief ブロック名 
        };
    }
}
