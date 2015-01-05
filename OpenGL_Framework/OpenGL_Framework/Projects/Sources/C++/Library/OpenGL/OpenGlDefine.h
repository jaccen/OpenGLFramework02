/* 二重インクルード防止 */
#pragma once


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL関連の名前空間
//!
//-------------------------------------------------------------
namespace OpenGL
{
    /* 別名 */
    using RenderingContext = void;                                                          // RenderingContext型
    using RenderingContextPtr = std::shared_ptr<RenderingContext>;                          // RenderingContextPtr型
    using DataEnum = GLenum;                                                                // DataEnum型
    using BlendEnum = GLenum;                                                               // BlendEnum型
    using FaceEnum = GLenum;                                                                // FaceEnum型
    using BufferBitFlag = GLbitfield;                                                       // BufferBitFlag型
    using StencilEnum = GLenum;                                                             // StencilEnum型
    using PrimitiveEnum = GLenum;                                                           // PrimitiveEnum型
    using ModifyEnum = GLenum;                                                              // ModifyEnum型
    using VertexArrayObjectHandle = GLuint;                                                 // VertexArrayObjectHandle型
    using VertexBufferObjectHandle = GLuint;                                                // VertexBufferObjectHandle型
    using IndexBufferObjenctHandle = GLuint;                                                // IndexBufferObjenctHandle型
    using BufferEnum = GLenum;                                                              // BufferEnum型
    using FormatType = GLint;                                                                   // FormatType型


    namespace
    {
        /* データ型 */
        namespace DataType
        {
            const DataEnum s_BOOL = GL_BOOL;                                                ///< @brief bool型
            const DataEnum s_SHORT = GL_SHORT;                                              ///< @brief short型
            const DataEnum s_UNSIGNED_SHORT = GL_UNSIGNED_SHORT;                            ///< @brief unsigned short型
            const DataEnum s_INT = GL_INT;                                                  ///< @brief int型
            const DataEnum s_UNSIGNED_INT = GL_UNSIGNED_INT;                                ///< @brief unsigned int型
            const DataEnum s_FLOAT = GL_FLOAT;                                              ///< @brief float型
            const DataEnum s_DOUBLE = GL_DOUBLE;                                            ///< @brief double型
        }


        /* ブレンド係数 */
        namespace BlendFactor
        {
            const BlendEnum s_ALL_ZERO = GL_ZERO;                                           ///< @brief 全て0
            const BlendEnum s_ALL_ONE = GL_ONE;                                             ///< @brief 全て1
            const BlendEnum s_SOURCE_COLOR = GL_SRC_COLOR;                                  ///< @brief 新しい色のRGBA
            const BlendEnum s_ONE_MINUS_SOURCE_COLOR = GL_ONE_MINUS_SRC_COLOR;              ///< @brief 1 - 新しい色のRGBA
            const BlendEnum s_SOURCE_ALPHA = GL_SRC_ALPHA;                                  ///< @brief 新しい色のアルファ
            const BlendEnum s_ONE_MINUS_SOURCE_ALPHA = GL_ONE_MINUS_SRC_ALPHA;              ///< @brief 1 - 新しい色のアルファ
            const BlendEnum s_DESTINATION_COLOR = GL_DST_COLOR;                             ///< @brief 現在の色のRGBA
            const BlendEnum s_ONE_MINUS_DESTINATION_COLOR = GL_ONE_MINUS_DST_COLOR;         ///< @brief 1 - 現在の色のRGBA
            const BlendEnum s_DESTINATION_ALPHA = GL_DST_ALPHA;                             ///< @brief 現在の色のアルファ
            const BlendEnum s_ONE_MINUS_DESTINATION_ALPHA = GL_ONE_MINUS_DST_ALPHA;         ///< @brief 1 - 現在の色のアルファ
        }

        /* 面 */
        namespace Face
        {
            const FaceEnum s_FRONT = GL_FRONT;                                              ///< @brief 表面
            const FaceEnum s_BACK = GL_BACK;                                                ///< @brief 裏面
            const FaceEnum s_BOTH = GL_FRONT_AND_BACK;                                      ///< @brief 両面
        }

        /* バッファ */
        namespace Buffer
        {
            const BufferEnum s_VERTEX = GL_ARRAY_BUFFER;                                    ///< @brief 頂点バッファ
            const BufferEnum s_INDEX = GL_ELEMENT_ARRAY_BUFFER;                             ///< @brief インデックスバッファ
            const BufferEnum s_UNIFORM = GL_UNIFORM_BUFFER;                                 ///< @brief ユニフォームバッファ
            const BufferEnum s_FRAME = GL_FRAMEBUFFER;                                      ///< @brief フレームバッファ
            const BufferEnum s_RENDER = GL_RENDERBUFFER;                                    ///< @brief レンダーバッファ

