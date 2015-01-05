/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../../Math/Vector/Vector2.h"
#include "../../Detection/Detection2D.h"


//-------------------------------------------------------------
//!
//! @brief コリジョン
//! @brief 衝突関連の名前空間
//!
//-------------------------------------------------------------
namespace Collision
{
    //-------------------------------------------------------------
    //!
    //! @brief AABB2D
    //! @brief 2DのAABBの判定を行う構造体
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    struct S_Aabb2D
    {
        /* 別名 */
        using Point2 = Point2<T>;                                       // Point2型を省略

        Point2 min_;                                                    ///< @brief 最小座標
        Point2 max_;                                                    ///< @brief 最大座標

        S_Aabb2D() = default;                                           // デフォルトコンストラクタ
        S_Aabb2D(const Point2& rMin, const Point2& rMax);               // コンストラクタ
        S_Aabb2D(const Point2& rCenterPoint, T width, T height);        // コンストラクタ
        bool Detection(const S_Aabb2D& rAnother);                       // 衝突判定
    };


    /* 別名 */
    using Aabb2D = S_Aabb2D<>;                                          // Aabb2D型
}



