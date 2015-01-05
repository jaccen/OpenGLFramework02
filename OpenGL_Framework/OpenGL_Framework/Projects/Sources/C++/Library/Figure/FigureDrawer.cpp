/* ヘッダファイル */
#include "FigureDrawerImpl.h"


//-------------------------------------------------------------
//!
//! @brief フィギュア
//! @brief 図形関連の名前空間
//!
//-------------------------------------------------------------
namespace Figure
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_FigureDrawer::C_FigureDrawer() :

        // 実装情報
        upImpl_(std::make_unique<C_FigureDrawerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_FigureDrawer::~C_FigureDrawer()
    {
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  なし
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_FigureDrawer::Initialize()
    {
        if (upImpl_->Initialize() == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_FigureDrawer::Finalize()
    {
        upImpl_->Finalize();
    }


        /*************************************************************//**
     *
     *  @brief  点の描画を行う
     *  @param  座標
     *  @param  色
     *  @param  ビュープロジェクション行列
     *  @return なし
     *
     ****************************************************************/
    void C_FigureDrawer::DrawPoint(const Vector3& rPosition,
                                   const Vector4& rColor,
                                   const Matrix4x4& rViewProjectionMatrix)
    {
        upImpl_->DrawPoint(rPosition, rColor, rViewProjectionMatrix);
    }


    /*************************************************************//**
     *
     *  @brief  線の描画を行う
     *  @param  開始座標
     *  @param  終了座標
     *  @param  色
     *  @param  ビュープロジェクション行列
     *  @return なし
     *
     ****************************************************************/
    void C_FigureDrawer::DrawLine(const Vector3& rStartPosition,
                                  const Vector3& rEndPosition,
                                  const Vector4& rColor,
                                  const Matrix4x4& rViewProjectionMatrix)
    {
        upImpl_->DrawLine(rStartPosition, rEndPosition, rColor, rViewProjectionMatrix);
    }


    /*************************************************************//**
     *
     *  @brief  点のサイズを設定する
     *  @param  点のサイズ
     *  @return なし
     *
     ****************************************************************/
    void C_FigureDrawer::SetPointSize(float pointSize)
    {
        upImpl_->SetPointSize(pointSize);
    }
}