            /* ピクセル */
            namespace Pixel
            {
                BufferBitFlag s_COLOR = GL_COLOR_BUFFER_BIT;                                ///< @brief カラーバッファ
                BufferBitFlag s_DEPTH = GL_DEPTH_BUFFER_BIT;                                ///< @brief 深度バッファ
                BufferBitFlag s_STENCIL = GL_STENCIL_BUFFER_BIT;                            ///< @brief ステンシルバッファ
            }
        }

        /* ステンシル関数 */
        namespace StencilFunction
        {
            const StencilEnum s_ALWAYS = GL_ALWAYS;                                         ///< @brief 常に通過
            const StencilEnum s_NEVER = GL_NEVER;                                           ///< @brief 常に非通過
            const StencilEnum s_LESS = GL_LESS;                                             ///< @brief 比較値がステンシル値未満のとき通過
            const StencilEnum s_LEQUAL = GL_LEQUAL;                                         ///< @brief 比較値がステンシル値以下のとき通過
            const StencilEnum s_GREATER = GL_GREATER;                                       ///< @brief 比較値がステンシル値超過のとき通過
            const StencilEnum s_GEQUAL = GL_GEQUAL;                                         ///< @brief 比較値がステンシル値以上のとき通過
            const StencilEnum s_EQUAL = GL_EQUAL;                                           ///< @brief 比較値がステンシル値と等しいとき通過
            const StencilEnum s_NOTEQUAL = GL_NOTEQUAL;                                     ///< @brief 比較値がステンシル値と等しくないとき通過
        }

        /* ステンシルの処理 */
        namespace StencilProcess
        {
            const StencilEnum s_ZERO = GL_ZERO;                                             ///< @brief ステンシル値を0へ変更
            const StencilEnum s_KEEP = GL_KEEP;                                             ///< @brief ステンシル値を維持
            const StencilEnum s_REPLACE = GL_REPLACE;                                       ///< @brief ステンシル値を比較値へ変更
            const StencilEnum s_INCREMENT = GL_INCR;                                        ///< @brief ステンシル値をインクリメント
            const StencilEnum s_DECREMENT = GL_DECR;                                        ///< @brief ステンシル値をデクリメント
            const StencilEnum s_INVERT = GL_INVERT;                                         ///< @brief ステンシル値をビット反転
            const StencilEnum s_INCREMENT_WARP = GL_INCR_WRAP;                              ///< @brief ステンシル値をインクリメントし、最大値を超えたら0へ変更
            const StencilEnum s_DECREMENT_WARP = GL_DECR_WRAP;                              ///< @brief ステンシル値をデクリメントし、0を下回ったら最大値へ変更
        }

        /* プリミティブ */
        namespace Primitive
        {
            const PrimitiveEnum s_POINT = GL_POINTS;                                        ///< @brief 点
            const PrimitiveEnum s_LINE = GL_LINES;                                          ///< @brief 2つの頂点を結ぶ線
            const PrimitiveEnum s_LINE_STRIP = GL_LINE_STRIP;                               ///< @brief 各頂点を連続して結ぶ線
            const PrimitiveEnum s_LINE_LOOP = GL_LINE_LOOP;                                 ///< @brief 各頂点を連続して結び、かつ始点と終点を結ぶ線
            const PrimitiveEnum s_TRIANGLE = GL_TRIANGLES;                                  ///< @brief 3つの頂点からなる三角形
            const PrimitiveEnum s_TRIANGLE_STRIP = GL_TRIANGLE_STRIP;                       ///< @brief 各頂点から連続してなる三角形
            const PrimitiveEnum s_TRIANGLE_FAN = GL_TRIANGLE_FAN;                           ///< @brief 各頂点から連続し、始点を中心に扇状になる三角形
        }

        /* 修正 */
        namespace Modify
        {
            ModifyEnum s_STATIC = GL_STATIC_DRAW;                                           ///< @brief データを変更しない
            ModifyEnum s_STREAM = GL_STREAM_DRAW;                                           ///< @brief データを定期的に書き換え
            ModifyEnum s_DYNAMIC = GL_DYNAMIC_DRAW;                                         ///< @brief データを頻繁に書き換え
        }

