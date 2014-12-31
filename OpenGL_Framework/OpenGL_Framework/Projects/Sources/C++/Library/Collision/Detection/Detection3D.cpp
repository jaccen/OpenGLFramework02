/* ヘッダファイル */
#include "Detection3D.h"
#include "../../Math/Vector/Vector3.h"
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
     *  @brief  点と線分の衝突判定を行う
     *  @param  点
     *  @param  線分の始点
     *  @param  線分の終点
     *  @return 衝突した場合：true
     *  @return 衝突しなかった場合：false
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection3D<T>::s_CheckPointAndSegment(const Point3& rPoint,
                                                  const Point3& rSegmentBeginPoint,
                                                  const Point3& rSegmentEndPoint)
    {
        // 線分の始点から終点までのベクトルを求め、長さを取得
        Point3 segmentVector(rSegmentEndPoint - rSegmentBeginPoint);
        T segmentLength = segmentVector.GetLength();

        // 線分の始点から点までのベクトルを求め、距離を取得
        Point3 vectorFromSegmentBeginToPoint(rPoint - rSegmentBeginPoint);
        T segmentBeginFromPointDistance = vectorFromSegmentBeginToPoint.GetLength();

        // 2つのベクトルの外積
        Point3 crossProduct(Point3::s_CrossProduct(segmentVector, vectorFromSegmentBeginToPoint));

        // 2つのベクトルの外積が0と等しく、
        // 線分の始点から点までの長さが線分の長さより短かった場合は衝突
        if ((std::abs(crossProduct.GetLength()) <= static_cast<T>(Math::s_EPSILON)) && (segmentBeginFromPointDistance <= segmentLength))
        {
            return true;
        }

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  線分と平面の衝突判定を行う
     *  @param  線分の始点
     *  @param  線分の終点
     *  @param  平面上の点
     *  @param  平面の法線ベクトル
     *  @return 衝突した場合：true
     *  @return 衝突しなかった場合：false
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection3D<T>::s_CheckSegmentAndPlane(const Point3& rSegmentBeginPoint,
                                                  const Point3& rSegmentEndPoint,
                                                  const Point3& rPlanePoint,
                                                  const Point3& rPlaneNomal)
    {
        // 平面上の点から線分の始点までのベクトル
        Point3 vectorFromPlanePointToSegmentBegin(rSegmentBeginPoint - rPlanePoint);

        // 平面上の点から線分の終点までのベクトル
        Point3 vectorFromPlanePointToSegmenEnd(rSegmentEndPoint - rPlanePoint);

        // 各ベクトルと平面の法線ベクトルとの内積の乗算が0以下であれば衝突
        if (Point3::s_DotProduct(vectorFromPlanePointToSegmentBegin, rPlaneNomal)
            * Point3::s_DotProduct(vectorFromPlanePointToSegmenEnd, rPlaneNomal) <= static_cast<T>(0.0))
        {
            return true;
        }

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  球と球の衝突判定を行う
     *  @param  中心座標
     *  @param  半径
     *  @param  もう一つの中心座標
     *  @param  もう一つの半径
     *  @return 衝突した場合：true
     *  @return 衝突しなかった場合：false
     *
     ****************************************************************/
    template<typename T>
    bool C_Detection3D<T>::s_CheckSphereAndSphere(const Point3& rCenterPosition,
                                                  T radius,
                                                  const Point3& rAnotherCenterPosition,
                                                  T anotherRadius)
    {
        // 距離
        Point3 distance(rCenterPosition - rAnotherCenterPosition);

        // 半径の合計
        T sumRadius = radius + anotherRadius;

        // 距離の2乗が半径の2乗より短い場合は衝突
        if (distance.GetLengthSquare() <= sumRadius * sumRadius) return true;

        return false;
    }


    /*************************************************************//**
     *
     *  @brief  点から平面までの距離を取得する
     *  @param  点
     *  @param  半径
     *  @param  平面上の点
     *  @param  平面の法線ベクトル
     *  @return 点から平面までの距離
     *
     ****************************************************************/
    template<typename T>
    T C_Detection3D<T>::s_GetLengthFromPointToPlane(const Point3& rPoint,
                                                    const Point3& rPlanePoint,
                                                    const Point3& rPlaneNormal)
    {
        // 平面上の点から点までのベクトル
        Point3 vectorFromPlanePointToPoint(rPoint - rPlanePoint);

        // 平面上の点から点までのベクトルと単位ベクトル化した法線ベクトルの内積の絶対値
        return std::abs(Point3::s_DotProduct(vectorFromPlanePointToPoint, rPlaneNormal.GetNormalize()));
    }


    /* 明示的インスタンス化 */
    template class C_Detection3D<float>;
    template class C_Detection3D<double>;
}
