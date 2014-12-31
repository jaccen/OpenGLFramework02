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
        using BufferEnum = GLenum;                                                          // BufferEnum�^
        using ShaderObjectHandle = GLint;                                                   // ShaderObjectHandle�^
        using ProgramObjectHandle = GLint;                                                  // ProgramObjectHandle�^
        using UniformBufferObjectHandle = GLuint;                                           // UniformBufferObjectHandle�^
        using UniformBlockIndex = GLuint;                                                   // UniformBlockIndex
        using SubroutineIndex = GLuint;                                                     // SubroutineIndex�^
        using ModifyEnum = GLenum;                                                          // ModifyEnum�^


        namespace
        {
            /* �V�F�[�_�[�̎�� */
            namespace ShaderType
            {
                const TypeEnum s_VERTEX = GL_VERTEX_SHADER;                                 ///< @brief ���_�V�F�[�_�[
                const TypeEnum s_TESSELLATION_CONTROL = GL_TESS_CONTROL_SHADER;             ///< @brief �e�b�Z���[�V��������V�F�[�_�[
                const TypeEnum s_TESSELLATION_EVALUATION = GL_TESS_EVALUATION_SHADER;       ///< @brief �e�b�Z���[�V�����]���V�F�[�_�[
                const TypeEnum s_GEOMETRY = GL_GEOMETRY_SHADER;                             ///< @brief �W�I���g���V�F�[�_�[
                const TypeEnum s_FRAGMENT = GL_FRAGMENT_SHADER;                             ///< @brief �t���O�����g�V�F�[�_�[
            }

            /* �o�b�t�@�̎�� */
            namespace BufferType
            {
                const BufferEnum s_VERTEX = GL_ARRAY_BUFFER;                                ///< @brief ���_�o�b�t�@
                const BufferEnum s_VERTEX_ARRAY = GL_ELEMENT_ARRAY_BUFFER;                  ///< @brief ���_�z��o�b�t�@
                const BufferEnum s_UNIFORM = GL_UNIFORM_BUFFER;                             ///< @brief ���j�t�H�[���o�b�t�@
            }

            /* �C���̎�� */
            namespace ModifyType
            {
                ModifyEnum s_STATIC = GL_STATIC_DRAW;                                       ///< @brief �f�[�^��ύX���Ȃ�
                ModifyEnum s_STREAM = GL_STREAM_DRAW;                                       ///< @brief �f�[�^�����I�ɏ�������
                ModifyEnum s_DYNAMIC = GL_DYNAMIC_DRAW;                                     ///< @brief �f�[�^��p�ɂɏ�������
            }
        }
    }
}