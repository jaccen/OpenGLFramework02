/* ヘッダファイル */
#include "OrthographicCamera.h"
#include "../../../Debug/Helper/DebugHelper.h"


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
    C_OrthographicCamera::C_OrthographicCamera()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_OrthographicCamera::~C_OrthographicCamera()
    {
    }


    /*************************************************************//**
     *
     *  @brief  カメラの更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_OrthographicCamera::Update()
    {
        projectionMatrix_ = Matrix4x4::s_CreateOrthographicProjection(clipSpaceLeft_,
                                                                      clipSpaceRight_,
                                                                      clipSpaceBottom_,
                                                                      clipSpaceTop_,
                                                                      nearClippingPlane_,
                                                                      farClippingPlane_);
    }


    /*************************************************************//**
     *
     *  @brief  ビュー行列を取得する
     *  @param  なし
     *  @return ビュー行列
     *
     ****************************************************************/
    const Matrix4x4& C_OrthographicCamera::GetViewMatrix() const
    {
        return Matrix4x4::s_IDENTITY;
    }


    /*************************************************************//**
     *
     *  @brief  プロジェクション行列を取得する
     *  @param  なし
     *  @return プロジェクション行列
     *
     ****************************************************************/
    const Matrix4x4& C_OrthographicCamera::GetProjectionMatrix() const
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
    const Matrix4x4& C_OrthographicCamera::GetViewProjectionMatrix() const
    {
        return projectionMatrix_;
    }


    /*************************************************************//**
     *
     *  @brief  クリップ空間を設定する
     *  @param  クリップ空間の左側
     *  @param  クリップ空間の右側
     *  @param  クリップ空間の下側
     *  @param  クリップ空間の上側
     *  @return なし
     *
     ****************************************************************/
    void C_OrthographicCamera::SetClipSpace(float left, float right, float bottom, float top)
    {
        clipSpaceLeft_ = left;
        clipSpaceRight_ = right;
        clipSpaceBottom_ = bottom;
        clipSpaceTop_ = top;
    }


    /*************************************************************//**
     *
     *  @brief  ニアークリップ面を設定する
     *  @param  ニアークリップ面
     *  @return なし
     *
     ****************************************************************/
    void C_OrthographicCamera::SetNearClippingPlane(float nearClippingPlane)
    {
        nearClippingPlane_ = nearClippingPlane;
    }

    /*************************************************************//**
     *
     *  @brief  ファークリップ面を設定する
     *  @param  ファークリップ面
     *  @return なし
     *
     ****************************************************************/
    void C_OrthographicCamera::SetFarClippingPlane(float farClippingPlane)
    {
        farClippingPlane_ = farClippingPlane;
    }
}