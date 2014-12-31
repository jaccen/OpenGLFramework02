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
    using BlendEnum = GLenum;                                                               // BlendEnum型
    using FaceEnum = GLenum;                                                                // FaceEnum型
    using BufferBitFlag = GLbitfield;                                                       // BufferBitFlag型
    using StencilEnum = GLenum;                                                             // StencilEnum型


    namespace
    {
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
            BufferBitFlag s_COLOR = GL_COLOR_BUFFER_BIT;                                    ///< @brief カラーバッファ
            BufferBitFlag s_DEPTH = GL_DEPTH_BUFFER_BIT;                                    ///< @brief 深度バッファ
            BufferBitFlag s_STENCIL = GL_STENCIL_BUFFER_BIT;                                ///< @brief ステンシルバッファ
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
    }
}