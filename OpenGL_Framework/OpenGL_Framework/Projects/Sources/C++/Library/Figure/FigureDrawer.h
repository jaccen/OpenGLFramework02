/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Singleton/Singleton.h"
#include "../Math/Vector/Vector4.h"
#include "../Math/Matrix/Matrix4x4.h"


//-------------------------------------------------------------
//!
//! @brief フィギュア
//! @brief 図形関連の名前空間
//!
//-------------------------------------------------------------
namespace Figure
{
    /* 別名 */
    using Vector3 = Math::S_Vector3<float>;                                                         // Vector3型
    using Vector4 = Math::S_Vector4<float>;                                                         // Vector4型
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                                     // Matrix4x4型


    namespace
    {
        /* 固定 */
        namespace Fixed
        {
            /* シェーダー */
            namespace Shader
            {
                const char* s_pVERTEX_FILE_PATH = "Projects/Shaders/GLSL/Figure/Figure.vert";       ///< @brief 頂点シェーダーのファイルパス
                const char* s_pFRAGMENT_FILE_PATH = "Projects/Shaders/GLSL/Figure/Figure.frag";     ///< @brief フラグメントシェーダーのファイルパス
                const char* s_pGLSL_OBJECT_ID = "FigureDrawer";                                     ///< @brief シェーダーオブジェクトのID
            }
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief フィギュアドロワー
    //! @brief 図形描画を行うクラス
    //!
    //-------------------------------------------------------------
    class C_FigureDrawer : public Singleton::C_Singleton<C_FigureDrawer>
    {
        friend C_Singleton<C_FigureDrawer>;                                                         // シングルトンクラスをフレンド化
    public:
        bool Initialize();                                                                          // 初期化処理
        void Finalize();                                                                            // 終了処理
        void DrawPoint(const Vector3& rPosition,                                                    // 点の描画
                       const Vector4& rColor,
                       const Matrix4x4& rViewProjectionMatrix);               
        void DrawLine(const Vector3& rStartPosition,                                                // 線の描画
                      const Vector3& rEndPositiont, 
                      const Vector4& rColor,
                      const Matrix4x4& rViewProjectionMatrix);
        void SetPointSize(float pointSize);                                                         // 点のサイズを設定
    private:
        /* 前方宣言 */
        class C_FigureDrawerImpl;

        std::unique_ptr<C_FigureDrawerImpl> upImpl_;                                                ///< @brief 実装情報

        C_FigureDrawer();                                                                           // コンストラクタ
        ~C_FigureDrawer() override;                                                                 // デストラクタ
    };
}