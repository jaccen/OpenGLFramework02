/* ヘッダファイル */
#include "FrameBuffer.h"


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL関連の名前空間
//!
//-------------------------------------------------------------
namespace OpenGL
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_FrameBuffer::C_FrameBuffer()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_FrameBuffer::~C_FrameBuffer()
    {
        if (frameBufferObjectHandle_ != 0) Finalize();
    }



    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  テクスチャの幅
     *  @param  テクスチャの高さ
     *  @param  テクスチャハンドル
     *  @param  テクスチャハンドルの数
     *  @param  深度の内部フォーマット
     *  @return なし
     *
     ****************************************************************/
    void C_FrameBuffer::Initialize(int32_t textureWidth,
                                   int32_t textureHeight,
                                   Texture::TextureHandle textureHandles[],
                                   uint32_t textureHandleCount,
                                   OpenGL::FormatType depthInternalFormat)
    {
        // レンダーバッファオブジェクトを作成
        glGenRenderbuffers(1, &renderBufferObjectHandle_);
        glBindRenderbuffer(OpenGL::Buffer::s_RENDER, renderBufferObjectHandle_);
        glRenderbufferStorage(OpenGL::Buffer::s_RENDER, depthInternalFormat, textureWidth, textureHeight);
        glBindRenderbuffer(OpenGL::Buffer::s_RENDER, 0);
        
        // フレームバッファオブジェクトを作成し、バインド
        glGenFramebuffers(1, &frameBufferObjectHandle_);
        Bind();

        for (size_t i = 0; i < textureHandleCount; ++i)
        {
            // テクスチャを関連付け
            glFramebufferTexture2D(OpenGL::Buffer::s_FRAME, GL_COLOR_ATTACHMENT0 + i, Texture::Type::s_2D, textureHandles[i], 0);
        }
        
        // レンダーバッファを関連付け 
        glFramebufferRenderbuffer(OpenGL::Buffer::s_FRAME, GL_DEPTH_ATTACHMENT, OpenGL::Buffer::s_RENDER, renderBufferObjectHandle_);

        // 関連付けの種類を設定
        for (size_t i = 0; i < textureHandleCount; ++i)
        {
            attachmentTypes_.push_back(GL_COLOR_ATTACHMENT0 + i);
        }

        glDrawBuffers(textureHandleCount, attachmentTypes_.data());


        // フレームバッファをアンバインド
        Unbind();
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_FrameBuffer::Finalize()
    {
        // 各オブジェクトを破棄
        glDeleteRenderbuffers(1, &renderBufferObjectHandle_);
        glDeleteFramebuffers(1, &frameBufferObjectHandle_);

        renderBufferObjectHandle_ = 0;
        frameBufferObjectHandle_ = 0;
        
        // アタッチメントの種類をクリア
        attachmentTypes_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  フレームバッファをバインドする
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_FrameBuffer::Bind()
    {
        glBindFramebuffer(OpenGL::Buffer::s_FRAME, frameBufferObjectHandle_);
    }


    /*************************************************************//**
     *
     *  @brief  フレームバッファをアンバインドする
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_FrameBuffer::Unbind()
    {
        glBindFramebuffer(OpenGL::Buffer::s_FRAME, 0);
    }


    /*************************************************************//**
     *
     *  @brief  生成処理を行う
     *  @param  なし
     *  @return フレームバッファ
     *
     ****************************************************************/
    FrameBufferPtr C_FrameBuffer::s_Create()
    {
        return std::make_shared<C_FrameBuffer>();
    }
}