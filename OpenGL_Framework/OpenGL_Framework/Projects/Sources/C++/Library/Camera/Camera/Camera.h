/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Math/Vector/Vector3.h"
#include "../../Math/Matrix/Matrix4x4.h"


//-------------------------------------------------------------
//!
//! @brief カメラ
//! @brief カメラ関連の名前空間
//!
//-------------------------------------------------------------
namespace Camera
{
    /* 別名 */
    using Vector3 = Math::S_Vector3<float>;                                     // Vector3型
    using Matrix4 = Math::S_Matrix4x4<float>;                                   // Matrix4型


    //-------------------------------------------------------------
    //!
    //! @brief カメラ
    //! @brief カメラのインタフェース
    //!
    //-------------------------------------------------------------
    class IC_Camera
    {
    public:
        IC_Camera() = default;                                                  // コンストラクタ
        virtual ~IC_Camera() = default;                                         // デストラクタ
        virtual void Update() = 0;                                              // 更新処理
        virtual const Matrix4& GetViewMatrix() const = 0;                       // ビュー行列を取得
        virtual const Matrix4& GetProjectionMatrix() const = 0;                 // プロジェクション行列を取得
        virtual const Matrix4& GetViewProjectionMatrix() const = 0;             // ビュープロジェクション行列を取得
        virtual void SetNearClippingPlane(float nearClippingPlane) = 0;         // ニアークリップ面を設定
        virtual void SetFarClippingPlane(float farClippingPlane) = 0;           // ファークリップ面を設定
    };
}