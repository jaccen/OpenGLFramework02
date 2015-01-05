/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include <vector>
#include "../../OpenGlDefine.h"
#include "../../../Texture/TextureDefine.h"


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL関連の名前空間
//!
//-------------------------------------------------------------
namespace OpenGL
{
    /* 前方宣言 */
    class C_FrameBuffer;


    /* 別名 */
    using FrameBufferObjectHandle = GLuint;                                                                 // FrameBufferObjectHandle型
    using RenderBufferObjectHandle = GLuint;                                                                // RenderBufferObjectHandle型
    using FrameBufferPtr = std::shared_ptr<C_FrameBuffer>;                                                  // FrameBufferPtr型
    using AttachmentType = GLenum;                                                                          // AttachmentType型


    //-------------------------------------------------------------
    //!
    //! @brief フレームバッファ
    //! @brief フレームバッファのラッパークラス
    //!
    //-------------------------------------------------------------
    class C_FrameBuffer
    {
    public:
        C_FrameBuffer();                                                                                    // コンストラクタ
        ~C_FrameBuffer();                                                                                   // デストラクタ
        void Initialize(int32_t windowWidth,                                                                // 初期化処理
                        int32_t windowHeight,
                        Texture::TextureHandle textureHandles[],
                        uint32_t textureHandleCount,
                        OpenGL::FormatType depthInternalFormat = OpenGL::Format::Internal::s_DEPTH_24);
        void Finalize();                                                                                    // 終了処理
        void Bind();                                                                                        // フレームバッファをバインド
        void Unbind();                                                                                      // フレームバッファをアンバインド

        static FrameBufferPtr s_Create();                                                                   // 生成処理
    private:
        FrameBufferObjectHandle frameBufferObjectHandle_ = 0;                                               ///< @brief フレームバッファオブジェクトハンドル
        RenderBufferObjectHandle renderBufferObjectHandle_ = 0;                                             ///< @brief レンダーバッファオブジェクトハンドル
        std::vector<AttachmentType> attachmentTypes_;                                                       ///< @brief 関連付けの種類
    };
}
