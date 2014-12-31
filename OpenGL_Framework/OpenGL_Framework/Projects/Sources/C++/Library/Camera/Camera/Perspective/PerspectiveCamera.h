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
    //! @brief パースペクティブカメラ
    //! @brief 透視投影を行うカメラ
    //!
    //-------------------------------------------------------------
    class C_PerspectiveCamera : public IC_Camera
    {
    public:
        C_PerspectiveCamera();                                                      // コンストラクタ
        virtual ~C_PerspectiveCamera() override;                                    // デストラクタ
        virtual void Update() override;                                             // 更新処理
        const Vector3& GetEyePoint() const;                                         // 視点を取得
        const Vector3& GetTargetPoint() const;                                      // 注視点を取得
        const Vector3& GetUpVector() const;                                         // アップベクトルを取得
        virtual const Matrix4& GetViewMatrix() const override;                      // ビュー行列を取得
        virtual const Matrix4& GetProjectionMatrix() const override;                // プロジェクション行列を取得
        virtual const Matrix4& GetViewProjectionMatrix() const override;            // ビュープロジェクション行列を取得
        virtual void SetEyePoint(const Vector3& rEyePoint);                         // 視点を設定
        virtual void SetTargetPoint(const Vector3& rTargetPoint);                   // 注視点を設定
        void SetUpVector(const Vector3& rUpVector);                                 // アップベクトルを設定
        void SetFieldOfViewY(float fieldOfView);                                    // 視野の垂直方向の画角
        void SetAspectRatio(float aspectRatio);                                     // アスペクト比を設定
        virtual void SetNearClippingPlane(float nearClippingPlane) override;        // ニアークリップ面を設定
        virtual void SetFarClippingPlane(float farClippingPlane) override;          // ファークリップ面を設定
    protected:
        float fieldOfViewY_ = 0.0f;                                                 ///< @brief 視野の垂直方向の画角
        float aspectRatio_ = 0.0f;                                                  ///< @brief アスペクト比
        float nearClippingPlane_ = 0.0f;                                            ///< @brief ニアークリップ面
        float farClippingPlane_ = 0.0f;                                             ///< @brief ファークリップ面
        Vector3 eyePoint_;                                                          ///< @brief 視点
        Vector3 targetPoint_;                                                       ///< @brief 注視点
        Vector3 upVector_;                                                          ///< @brief アップベクトル
        Matrix4 viewMatrix_;                                                        ///< @brief ビュー行列
        Matrix4 projectionMatrix_;                                                  ///< @brief プロジェクション行列
        Matrix4 viewProjectionMatrix_;                                              ///< @brief ビュープロジェクション行列
    };
}