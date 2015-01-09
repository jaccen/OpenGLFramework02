/* ヘッダファイル */
#include "PerspectiveCamera.h"


//-------------------------------------------------------------
//!
//! @brief カメラ
//! @brief カメラ関連の名前空間
//!
//-------------------------------------------------------------
namespace Camera
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PerspectiveCamera::C_PerspectiveCamera()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PerspectiveCamera::~C_PerspectiveCamera()
    {
    }


    /*************************************************************//**
     *
     *  @brief  カメラの更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PerspectiveCamera::Update()
    {
        // ビュー行列を更新
        viewMatrix_ = Matrix4x4::s_CreateLookAt(eyePoint_,
                                                targetPoint_,
                                                upVector_);

        // プロジェクション行列を更新
        projectionMatrix_ = Matrix4x4::s_CreatePerspectiveProjection(fieldOfViewY_,
                                                                     aspectRatio_,
                                                                     nearClippingPlane_,
                                                                     farClippingPlane_);

        // ビュープロジェクション行列を計算
        viewProjectionMatrix_ = projectionMatrix_ * viewMatrix_;
    }


    /*************************************************************//**
     *
     *  @brief  視点を取得する
     *  @param  なし
     *  @return 視点
     *
     ****************************************************************/
    const Vector3& C_PerspectiveCamera::GetEyePoint() const
    {
        return eyePoint_;
    }


    /*************************************************************//**
     *
     *  @brief  注視点を取得する
     *  @param  なし
     *  @return 注視点
     *
     ****************************************************************/
    const Vector3& C_PerspectiveCamera::GetTargetPoint() const
    {
        return targetPoint_;
    }


    /*************************************************************//**
     *
     *  @brief  アップベクトルを取得する
     *  @param  なし
     *  @return アップベクトル
     *
     ****************************************************************/
    const Vector3& C_PerspectiveCamera::GetUpVector() const
    {
        return upVector_;
    }


    /*************************************************************//**
     *
     *  @brief  ビュー行列を取得する
     *  @param  なし
     *  @return ビュー行列
     *
     ****************************************************************/
    const Matrix4x4& C_PerspectiveCamera::GetViewMatrix() const
    {
        return viewMatrix_;
    }


    /*************************************************************//**
     *
     *  @brief  プロジェクション行列を取得する
     *  @param  なし
     *  @return プロジェクション行列
     *
     ****************************************************************/
    const Matrix4x4& C_PerspectiveCamera::GetProjectionMatrix() const
    {
        return projectionMatrix_;
    }


    /*************************************************************//**
     *
     *  @brief  ビュープロジェクション行列を取得する
     *  @param  なし
     *  @return ビュープロジェクション行列
     *
     ****************************************************************/
    const Matrix4x4& C_PerspectiveCamera::GetViewProjectionMatrix() const
    {
        return viewProjectionMatrix_;
    }


    /*************************************************************//**
     *
     *  @brief  視点を設定する
     *  @param  視点
     *  @return なし
     *
     ****************************************************************/
    void C_PerspectiveCamera::SetEyePoint(const Vector3& rEyePoint)
    {
        eyePoint_ = rEyePoint;
    }


    /*************************************************************//**
     *
     *  @brief  注視点を設定する
     *  @param  注視点
     *  @return なし
     *
     ****************************************************************/
    void C_PerspectiveCamera::SetTargetPoint(const Vector3& rTargetPoint)
    {
        targetPoint_ = rTargetPoint;
    }


    /*************************************************************//**
     *
     *  @brief  アップベクトルを設定する
     *  @param  アップベクトル
     *  @return なし
     *
     ****************************************************************/
    void C_PerspectiveCamera::SetUpVector(const Vector3& rUpVector)
    {
        upVector_ = rUpVector;
    }


    /*************************************************************//**
     *
     *  @brief  視野の垂直方向の画角を設定する
     *  @param  視野の垂直方向の画角
     *  @return なし
     *
     ****************************************************************/
    void C_PerspectiveCamera::SetFieldOfViewY(float fieldOfViewY)
    {
        fieldOfViewY_ = fieldOfViewY;
    }


    /*************************************************************//**
     *
     *  @brief  アスペクト比を設定する
     *  @param  アスペクト比
     *  @return なし
     *
     ****************************************************************/
    void C_PerspectiveCamera::SetAspectRatio(float aspectRatio)
    {
        aspectRatio_ = aspectRatio;
    }


    /*************************************************************//**
     *
     *  @brief  視点から最も近いクリップ面を設定する
     *  @param  視点から最も近いクリップ面
     *  @return なし
     *
     ****************************************************************/
    void C_PerspectiveCamera::SetNearClippingPlane(float nearClippingPlane)
    {
        nearClippingPlane_ = nearClippingPlane;
    }


    /*************************************************************//**
     *
     *  @brief  視点から最も遠いクリップ面を設定する
     *  @param  視点から最も遠いクリップ面
     *  @return なし
     *
     ****************************************************************/
    void C_PerspectiveCamera::SetFarClippingPlane(float farClippingPlane)
    {
        farClippingPlane_ = farClippingPlane;
    }
}