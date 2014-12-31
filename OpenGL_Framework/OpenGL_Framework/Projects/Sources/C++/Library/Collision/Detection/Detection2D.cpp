/* ヘッダファイル */
#include "Detection2D.h"
#include "../../Math/Vector/Vector2.h"
#include "../../Math/Define/MathDefine.h"


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
     *  @brief  矩形同士の衝突判定を行う
     *  @param  中心座標
     *  @param  幅の半分
     *  @param  高さの半分
     *  @param  もう一つの中心座標
     *  @param  もう一つの幅の半分
     *  @param  もう一つの高さの半分
     *  @return 衝突した場合：true
     *  @return 衝突しなかった場合：false
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckRectangleAndRectangle(const Point2& rCenterPosition,
                                                        T halfWidth,
                                                        T halfHeight,
                                                        const Point2& rAnotherCenterPosition,
                                                        T anotherHalfWidth,
                                                        T anotherHalfHeihgt)
    {
        // 矩形の4つの端を比較して全ての条件を満たした場合は衝突
        if ((rCenterPosition.x_ - halfWidth <= rAnotherCenterPosition.x_ + anotherHalfWidth)
         && (rCenterPosition.x_ + halfWidth >= rAnotherCenterPosition.x_ - anotherHalfWidth)
         && (rCenterPosition.y_ - halfHeight <= rAnotherCenterPosition.y_ + anotherHalfHeihgt)
         && (rCenterPosition.y_ + halfHeight >= rAnotherCenterPosition.y_ - anotherHalfHeihgt))
        {
            return true;
        }

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  矩形同士の衝突判定を行う
     *  @param  中心座標
     *  @param  幅の半分
     *  @param  高さの半分
     *  @param  角度
     *  @param  もう一つの中心座標
     *  @param  もう一つの幅の半分
     *  @param  もう一つの高さの半分
     *  @param  もう一つの角度
     *  @return 衝突した場合：true
     *  @return 衝突しなかった場合：false
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckRectangleAndRectangle(const Point2& rCenterPosition,
                                                        T halfWidth,
                                                        T halfHeight,
                                                        T angle,
                                                        const Point2& rAnotherCenterPosition,
                                                        T anotherHalfWidth,
                                                        T anotherHalfHeight,
                                                        T anotherAngle)
    {
        // 中心座標に加える座標
        Point2 addPositions[4] = { Point2(-halfWidth, halfHeight),
                                   Point2(-halfWidth, -halfHeight),
                                   Point2(halfWidth, halfHeight),
                                   Point2(halfWidth, -halfHeight) };

        Point2 anotherAddPositions[4] = { Point2(-anotherHalfWidth, anotherHalfHeight),
                                          Point2(-anotherHalfWidth, -anotherHalfHeight),
                                          Point2(anotherHalfWidth, anotherHalfHeight),
                                          Point2(anotherHalfWidth, -anotherHalfHeight) };
        for (size_t i = 0; i < 4; ++i)
        {
            addPositions[i].Rotate(angle);
            anotherAddPositions[i].Rotate(anotherAngle);
        }

        // 頂点
        Point2 vertices[4] = { rCenterPosition + addPositions[0],
                               rCenterPosition + addPositions[1],
                               rCenterPosition + addPositions[2],
                               rCenterPosition + addPositions[3] };

        Point2 anotherVertices[4] = { rAnotherCenterPosition + anotherAddPositions[0],
                                      rAnotherCenterPosition + anotherAddPositions[1],
                                      rAnotherCenterPosition + anotherAddPositions[2],
                                      rAnotherCenterPosition + anotherAddPositions[3] };

        // 頂点からできるベクトル
        Point2 vertexVectors[4] = { vertices[2] - vertices[0],
                                    vertices[0] - vertices[1],
                                    vertices[1] - vertices[3],
                                    vertices[3] - vertices[2] };

        Point2 anotherVertexVectors[4] = { anotherVertices[2] - anotherVertices[0],
                                           anotherVertices[0] - anotherVertices[1],
                                           anotherVertices[1] - anotherVertices[3],
                                           anotherVertices[3] - anotherVertices[2] };

        // 各頂点から生成されたベクトルと外積を取り、2つの矩形の頂点が
        for (auto& rVertexVector : vertexVectors)
        {
            for (size_t i = 0; i < 4; ++i)
            {
                if (Point2::s_CrossProduct(rVertexVector, anotherVertexVectors[i]) > 0.0f)  break;

                if (i == 4) return true;
            }
        }

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  円同士の衝突判定を行う
     *  @param  中心座標
     *  @param  半径
     *  @param  もう一つの中心座標
     *  @param  もう一つの半径
     *  @return 衝突した場合：true
     *  @return 衝突しなかった場合：false
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckCircleAndCircle(const Point2& rCenterPosition,
                                                  T radius,
                                                  const Point2& rAnotherCenterPosition,
                                                  T anotherRadius)
    {
        // 距離
        Point2 distance(rCenterPosition - rAnotherCenterPosition);

        // 半径の合計
        T sumRadius = radius + anotherRadius;

        // 距離の2乗の半径の和の2乗より短い場合は衝突
        if (distance.GetLengthSquare() <= sumRadius * sumRadius) return true;

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  矩形と円の衝突判定を行う
     *  @param  矩形の中心座標
     *  @param  矩形の幅の半分
     *  @param  矩形の高さの半分
     *  @param  矩形の角度( ラジアン値 )
     *  @param  円の中心座標
     *  @param  円の半径
     *  @return 衝突した場合：true
     *  @return 衝突しなかった場合：false
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckRectangleAndCircle(const Point2& rRectangleCenterPosition,
                                                     T rectangleHalfWidth,
                                                     T rectangleHalfHeight,
                                                     T rectangleAngle,
                                                     const Point2& rCircleCenterPosition,
                                                     T circleRadius)
    {
        // 矩形から円までの距離
        Point2 distance(rCircleCenterPosition - rRectangleCenterPosition);

        // 反転した矩形の角度
        T inverseRectangleAngle = -rectangleAngle;

        // 矩形を中心に反転した矩形の角度分だけ回転した円の座標を求める
        Point2 circleRotateCenterPosition;

        circleRotateCenterPosition.x_ = std::cos(inverseRectangleAngle) * distance.x_ - std::sin(inverseRectangleAngle) * distance.y_;
        circleRotateCenterPosition.y_ = std::sin(inverseRectangleAngle) * distance.x_ + std::cos(inverseRectangleAngle) * distance.y_;

        // 矩形の左端座標と上端座標
        T rectangleLeft = -rectangleHalfWidth;
        T rectangleTop = -rectangleHalfHeight;

        // 回転後の円から矩形に対して最も近い点
        Point2 shortestPoint;

        // 回転後の円から矩形に対して最も近いX座標を求める
        if (circleRotateCenterPosition.x_ < rectangleLeft)
        {
            shortestPoint.x_ = rectangleLeft;
        }
        else
        {
            // 矩形の右端座標を求める
            T rectangleRight = rectangleHalfWidth;

            if (circleRotateCenterPosition.x_ > rectangleRight)
            {
                shortestPoint.x_ = rectangleRight;
            }
            else
            {
                shortestPoint.x_ = circleRotateCenterPosition.x_;
            }
        }

        // 回転後の円型矩形に対してい最も近いY座標を求める
        if (circleRotateCenterPosition.y_ < rectangleTop)
        {
            shortestPoint.y_ = rectangleTop;
        }
        else
        {
            // 矩形の下端座標を求める
            T rectangleBottom = rectangleHalfHeight;

            if (circleRotateCenterPosition.y_ > rectangleBottom)
            {
                shortestPoint.y_ = rectangleBottom;
            }
            else
            {
                shortestPoint.y_ = circleRotateCenterPosition.y_;
            }
        }

        // 回転後の円の中心と最も近い点が衝突していたら衝突
        if (s_CheckCircleAndPoint(circleRotateCenterPosition, circleRadius, shortestPoint) == true) return true;

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  円と点の衝突判定を行う
     *  @param  矩形の中心座標
     *  @param  円の半径
     *  @param  点
     *  @return 衝突した場合：true
     *  @return 衝突しなかった場合：false
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckCircleAndPoint(const Point2& rCircleCenterPosition,
                                                 T circleRadius,
                                                 const Point2& rPoint)
    {
        // 点から円の中心までの距離
        Point2 distance(rCircleCenterPosition - rPoint);

        // 点から円の中心までの距離の2乗が円の2乗より短い場合は衝突
        if (distance.GetLengthSquare() <= circleRadius * circleRadius) return true;

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  円と線分の衝突判定を行う
     *  @param  円の中心座標
     *  @param  円の半径
     *  @param  線分の始点
     *  @param  線分の終点
     *  @return 衝突した場合：true
     *  @return 衝突しなかった場合：false
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckCircleAndSegment(const Point2& rCircleCenterPosition,
                                                   T circleRadius,
                                                   const Point2& rSegmentBeginPoint,
                                                   const Point2& rSegmentEndPoint)
    {
        // 線分の始点から終点までのベクトル
        Point2 segmentVector(rSegmentEndPoint - rSegmentBeginPoint);

        // 線分の始点から円の中心座標までのベクトル
        Point2 vectorFromSegmentBeginToCircleCenter(rCircleCenterPosition - rSegmentBeginPoint);

        // 2つのベクトルの外積
        T crossProduct = Point2::s_CrossProduct(segmentVector, vectorFromSegmentBeginToCircleCenter);

        // 線分から円までの距離
        T distance = std::abs(crossProduct) / segmentVector.GetLength();

        // 線分から円までの距離が円の半径より短い場合
        if (distance <= circleRadius)
        {
            // 線分の終点から円の中心座標までのベクトルを求める
            Point2 vectorFromSegmentEndToCircleCenter(rCircleCenterPosition - rSegmentEndPoint);

            // 線分の始点から終点までのベクトルに線分の始点から円の中心座標までのベクトルと
            // 線分の終点から円の中心座標までのベクトルを内積し、その値の乗算が0以下の場合は衝突
            if (Point2::s_DotProduct(segmentVector, vectorFromSegmentBeginToCircleCenter)
                * Point2::s_DotProduct(segmentVector, vectorFromSegmentEndToCircleCenter) <= static_cast<T>(0.0))
            {
                return true;
            }
            else
            {
                // 円の半径の2乗を求める
                T radiusSquare = circleRadius * circleRadius;

                // 線分の始点から円の中心座標の距離の2乗、
                // または線分の終点から円の中心座標の距離の2乗が円の半径の2乗より短い場合は衝突
                if ((vectorFromSegmentBeginToCircleCenter.GetLengthSquare() <= radiusSquare)
                    || (vectorFromSegmentEndToCircleCenter.GetLengthSquare() < radiusSquare))
                {
                    return true;
                }
            }
        }

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  2Dの点と点の衝突判定を行う
     *  @param  点
     *  @param  もう一つの点
     *  @return 衝突した場合：true
     *  @return 衝突しなかった場合：false
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckPointAndPoint(const Point2& rPoint,
                                                const Point2& rAnotherPoint)
    {
        // 点の座標が誤差範囲内であれば衝突
        if ((std::abs(rPoint.x_ - rAnotherPoint.x_) <= static_cast<T>(Math::s_EPSILON))
            && (std::abs(rPoint.y_ - rAnotherPoint.y_) <= static_cast<T>(Math::s_EPSILON)))
        {
            return true;
        }

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  点と線分の衝突判定を行う
     *  @param  点
     *  @param  線分の始点
     *  @param  線分の終点
     *  @return 衝突した場合：true
     *  @return 衝突しなかった場合：false
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckPointAndSegment(const Point2& rPoint,
                                                  const Point2& rSegmentBeginPoint,
                                                  const Point2& rSegmentEndPoint)
    {
        // 線分の始点から終点までのベクトルを求め、長さを取得
        Point2 segmentVector(rSegmentEndPoint - rSegmentBeginPoint);
        T segmentLength = segmentVector.GetLength();

        // 線分の始点から点までのベクトルを求め、距離を取得
        Point2 vectorFromSegmentBeginToPoint(rPoint - rSegmentBeginPoint);
        T segmentBeginFromPointDistance = vectorFromSegmentBeginToPoint.GetLength();

        // 2つのベクトルの外積
        T crossProduct = Point2::s_CrossProduct(segmentVector, vectorFromSegmentBeginToPoint);

        // 2つのベクトルの外積が0と等しく、
        // 線分の始点から点までの長さが線分の長さより短かった場合は衝突
        if ((std::abs(crossProduct) <= static_cast<T>(Math::s_EPSILON)) && (segmentBeginFromPointDistance <= segmentLength))
        {
            return true;
        }

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  点と楕円の衝突判定を行う
     *  @param  点
     *  @param  楕円の中心座標
     *  @param  楕円の軸長
     *  @param  楕円の角度( ラジアン値 )
     *  @return 衝突した場合：true
     *  @return 衝突しなかった場合：false
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckPointAndEllipse(const Point2& rPoint,
                                                  const Point2& rEllipseCenterPosition,
                                                  const Point2& rEllipseSemidiameter,
                                                  T ellipseAngle)
    {
        // 楕円の中心座標から点までの距離
        Point2 distance(rPoint - rEllipseCenterPosition);

        // 反転した楕円の角度
        T inverseEllipseAngle = -ellipseAngle;

        // 楕円を中心に反転した楕円の角度分だけ回転した点を求める
        Point2 rotatePoint;

        rotatePoint.x_ = std::cos(inverseEllipseAngle) * distance.x_ - std::sin(inverseEllipseAngle) * distance.y_;
        rotatePoint.y_ = std::sin(inverseEllipseAngle) * distance.x_ + std::cos(inverseEllipseAngle) * distance.y_;

        // 楕円の半径をX軸長に合わせ、円に変形した場合の点の座標を求める
        rotatePoint.y_ *= rEllipseSemidiameter.x_ / rEllipseSemidiameter.y_;

        // 楕円の中心から点までの距離の2乗が楕円のX軸長( 円の半径 )の2乗より短い場合は衝突
        if (rotatePoint.GetLengthSquare() <= rEllipseSemidiameter.x_ * rEllipseSemidiameter.x_) return true;

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  線分と線分の衝突判定を行う
     *  @param  始点
     *  @param  終点
     *  @param  もう一つの始点
     *  @param  もう一つの終点
     *  @return 衝突した場合：true
     *  @return 衝突しなかった場合：false
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection2D<T>::s_CheckSegmentAndSegment(const Point2& rBeginPoint,
                                                    const Point2& rEndPoint,
                                                    const Point2& rAnotherBeginPoint,
                                                    const Point2& rAnotherEndPoint,
                                                    Point2* pIntersectionPoint)
    {
        // 始点から終点までのベクトル
        Point2 vector(rEndPoint - rBeginPoint);

        // 始点からもう一つの始点までのベクトル
        Point2 beginFromAnotherBegin(rAnotherBeginPoint - rBeginPoint);

        // 始点からもう一つの終点までのベクトル
        Point2 beginFromAnotherEnd(rAnotherEndPoint - rBeginPoint);

        // もう一つの線分の始点から終点までのベクトル
        Point2 anotherVector(rAnotherEndPoint - rAnotherBeginPoint);

        // もう一つの線分の始点から線分の始点までのベクトル
        Point2 anotherBeginFromBegin(beginFromAnotherBegin.GetInvert());

        // もう一つの線分の始点から線分の終点までのベクトル
        Point2 anotherBeginFromEnd(rEndPoint - rAnotherBeginPoint);

        // もう一つの線分の始点から終点までのベクトルともう一つの線分の始点から始まるベクトル2つの外積を求める
        T anotherCrossAnotherBeginFromBegin = Point2::s_CrossProduct(anotherVector, anotherBeginFromBegin);
        T anotherCrossAnotherBeginFromEnd = Point2::s_CrossProduct(anotherVector, anotherBeginFromEnd);

        // 各ベクトルの外積同士の乗算が両方とも0の場合は衝突
        if ((Point2::s_CrossProduct(vector, beginFromAnotherBegin) * Point2::s_CrossProduct(vector, beginFromAnotherEnd) <= static_cast<T>(0.0))
         && (anotherCrossAnotherBeginFromBegin * anotherCrossAnotherBeginFromEnd <= static_cast<T>(0.0)))
        {
            // 交点が設定されている場合は交点を求める
            if (pIntersectionPoint)
            {
                // 線分の交点までの長さの比率を求める
                T ratio1 = std::abs(anotherCrossAnotherBeginFromBegin);
                T ratio2 = std::abs(anotherCrossAnotherBeginFromEnd);

                // 比率の合計
                T sumRatio = ratio1 + ratio2;

                // 交点を求める
                (*pIntersectionPoint) = rBeginPoint + (vector * (ratio1 / sumRatio));
            }

            return true;
        }

        return false;
    }


    /* 明示的インスタンス化 */
    template class C_Detection2D<float>;
    template class C_Detection2D<double>;
}


