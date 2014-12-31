/* 二重インクルード防止 */
#pragma once


//-------------------------------------------------------------
//!
//! @brief テクスチャ
//! @brief テクスチャ関連の名前空間
//!
//-------------------------------------------------------------
namespace Texture
{
    /* 別名 */
    using TextureHandle = GLuint;                                                               // TextureHandle型
    using TypeEnum = GLenum;                                                                    // TypeEnum型
    using ParameterEnum = GLenum;                                                               // ParameterEnum型
    using FilterEnum = GLenum;                                                                  // FilterEnum型
    using WrapEnum = GLenum;                                                                    // WrapEnum型
    using FormatType = GLint;                                                                   // FormatType型
    using CompareModeType = GLint;                                                              // CompareModeType型
    using CompareFunctionType = GLint;                                                          // CompareFunctionType型

    
    namespace
    {
        /* 種類 */
        namespace Type
        {
            const TypeEnum s_1D = GL_TEXTURE_1D;                                                ///< @brief 1D
            const TypeEnum s_2D = GL_TEXTURE_2D;                                                ///< @brief 2D
            const TypeEnum s_3D = GL_TEXTURE_3D;                                                ///< @brief 3D
            const TypeEnum s_CUBE_MAP = GL_TEXTURE_CUBE_MAP;                                    ///< @brief キューブマップ

            /* ターゲット */
            namespace Target
            {
                const TypeEnum s_CUBE_MAP_POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X;          ///< @brief キューブマップの右方向 
                const TypeEnum s_CUBE_MAP_POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y;          ///< @brief キューブマップの上方向
                const TypeEnum s_CUBE_MAP_POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z;          ///< @brief キューブマップの後方向
                const TypeEnum s_CUBE_MAP_NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X;          ///< @brief キューブマップの左方向
                const TypeEnum s_CUBE_MAP_NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;          ///< @brief キューブマップの下方向
                const TypeEnum s_CUBE_MAP_NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;          ///< @brief キューブマップの前方向
            }
        }

        /* パラメータ */
        namespace Parameter
        {
            const ParameterEnum s_MAGNIFICATION_FILTER = GL_TEXTURE_MAG_FILTER;                 ///< @brief 拡大
            const ParameterEnum s_REDUCION_FILTER = GL_TEXTURE_MIN_FILTER;                      ///< @brief 縮小
            const ParameterEnum s_WRAP_S = GL_TEXTURE_WRAP_S;                                   ///< @brief S軸方向のラップ
            const ParameterEnum s_WRAP_T = GL_TEXTURE_WRAP_T;                                   ///< @brief T軸方向のラップ
            const ParameterEnum s_WRAP_R = GL_TEXTURE_WRAP_R;                                   ///< @brief R軸方向のラップ
            const ParameterEnum s_BORDER_COLOR = GL_TEXTURE_BORDER_COLOR;                       ///< @brief 境界色
            const ParameterEnum s_COMPARE_MODE = GL_TEXTURE_COMPARE_MODE;                       ///< @brief 比較モード
            const ParameterEnum s_COMPARE_FUNCTION = GL_TEXTURE_COMPARE_FUNC;                   ///< @brief 比較の関数
        }


        /* フィルタの種類 */
        namespace FilterType
        {
            /* 拡大 */
            namespace Magnification
            {
                const FilterEnum s_NEAREST = GL_NEAREST;                                       ///< @brief 最近傍補間
                const FilterEnum s_LINEAR = GL_LINEAR;                                         ///< @brief 線形補間
            }

            /* 縮小 */
            namespace Reduction
            {
                const FilterEnum s_NEAREST = GL_NEAREST;                                       ///< @brief 最近傍補間
                const FilterEnum s_LINEAR = GL_LINEAR;                                         ///< @brief 線形補間

                /* ミップマップ */
                namespace MipMap
                {
                    /* 最も小さいサイズ */
                    namespace NearestSize
                    {
                        const FilterEnum s_NEAREST = GL_NEAREST_MIPMAP_NEAREST;                 ///< @brief 最近傍補間
                        const FilterEnum s_LINEAR = GL_LINEAR_MIPMAP_NEAREST;                   ///< @brief 線形補間
                    }

                    /* 平均のサイズ */
                    namespace AverageSize
                    {
                        const FilterEnum s_NEAREST = GL_NEAREST_MIPMAP_LINEAR;                  ///< @brief 最近傍補間
                        const FilterEnum s_LINEAR = GL_LINEAR_MIPMAP_LINEAR;                    ///< @brief 線形補間
                    }
                }
            }
        }

