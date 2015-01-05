/* ヘッダファイル */
#include "ViewHelper.h"
#include "../Figure/FigureDrawer.h"


//-------------------------------------------------------------
//!
//! @brief ビュー
//! @brief ビュー関連の名前空間
//!
//-------------------------------------------------------------
namespace View
{
    /*************************************************************//**
     *
     *  @brief  グリッドの描画を行う
     *  @param  線の半分の長さ
     *  @param  線の間隔
     *  @param  線の数
     *  @param  線の色
     *  @param  ビュープロジェクション行列
     *
     ****************************************************************/
    void C_ViewHelper::s_DrawGrid(float lineHelfLength,
                                  float lineInterval,
                                  uint32_t lineCount, 
                                  const Vector4& rLineColor,
                                  const Matrix4x4& rViewProjectionMatrix)
    {
        // 図形の描画者を取得
        auto pFigureDrawer = Figure::C_FigureDrawer::s_GetInstance();

        // 線の端
        float lineSide = -lineInterval * static_cast<float>(lineCount / 2);

        Figure::Vector3 startPosition;
        Figure::Vector3 endPosition;

        for (size_t i = 0; i < lineCount; ++i)
        {
            // 線を描画
            startPosition = Figure::Vector3(lineSide, 0.0f, lineHelfLength);
            endPosition = Figure::Vector3(lineSide, 0.0f, -lineHelfLength);
            pFigureDrawer->DrawLine(startPosition, endPosition, rLineColor, rViewProjectionMatrix);

            startPosition = Figure::Vector3(lineHelfLength, 0.0f, lineSide);
            endPosition = Figure::Vector3(-lineHelfLength, 0.0f, lineSide);
            pFigureDrawer->DrawLine(startPosition, endPosition, rLineColor, rViewProjectionMatrix);

            // 線の端を間隔分ずらす
            lineSide += lineInterval;
        }
    }

    /*************************************************************//**
     *
     *  @brief  軸の描画を行う
     *  @param  線の長さ
     *  @param  ビュープロジェクション行列
     *
     ****************************************************************/
    void C_ViewHelper::s_DrawAxis(float lineLength,
                                  const Matrix4x4& rViewProjectionMatrix)
    {
        // 各軸の色
        Figure::Vector4 colorAxisX(1.0f, 0.0f, 0.0f, 1.0f);
        Figure::Vector4 colorAxisY(0.0f, 1.0f, 0.0f, 1.0f);
        Figure::Vector4 colorAxisZ(0.0f, 0.0f, 1.0f, 1.0f);

        // 図形の描画者を取得
        auto pFigureDrawer = Figure::C_FigureDrawer::s_GetInstance();

        // 原点
        Figure::Vector3 origin;

        // 線を描画
        pFigureDrawer->DrawLine(origin, Figure::Vector3(lineLength, 0.0f, 0.0f), colorAxisX, rViewProjectionMatrix);
        pFigureDrawer->DrawLine(origin, Figure::Vector3(0.0f, lineLength, 0.0f), colorAxisY, rViewProjectionMatrix);
        pFigureDrawer->DrawLine(origin, Figure::Vector3(0.0f, 0.0f, lineLength), colorAxisZ, rViewProjectionMatrix);
    }
}