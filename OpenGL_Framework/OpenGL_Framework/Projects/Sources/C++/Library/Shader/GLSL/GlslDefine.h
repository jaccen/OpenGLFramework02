/* 二重インクルード防止 */
#pragma once


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
        using TypeEnum = GLenum;                                                            // TypeEnum型
        using BufferEnum = GLenum;                                                          // BufferEnum型
        using ShaderObjectHandle = GLint;                                                   // ShaderObjectHandle型
        using ProgramObjectHandle = GLint;                                                  // ProgramObjectHandle型
        using UniformBufferObjectHandle = GLuint;                                           // UniformBufferObjectHandle型
        using UniformBlockIndex = GLuint;                                                   // UniformBlockIndex
        using SubroutineIndex = GLuint;                                                     // SubroutineIndex型
        using ModifyEnum = GLenum;                                                          // ModifyEnum型


        namespace
        {
            /* シェーダーの種類 */
            namespace ShaderType
            {
                const TypeEnum s_VERTEX = GL_VERTEX_SHADER;                                 ///< @brief 頂点シェーダー
                const TypeEnum s_TESSELLATION_CONTROL = GL_TESS_CONTROL_SHADER;             ///< @brief テッセレーション制御シェーダー
                const TypeEnum s_TESSELLATION_EVALUATION = GL_TESS_EVALUATION_SHADER;       ///< @brief テッセレーション評価シェーダー
                const TypeEnum s_GEOMETRY = GL_GEOMETRY_SHADER;                             ///< @brief ジオメトリシェーダー
                const TypeEnum s_FRAGMENT = GL_FRAGMENT_SHADER;                             ///< @brief フラグメントシェーダー
            }

            /* バッファの種類 */
            namespace BufferType
            {
                const BufferEnum s_VERTEX = GL_ARRAY_BUFFER;                                ///< @brief 頂点バッファ
                const BufferEnum s_VERTEX_ARRAY = GL_ELEMENT_ARRAY_BUFFER;                  ///< @brief 頂点配列バッファ
                const BufferEnum s_UNIFORM = GL_UNIFORM_BUFFER;                             ///< @brief ユニフォームバッファ
            }

            /* 修正の種類 */
            namespace ModifyType
            {
                ModifyEnum s_STATIC = GL_STATIC_DRAW;                                       ///< @brief データを変更しない
                ModifyEnum s_STREAM = GL_STREAM_DRAW;                                       ///< @brief データを定期的に書き換え
                ModifyEnum s_DYNAMIC = GL_DYNAMIC_DRAW;                                     ///< @brief データを頻繁に書き換え
            }
        }
    }
}