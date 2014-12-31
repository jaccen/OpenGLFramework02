/* 二重インクルード防止 */
#pragma once


/* 前方宣言 */
namespace Math
{
    template<typename T>
    struct S_Vector3;
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
    using Point3 = Math::S_Vector3<T>;           // Point3型


    //-------------------------------------------------------------
    //!
    //! @brief ディテクション2D
    //! @brief 3Dの衝突判定の関数をまとめたユーティリティクラス
    //!
    //-------------------------------------------------------------
    template<typename T>
    class C_Detection3D
    {
    public:
        /* 別名 */
        using Point3 = Point3<T>;               // Point3型を省略


        /* 点と線分の衝突判定 */
        static bool s_CheckPointAndSegment(const Point3& rPoint,
                                           const Point3& rSegmentBeginPoint,
                                           const Point3& rSegmentEndPoint);

        /* 線分と平面の衝突判定 */
        static bool s_CheckSegmentAndPlane(const Point3& rSegmentBeginPoint,
                                           const Point3& rSegmentEndPoint,
                                           const Point3& rPlanePoint,
                                           const Point3& rPlaneNomal);

        /* 球と球の衝突判定 */
        static bool s_CheckSphereAndSphere(const Point3& rCenterPosition,
                                           T radius,
                                           const Point3& rAnotherCenterPosition,
                                           T anotherRadius);

        /* 点から平面までの距離を取得 */
        static T s_GetLengthFromPointToPlane(const Point3& rPoint,
                                             const Point3& rPlanePoint,
                                             const Point3& rPlaneNormal);
    };
}
