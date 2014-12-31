/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include <vector>


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
    //! @brief コモン
    //! @brief 共通関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace Common
    {
        /* 前方宣言 */
        struct S_BufferSize;


        /* 別名 */
        using FrameBufferObjectHandle = GLuint;                                                 // FrameBufferObjectHandle型
        using RenderBufferHandle = GLuint;                                                      // RenderBufferHandle型
        using InternalFormat = GLenum;                                                          // InternalFormat型
        using CreateBufferFunction = void(*)(RenderBufferHandle*, S_BufferSize*);               // CreateBufferFunction型


        /* バッファの種類 */
        enum class ecBufferType
        {
            RENDER,                                                                             ///< @brief レンダーバッファ
            TEXTURE,                                                                            ///< @brief ( 2D )テクスチャ
        };

        /** ピクセルデータ */
        enum class ecPixelDataType
        {
            COLOR,                                                                              ///< @brief 色
            DEPTH,                                                                              ///< @brief 深度
            STENCIL,                                                                            ///< @brief ステンシル
        };

         /** バッファのサイズ */
        struct S_BufferSize
        {
            uint32_t width_ = 0;                                                                ///< @brief 幅
            uint32_t height_ = 0;                                                               ///< @brief 高さ
        };

        /** レンダーバッファデータ*/
        struct S_RenderBufferData
        {
            RenderBufferHandle handle_ = 0;                                                     ///< @brief ハンドル
            S_BufferSize size_;                                                                 ///< @brief サイズ
            ecBufferType type_ = ecBufferType::RENDER;                                          ///< @brief 種類
            ecPixelDataType pixelDataType_ = ecPixelDataType::COLOR;                            ///< @brief ピクセルデータの種類
        };


        //-------------------------------------------------------------
        //!
        //! @brief フレームバッファ
        //! @brief フレームバッファのラッパークラス
        //!
        //-------------------------------------------------------------
        class C_FrameBuffer
        {
        public:
            C_FrameBuffer(S_BufferSize bufferSizes[],                                           // コンストラクタ
                          ecBufferType bufferTypes[],
                          ecPixelDataType pixelDataTypes[],
                          CreateBufferFunction pCreateBufferFunctions[],
                          uint32_t bufferCount);
            ~C_FrameBuffer();                                                                   // デストラクタ
            void Bind();                                                                        // フレームバッファをバインド
            void Unbind();                                                                      // フレームバッファをアンバインド
            const S_RenderBufferData& GetRenderBufferData(uint32_t index) const;                // レンダーバッファデータを取得
        private:
            FrameBufferObjectHandle frameBufferObjectHandle_ = 0;                               ///< @brief フレームバッファオブジェクトハンドル
            std::vector<S_RenderBufferData> renderBufferDatas_;                                 ///< @brief レンダーバッファデータ
        };
    }
}