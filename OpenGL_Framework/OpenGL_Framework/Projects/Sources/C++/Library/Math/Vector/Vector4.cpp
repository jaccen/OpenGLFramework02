/* ヘッダファイル */
#include "Vector4.h"
#include "../Define/MathDefine.h"


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
    const S_Vector4<T> S_Vector4<T>::s_ZERO;

    template<typename T>
    const S_Vector4<T> S_Vector4<T>::s_ONE(static_cast<T>(1));


#pragma endregion


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::S_Vector4() : S_Vector4(static_cast<T>(0))
    {
    }


    /*************************************************************//**
     *
     *  @brief  コンストラクタ( 指定した1つの値で各成分を初期化 )
     *  @param  値
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::S_Vector4(T value) : S_Vector4(value, value, value, value)
    {
    }


    /*************************************************************//**
     *
     *  @brief  コンストラクタ( 指定した値で各成分を初期化 )
     *  @param  X成分
     *  @param  Y成分
     *  @param  Z成分
     *  @param  W成分
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::S_Vector4(T x, T y, T z, T w) :

        // X・Y・Z成分
        xyz_(x, y, z),

        // W成分
        w_(w)

    {
    }


    /*************************************************************//**
     *
     *  @brief  コンストラクタ( 指定した配列で各成分を初期化 )
     *  @param  要素が4つの配列
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::S_Vector4(const T a[4]) : S_Vector4(a[0], a[1], a[2], a[3])
    {
    }


    /*************************************************************//**
     *
     *  @brief  コンストラクタ( 指定した3Dベクトルと値で各成分を初期化 )
     *  @param  X・Y成分
     *  @param  Z成分
     *  @param  W成分
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::S_Vector4(const S_Vector2<T>& rXY, T z, T w) :

        // X・Y・Z成分
        xyz_(rXY, z),

        // W成分
        w_(w)

    {
    }


    /*************************************************************//**
     *
     *  @brief  コンストラクタ( 指定した3Dベクトルと値で各成分を初期化 )
     *  @param  X・Y・Z成分
     *  @param  W成分
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::S_Vector4(const S_Vector3<T>& rXYZ, T w) :

        // X・Y・Z成分
        xyz_(rXYZ),

        // W成分
        w_(w)

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::~S_Vector4()
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
    void S_Vector4<T>::Zero()
    {
        x_ = static_cast<T>(0);
        y_ = static_cast<T>(0);
        z_ = static_cast<T>(0);
        w_ = static_cast<T>(0);
    }


    /*************************************************************//**
     *
     *  @brief  各成分を特定の値に変更する
     *  @param  値
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Vector4<T>::Fill(T value)
    {
        x_ = value;
        y_ = value;
        z_ = value;
        w_ = value;
    }


    /*************************************************************//**
     *
     *  @brief  単位ベクトル化する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Vector4<T>::Normalize()
    {
        // 長さを取得
        T length = GetLength();

        assert(length != static_cast<T>(0));

        // 単位ベクトル化
        x_ /= length;
        y_ /= length;
        z_ /= length;
        w_ /= length;
    }


    /*************************************************************//**
     *
     *  @brief  ベクトルを反転する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Vector4<T>::Invert()
    {
        x_ *= static_cast<T>(-1);
        y_ *= static_cast<T>(-1);
        z_ *= static_cast<T>(-1);
        w_ *= static_cast<T>(-1);
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
    void S_Vector4<T>::ClampLength(T minLength, T maxLength)
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
    T S_Vector4<T>::GetLength() const
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
    T S_Vector4<T>::GetLengthSquare() const
    {
        return Square(x_) + Square(y_) + Square(z_) + Square(w_);
    }


    /*************************************************************//**
     *
     *  @brief  単位ベクトルを取得する
     *  @param  なし
     *  @return 単位ベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T> S_Vector4<T>::GetNormalize() const
    {
        S_Vector4 normalizationVector(*this);
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
    S_Vector4<T> S_Vector4<T>::GetInvert() const
    {
        return S_Vector4(-x_, -y_, -z_, -w_);
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
    S_Vector4<T> S_Vector4<T>::GetClampLength(T minLength, T maxLength) const
    {
        S_Vector4 clampVector = (*this);
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
    std::string S_Vector4<T>::GetConvertToString() const
    {
        return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ", " + std::to_string(z_) + ", " + std::to_string(w_) + ")";
    }


    /*************************************************************//**
     *
     *  @brief  内積を求める
     *  @param  ベクトル
     *  @param  もう一つのベクトル
     *  @return 内積
     *
     ****************************************************************/
    template<typename T>
    T S_Vector4<T>::s_DotProduct(const S_Vector4<T>& rVector, const S_Vector4<T>& rAnotherVector)
    {
        return (rVector.x_ * rAnotherVector.x_)
             + (rVector.y_ * rAnotherVector.y_)
             + (rVector.z_ * rAnotherVector.z_)
             + (rVector.w_ * rAnotherVector.w_);
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
    S_Vector4<T> S_Vector4<T>::s_Lerp(const S_Vector4<T>& rStartPoint,
                                      const S_Vector4<T>& rEndPoint,
                                      T coefficient)
    {
        S_Vector4 lerpPoint;

        lerpPoint.x_ = (rEndPoint.x_ - rStartPoint.x_) * coefficient + rStartPoint.x_;
        lerpPoint.y_ = (rEndPoint.y_ - rStartPoint.y_) * coefficient + rStartPoint.y_;
        lerpPoint.z_ = (rEndPoint.z_ - rStartPoint.z_) * coefficient + rStartPoint.z_;
        lerpPoint.w_ = (rEndPoint.w_ - rStartPoint.w_) * coefficient + rStartPoint.w_;

        return lerpPoint;
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
    S_Vector4<T> S_Vector4<T>::s_Minimize(const S_Vector4<T>& rLhs, const S_Vector4<T>& rRhs)
    {
        S_Vector4 minimizationVector;

        minimizationVector.x_ = (rLhs.x_ < rRhs.x_) ? rLhs.x_ : rRhs.x_;
        minimizationVector.y_ = (rLhs.y_ < rRhs.y_) ? rLhs.y_ : rRhs.y_;
        minimizationVector.z_ = (rLhs.z_ < rRhs.z_) ? rLhs.z_ : rRhs.z_;
        minimizationVector.w_ = (rLhs.w_ < rRhs.w_) ? rLhs.w_ : rRhs.w_;

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
    S_Vector4<T> S_Vector4<T>::s_Maximize(const S_Vector4<T>& rLhs, const S_Vector4<T>& rRhs)
    {
        S_Vector4 maximizationVector;

        maximizationVector.x_ = (rLhs.x_ > rRhs.x_) ? rLhs.x_ : rRhs.x_;
        maximizationVector.y_ = (rLhs.y_ > rRhs.y_) ? rLhs.y_ : rRhs.y_;
        maximizationVector.z_ = (rLhs.z_ > rRhs.z_) ? rLhs.z_ : rRhs.z_;
        maximizationVector.w_ = (rLhs.w_ > rRhs.w_) ? rLhs.w_ : rRhs.w_;

        return maximizationVector;
    }


#pragma region S_Vector4型との演算子のオーバーロード


    /*************************************************************//**
     *
     *  @brief  もう一つのベクトルを加算したベクトルを求める
     *  @param  もう一つのベクトル
     *  @return 加算したベクトル
     *
     ****************************************************************/
    template<typename T>
    const S_Vector4<T> S_Vector4<T>::operator+(const S_Vector4<T>& rAnother) const
    {
        return S_Vector4(x_ + rAnother.x_,
                         y_ + rAnother.y_,
                         z_ + rAnother.z_,
                         w_ + rAnother.w_);
    }


    /*************************************************************//**
     *
     *  @brief  もう一つのベクトルで減算したベクトルを求める
     *  @param  もう一つのベクトル
     *  @return 減算したベクトル
     *
     ****************************************************************/
    template<typename T>
    const S_Vector4<T> S_Vector4<T>::operator-(const S_Vector4<T>& rAnother) const
    {
        return S_Vector4(x_ - rAnother.x_,
                         y_ - rAnother.y_,
                         z_ - rAnother.z_,
                         w_ - rAnother.w_);
    }


    /*************************************************************//**
     *
     *  @brief  もう一つのベクトルを乗算したベクトルを求める
     *  @param  もう一つのベクトル
     *  @return 乗算したベクトル
     *
     ****************************************************************/
    template<typename T>
    const S_Vector4<T> S_Vector4<T>::operator*(const S_Vector4<T>& rAnother) const
    {
        return S_Vector4(x_ * rAnother.x_,
                         y_ * rAnother.y_,
                         z_ * rAnother.z_,
                         w_ * rAnother.w_);
    }


    /*************************************************************//**
     *
     *  @brief  もう一つのベクトルで除算したベクトルを求める
     *  @param  もう一つのベクトル
     *  @return 除算したベクトル
     *
     ****************************************************************/
    template<typename T>
    const S_Vector4<T> S_Vector4<T>::operator/(const S_Vector4<T>& rAnother) const
    {
        assert(rAnother.x_ != static_cast<T>(0));
        assert(rAnother.y_ != static_cast<T>(0));
        assert(rAnother.z_ != static_cast<T>(0));
        assert(rAnother.w_ != static_cast<T>(0));

        return S_Vector4(x_ / rAnother.x_,
                         y_ / rAnother.y_,
                         z_ / rAnother.z_,
                         w_ / rAnother.w_);
    }


    /*************************************************************//**
     *
     *  @brief  もう一つのベクトルを加算する
     *  @param  もう一つのベクトル
     *  @return 加算後のベクトル( 自分自身 )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector4<T>& S_Vector4<T>::operator+=(const S_Vector4<T>& rAnother)
    {
        x_ += rAnother.x_;
        y_ += rAnother.y_;
        z_ += rAnother.z_;
        w_ += rAnother.w_;

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
    const S_Vector4<T>& S_Vector4<T>::operator-=(const S_Vector4<T>& rAnother)
    {
        x_ -= rAnother.x_;
        y_ -= rAnother.y_;
        z_ -= rAnother.z_;
        w_ -= rAnother.w_;

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  もう一つのベクトルを乗算する
     *  @param  もう一つのベクトル
     *  @return 乗算後のベクトル( 自分自身 )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector4<T>& S_Vector4<T>::operator*=(const S_Vector4<T>& rAnother)
    {
        x_ *= rAnother.x_;
        y_ *= rAnother.y_;
        z_ *= rAnother.z_;
        w_ *= rAnother.w_;

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
    const S_Vector4<T>& S_Vector4<T>::operator/=(const S_Vector4<T>& rAnother)
    {
        assert(rAnother.x_ != static_cast<T>(0));
        assert(rAnother.y_ != static_cast<T>(0));
        assert(rAnother.z_ != static_cast<T>(0));
        assert(rAnother.w_ != static_cast<T>(0));

        x_ /= rAnother.x_;
        y_ /= rAnother.y_;
        z_ /= rAnother.z_;
        w_ /= rAnother.w_;

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
    bool S_Vector4<T>::operator==(const S_Vector4<T>& rAnother) const
    {
        return std::abs(x_ - rAnother.x_) < static_cast<T>(s_EPSILON)
            && std::abs(y_ - rAnother.y_) < static_cast<T>(s_EPSILON)
            && std::abs(z_ - rAnother.z_) < static_cast<T>(s_EPSILON)
            && std::abs(w_ - rAnother.w_) < static_cast<T>(s_EPSILON);
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
    bool S_Vector4<T>::operator!=(const S_Vector4<T>& rAnother) const
    {
        return std::abs(x_ - rAnother.x_) > static_cast<T>(s_EPSILON)
            || std::abs(y_ - rAnother.y_) > static_cast<T>(s_EPSILON)
            || std::abs(z_ - rAnother.z_) > static_cast<T>(s_EPSILON)
            || std::abs(w_ - rAnother.w_) > static_cast<T>(s_EPSILON);
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
    const S_Vector4<T> S_Vector4<T>::operator*(T value) const
    {
        return S_Vector4(x_ * value,
                         y_ * value,
                         z_ * value,
                         w_ * value);
    }


    /*************************************************************//**
     *
     *  @brief  T型の値で各成分を除算したベクトルを求める
     *  @param  T型の値
     *  @return 除算したベクトル
     *
     ****************************************************************/
    template<typename T>
    const S_Vector4<T> S_Vector4<T>::operator/(T value) const
    {
        assert(value != static_cast<T>(0));

        return S_Vector4(x_ / value,
                         y_ / value,
                         z_ / value,
                         w_ / value);
    }


    /*************************************************************//**
     *
     *  @brief  T型の値を各成分に乗算する
     *  @param  T型の値
     *  @return 乗算後のベクトル( 自分自身 )
     *
     ****************************************************************/
    template<typename T>
    const S_Vector4<T>& S_Vector4<T>::operator*=(T value)
    {
        x_ *= value;
        y_ *= value;
        z_ *= value;
        w_ *= value;

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
    const S_Vector4<T>& S_Vector4<T>::operator/=(T value)
    {
        assert(value != static_cast<T>(0));

        x_ /= value;
        y_ /= value;
        z_ /= value;
        w_ /= value;

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
    S_Vector4<T>::operator S_Vector2<T>() const
    {
        return xyz_.xy_;
    }


    /*************************************************************//**
     *
     *  @brief  S_Vector3型へキャストする
     *  @param  なし
     *  @return 3Dベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::operator S_Vector3<T>() const
    {
        return xyz_;
    }


    /*************************************************************//**
     *
     *  @brief  string型へキャストする
     *  @param  なし
     *  @return 文字列に変換したベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T>::operator std::string() const
    {
        return GetConvertToString();
    }


#pragma endregion


    /* 明示的インスタンス化 */
    template struct S_Vector4<float>;
    template struct S_Vector4<double>;

}