/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Math/Matrix/Matrix4x4.h"


//-------------------------------------------------------------
//!
//! @brief ビュー
//! @brief ビュー関連の名前空間
//!
//-------------------------------------------------------------
namespace View
{
    /* 別名 */
    using Vector4 = Math::S_Vector4<float>;                                         // Vector4型
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                     // Matrix4x4型


    //-------------------------------------------------------------
    //!
    //! @brief ビューヘルパー
    //! @brief 視認の補助を行う関数をまとめたユーティリティクラス
    //!
    //-------------------------------------------------------------
    class C_ViewHelper
    {
    public:
        static void s_DrawGrid(float lineHelfLength,                                // グリッドを描画
                               float lineInterval,
                               uint32_t lineCount,
                               const Vector4& rLineColor,
                               const Matrix4x4& rViewProjectionMatrix);
        static void s_DrawAxis(float lineLength,                                    // 軸を描画
                               const Matrix4x4& rViewProjectionMatrix);
    };
}