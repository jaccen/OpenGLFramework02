/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Singleton/Singleton.h"
#include "../../Math/Vector/Vector3.h"


//-------------------------------------------------------------
//!
//! @brief デバッグ
//! @brief デバッグ関連の名前空間
//!
//-------------------------------------------------------------
namespace Debug
{
    /* 別名 */
    using Vector3 = Math::S_Vector3<float>;                                                                         // Vector3型


    namespace
    {
        /* デフォルト */
        namespace Default
        {
            /* フォント */
            namespace Font
            {
                const char* s_pFILE_PATH = "Projects/Fonts/やさしさゴシック/07やさしさゴシック.ttf";                ///< @brief ファイルパス
                const int32_t s_SIZE = 32;                                                                          ///< @brief サイズ
            }
        }

        /* 固定 */
        namespace Fixed
        {
            /* シェーダー */
            namespace Shader
            {
                const char* s_pVERTEX_FILE_PATH = "Projects/Shaders/GLSL/Debug/DebugString.vert";                   ///< @brief 頂点シェーダーのファイルパス
                const char* s_pGEOMETRY_FILE_PATH = "Projects/Shaders/GLSL/Debug/DebugString.geom";                 ///< @brief ジオメトリシェーダーのファイルパス
                const char* s_pFRAGMENT_FILE_PATH = "Projects/Shaders/GLSL/Debug/DebugString.frag";                 ///< @brief フラグメントシェーダーのファイルパス
                const char* s_pGLSL_OBJECT_ID = "DebugString";                                                      ///< @brief シェーダーオブジェクトのID
            }

            /* テクスチャ */
            namespace Texture
            {
                const int32_t s_UNIT_NUMBER = 26;                                                                   ///< @brief ユニット番号
            }
        }
    }


    /** 文字揃え */
    enum class ecTypographicAlignment
    {
        LEFT,                                                                                                       ///< @brief 左揃え
        RIGHT,                                                                                                      ///< @brief 右揃え
        CENTER,                                                                                                     ///< @brief 中央揃え
    };


    //-------------------------------------------------------------
    //!
    //! @brief デバッグストリング
    //! @brief デバッグ用の文字列描画を行うためのクラス
    //!
    //-------------------------------------------------------------
    class C_DebugString : public Singleton::C_Singleton<C_DebugString>
    {
    public:
        C_DebugString();                                                                                            // コンストラクタ
        ~C_DebugString() override;                                                                                  // デストラクタ
        bool Initialize(const std::string& rFontFilePath = Default::Font::s_pFILE_PATH,                             // 初期化処理
                        int32_t fontSize = Default::Font::s_SIZE);
        void Draw(const std::string& rString,                                                                        // 描画処理
                  const Vector3& rPosition,
                  float scale = 1.0f,
                  uint8_t red = 0,
                  uint8_t green = 0,
                  uint8_t blue = 0,
                  ecTypographicAlignment alignment = ecTypographicAlignment::LEFT);
        void Finalize();                                                                                            // 終了処理
    private:
        /* 前方宣言 */
        class C_DebugStringImpl;

        std::unique_ptr<C_DebugStringImpl> upImpl_;                                                                 ///< brief 実装情報
    };
}