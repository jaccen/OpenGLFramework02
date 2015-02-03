/* ヘッダファイル */
#include "Vector3.h"
#include "../Quaternion/Quaternion.h"


//-------------------------------------------------------------
///
/// @brief マス
/// @brief 数学関連の名前空間
///
//-------------------------------------------------------------
namespace Math
{

#pragma region 静的メンバ変数の初期化
    
    
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::s_RIGHT_DIRECTION(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
    
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::s_LEFT_DIRECTION(-static_cast<T>(-1), static_cast<T>(0), static_cast<T>(0));
    
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::s_UP_DIRECTION(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
    
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::s_DOWN_DIRECTION(static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0));
    
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::s_FRONT_DIRECTION(static_cast<T>(0), static_cast<T>(0), static_cast<T>(-1));
    
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::s_BACK_DIRECTION(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
    
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::s_ZERO;
    
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::s_ONE(static_cast<T>(1));
    
    
#pragma endregion
    
    
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T>::S_Vector3() : S_Vector3(static_cast<T>(0))
    {
    }
    
    
    /*************************************************************//**
     *
     *  @brief  コンストラクタ( 指定した1つの値で各成分の初期化 )
     *  @param  値
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T>::S_Vector3(T value) : S_Vector3(value, value ,value)
    {
    }
    
    
    /*************************************************************//**
     *
     *  @brief  コンストラクタ( 指定した値で各成分の初期化 )
     *  @param  X成分
     *  @param  Y成分
     *  @param  Z成分
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T>::S_Vector3(T x, T y, T z) : 
    
        // X・Y成分
        xy_(x, y),
    
        // Z成分
        z_(z)
    
    {
    }
    
    
    /*************************************************************//**
     *
     *  @brief  コンストラクタ( 指定した配列で各成分の初期化 )
     *  @param  要素が3つの配列
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T>::S_Vector3(const T a[3]) : S_Vector3(a[0], a[1], a[2])
    {
    }
    
    
    /*************************************************************//**
     *
     *  @brief  コンストラクタ( 2DベクトルとZ成分で初期化初期化 )
     *  @param  X・Y成分
     *  @param  Z成分
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T>::S_Vector3(const S_Vector2<T>& rXY, T z) : 
    
        // X・Y成分
        xy_(rXY),
    
        // Z成分
        z_(z)
    
    {
    }
    
    
    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T>::~S_Vector3()
    {
    }
    
    
    /*************************************************************//**
     *
     *  @brief  ゼロベクトル化する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::Zero()
    {
        x_ = static_cast<T>(0);
        y_ = static_cast<T>(0);
        z_ = static_cast<T>(0);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  各成分を特定の値に変更する
     *  @param  値
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::Fill(T value)
    {
        x_ = value;
        y_ = value;
        z_ = value;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  単位ベクトル化する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::Normalize()
    {
        // 長さを取得
        T length = GetLength();
    
        assert(length != static_cast<T>(0));
    
        // 単位ベクトル化
        x_ /= length;
        y_ /= length;
        z_ /= length;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  ベクトルを反転する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::Invert()
    {
        x_ *= static_cast<T>(-1);
        y_ *= static_cast<T>(-1);
        z_ *= static_cast<T>(-1);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  X軸からベクトルを回転する
     *  @param  角度( ラジアン値 )
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::RotateX(T angle)
    {
        T tempZ = z_;
    
        z_ = tempZ * std::cos(angle) - y_ * std::sin(angle);
        y_ = tempZ * std::sin(angle) + y_ * std::cos(angle);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  Y軸からベクトルを回転する
     *  @param  角度( ラジアン値 )
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::RotateY(T angle)
    {
        T tempX = x_;
    
        x_ = tempX * std::cos(angle) - z_ * std::sin(angle);
        z_ = tempX * std::sin(angle) + z_ * std::cos(angle);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  Z軸からベクトルを回転する
     *  @param  角度( ラジアン値 )
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::RotateZ(T angle)
    {
        T tempX = x_;
    
        x_ = tempX * std::cos(angle) - y_ * std::sin(angle);
        y_ = tempX * std::sin(angle) + y_ * std::cos(angle);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  任意軸からベクトルを回転する
     *  @param  軸
     *  @param  角度( ラジアン値 )
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::RotateAxis(const S_Vector3<T>& rAxis, T angle)
    {
        // 回転するベクトル
        S_Quaternion<T> rotationVector(static_cast<T>(0), *this);
    
        // 回転クォータニオンを作成
        S_Quaternion<T> rotationQuaternion = S_Quaternion<T>::s_CreateRotationAxis(rAxis, angle);
        S_Quaternion<T> inverseRotationQuaternion = S_Quaternion<T>::s_CreateRotationAxis(rAxis.GetInvert(), angle);
    
        // ベクトルを回転し、自身に代入
        rotationVector =  inverseRotationQuaternion * rotationVector * rotationQuaternion;
        (*this) = rotationVector.xyz_;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  長さでベクトルをクランプする
     *  @param  最小の長さ
     *  @param  最大の長さ
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Vector3<T>::ClampLength(T minLength, T maxLength)
    {
        // 長さを取得し、その長さをクランプ
        T length = GetLength();
        Clamp(length, minLength, maxLength);
    
        // 単位ベクトル化して、長さ分スケール
        Normalize();
        (*this) = (*this) * length;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  長さを取得する
     *  @param  なし
     *  @return 長さ
     *
     ****************************************************************/
    template<typename T>
    T S_Vector3<T>::GetLength() const
    {
        return SquareRoot(GetLengthSquare());
    }
    
    
    /*************************************************************//**
     *
     *  @brief  長さの2乗を取得する
     *  @param  なし
     *  @return 長さの2乗
     *
     ****************************************************************/
    template<typename T>
    T S_Vector3<T>::GetLengthSquare() const
    {
        return Square(x_) + Square(y_) + Square(z_);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  単位ベクトルを取得する
     *  @param  なし
     *  @return 単位ベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::GetNormalize() const
    {
        S_Vector3 normalizationVector(*this);
        normalizationVector.Normalize();
    
        return normalizationVector;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  反転したベクトルを取得する
     *  @param  なし
     *  @return 反転したベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::GetInvert() const
    {
        return S_Vector3(-x_, -y_, -z_);
    }

    
    /*************************************************************//**
     *
     *  @brief  X軸から回転したベクトルを取得する
     *  @param  角度( ラジアン値 )
     *  @return 回転したベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::GetRotateX(T angle) const
    {
        S_Vector3 rotationVector(*this);
        rotationVector.RotateX(angle);
    
        return rotationVector;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  Y軸から回転したベクトルを取得する
     *  @param  角度( ラジアン値 )
     *  @return 回転したベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::GetRotateY(T angle) const
    {
        S_Vector3 rotationVector(*this);
        rotationVector.RotateY(angle);
    
        return rotationVector;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  Z軸から回転したベクトルを取得する
     *  @param  角度( ラジアン値 )
     *  @return 回転したベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::GetRotateZ(T angle) const
    {
        S_Vector3 rotationVector(*this);
        rotationVector.RotateZ(angle);
    
        return rotationVector;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  任意軸から回転したベクトルを取得する
     *  @param  軸
     *  @param  角度( ラジアン値 )
     *  @return 回転したベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::GetRotateAxis(const S_Vector3<T>& rAxis, T angle) const
    {
        S_Vector3 rotationPosition(*this);
        rotationPosition.RotateAxis(rAxis, angle);
    
        return rotationPosition;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  長さでクランプしたベクトルを取得する
     *  @param  最小の長さ
     *  @param  最大の長さ
     *  @return クランプしたベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::GetClampLength(T minLength, T maxLength) const
    {
        S_Vector3 clampVector = (*this);
        clampVector.ClampLength(minLength, maxLength);
    
        return clampVector;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  ベクトルを文字列に変換して取得する
     *  @param  なし
     *  @return 文字列に変換したベクトル
     *
     ****************************************************************/
    template<typename T>
    std::string S_Vector3<T>::GetConvertToString() const
    {
        return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ", " + std::to_string(z_) + ")";
    }
    
    
    /*************************************************************//**
     *
     *  @brief  内積を求める
     *  @param  一つ目のベクトル
     *  @param  二つ目のベクトル
     *  @return 内積
     *
     ****************************************************************/
    template<typename T>
    T S_Vector3<T>::s_DotProduct(const S_Vector3<T>& rLhs, const S_Vector3<T>& rRhs)
    {
        return (rLhs.x_ * rRhs.x_) + (rLhs.y_ * rRhs.y_) + (rLhs.z_ * rRhs.z_);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  外積を求める
     *  @param  一つ目のベクトル
     *  @param  二つ目のベクトル
     *  @return 外積
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_CrossProduct(const S_Vector3<T>& rLhs, const S_Vector3<T>& rRhs)
    {
        S_Vector3 crossVector;
    
        crossVector.x_ = (rLhs.y_ * rRhs.z_) - (rLhs.z_ * rRhs.y_);
        crossVector.y_ = (rLhs.z_ * rRhs.x_) - (rLhs.x_ * rRhs.z_);
        crossVector.z_ = (rLhs.x_ * rRhs.y_) - (rLhs.y_ * rRhs.x_);
        
        return crossVector;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  スカラー三重積を求める
     *  @param  一つ目のベクトル
     *  @param  二つ目のベクトル
     *  @param  三つ目のベクトル
     *  @return スカラー三重積
     *
     ****************************************************************/
    template<typename T>
    T S_Vector3<T>::s_ScalarTripleProduct(const S_Vector3<T>& rA,
                                          const S_Vector3<T>& rB,
                                          const S_Vector3<T>& rC)
    {
        return s_DotProduct(rA, s_CrossProduct(rB, rC));
    }
    
    
    /*************************************************************//**
     *
     *  @brief  ベクトル三重積を求める
     *  @param  一つ目のベクトル
     *  @param  二つ目のベクトル
     *  @param  三つ目のベクトル
     *  @return ベクトル三重積
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_VectorTripleProduct(const S_Vector3<T>& rA,
                                                     const S_Vector3<T>& rB,
                                                     const S_Vector3<T>& rC)
    {
        return s_CrossProduct(rA, s_CrossProduct(rB, rC));
    }
    
    
    /*************************************************************//**
     *
     *  @brief  線形補間を行う
     *  @param  始点
     *  @param  終点
     *  @param  補間係数( 0 ～ 1 )
     *  @return 二つの点を線形補間した点
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_Lerp(const S_Vector3<T>& rStartPoint,
                                      const S_Vector3<T>& rEndPoint,
                                      T coefficient)
    {
        S_Vector3 lerpPoint;
    
        lerpPoint.x_ = (rEndPoint.x_ - rStartPoint.x_) * coefficient + rStartPoint.x_;
        lerpPoint.y_ = (rEndPoint.y_ - rStartPoint.y_) * coefficient + rStartPoint.y_;
        lerpPoint.z_ = (rEndPoint.z_ - rStartPoint.z_) * coefficient + rStartPoint.z_;
    
        return lerpPoint;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  球面線形補間を行う
     *  @param  始点
     *  @param  終点
     *  @param  補間係数( 0 ～ 1 )
     *  @return 二つの点を球面線形補間した点
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_Slerp(const S_Vector3<T>& rStartPoint,
                                       const S_Vector3<T>& rEndPoint,
                                       T coefficient)
    {
        // 角度とサインを求める
        T angle = s_AngleBetweenVectors(rStartPoint, rEndPoint);
        T sine = std::sin(angle);
    
        // 各補間係数を求める
        T startCoefficient = std::sin(angle * (static_cast<T>(1) - coefficient));
        T endCoefficient = std::sin(angle * coefficient);
    
        // 球面線形補間した点を求める
        S_Vector3 slerpPoint = rStartPoint * startCoefficient + rEndPoint * endCoefficient;
    
        return slerpPoint;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  エルミート補間を行う
     *  @param  始点
     *  @param  始点の接線
     *  @param  終点
     *  @param  終点の接線
     *  @param  補間係数( 0 ～ 1 )
     *  @return 二つの点をエルミート補間した点
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_Hermite(const S_Vector3<T>& rStartPoint,
                                         const S_Vector3<T>& rStartTangent,
                                         const S_Vector3<T>& rEndPoint,
                                         const S_Vector3<T>& rEndTangent,
                                         T coefficient)
    {
        // 各点と各接点の係数を求める
        T u1 = coefficient;
        T u2 = Square(coefficient);
        T u3 = u2 * coefficient;
    
        T p0 = (static_cast<T>(2) * u3) - (static_cast<T>(3) * u2) + static_cast<T>(1);
        T t0 = u3 - (static_cast<T>(2) * u2) + u1;
        T p1 = (static_cast<T>(-2) * u3) + static_cast<T>(3) * u2;
        T t1 = u3 - u2;
    
        // エルミート補間する
        S_Vector3 hermitePoint;
    
        hermitePoint.x_ = rStartPoint.x_ * p0 + rStartTangent.x_ * t0 + rEndPoint.x_ * p1 + rEndTangent.x_ * t1;
        hermitePoint.y_ = rStartPoint.y_ * p0 + rStartTangent.y_ * t0 + rEndPoint.y_ * p1 + rEndTangent.y_ * t1;
        hermitePoint.z_ = rStartPoint.z_ * p0 + rStartTangent.z_ * t0 + rEndPoint.z_ * p1 + rEndTangent.z_ * t1;
    
        return hermitePoint;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  Catmull-Romスプライン補間を行う
     *  @param  始点の前の点
     *  @param  始点
     *  @param  終点
     *  @param  次の終点
     *  @param  補間係数( 0 ～ 1 )
     *  @return 二つの点をCatmull-Romスプライン補間した点
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_CatmullRomSpline(const S_Vector3<T>& rPreviousStartPoint,
                                                  const S_Vector3<T>& rStartPoint,
                                                  const S_Vector3<T>& rEndPoint,
                                                  const S_Vector3<T>& rNextEndPoint,
                                                  T coefficient)
    {
        // 両サイドの点から接線を求める
        S_Vector3 startTangent = (rEndPoint - rPreviousStartPoint) * static_cast<T>(0.5);
        S_Vector3 endTangent = (rNextEndPoint - rStartPoint) * static_cast<T>(0.5);
    
        // 接線を利用して、エルミート補間
        S_Vector3 catmullRomSplinePoint = s_Hermite(rStartPoint, startTangent, rEndPoint, endTangent, coefficient);
    
        return catmullRomSplinePoint;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  ベジェ補間を行う
     *  @param  始点
     *  @param  終点
     *  @param  制御点1
     *  @param  制御点2
     *  @param  補間係数( 0 ～ 1 )
     *  @return 二つの点をベジェ―補間した点
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_Bezier(const S_Vector3<T>& rStartPoint,
                                        const S_Vector3<T>& rEndPoint,
                                        const S_Vector3<T>& rControlPoint1,
                                        const S_Vector3<T>& rControlPoint2,
                                        T coefficient)
    {
        // 各点の係数を求める
        T oneMinusCoefficient = static_cast<T>(1) - coefficient;
        
        T p0 = Cubic(oneMinusCoefficient);
        T p1 = Cubic(coefficient);
        T c0 = static_cast<T>(3) * coefficient * Square(oneMinusCoefficient);
        T c1 = static_cast<T>(3) * Square(coefficient) * oneMinusCoefficient;
    
        // ベジェ補間する
        S_Vector3 bezierPoint;
    
        bezierPoint.x_ = rStartPoint.x_ * p0 + rEndPoint.x_ * p1 + rControlPoint1.x_ * c0 + rControlPoint2.x_ * c1;
        bezierPoint.y_ = rStartPoint.y_ * p0 + rEndPoint.y_ * p1 + rControlPoint1.y_ * c0 + rControlPoint2.y_ * c1;
        bezierPoint.z_ = rStartPoint.z_ * p0 + rEndPoint.z_ * p1 + rControlPoint1.z_ * c0 + rControlPoint2.z_ * c1;
    
        return bezierPoint;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  迎撃ポイント( 交差位置 )を求める
     *  @param  座標
     *  @param  速度
     *  @param  もう一つの座標
     *  @param  もう一つの速度
     *  @return 迎撃ポイント
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_InterceptPoint(const S_Vector3<T>& rPosition,
                                                const S_Vector3<T>& rVelocity,
                                                const S_Vector3<T>& rAnotherPosition,
                                                const S_Vector3<T>& rAnotherVelocity)
    {
        // 距離と速度の差を求める
        S_Vector3 distance = rPosition - rAnotherPosition;
        S_Vector3 velocityDifference = rVelocity - rAnotherVelocity;
    
        // 距離から速度を割り、時間をだす
        T time = distance.GetLength() / velocityDifference.GetLength();
    
        // 迎撃ポイントを求める
        S_Vector3 interceptPoint = rPosition + (rVelocity * time);
    
        return interceptPoint;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  ベクトル間の角度を求める
     *  @param  一つ目のベクトル
     *  @param  二つ目のベクトル
     *  @return 角度( ラジアン値 )
     *
     ****************************************************************/
    template<typename T>
    T S_Vector3<T>::s_AngleBetweenVectors(const S_Vector3<T>& rLhs, const S_Vector3<T>& rRhs)
    {
        T cosine = s_DotProduct(rLhs.GetNormalize(), rRhs.GetNormalize());
        T angle = std::acos(cosine);
        
        return angle;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  ベクトル間の距離を求める
     *  @param  一つ目のベクトル
     *  @param  二つ目のベクトル
     *  @return 距離
     *
     ****************************************************************/
    template<typename T>
    T S_Vector3<T>::s_DistanceBetweenVectors(const S_Vector3<T>& rLhs, const S_Vector3<T>& rRhs)
    {
        S_Vector3 distance = rLhs - rRhs;
    
        return distance.GetLength();
    }
    
    
    /*************************************************************//**
     *
     *  @brief  各成分の最小値を成分にしたベクトルを取得する
     *  @param  一つ目のベクトル
     *  @param  二つ目のベクトル
     *  @return 最小値を成分にしたベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_Minimize(const S_Vector3<T>& rLhs, const S_Vector3<T>& rRhs)
    {
        S_Vector3 minimizationVector;
    
        minimizationVector.x_ = (rLhs.x_ < rRhs.x_) ? rLhs.x_ : rRhs.x_;
        minimizationVector.y_ = (rLhs.y_ < rRhs.y_) ? rLhs.y_ : rRhs.y_;
        minimizationVector.z_ = (rLhs.z_ < rRhs.z_) ? rLhs.z_ : rRhs.z_;
    
        return minimizationVector;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  各成分の最大値を成分にしたベクトルを取得する
     *  @param  一つ目のベクトル
     *  @param  二つ目のベクトル
     *  @return 最大値を成分にしたベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_Maximize(const S_Vector3<T>& rLhs, const S_Vector3<T>& rRhs)
    {
        S_Vector3 maximizationVector;
    
        maximizationVector.x_ = (rLhs.x_ > rRhs.x_) ? rLhs.x_ : rRhs.x_;
        maximizationVector.y_ = (rLhs.y_ > rRhs.y_) ? rLhs.y_ : rRhs.y_;
        maximizationVector.z_ = (rLhs.z_ > rRhs.z_) ? rLhs.z_ : rRhs.z_;
    
        return maximizationVector;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  2点間からの距離分だけ進んだ点を取得する
     *  @param  始点
     *  @param  終点
     *  @param  距離
     *  @return 始点から距離分だけ進んだ点
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_MoveTowards(const S_Vector3<T>& rStartPoint, 
                                             const S_Vector3<T>& rEndPoint,
                                             T distance)
    {
        if (distance < static_cast<T>(0)) return rStartPoint;
    
        S_Vector3 difference = rStartPoint - rEndPoint;
        S_Vector3 movement = difference.GetNormalize() * distance;
    
        if (movement.GetLengthSquare() >= difference.GetLengthSquare()) return rEndPoint;
    
        return rStartPoint + movement;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  投影ベクトルを取得する
     *  @param  ベクトル
     *  @param  法線ベクトル
     *  @return 投影ベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_Project(const S_Vector3<T>& rVector, 
                                         const S_Vector3<T>& rNormal)
    {
        // 単位ベクトル化した法線と投影の長さを取得
        S_Vector3 normalizationNormal = rNormal.GetNormalize();
        T projectLength = s_DotProduct(rVector, normalizationNormal);
    
        return normalizationNormal * projectLength;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  反射ベクトルを取得する
     *  @param  ベクトル
     *  @param  法線ベクトル
     *  @return 反射ベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_Reflect(const S_Vector3<T>& rVector, 
                                         const S_Vector3<T>& rNormal)
    {
        // 単位ベクトル化した法線を取得
        S_Vector3 normalizationNormal = rNormal.GetNormalize();
    
        // 反射ベクトルを求める
        S_Vector3 reflectionVector = rVector - static_cast<T>(2) * s_DotProduct(rVector, normalizationNormal) * normalizationNormal;
    
        return reflectionVector;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  屈折ベクトルを取得する
     *  @param  入射ベクトル
     *  @param  法線ベクトル
     *  @param  屈折率
     *  @return 屈折ベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_Refract(const S_Vector3<T>& rIncidentVector, 
                                         const S_Vector3<T>& rNormal,
                                         T refractiveIndex)
    {
        // 各ベクトルを単位ベクトル化
        S_Vector3 normalizationIncidentVector = rIncidentVector.GetNormalize();
        S_Vector3 normalizationNormal = rNormal.GetNormalize();
    
        // 入射ベクトルと法線ベクトルの内積を求める
        T dotProduct = s_DotProduct(normalizationIncidentVector, normalizationNormal);
    
        // 屈折の角度
        T refractAngle = static_cast<T>(1) - refractiveIndex * refractiveIndex * (static_cast<T>(1) - dotProduct * dotProduct);
    
        // 屈折ベクトルを求める
        S_Vector3 refractVector;
        if (refractAngle < static_cast<T>(0)) return refractVector;
    
        refractVector = refractiveIndex * normalizationIncidentVector 
                      - (refractiveIndex * dotProduct * SquareRoot(refractAngle)) * normalizationNormal;
    
        return refractVector;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  滑りしたベクトルを取得する
     *  @param  ベクトル
     *  @param  法線ベクトル
     *  @return 滑りしたベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_Slide(const S_Vector3<T>& rVector, 
                                       const S_Vector3<T>& rNormal)
    {
        // 単位ベクトル化した法線を取得
        S_Vector3 normalizationNormal = rNormal.GetNormalize();
    
        // 滑りベクトルを求める
        S_Vector3 sliderVector = rVector - s_DotProduct(rVector, normalizationNormal) * normalizationNormal;
    
        return sliderVector;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  法線ベクトルを作成
     *  @param  1つ目の座標
     *  @param  2つ目の座標
     *  @param  3つ目の座標
     *  @return 法線ベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_CreateNormal(const S_Vector3<T>& rPositionA, 
                                              const S_Vector3<T>& rPositionB,
                                              const S_Vector3<T>& rPositionC)
    {
        // 各座標からベクトルを求める
        S_Vector3 vectorAB = rPositionB - rPositionA;
        S_Vector3 vectorBC = rPositionC - rPositionB;
    
        // 法線ベクトルを求める
        S_Vector3 normal = s_CrossProduct(vectorAB, vectorBC);
        normal.Normalize();
    
        return normal;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  接線ベクトルと従法線を作成
     *  @param  1つ目の座標
     *  @param  1つ目のテクスチャ座標
     *  @param  2つ目の座標
     *  @param  2つ目のテクスチャ座標
     *  @param  3つ目の座標
     *  @param  3つ目のテクスチャ座標
     *  @return 接線ベクトルと従法線ベクトル
     *
     ****************************************************************/
    template<typename T>
    std::tuple<S_Vector3<T>, S_Vector3<T>> S_Vector3<T>::s_CreateTangentAndBinormal(const S_Vector3<T>& rPositionA,   
                                                                                    const S_Vector2<T>& rTextureCoordA,
                                                                                    const S_Vector3<T>& rPositionB,
                                                                                    const S_Vector2<T>& rTextureCoordB,
                                                                                    const S_Vector3<T>& rPositionC,
                                                                                    const S_Vector2<T>& rTextureCoordC)
    {
        // 頂点Aに対する相対的なベクトルを求める
        S_Vector3 vectorPositionAB = rPositionB - rPositionA;
        S_Vector3 vectorPositionAC = rPositionC - rPositionA;
    
        S_Vector2<T> vectorTextureCoordAB = rTextureCoordB - rTextureCoordA;
        S_Vector2<T> vectorTextureCoordAC = rTextureCoordC - rTextureCoordA;
    
        // 接線ベクトルと従法線ベクトルを求める
        T denominator = vectorTextureCoordAB.x_ * vectorTextureCoordAC.y_ - vectorTextureCoordAB.y_ * vectorTextureCoordAC.x_;
        assert(denominator != static_cast<T>(0));
        
        T partOfInverseMatrix = static_cast<T>(1) / denominator;
    
        S_Vector3 tangent((vectorTextureCoordAC.y_ * vectorPositionAB.x_ - vectorTextureCoordAB.y_ * vectorPositionAC.x_) * partOfInverseMatrix,
                          (vectorTextureCoordAC.y_ * vectorPositionAB.y_ - vectorTextureCoordAB.y_ * vectorPositionAC.y_) * partOfInverseMatrix,
                          (vectorTextureCoordAC.y_ * vectorPositionAB.z_ - vectorTextureCoordAB.y_ * vectorPositionAC.z_) * partOfInverseMatrix);
    
        S_Vector3 binormal((vectorTextureCoordAB.x_ * vectorPositionAC.x_ - vectorTextureCoordAC.x_ * vectorPositionAB.x_) * partOfInverseMatrix,
                           (vectorTextureCoordAB.x_ * vectorPositionAC.y_ - vectorTextureCoordAC.x_ * vectorPositionAB.y_) * partOfInverseMatrix,
                           (vectorTextureCoordAB.x_ * vectorPositionAC.z_ - vectorTextureCoordAC.x_ * vectorPositionAB.z_) * partOfInverseMatrix);
    
        return std::make_tuple(tangent, binormal);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  3点から重心を取得する
     *  @param  1つ目の点
     *  @param  2つ目の点
     *  @param  3つ目の点
     *  @return 重心
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Vector3<T>::s_CenterOfGravityWith3Points(const S_Vector3<T>& rA,
                                                            const S_Vector3<T>& rB,
                                                            const S_Vector3<T>& rC)
    {
        S_Vector3 centerOfGravity(rA + rB + rC);
        centerOfGravity /= static_cast<T>(3);
    
        return centerOfGravity;
    }
    
    
    #pragma region S_Vector3型との演算子のオーバーロード
    
    
    /*************************************************************//**
     *
     *  @brief  もう一つのベクトルを加算したベクトルを求める
     *  @param  もう一つのベクトル
     *  @return 加算したベクトル
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::operator+(const S_Vector3<T>& rAnother) const
    {
        return S_Vector3(x_ + rAnother.x_, 
                         y_ + rAnother.y_,
                         z_ + rAnother.z_);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  もう一つのベクトルを減算したベクトルを求める
     *  @param  もう一つのベクトル
     *  @return 減算したベクトル
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::operator-(const S_Vector3<T>& rAnother) const
    {
        return S_Vector3(x_ - rAnother.x_,
                         y_ - rAnother.y_,
                         z_ - rAnother.z_);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  もう一つのベクトルを乗算したベクトルを求める
     *  @param  もう一つのベクトル
     *  @return 乗算したベクトル
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::operator*(const S_Vector3<T>& rAnother) const
    {
        return S_Vector3(x_ * rAnother.x_,
                         y_ * rAnother.y_,
                         z_ * rAnother.z_);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  もう一つのベクトルを除算したベクトルを求める
     *  @param  もう一つのベクトル
     *  @return 除算したベクトル
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::operator/(const S_Vector3<T>& rAnother) const
    {
        assert(rAnother.x_ != static_cast<T>(0));
        assert(rAnother.y_ != static_cast<T>(0));
        assert(rAnother.z_ != static_cast<T>(0));
    
        return S_Vector3(x_ / rAnother.x_,
                         y_ / rAnother.y_,
                         z_ / rAnother.z_);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  もう一つのベクトルを加算する
     *  @param  もう一つのベクトル
     *  @return 加算後のベクトル( 自分自身 )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T>& S_Vector3<T>::operator+=(const S_Vector3<T>& rAnother)
    {
        x_ += rAnother.x_;
        y_ += rAnother.y_;
        z_ += rAnother.z_;
    
        return (*this);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  もう一つのベクトルで減算する
     *  @param  もう一つのベクトル
     *  @return 減算後のベクトル( 自分自身 )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T>& S_Vector3<T>::operator-=(const S_Vector3<T>& rAnother)
    {
        x_ -= rAnother.x_;
        y_ -= rAnother.y_;
        z_ -= rAnother.z_;
    
        return (*this);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  もう一つのベクトルで乗算する
     *  @param  もう一つのベクトル
     *  @return 乗算後のベクトル( 自分自身 )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T>& S_Vector3<T>::operator*=(const S_Vector3<T>& rAnother)
    {
        x_ *= rAnother.x_;
        y_ *= rAnother.y_;
        z_ *= rAnother.z_;
    
        return (*this);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  もう一つのベクトルで除算する
     *  @param  もう一つのベクトル
     *  @return 除算後のベクトル( 自分自身 )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T>& S_Vector3<T>::operator/=(const S_Vector3<T>& rAnother)
    {
        assert(rAnother.x_ != static_cast<T>(0));
        assert(rAnother.y_ != static_cast<T>(0));
        assert(rAnother.z_ != static_cast<T>(0));
    
        x_ /= rAnother.x_;
        y_ /= rAnother.y_;
        z_ /= rAnother.z_;
    
        return (*this);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  もう一つのベクトルと比較する
     *  @param  もう一つのベクトル
     *  @return 同じベクトルの場合：true
     *  @return 違うベクトルの場合：false
     *
     ****************************************************************/
    template<typename T>
    bool S_Vector3<T>::operator==(const S_Vector3<T>& rAnother) const
    {
        return std::abs(x_ - rAnother.x_) < static_cast<T>(s_EPSILON)
            && std::abs(y_ - rAnother.y_) < static_cast<T>(s_EPSILON)
            && std::abs(z_ - rAnother.z_) < static_cast<T>(s_EPSILON);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  もう一つのベクトルと比較する
     *  @param  もう一つのベクトル
     *  @return 違うベクトルの場合：true
     *  @return 同じベクトルの場合：false
     *
     ****************************************************************/
    template<typename T>
    bool S_Vector3<T>::operator!=(const S_Vector3<T>& rAnother) const
    {
        return std::abs(x_ - rAnother.x_) > static_cast<T>(s_EPSILON)
            || std::abs(y_ - rAnother.y_) > static_cast<T>(s_EPSILON)
            || std::abs(z_ - rAnother.z_) > static_cast<T>(s_EPSILON);
    }
    
    
    #pragma endregion
    
    
    #pragma region T型との演算子のオーバーロード
    
    
    /*************************************************************//**
     *
     *  @brief  T型の値を各成分に乗算したベクトルを求める
     *  @param  T型の値
     *  @return 乗算したベクトル
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::operator*(T value) const
    {
        return S_Vector3(x_ * value, y_ * value, z_ * value);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  T型の値で各成分を除算したベクトルを求める
     *  @param  T型の値
     *  @return 除算したベクトル
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T> S_Vector3<T>::operator/(T value) const
    {
        assert(value != static_cast<T>(0));
    
        return S_Vector3(x_ / value, y_ / value, z_ / value);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  T型の値を各成分に乗算する
     *  @param  T型の値
     *  @return 乗算後のベクトル( 自分自身 )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T>& S_Vector3<T>::operator*=(T value)
    {
        x_ *= value;
        y_ *= value;
        z_ *= value;
    
        return (*this);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  T型の値で各成分を除算する
     *  @param  T型の値
     *  @return 除算後のベクトル( 自分自身 )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T>& S_Vector3<T>::operator/=(T value)
    {
        assert(value != static_cast<T>(0));
    
        x_ /= value;
        y_ /= value;
        z_ /= value;
    
        return (*this);
    }
    
    
    #pragma endregion
    
    
    #pragma region キャスト演算子のオーバーロード
    
    
    /*************************************************************//**
     *
     *  @brief  S_Vector2型へキャストする
     *  @param  なし
     *  @return 2Dベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T>::operator S_Vector2<T>() const
    {
        return xy_;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  string型へキャストする
     *  @param  なし
     *  @return 文字列に変換したベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T>::operator std::string() const
    {
        return GetConvertToString();
    }
    
    
    #pragma endregion
    
    
    /* 明示的インスタンス化 */
    template struct S_Vector3<float>;
    template struct S_Vector3<double>;

}