/* 二重インクルード防止 */
#pragma once


/* 前方宣言 */
namespace Math
{
    template<typename T>
    struct S_Vector2;
};


//-------------------------------------------------------------
//!
//! @brief コリジョン
//! @brief 衝突関連の名前空間
//!
//-------------------------------------------------------------
namespace Collision
{
    /* 別名 */
    template<typename T>
    using Point2 = Math::S_Vector2<T>;          // Point2型


    //-------------------------------------------------------------
    //!
    //! @brief ディテクション2D
    //! @brief 2Dの衝突判定の関数をまとめたユーティリティクラス
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    class C_Detection2D
    {
    public:
        /* 別名 */
        using Point2 = Point2<T>;               // Point2型を省略


        /* 矩形同士の衝突判定 */
        static bool s_CheckRectangleAndRectangle(const Point2& rCenterPosition,
                                                 T halfWidth,
                                                 T halfHeight,
                                                 const Point2& rAnotherCenterPosition,
                                                 T anotherHalfWidth,
                                                 T anotherHalfHeihgt);

        static bool s_CheckRectangleAndRectangle(const Point2& rCenterPosition,
                                                 T halfWidth,
                                                 T halfHeight,
                                                 T angle,
                                                 const Point2& rAnotherCenterPosition,
                                                 T anotherHalfWidth,
                                                 T anotherHalfHeight,
                                                 T anotherAngle);

        /* 円同士の衝突判定 */
        static bool s_CheckCircleAndCircle(const Point2& rCenterPosition,
                                           T radius,
                                           const Point2& rAnotherCenterPosition,
                                           T anotherRadius);

        /* 矩形と円の衝突判定 */
        static bool s_CheckRectangleAndCircle(const Point2& rRectangleCenterPosition,
                                              T rectangleHalfWidth,
                                              T rectangleHalfHeight,
                                              T rectangleAngle,
                                              const Point2& rCircleCenterPosition,
                                              T circleRadius);

        /* 円と点の衝突判定 */
        static bool s_CheckCircleAndPoint(const Point2& rCircleCenterPosition,
                                          T circleRadius,
                                          const Point2& rPoint);

        /* 円と線分の衝突判定 */
        static bool s_CheckCircleAndSegment(const Point2& rCircleCenterPosition,
                                            T circleRadius,
                                            const Point2& rSegmentBeginPoint,
                                            const Point2& rSegmentEndPoint);

        /* 点と点の衝突判定 */
        static bool s_CheckPointAndPoint(const Point2& rPoint,
                                         const Point2& rAnotherPoint);

        /* 点と線分の衝突判定 */
        static bool s_CheckPointAndSegment(const Point2& rPoint,
                                           const Point2& rSegmentBeginPoint,
                                           const Point2& rSegmentEndPoint);

        /* 点と楕円の衝突判定 */
        static bool s_CheckPointAndEllipse(const Point2& rPoint,
                                           const Point2& rEllipseCenterPosition,
                                           const Point2& rEllipseSemidiameter,
                                           T ellipseAngle);

        /* 線分と線分の衝突判定 */
        static bool s_CheckSegmentAndSegment(const Point2& rBeginPoint,
                                             const Point2& rEndPoint,
                                             const Point2& rAnotherBeginPoint,
                                             const Point2& rAnotherEndPoint,
                                             Point2* pIntersectionPoint);
    };
}
