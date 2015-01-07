/* ��d�C���N���[�h�h�~ */
#pragma once


//-------------------------------------------------------------
//!
//! @brief �e�N�X�`��
//! @brief �e�N�X�`���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Texture
{
    /* �ʖ� */
    using TextureHandle = GLuint;                                                               // TextureHandle�^
    using TypeEnum = GLenum;                                                                    // TypeEnum�^
    using ParameterEnum = GLenum;                                                               // ParameterEnum�^
    using FilterEnum = GLenum;                                                                  // FilterEnum�^
    using WrapEnum = GLenum;                                                                    // WrapEnum�^
    using CompareModeType = GLint;                                                              // CompareModeType�^
    using CompareFunctionType = GLint;                                                          // CompareFunctionType�^

    
    namespace
    {
        /* ��� */
        namespace Type
        {
            const TypeEnum s_1D = GL_TEXTURE_1D;                                                ///< @brief 1D
            const TypeEnum s_2D = GL_TEXTURE_2D;                                                ///< @brief 2D
            const TypeEnum s_3D = GL_TEXTURE_3D;                                                ///< @brief 3D
            const TypeEnum s_CUBE_MAP = GL_TEXTURE_CUBE_MAP;                                    ///< @brief �L���[�u�}�b�v

            /* �^�[�Q�b�g */
            namespace Target
            {
                const TypeEnum s_CUBE_MAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X;          ///< @brief �L���[�u�}�b�v�̉E���� 
                const TypeEnum s_CUBE_MAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y;          ///< @brief �L���[�u�}�b�v�̏����
                const TypeEnum s_CUBE_MAP_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z;          ///< @brief �L���[�u�}�b�v�̌����
                const TypeEnum s_CUBE_MAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X;          ///< @brief �L���[�u�}�b�v�̍�����
                const TypeEnum s_CUBE_MAP_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;          ///< @brief �L���[�u�}�b�v�̉�����
                const TypeEnum s_CUBE_MAP_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;          ///< @brief �L���[�u�}�b�v�̑O����
            }
        }

        /* �p�����[�^ */
        namespace Parameter
        {
            const ParameterEnum s_MAGNIFICATION_FILTER = GL_TEXTURE_MAG_FILTER;                 ///< @brief �g��
            const ParameterEnum s_REDUCION_FILTER = GL_TEXTURE_MIN_FILTER;                      ///< @brief �k��
            const ParameterEnum s_WRAP_S = GL_TEXTURE_WRAP_S;                                   ///< @brief S�������̃��b�v
            const ParameterEnum s_WRAP_T = GL_TEXTURE_WRAP_T;                                   ///< @brief T�������̃��b�v
            const ParameterEnum s_WRAP_R = GL_TEXTURE_WRAP_R;                                   ///< @brief R�������̃��b�v
            const ParameterEnum s_BORDER_COLOR = GL_TEXTURE_BORDER_COLOR;                       ///< @brief ���E�F
            const ParameterEnum s_COMPARE_MODE = GL_TEXTURE_COMPARE_MODE;                       ///< @brief ��r���[�h
            const ParameterEnum s_COMPARE_FUNCTION = GL_TEXTURE_COMPARE_FUNC;                   ///< @brief ��r�̊֐�
        }


        /* �t�B���^ */
        namespace Filter
        {
            /* �g�� */
            namespace Magnification
            {
                const FilterEnum s_NEAREST = GL_NEAREST;                                       ///< @brief �ŋߖT���
                const FilterEnum s_LINEAR = GL_LINEAR;                                         ///< @brief ���`���
            }

            /* �k�� */
            namespace Reduction
            {
                const FilterEnum s_NEAREST = GL_NEAREST;                                       ///< @brief �ŋߖT���
                const FilterEnum s_LINEAR = GL_LINEAR;                                         ///< @brief ���`���

                /* �~�b�v�}�b�v */
                namespace MipMap
                {
                    /* �ł��������T�C�Y */
                    namespace NearestSize
                    {
                        const FilterEnum s_NEAREST = GL_NEAREST_MIPMAP_NEAREST;                 ///< @brief �ŋߖT���
                        const FilterEnum s_LINEAR = GL_LINEAR_MIPMAP_NEAREST;                   ///< @brief ���`���
                    }

                    /* ���ς̃T�C�Y */
                    namespace AverageSize
                    {
                        const FilterEnum s_NEAREST = GL_NEAREST_MIPMAP_LINEAR;                  ///< @brief �ŋߖT���
                        const FilterEnum s_LINEAR = GL_LINEAR_MIPMAP_LINEAR;                    ///< @brief ���`���
                    }
                }
            }
        }

        /* ���b�v�̎�� */
        namespace WrapType
        {
            const WrapEnum s_REPEAT = GL_REPEAT;                                                ///< @brief �J��Ԃ�
            const WrapEnum s_CLAMP = GL_CLAMP;                                                  ///< @brief �[�̃s�N�Z���F���������΂�
            const WrapEnum s_CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE;                                  ///< @brief ���E�F�������̃s�N�Z�����������΂�
            const WrapEnum s_CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER;                              ///< @brief ���E�F���������΂�
        }

        /* ��r���[�h */
        namespace CompareMode
        {
            const CompareModeType s_REF_TO_TEXTURE = GL_COMPARE_REF_TO_TEXTURE;                 ///< @brief �[�x��r
        }

        /* ��r�֐� */
        namespace CompareFunction
        {
            const CompareFunctionType s_LESS = GL_LESS;                                         ///< @brief ����
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief �e�N�X�`���f�[�^
    //! @brief �e�N�X�`���f�[�^��\���\����
    //!
    //-------------------------------------------------------------
    struct S_TextureData
    {
        TextureHandle handle_ = 0;                                      ///< @brief �e�N�X�`���n���h��
        int32_t width_ = 0;                                             ///< @brief ��
        int32_t height_ = 0;                                            ///< @brief ����
        int32_t depth_ = 0;                                             ///< @brief ���s

        S_TextureData() = default;                                      //!< @brief �f�t�H���g�R���X�g���N�^

        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        S_TextureData(int32_t width, int32_t height = 0, int32_t depth = 0) :

            // �T�C�Y
            width_(width),
            height_(height),
            depth_(depth)

        {
            ::glGenTextures(1, &handle_);
        }

        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        ~S_TextureData()
        {
            ::glDeleteTextures(1, &handle_);
        }
    };


    /*************************************************************//**
     *
     *  @brief  2D�e�N�X�`���̃f�t�H���g�̃p�����[�^�ݒ���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    inline static void s_Default2DParameter()
    {
        ::glTexParameteri(Type::s_2D, Parameter::s_MAGNIFICATION_FILTER, Filter::Magnification::s_LINEAR);
        ::glTexParameteri(Type::s_2D, Parameter::s_REDUCION_FILTER, Filter::Reduction::s_LINEAR);
    }


    /*************************************************************//**
     *
     *  @brief  �L���[�u�}�b�v�e�N�X�`���̃f�t�H���g�̃p�����[�^�ݒ���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    inline static void s_DefaultCubeMapParameter()
    {
        ::glTexParameteri(Type::s_CUBE_MAP, Parameter::s_MAGNIFICATION_FILTER, Filter::Magnification::s_LINEAR);
        ::glTexParameteri(Type::s_CUBE_MAP, Parameter::s_REDUCION_FILTER, Filter::Reduction::s_LINEAR);
        ::glTexParameteri(Type::s_CUBE_MAP, Parameter::s_WRAP_S, WrapType::s_CLAMP_TO_EDGE);
        ::glTexParameteri(Type::s_CUBE_MAP, Parameter::s_WRAP_T, WrapType::s_CLAMP_TO_EDGE);
        ::glTexParameteri(Type::s_CUBE_MAP, Parameter::s_WRAP_R, WrapType::s_CLAMP_TO_EDGE);
    }
}