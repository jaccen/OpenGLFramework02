/* ヘッダファイル */
#include "AABB2D.h"


//-------------------------------------------------------------
//!
//! @brief コリジョン
//! @brief 衝突関連の名前空間
//!
//-------------------------------------------------------------
namespace Collision
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  最小座標
     *  @param  最大座標
     *
     ****************************************************************/
    template<typename T>
    S_Aabb2D<T>::S_Aabb2D(const Point2& rMin, const Point2& rMax) :

        // 各座標
        min_(rMin),
        max_(rMax)

    {
    }


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  中心点
     *  @param  幅
     *  @param  高さ
     *
     ****************************************************************/
    template<typename T>
    S_Aabb2D<T>::S_Aabb2D(const Point2& rCenterPoint, T width, T height)
    {
        T halfWidth = width * static_cast<T>(0.5);
        T halfHeight = height * static_cast<T>(0.5);

        min_.x_ = rCenterPoint.x_ - halfWidth;
        min_.y_ = rCenterPoint.y_ - halfHeight;

        max_.x_ = rCenterPoint.x_ + halfWidth;
        max_.y_ = rCenterPoint.y_ + halfHeight;
    }


    /*************************************************************//**
     *
     *  @brief  衝突判定を行う
     *  @param  もう一つのAABB
     *  @return 衝突した場合    ：true
     *  @return 衝突してない場合：false
     *
     ****************************************************************/
    template<typename T>
    bool S_Aabb2D<T>::Detection(const S_Aabb2D<T>& rAnother)
    {
        return C_Detection2D<T>::s_CheckRectangleAndRectangle(min_, max_, rAnother.min_, rAnother.max_);
    }


    /* 明示的インスタンス化 */
    template struct S_Aabb2D<float>;
    template struct S_Aabb2D<double>;
}


