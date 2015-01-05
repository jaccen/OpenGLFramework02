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
    using DataEnum = GLenum;                                                                // DataEnum�^
    using BlendEnum = GLenum;                                                               // BlendEnum�^
    using FaceEnum = GLenum;                                                                // FaceEnum�^
    using BufferBitFlag = GLbitfield;                                                       // BufferBitFlag�^
    using StencilEnum = GLenum;                                                             // StencilEnum�^
    using PrimitiveEnum = GLenum;                                                           // PrimitiveEnum�^
    using ModifyEnum = GLenum;                                                              // ModifyEnum�^
    using VertexArrayObjectHandle = GLuint;                                                 // VertexArrayObjectHandle�^
    using VertexBufferObjectHandle = GLuint;                                                // VertexBufferObjectHandle�^
    using IndexBufferObjenctHandle = GLuint;                                                // IndexBufferObjenctHandle�^
    using BufferEnum = GLenum;                                                              // BufferEnum�^
    using FormatType = GLint;                                                                   // FormatType�^


    namespace
    {
        /* �f�[�^�^ */
        namespace DataType
        {
            const DataEnum s_BOOL = GL_BOOL;                                                ///< @brief bool�^
            const DataEnum s_SHORT = GL_SHORT;                                              ///< @brief short�^
            const DataEnum s_UNSIGNED_SHORT = GL_UNSIGNED_SHORT;                            ///< @brief unsigned short�^
            const DataEnum s_INT = GL_INT;                                                  ///< @brief int�^
            const DataEnum s_UNSIGNED_INT = GL_UNSIGNED_INT;                                ///< @brief unsigned int�^
            const DataEnum s_FLOAT = GL_FLOAT;                                              ///< @brief float�^
            const DataEnum s_DOUBLE = GL_DOUBLE;                                            ///< @brief double�^
        }


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
            const BufferEnum s_VERTEX = GL_ARRAY_BUFFER;                                    ///< @brief ���_�o�b�t�@
            const BufferEnum s_INDEX = GL_ELEMENT_ARRAY_BUFFER;                             ///< @brief �C���f�b�N�X�o�b�t�@
            const BufferEnum s_UNIFORM = GL_UNIFORM_BUFFER;                                 ///< @brief ���j�t�H�[���o�b�t�@
            const BufferEnum s_FRAME = GL_FRAMEBUFFER;                                      ///< @brief �t���[���o�b�t�@
            const BufferEnum s_RENDER = GL_RENDERBUFFER;                                    ///< @brief �����_�[�o�b�t�@

            /* �s�N�Z�� */
            namespace Pixel
            {
                BufferBitFlag s_COLOR = GL_COLOR_BUFFER_BIT;                                ///< @brief �J���[�o�b�t�@
                BufferBitFlag s_DEPTH = GL_DEPTH_BUFFER_BIT;                                ///< @brief �[�x�o�b�t�@
                BufferBitFlag s_STENCIL = GL_STENCIL_BUFFER_BIT;                            ///< @brief �X�e���V���o�b�t�@
            }
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

        /* �v���~�e�B�u */
        namespace Primitive
        {
            const PrimitiveEnum s_POINT = GL_POINTS;                                        ///< @brief �_
            const PrimitiveEnum s_LINE = GL_LINES;                                          ///< @brief 2�̒��_�����Ԑ�
            const PrimitiveEnum s_LINE_STRIP = GL_LINE_STRIP;                               ///< @brief �e���_��A�����Č��Ԑ�
            const PrimitiveEnum s_LINE_LOOP = GL_LINE_LOOP;                                 ///< @brief �e���_��A�����Č��сA���n�_�ƏI�_�����Ԑ�
            const PrimitiveEnum s_TRIANGLE = GL_TRIANGLES;                                  ///< @brief 3�̒��_����Ȃ�O�p�`
            const PrimitiveEnum s_TRIANGLE_STRIP = GL_TRIANGLE_STRIP;                       ///< @brief �e���_����A�����ĂȂ�O�p�`
            const PrimitiveEnum s_TRIANGLE_FAN = GL_TRIANGLE_FAN;                           ///< @brief �e���_����A�����A�n�_�𒆐S�ɐ��ɂȂ�O�p�`
        }

        /* �C�� */
        namespace Modify
        {
            ModifyEnum s_STATIC = GL_STATIC_DRAW;                                           ///< @brief �f�[�^��ύX���Ȃ�
            ModifyEnum s_STREAM = GL_STREAM_DRAW;                                           ///< @brief �f�[�^�����I�ɏ�������
            ModifyEnum s_DYNAMIC = GL_DYNAMIC_DRAW;                                         ///< @brief �f�[�^��p�ɂɏ�������
        }

        /* �t�H�[�}�b�g */
        namespace Format
        {
            /* ���� */
            namespace Internal
            {
                const FormatType s_RGB_8_SNORM = GL_RGB8_SNORM;                                 ///< @brief �e������8�r�b�gRGB�̕����t�����K�l
                const FormatType s_RGB_8_UNORM = GL_RGB8;                                       ///< @brief �e������8�r�b�gRGB�̕����Ȃ����K�l
                const FormatType s_RGB_8_SINT = GL_RGB8I;                                       ///< @brief �e������8�r�b�gRGB�̕����t������
                const FormatType s_RGB_8_UINT = GL_RGB8UI;                                      ///< @brief �e������8�r�b�gRGB�̕����Ȃ�����

                const FormatType s_RGB_16_SNORM = GL_RGB16_SNORM;                               ///< @brief �e������16�r�b�gRGB�̕����t�����K�l
                const FormatType s_RGB_16_UNORM = GL_RGB16;                                     ///< @brief �e������16�r�b�gRGB�̕����Ȃ����K�l
                const FormatType s_RGB_16_SINT = GL_RGB16I;                                     ///< @brief �e������16�r�b�gRGB�̕����t������
                const FormatType s_RGB_16_UINT = GL_RGB16UI;                                    ///< @brief �e������16�r�b�gRGB�̕����Ȃ�����
                const FormatType s_RGB_16_FLOAT = GL_RGB16F;                                    ///< @brief �e������16�r�b�gRGB�̕��������_��

                const FormatType s_RGB_32_SINT = GL_RGB32I;                                     ///< @brief �e������32�r�b�gRGB�̕����t������
                const FormatType s_RGB_32_UINT = GL_RGB32UI;                                    ///< @brief �e������32�r�b�gRGB�̕����Ȃ�����
                const FormatType s_RGB_32_FLOAT = GL_RGB32F;                                    ///< @brief �e������32�r�b�gRGB�̕��������_��

                const FormatType s_RGBA_8_SNORM = GL_RGBA8_SNORM;                               ///< @brief �e������8�r�b�gRGBA�̕����t�����K�l
                const FormatType s_RGBA_8_UNORM = GL_RGBA8;                                     ///< @brief �e������8�r�b�gRGBA�̕����Ȃ����K�l
                const FormatType s_RGBA_8_SINT = GL_RGBA8I;                                     ///< @brief �e������8�r�b�gRGBA�̕����t������
                const FormatType s_RGBA_8_UINT = GL_RGBA8UI;                                    ///< @brief �e������8�r�b�gRGBA�̕����Ȃ�����

                const FormatType s_RGBA_16_SNORM = GL_RGBA16_SNORM;                             ///< @brief �e������16�r�b�gRGBA�̕����t�����K�l
                const FormatType s_RGBA_16_UNORM = GL_RGBA16;                                   ///< @brief �e������16�r�b�gRGBA�̕����Ȃ����K�l
                const FormatType s_RGBA_16_SINT = GL_RGBA16I;                                   ///< @brief �e������16�r�b�gRGBA�̕����t������
                const FormatType s_RGBA_16_UINT = GL_RGBA16UI;                                  ///< @brief �e������16�r�b�gRGBA�̕����Ȃ�����
                const FormatType s_RGBA_16_FLOAT = GL_RGBA16F;                                  ///< @brief �e������16�r�b�gRGBA�̕��������_��

                const FormatType s_RGBA_32_SINT = GL_RGBA32I;                                   ///< @brief �e������32�r�b�gRGBA�̕����t������
                const FormatType s_RGBA_32_UINT = GL_RGBA32UI;                                  ///< @brief �e������32�r�b�gRGBA�̕����Ȃ�����
                const FormatType s_RGBA_32_FLOAT = GL_RGBA32F;                                  ///< @brief �e������32�r�b�gRGBA�̕��������_��

                const FormatType s_DEPTH_16 = GL_DEPTH_COMPONENT16;                             ///< @brief 16�r�b�g�[�x�o�b�t�@
                const FormatType s_DEPTH_24 = GL_DEPTH_COMPONENT24;                             ///< @brief 24�r�b�g�[�x�o�b�t�@
                const FormatType s_DEPTH_32 = GL_DEPTH_COMPONENT32;                             ///< @brief 32�r�b�g�[�x�o�b�t�@

                const FormatType s_STENCIL_8 = GL_STENCIL_INDEX8;                               ///< @brief 8�r�b�g�X�e���V���o�b�t�@
                const FormatType s_STENCIL_16 = GL_STENCIL_INDEX8;                              ///< @brief 16�r�b�g�X�e���V���o�b�t�@

                // �� SNORM �F ( -1.0 �` 1.0 ), UNORM : ( 0.0 �` 1.0 )
            }

            /* �s�N�Z�� */
            namespace Pixel
            {
                const FormatType s_RGB = GL_RGB;                                                ///< @brief RGB
                const FormatType s_RGBA = GL_RGBA;                                              ///< @brief RGBA
            }
        }
    }
}