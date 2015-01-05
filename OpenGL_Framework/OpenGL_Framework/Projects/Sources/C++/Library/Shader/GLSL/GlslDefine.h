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
        using ShaderObjectHandle = GLint;                                                   // ShaderObjectHandle型
        using ProgramObjectHandle = GLint;                                                  // ProgramObjectHandle型
        using UniformBufferObjectHandle = GLuint;                                           // UniformBufferObjectHandle型
        using UniformBlockIndex = GLuint;                                                   // UniformBlockIndex
        using SubroutineIndex = GLuint;                                                     // SubroutineIndex型


        namespace
        {
            /* 種類 */
            namespace Type
            {
                const TypeEnum s_VERTEX = GL_VERTEX_SHADER;                                 ///< @brief 頂点シェーダー
                const TypeEnum s_TESSELLATION_CONTROL = GL_TESS_CONTROL_SHADER;             ///< @brief テッセレーション制御シェーダー
                const TypeEnum s_TESSELLATION_EVALUATION = GL_TESS_EVALUATION_SHADER;       ///< @brief テッセレーション評価シェーダー
                const TypeEnum s_GEOMETRY = GL_GEOMETRY_SHADER;                             ///< @brief ジオメトリシェーダー
                const TypeEnum s_FRAGMENT = GL_FRAGMENT_SHADER;                             ///< @brief フラグメントシェーダー
            }
        }
    }
}