        /* フォーマット */
        namespace Format
        {
            /* 内部 */
            namespace Internal
            {
                const FormatType s_RGB_8_SNORM = GL_RGB8_SNORM;                                 ///< @brief 各成分が8ビットRGBの符号付き正規値
                const FormatType s_RGB_8_UNORM = GL_RGB8;                                       ///< @brief 各成分が8ビットRGBの符号なし正規値
                const FormatType s_RGB_8_SINT = GL_RGB8I;                                       ///< @brief 各成分が8ビットRGBの符号付き整数
                const FormatType s_RGB_8_UINT = GL_RGB8UI;                                      ///< @brief 各成分が8ビットRGBの符号なし整数

                const FormatType s_RGB_16_SNORM = GL_RGB16_SNORM;                               ///< @brief 各成分が16ビットRGBの符号付き正規値
                const FormatType s_RGB_16_UNORM = GL_RGB16;                                     ///< @brief 各成分が16ビットRGBの符号なし正規値
                const FormatType s_RGB_16_SINT = GL_RGB16I;                                     ///< @brief 各成分が16ビットRGBの符号付き整数
                const FormatType s_RGB_16_UINT = GL_RGB16UI;                                    ///< @brief 各成分が16ビットRGBの符号なし整数
                const FormatType s_RGB_16_FLOAT = GL_RGB16F;                                    ///< @brief 各成分が16ビットRGBの浮動小数点数

                const FormatType s_RGB_32_SINT = GL_RGB32I;                                     ///< @brief 各成分が32ビットRGBの符号付き整数
                const FormatType s_RGB_32_UINT = GL_RGB32UI;                                    ///< @brief 各成分が32ビットRGBの符号なし整数
                const FormatType s_RGB_32_FLOAT = GL_RGB32F;                                    ///< @brief 各成分が32ビットRGBの浮動小数点数

                const FormatType s_RGBA_8_SNORM = GL_RGBA8_SNORM;                               ///< @brief 各成分が8ビットRGBAの符号付き正規値
                const FormatType s_RGBA_8_UNORM = GL_RGBA8;                                     ///< @brief 各成分が8ビットRGBAの符号なし正規値
                const FormatType s_RGBA_8_SINT = GL_RGBA8I;                                     ///< @brief 各成分が8ビットRGBAの符号付き整数
                const FormatType s_RGBA_8_UINT = GL_RGBA8UI;                                    ///< @brief 各成分が8ビットRGBAの符号なし整数

                const FormatType s_RGBA_16_SNORM = GL_RGBA16_SNORM;                             ///< @brief 各成分が16ビットRGBAの符号付き正規値
                const FormatType s_RGBA_16_UNORM = GL_RGBA16;                                   ///< @brief 各成分が16ビットRGBAの符号なし正規値
                const FormatType s_RGBA_16_SINT = GL_RGBA16I;                                   ///< @brief 各成分が16ビットRGBAの符号付き整数
                const FormatType s_RGBA_16_UINT = GL_RGBA16UI;                                  ///< @brief 各成分が16ビットRGBAの符号なし整数
                const FormatType s_RGBA_16_FLOAT = GL_RGBA16F;                                  ///< @brief 各成分が16ビットRGBAの浮動小数点数

                const FormatType s_RGBA_32_SINT = GL_RGBA32I;                                   ///< @brief 各成分が32ビットRGBAの符号付き整数
                const FormatType s_RGBA_32_UINT = GL_RGBA32UI;                                  ///< @brief 各成分が32ビットRGBAの符号なし整数
                const FormatType s_RGBA_32_FLOAT = GL_RGBA32F;                                  ///< @brief 各成分が32ビットRGBAの浮動小数点数

                const FormatType s_DEPTH_16 = GL_DEPTH_COMPONENT16;                             ///< @brief 16ビット深度バッファ
                const FormatType s_DEPTH_24 = GL_DEPTH_COMPONENT24;                             ///< @brief 24ビット深度バッファ
                const FormatType s_DEPTH_32 = GL_DEPTH_COMPONENT32;                             ///< @brief 32ビット深度バッファ

                const FormatType s_STENCIL_8 = GL_STENCIL_INDEX8;                               ///< @brief 8ビットステンシルバッファ
                const FormatType s_STENCIL_16 = GL_STENCIL_INDEX8;                              ///< @brief 16ビットステンシルバッファ

                // ※ SNORM ： ( -1.0 ～ 1.0 ), UNORM : ( 0.0 ～ 1.0 )
            }

            /* ピクセル */
            namespace Pixel
            {
                const FormatType s_RGB = GL_RGB;                                                ///< @brief RGB
                const FormatType s_RGBA = GL_RGBA;                                              ///< @brief RGBA
            }
        }
    }
}