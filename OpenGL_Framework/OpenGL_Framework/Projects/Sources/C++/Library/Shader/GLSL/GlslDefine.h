/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
//!
//! @brief �V�F�[�_�[
//! @brief �V�F�[�_�[�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Shader
{
    //-------------------------------------------------------------
    //!
    //! @brief GLSL
    //! @brief GLSL�֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace GLSL
    {
        /* �ʖ� */
        using TypeEnum = GLenum;                                                            // TypeEnum�^
        using ShaderObjectHandle = GLint;                                                   // ShaderObjectHandle�^
        using ProgramObjectHandle = GLint;                                                  // ProgramObjectHandle�^
        using UniformBufferObjectHandle = GLuint;                                           // UniformBufferObjectHandle�^
        using UniformBlockIndex = GLuint;                                                   // UniformBlockIndex
        using SubroutineIndex = GLuint;                                                     // SubroutineIndex�^


        namespace
        {
            /* ��� */
            namespace Type
            {
                const TypeEnum s_VERTEX = GL_VERTEX_SHADER;                                 ///< @brief ���_�V�F�[�_�[
                const TypeEnum s_TESSELLATION_CONTROL = GL_TESS_CONTROL_SHADER;             ///< @brief �e�b�Z���[�V��������V�F�[�_�[
                const TypeEnum s_TESSELLATION_EVALUATION = GL_TESS_EVALUATION_SHADER;       ///< @brief �e�b�Z���[�V�����]���V�F�[�_�[
                const TypeEnum s_GEOMETRY = GL_GEOMETRY_SHADER;                             ///< @brief �W�I���g���V�F�[�_�[
                const TypeEnum s_FRAGMENT = GL_FRAGMENT_SHADER;                             ///< @brief �t���O�����g�V�F�[�_�[
            }
        }
    }
}