/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace OpenGL
{
    /* �ʖ� */
    using RenderingContext = void;                                                          // RenderingContext�^
    using RenderingContextPtr = std::shared_ptr<RenderingContext>;                          // RenderingContextPtr�^
    using BlendEnum = GLenum;                                                               // BlendEnum�^
    using FaceEnum = GLenum;                                                                // FaceEnum�^
    using BufferBitFlag = GLbitfield;                                                       // BufferBitFlag�^
    using StencilEnum = GLenum;                                                             // StencilEnum�^


    namespace
    {
        /* �u�����h�W�� */
        namespace BlendFactor
        {
            const BlendEnum s_ALL_ZERO = GL_ZERO;                                           ///< @brief �S��0
            const BlendEnum s_ALL_ONE = GL_ONE;                                             ///< @brief �S��1
            const BlendEnum s_SOURCE_COLOR = GL_SRC_COLOR;                                  ///< @brief �V�����F��RGBA
            const BlendEnum s_ONE_MINUS_SOURCE_COLOR = GL_ONE_MINUS_SRC_COLOR;              ///< @brief 1 - �V�����F��RGBA
            const BlendEnum s_SOURCE_ALPHA = GL_SRC_ALPHA;                                  ///< @brief �V�����F�̃A���t�@
            const BlendEnum s_ONE_MINUS_SOURCE_ALPHA = GL_ONE_MINUS_SRC_ALPHA;              ///< @brief 1 - �V�����F�̃A���t�@
            const BlendEnum s_DESTINATION_COLOR = GL_DST_COLOR;                             ///< @brief ���݂̐F��RGBA
            const BlendEnum s_ONE_MINUS_DESTINATION_COLOR = GL_ONE_MINUS_DST_COLOR;         ///< @brief 1 - ���݂̐F��RGBA
            const BlendEnum s_DESTINATION_ALPHA = GL_DST_ALPHA;                             ///< @brief ���݂̐F�̃A���t�@
            const BlendEnum s_ONE_MINUS_DESTINATION_ALPHA = GL_ONE_MINUS_DST_ALPHA;         ///< @brief 1 - ���݂̐F�̃A���t�@
        }

        /* �� */
        namespace Face
        {
            const FaceEnum s_FRONT = GL_FRONT;                                              ///< @brief �\��
            const FaceEnum s_BACK = GL_BACK;                                                ///< @brief ����
            const FaceEnum s_BOTH = GL_FRONT_AND_BACK;                                      ///< @brief ����
        }

        /* �o�b�t�@ */
        namespace Buffer
        {
            BufferBitFlag s_COLOR = GL_COLOR_BUFFER_BIT;                                    ///< @brief �J���[�o�b�t�@
            BufferBitFlag s_DEPTH = GL_DEPTH_BUFFER_BIT;                                    ///< @brief �[�x�o�b�t�@
            BufferBitFlag s_STENCIL = GL_STENCIL_BUFFER_BIT;                                ///< @brief �X�e���V���o�b�t�@
        }

        /* �X�e���V���֐� */
        namespace StencilFunction
        {
            const StencilEnum s_ALWAYS = GL_ALWAYS;                                         ///< @brief ��ɒʉ�
            const StencilEnum s_NEVER = GL_NEVER;                                           ///< @brief ��ɔ�ʉ�
            const StencilEnum s_LESS = GL_LESS;                                             ///< @brief ��r�l���X�e���V���l�����̂Ƃ��ʉ�
            const StencilEnum s_LEQUAL = GL_LEQUAL;                                         ///< @brief ��r�l���X�e���V���l�ȉ��̂Ƃ��ʉ�
            const StencilEnum s_GREATER = GL_GREATER;                                       ///< @brief ��r�l���X�e���V���l���߂̂Ƃ��ʉ�
            const StencilEnum s_GEQUAL = GL_GEQUAL;                                         ///< @brief ��r�l���X�e���V���l�ȏ�̂Ƃ��ʉ�
            const StencilEnum s_EQUAL = GL_EQUAL;                                           ///< @brief ��r�l���X�e���V���l�Ɠ������Ƃ��ʉ�
            const StencilEnum s_NOTEQUAL = GL_NOTEQUAL;                                     ///< @brief ��r�l���X�e���V���l�Ɠ������Ȃ��Ƃ��ʉ�
        }

        /* �X�e���V���̏��� */
        namespace StencilProcess
        {
            const StencilEnum s_ZERO = GL_ZERO;                                             ///< @brief �X�e���V���l��0�֕ύX
            const StencilEnum s_KEEP = GL_KEEP;                                             ///< @brief �X�e���V���l���ێ�
            const StencilEnum s_REPLACE = GL_REPLACE;                                       ///< @brief �X�e���V���l���r�l�֕ύX
            const StencilEnum s_INCREMENT = GL_INCR;                                        ///< @brief �X�e���V���l���C���N�������g
            const StencilEnum s_DECREMENT = GL_DECR;                                        ///< @brief �X�e���V���l���f�N�������g
            const StencilEnum s_INVERT = GL_INVERT;                                         ///< @brief �X�e���V���l���r�b�g���]
            const StencilEnum s_INCREMENT_WARP = GL_INCR_WRAP;                              ///< @brief �X�e���V���l���C���N�������g���A�ő�l�𒴂�����0�֕ύX
            const StencilEnum s_DECREMENT_WARP = GL_DECR_WRAP;                              ///< @brief �X�e���V���l���f�N�������g���A0�����������ő�l�֕ύX
        }
    }
}