        /* ラップの種類 */
        namespace WrapType
        {
            const WrapEnum s_REPEAT = GL_REPEAT;                                                ///< @brief 繰り返し
            const WrapEnum s_CLAMP = GL_CLAMP;                                                  ///< @brief 端のピクセル色を引き延ばす
            const WrapEnum s_CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE;                                  ///< @brief 境界色より内側のピクセルを引き延ばす
            const WrapEnum s_CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER;                              ///< @brief 境界色を引き延ばす
        }

        /* フォーマット */
        namespace Format
        {
            const FormatType s_RGB = GL_RGB;                                                    ///< @brief RGB
            const FormatType s_RGBA = GL_RGBA;                                                  ///< @brief RGBA
            const FormatType s_RGB_4 = GL_RGB4;                                                 ///< @brief 各成分が4ビットRGB
            const FormatType s_RGB_8 = GL_RGB8;                                                 ///< @brief 各成分が8ビットRGB
            const FormatType s_RGB_16 = GL_RGB16;                                               ///< @brief 各成分が16ビットRGB
            const FormatType s_RGBA_4 = GL_RGBA4;                                               ///< @brief 各成分が4ビットRGBA
            const FormatType s_RGBA_8 = GL_RGBA8;                                               ///< @brief 各成分が8ビットRGBA
            const FormatType s_RGBA_16 = GL_RGBA16;                                             ///< @brief 各成分が16ビットRGBA
            const FormatType s_DEPTH_16 = GL_DEPTH_COMPONENT16;                                 ///< @brief 16ビット深度バッファ
            const FormatType s_DEPTH_24 = GL_DEPTH_COMPONENT24;                                 ///< @brief 24ビット深度バッファ
            const FormatType s_DEPTH_32 = GL_DEPTH_COMPONENT32;                                 ///< @brief 32ビット深度バッファ
            const FormatType s_STENCIL_8 = GL_STENCIL_INDEX8;                                   ///< @brief 8ビットステンシルバッファ
            const FormatType s_STENCIL_16 = GL_STENCIL_INDEX8;                                  ///< @brief 16ビットステンシルバッファ
        }

        /* 比較モード */
        namespace CompareMode
        {
            const CompareModeType s_REF_TO_TEXTURE = GL_COMPARE_REF_TO_TEXTURE;                 ///< @brief 深度比較
        }

        /* 比較関数 */
        namespace CompareFunction
        {
            const CompareFunctionType s_LESS = GL_LESS;                                         ///< @brief 未満
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief テクスチャデータ
    //! @brief テクスチャデータを表す構造体
    //!
    //-------------------------------------------------------------
    struct S_TextureData
    {
        TextureHandle textureHandle_ = 0;                               ///< @brief テクスチャハンドル
        int32_t width_ = 0;                                             ///< @brief 幅
        int32_t height_ = 0;                                            ///< @brief 高さ
        int32_t depth_ = 0;                                             ///< @brief 奥行

        S_TextureData() = default;                                      //!< @brief デフォルトコンストラクタ

        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        S_TextureData(int32_t width, int32_t height = 0, int32_t depth = 0) :

            // サイズ
            width_(width),
            height_(height),
            depth_(depth)

        {
            ::glGenTextures(1, &textureHandle_);
        }

        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        ~S_TextureData()
        {
            ::glDeleteTextures(1, &textureHandle_);
        }
    };


    /*************************************************************//**
     *
     *  @brief  2Dテクスチャのデフォルトのパラメータ設定を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    inline static void s_Default2DParameter()
    {
        ::glTexParameteri(Type::s_2D, Parameter::s_MAGNIFICATION_FILTER, FilterType::Magnification::s_LINEAR);
        ::glTexParameteri(Type::s_2D, Parameter::s_REDUCION_FILTER, FilterType::Reduction::s_LINEAR);
    }


    /*************************************************************//**
     *
     *  @brief  キューブマップテクスチャのデフォルトのパラメータ設定を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    inline static void s_DefaultCubeMapParameter()
    {
        ::glTexParameteri(Type::s_CUBE_MAP, Parameter::s_MAGNIFICATION_FILTER, FilterType::Magnification::s_LINEAR);
        ::glTexParameteri(Type::s_CUBE_MAP, Parameter::s_REDUCION_FILTER, FilterType::Reduction::s_LINEAR);
        ::glTexParameteri(Type::s_CUBE_MAP, Parameter::s_WRAP_S, WrapType::s_CLAMP_TO_EDGE);
        ::glTexParameteri(Type::s_CUBE_MAP, Parameter::s_WRAP_T, WrapType::s_CLAMP_TO_EDGE);
        ::glTexParameteri(Type::s_CUBE_MAP, Parameter::s_WRAP_R, WrapType::s_CLAMP_TO_EDGE);
    }
}