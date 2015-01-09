/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Camera.h"


//-------------------------------------------------------------
//!
//! @brief カメラ
//! @brief カメラ関連の名前空間
//!
//-------------------------------------------------------------
namespace Camera
{
    //-------------------------------------------------------------
    //!
    //! @brief オルトグラフィックカメラ
    //! @brief 正投影のカメラ
    //!
    //-------------------------------------------------------------
    class C_OrthographicCamera : public IC_Camera
    {
    public:
        C_OrthographicCamera();                                                                                         // コンストラクタ
        virtual ~C_OrthographicCamera() override;                                                                       // デストラクタ
        virtual void Update() override;                                                                                 // 更新処理
        virtual const Matrix4x4& GetViewMatrix() const override;                                                        // ビュー行列を取得
        virtual const Matrix4x4& GetProjectionMatrix() const override;                                                  // プロジェクション行列を取得
        virtual const Matrix4x4& GetViewProjectionMatrix() const override;                                              // ビュープロジェクション行列を取得
        virtual void SetClipSpace(float left, float right, float bottom, float top);                                    // クリップ空間を設定
        virtual void SetNearClippingPlane(float nearClippingPlane = Matrix4x4::s_ORTHOGRAPHIC_2D_NEAR) override;        // ニアークリップ面を設定
        virtual void SetFarClippingPlane(float farClippingPlane = Matrix4x4::s_ORTHOGRAPHIC_2D_FAR) override;           // ファークリップ面を設定
    private:
        float clipSpaceLeft_ = 0.0f;                                                                                    ///< @brief クリップ面の左側
        float clipSpaceRight_ = 0.0f;                                                                                   ///< @brief クリップ面の右側
        float clipSpaceBottom_ = 0.0f;                                                                                  ///< @brief クリップ面の下側
        float clipSpaceTop_ = 0.0f;                                                                                     ///< @brief クリップ面の上側
        float nearClippingPlane_ = Matrix4x4::s_ORTHOGRAPHIC_2D_NEAR;                                                   ///< @brief ニアークリップ面
        float farClippingPlane_ = Matrix4x4::s_ORTHOGRAPHIC_2D_FAR;                                                     ///< @brief ファークリップ面
        Matrix4x4 projectionMatrix_;                                                                                    ///< @brief プロジェクション行列
    };
}