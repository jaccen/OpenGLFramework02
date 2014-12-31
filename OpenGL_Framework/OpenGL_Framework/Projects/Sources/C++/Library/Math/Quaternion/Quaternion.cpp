/* ヘッダファイル */
#include "Quaternion.h"
#include "../Matrix/Matrix3x3.h"
#include "../Matrix/Matrix4x4.h"
#include "../Define/MathDefine.h"


//-------------------------------------------------------------
///
/// @brief マス
/// @brief 数学関連の名前空間
///
//-------------------------------------------------------------
namespace Math
{

    /* プロトタイプ宣言 */
    template<typename T>
    static S_Quaternion<T> s_LerpQuaternion(const S_Quaternion<T>& rStartQuaternion,
                                            const S_Quaternion<T>& rEndQuaternion,
                                            T coefficient);


#pragma region 静的メンバ変数の初期化


    template<typename T>
    const S_Quaternion<T> S_Quaternion<T>::s_IDENTITY(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));


#pragma endregion


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T>::S_Quaternion() : S_Quaternion(static_cast<T>(0))
    {
    }


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  値
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T>::S_Quaternion(T value) : S_Quaternion(value, value, value, value)
    {
    }


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  T成分
     *  @param  X成分
     *  @param  Y成分
     *  @param  Z成分
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T>::S_Quaternion(T t, T x, T y, T z) :

        // T成分
        t_(t),

        // X・Y・Z成分
        xyz_(x, y, z)

    {
    }


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  T成分
     *  @param  X・Y・Z成分
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T>::S_Quaternion(T t, const S_Vector3<T>& rXYZ) :

        // T成分
        t_(t),

        // X・Y・Z成分
        xyz_(rXYZ)

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T>::~S_Quaternion()
    {
    }


    /*************************************************************//**
     *
     *  @brief  各成分を特定の値に変更する
     *  @param  値
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Quaternion<T>::Fill(T value)
    {
        t_ = value;
        x_ = value;
        y_ = value;
        z_ = value;
    }


    /*************************************************************//**
     *
     *  @brief  単位クォータニオン化する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Quaternion<T>::Identity()
    {
        t_ = static_cast<T>(1);
        xyz_.Zero();
    }


    /*************************************************************//**
     *
     *  @brief  正規化を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Quaternion<T>::Normalize()
    {
        // 長さを取得
        T length = GetLength();
        assert(length != static_cast<T>(0));

        // 正規化
        t_ /= length;
        xyz_ /= length;
    }


    /*************************************************************//**
     *
     *  @brief  逆クォータニオン化を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Quaternion<T>::Invert()
    {
        xyz_.Invert();
    }


    /*************************************************************//**
     *
     *  @brief  長さを取得する
     *  @param  なし
     *  @return 長さ
     *
     ****************************************************************/
    template<typename T>
    T S_Quaternion<T>::GetLength() const
    {
        return SquareRoot(GetLengthSquare());
    }


    /*************************************************************//**
     *
     *  @brief  長さの2乗を取得する
     *  @param  なし
     *  @return 長さの２乗
     *
     ****************************************************************/
    template<typename T>
    T S_Quaternion<T>::GetLengthSquare() const
    {
        return Square(t_) + Square(x_) + Square(y_) + Square(z_);
    }


    /*************************************************************//**
     *
     *  @brief  正規化したクォータニオンを取得する
     *  @param  なし
     *  @return 正規化したクォータニオン
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::GetNormalize() const
    {
        S_Quaternion normalizeQuaternion(*this);
        normalizeQuaternion.Normalize();

        return normalizeQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  逆クォータニオンを取得する
     *  @param  なし
     *  @return 逆クォータニオン
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::GetInvert() const
    {
        S_Quaternion inverseQuaternion(*this);
        inverseQuaternion.Invert();

        return inverseQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  X軸からの角度を取得する
     *  @param  なし
     *  @return 角度( ラジアン値 )
     *
     ****************************************************************/
    template<typename T>
    T S_Quaternion<T>::GetAngleFromXAxis() const
    {
        T angle = std::atan2(static_cast<T>(2) * (y_ * z_ + t_ * x_),
                             Square(t_) - Square(x_) - Square(y_) + Square(z_));

        return angle;
    }


    /*************************************************************//**
     *
     *  @brief  Y軸からの角度を取得する
     *  @param  なし
     *  @return 角度( ラジアン値 )
     *
     ****************************************************************/
    template<typename T>
    T S_Quaternion<T>::GetAngleFromYAxis() const
    {
        T angle = std::asin(static_cast<T>(-2) * (x_ * z_ - t_ * y_));

        return angle;
    }


    /*************************************************************//**
     *
     *  @brief  Z軸からの角度を取得する
     *  @param  なし
     *  @return 角度( ラジアン値 )
     *
     ****************************************************************/
    template<typename T>
    T S_Quaternion<T>::GetAngleFromZAxis() const
    {
        T angle = std::atan2(static_cast<T>(2) * (x_ * y_ + t_ * z_),
                             Square(t_) + Square(x_) - Square(y_) - Square(z_));

        return angle;
    }


    /*************************************************************//**
     *
     *  @brief  軸と角度を取得する
     *  @param  なし
     *  @return 軸と角度( ラジアン値 )
     *
     ****************************************************************/
    template<typename T>
    std::tuple<S_Vector3<T>, T> S_Quaternion<T>::GetAxisAndAngle() const
    {
        // 角度の半分とサインを求める
        T halfAngle = static_cast<T>(0), sine = static_cast<T>(0);

        halfAngle = std::acos(t_);

        sine = std::sqrt(Square(x_) + Square(y_) + Square(z_));
        T absoluteSine = std::abs(sine);

        // サインから軸と角度を設定
        T angle = static_cast<T>(0);
        S_Vector3<T> axis;

        if (absoluteSine < static_cast<T>(s_EPSILON) || std::abs(absoluteSine - s_PI2) < static_cast<T>(s_EPSILON))
        {
            axis.x_ = static_cast<T>(0);;
            axis.y_ = static_cast<T>(0);
            axis.z_ = static_cast<T>(1);
        }
        else
        {
            angle = halfAngle * static_cast<T>(2);

            axis = xyz_ / sine;
            axis.Normalize();
        }

        return std::make_tuple(axis, angle);
    }


    /*************************************************************//**
     *
     *  @brief  ベクトルを文字列に変換して取得する
     *  @param  なし
     *  @return 文字列に変換したベクトル
     *
     ****************************************************************/
    template<typename T>
    std::string S_Quaternion<T>::GetConvertToString() const
    {
        return "(" + std::to_string(t_) + ", " + std::to_string(x_) + ", " + std::to_string(y_) + ", " + std::to_string(z_) + ")";
    }



    /*************************************************************//**
     *
     *  @brief  内積を求める
     *  @param  なし
     *  @return 内積
     *
     ****************************************************************/
    template<typename T>
    T S_Quaternion<T>::s_DotProduct(const S_Quaternion<T>& rLhs, const S_Quaternion<T>& rRhs)
    {
        return (rLhs.t_ * rRhs.t_)
             + (rLhs.x_ * rRhs.x_)
             + (rLhs.y_ * rRhs.y_)
             + (rLhs.z_ * rRhs.z_);
    }


    /*************************************************************//**
     *
     *  @brief  任意軸から回転クォータニオンを作成する
     *  @param  軸
     *  @param  角度( ラジアン値 )
     *  @return 回転クォータニオン
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_CreateRotationAxis(const S_Vector3<T>& rAxis, T angle)
    {
        // 角度の半分とそのサインを求める
        T halfAngle = angle * static_cast<T>(0.5);
        T sine = static_cast<T>(std::sin(static_cast<T>(halfAngle)));

        // 回転クォータニオンを求める
        S_Quaternion rotationQuaternion(std::cos(halfAngle),
                                        rAxis.x_ * sine,
                                        rAxis.y_ * sine,
                                        rAxis.z_ * sine);

        rotationQuaternion.Normalize();

        return rotationQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  3軸の回転を反映した回転クォータニオンを作成する
     *  @param  ピッチ( X軸の角度・ラジアン値 )
     *  @param  ヨー( Y軸の角度・ラジアン値 )
     *  @param  ロール( Z軸の角度・ラジアン値 )
     *  @return 回転クォータニオン
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_CreateRotationPitchYawRoll(T pitch,
        T yaw,
        T roll)
    {
        // 各角度を調節
        pitch = AdjustAngleFrom0ToPI2(pitch);
        yaw = AdjustAngleFrom0ToPI2(yaw);
        roll = AdjustAngleFrom0ToPI2(roll);

        // 回転クォータニオン
        S_Quaternion rotationQuaternion;

        // 各軸のサインとコサインを求める
        T sineX = std::sin(pitch * static_cast<T>(0.5));
        T cosineX = std::cos(pitch * static_cast<T>(0.5));

        T sineY = std::sin(yaw * static_cast<T>(0.5));
        T cosineY = std::cos(yaw * static_cast<T>(0.5));

        T sineZ = std::sin(roll * static_cast<T>(0.5));
        T cosineZ = std::cos(roll * static_cast<T>(0.5));

        // 回転クォータニオンを求める
        rotationQuaternion.t_ = (cosineY * cosineZ * cosineX) - (sineY * sineZ   * sineX);
        rotationQuaternion.x_ = (sineY *   sineZ * cosineX) + (cosineY * cosineZ * sineX);
        rotationQuaternion.y_ = (sineY * cosineZ * cosineX) + (cosineY * sineZ   * sineX);
        rotationQuaternion.z_ = (cosineY *   sineZ * cosineX) - (sineY * cosineZ * sineX);

        return rotationQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  3軸の回転を反映した回転クォータニオンを作成する
     *  @param  回転量
     *  @return 回転クォータニオン
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_CreateRotationPitchYawRoll(const S_Vector3<T>& rRotation)
    {
        return s_CreateRotationPitchYawRoll(rRotation.x_, rRotation.y_, rRotation.z_);
    }


    /*************************************************************//**
     *
     *  @brief  任意の向きへ向くための回転クォータニオンを作成する
     *  @param  向き
     *  @param  上方向
     *  @return 回転クォータニオン
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_CreateLookRotation(const S_Vector3<T>& rDirection,
        const S_Vector3<T>& rUpVector)
    {
        // 3 * 3行列のビュー行列を作成し、クォータニオンに変換
        S_Matrix3x3<T> viewMatrix;
        viewMatrix = S_Matrix3x3<T>::s_CreateLookAt(S_Vector3<T>::s_ZERO, rDirection, rUpVector);

        S_Quaternion rotationQuaternion = s_ConvertMatrix3x3ToQuaternion(viewMatrix);
        rotationQuaternion.Normalize();

        return rotationQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  向きから向きへ回転させる回転クォータニオンを作成する
     *  @param  回転前の向き
     *  @param  回転後の向き
     *  @return 回転クォータニオン
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_CreateFromToRotation(const S_Vector3<T>& rFromDirection,
        const S_Vector3<T>& rToDirection)
    {
        // 角度と軸を求める
        T angle = S_Vector3<T>::s_AngleBetweenVectors(rFromDirection, rToDirection);
        S_Vector3<T> axis = S_Vector3<T>::s_CrossProduct(rFromDirection, rToDirection);

        // 回転クォータニオンを作成
        S_Quaternion rotationQuaternion = s_CreateRotationAxis(axis, angle);

        return rotationQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  3 * 3の行列からクォータニオンへ変換し、取得する
     *  @param  3 * 3の行列
     *  @return クォータニオン
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_ConvertMatrix3x3ToQuaternion(const S_Matrix3x3<T>& rMatrix)
    {
        // 誤差範囲を表す極小の値
        const T EPSILON = static_cast<T>(0.000001);

        // 変換後のクォータニオン
        S_Quaternion<T> convertionQuaternion;

        // 転置行列を取得
        S_Matrix3x3<T> transposeMatrix(rMatrix.GetTranspose());

        // ( 4x4行列の場合の )対角線の合計
        T diagonalSum = transposeMatrix.a11_
            + transposeMatrix.a22_
            + transposeMatrix.a33_
            + static_cast<T>(1);

        // 対角線のスケール
        T diagonalScale = static_cast<T>(0);

        // 対角線の合計が0超過の場合
        if (diagonalSum > EPSILON)
        {
            // 対角線のスケールを求める
            diagonalScale = SquareRoot(diagonalSum) * static_cast<T>(2);

            // 各成分を求める
            convertionQuaternion.t_ = static_cast<T>(0.25) * diagonalScale;
            convertionQuaternion.x_ = (transposeMatrix.a32_ - transposeMatrix.a23_) / diagonalScale;
            convertionQuaternion.y_ = (transposeMatrix.a13_ - transposeMatrix.a31_) / diagonalScale;
            convertionQuaternion.z_ = (transposeMatrix.a21_ - transposeMatrix.a12_) / diagonalScale;
        }
        else
        {
            // 対角線の最大値に応じて成分を求める
            if (transposeMatrix.a11_ > transposeMatrix.a22_ && transposeMatrix.a11_ > transposeMatrix.a33_)
            {
                // 対角線のスケールを求める
                diagonalScale = SquareRoot(static_cast<T>(1) + transposeMatrix.a11_ - transposeMatrix.a22_ - transposeMatrix.a33_) * static_cast<T>(2);

                // 各成分を求める
                convertionQuaternion.t_ = (transposeMatrix.a32_ - transposeMatrix.a23_) / diagonalScale;
                convertionQuaternion.x_ = static_cast<T>(0.25) * diagonalScale;
                convertionQuaternion.y_ = (transposeMatrix.a21_ - transposeMatrix.a12_) / diagonalScale;
                convertionQuaternion.z_ = (transposeMatrix.a13_ - transposeMatrix.a31_) / diagonalScale;
            }
            else if (transposeMatrix.a22_ > transposeMatrix.a33_)
            {
                // 対角線のスケールを求める
                diagonalScale = SquareRoot(static_cast<T>(1) + transposeMatrix.a22_ - transposeMatrix.a11_ - transposeMatrix.a33_) * static_cast<T>(2);

                // 各成分を求める
                convertionQuaternion.t_ = (transposeMatrix.a13_ - transposeMatrix.a31_) / diagonalScale;
                convertionQuaternion.x_ = (transposeMatrix.a21_ - transposeMatrix.a12_) / diagonalScale;
                convertionQuaternion.y_ = static_cast<T>(0.25) * diagonalScale;
                convertionQuaternion.z_ = (transposeMatrix.a32_ - transposeMatrix.a23_) / diagonalScale;
            }
            else
            {
                // 対角線のスケールを求める
                diagonalScale = SquareRoot(static_cast<T>(1) + transposeMatrix.a33_ - transposeMatrix.a11_ - transposeMatrix.a22_) * static_cast<T>(2);

                // 各成分を求める
                convertionQuaternion.t_ = (transposeMatrix.a21_ - transposeMatrix.a12_) / diagonalScale;
                convertionQuaternion.x_ = (transposeMatrix.a13_ - transposeMatrix.a31_) / diagonalScale;
                convertionQuaternion.y_ = (transposeMatrix.a32_ - transposeMatrix.a23_) / diagonalScale;
                convertionQuaternion.z_ = static_cast<T>(0.25) * diagonalScale;
            }
        }

        return convertionQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  4 * 4の行列からクォータニオンへ変換し、取得する
     *  @param  4 * 4の行列
     *  @return クォータニオン
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_ConvertMatrix4x4ToQuaternion(const S_Matrix4x4<T>& rMatrix)
    {
        return s_ConvertMatrix3x3ToQuaternion(S_Matrix3x3<T>::s_ConvertMatrix4x4ToMatrix3x3(rMatrix));
    }


    /*************************************************************//**
     *
     *  @brief  線形補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 二つの点を線形補間した点
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_Lerp(const S_Quaternion<T>& rStart,
                                            const S_Quaternion<T>& rEnd,
                                            T coefficient)
    {
        S_Quaternion lerpPoint;

        if (s_DotProduct(rStart, rEnd) > static_cast<T>(0))
        {
            lerpPoint = s_LerpQuaternion(rStart, rEnd, coefficient);
        }
        else
        {
            lerpPoint = s_LerpQuaternion(rStart, rEnd * static_cast<T>(-1), coefficient);
        }

        return lerpPoint;
    }


    /*************************************************************//**
     *
     *  @brief  球面線形補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 二つのを球面線形補間した点
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> S_Quaternion<T>::s_Slerp(const S_Quaternion<T>& rStart,
                                             const S_Quaternion<T>& rEnd,
                                             T coefficient)
    {
        // 球面線形補間後のクォータニオン
        S_Quaternion slerpQuaternion;

        // 内積
        T dotProduct = s_DotProduct(rStart, rEnd);

        // 内積のしきい値
        const T DOT_THRESHOLD = static_cast<T>(0.9995);

        // しきい値を超過していた場合
        if (dotProduct > DOT_THRESHOLD)
        {
            // もう一つのクォータニオンとの差
            S_Quaternion difference(rEnd - rStart);

            // 差に補間係数を掛け、それに自身を足した値を求める
            difference *= coefficient;
            slerpQuaternion = rStart + difference;

            // クォータニオンを正規化
            slerpQuaternion.Normalize();
        }
        else
        {
            // 内積をクランプし、角度を求める
            Clamp(dotProduct, static_cast<T>(-1), static_cast<T>(1));
            T angle = std::acos(dotProduct);

            // 角度に補間係数を掛ける
            T interpolationAngle = angle * coefficient;

            // 自身に内積をかけた値を求め、もう一つのクォータニオンとの差分を求める
            S_Quaternion dotQuaternion(rStart * dotProduct);
            S_Quaternion difference(rEnd - dotQuaternion);

            // 差分を正規化
            difference.Normalize();

            // 自身と補間係数を掛けた角度のコサインを掛けたクォータニオン
            S_Quaternion cosineQuaternion(rStart * ::cos(interpolationAngle));

            // 差分と補間係数をかけた角度のサインを掛けたクォータニオン
            S_Quaternion sineQuaternion(difference * ::sin(interpolationAngle));

            // 2つのクォータニオンを合わせる
            slerpQuaternion = cosineQuaternion + sineQuaternion;
        }

        return slerpQuaternion;
    }


#pragma region S_Quaternion型との演算子のオーバーロード


    /*************************************************************//**
     *
     *  @brief  もう一つのクォータニオンを加算したクォータニオンを求める
     *  @param  もう一つのクォータニオン
     *  @return 加算したクォータニオン
     *
     ****************************************************************/
    template<typename T>
    const S_Quaternion<T> S_Quaternion<T>::operator+(const S_Quaternion<T>& rAnother) const
    {
        S_Quaternion tempQuaternion;

        tempQuaternion.t_ = t_ + rAnother.t_;
        tempQuaternion.x_ = x_ + rAnother.x_;
        tempQuaternion.y_ = y_ + rAnother.y_;
        tempQuaternion.z_ = z_ + rAnother.z_;

        return tempQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  もう一つのクォータニオンを加算する
     *  @param  もう一つのクォータニオン
     *  @return 加算したクォータニオン( 自分自身 )
     *
     ****************************************************************/
    template<typename T>
    const S_Quaternion<T>& S_Quaternion<T>::operator+=(const S_Quaternion<T>& rAnother)
    {
        t_ += rAnother.t_;
        x_ += rAnother.x_;
        y_ += rAnother.y_;
        z_ += rAnother.z_;

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  もう一つのクォータニオンを減算したクォータニオンを求める
     *  @param  もう一つのクォータニオン
     *  @return 減算したクォータニオン
     *
     ****************************************************************/
    template<typename T>
    const S_Quaternion<T> S_Quaternion<T>::operator-(const S_Quaternion<T>& rAnother) const
    {
        S_Quaternion tempQuaternion;

        tempQuaternion.t_ = t_ - rAnother.t_;
        tempQuaternion.x_ = x_ - rAnother.x_;
        tempQuaternion.y_ = y_ - rAnother.y_;
        tempQuaternion.z_ = z_ - rAnother.z_;

        return tempQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  もう一つのクォータニオンを減算する
     *  @param  もう一つのクォータニオン
     *  @return 減算したクォータニオン( 自分自身 )
     *
     ****************************************************************/
    template<typename T>
    const S_Quaternion<T>& S_Quaternion<T>::operator-=(const S_Quaternion<T>& rAnother)
    {
        t_ -= rAnother.t_;
        x_ -= rAnother.x_;
        y_ -= rAnother.y_;
        z_ -= rAnother.z_;

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  もう一つのクォータニオンを乗算したクォータニオンを求める
     *  @param  もう一つのクォータニオン
     *  @return 乗算したクォータニオン
     *
     ****************************************************************/
    template<typename T>
    const S_Quaternion<T> S_Quaternion<T>::operator*(const S_Quaternion<T>& rAnother) const
    {
        S_Quaternion tempQuaternion;

        // 実部を求める
        tempQuaternion.t_ = (t_ * rAnother.t_) - S_Vector3<T>::s_DotProduct(xyz_, rAnother.xyz_);

        // 虚部を求める
        tempQuaternion.xyz_ = (t_ * rAnother.xyz_)
                            + (rAnother.t_ * xyz_)
                            + S_Vector3<T>::s_CrossProduct(xyz_, rAnother.xyz_);

        return tempQuaternion;
    }


    /*************************************************************//**
     *
     *  @brief  もう一つのクォータニオンを乗算する
     *  @param  もう一つのクォータニオン
     *  @return 乗算したクォータニオン( 自分自身 )
     *
     ****************************************************************/
    template<typename T>
    const S_Quaternion<T>& S_Quaternion<T>::operator*=(const S_Quaternion<T>& rAnother)
    {
        S_Quaternion tempQuaternion;

        // 実部を求める
        tempQuaternion.t_ = (t_ * rAnother.t_) - S_Vector3<T>::s_DotProduct(xyz_, rAnother.xyz_);

        // 虚部を求める
        tempQuaternion.xyz_ = (t_ * rAnother.xyz_)
            + (rAnother.t_ * xyz_)
            + S_Vector3<T>::s_CrossProduct(xyz_, rAnother.xyz_);

        (*this) = tempQuaternion;

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  もう一つのクォータニオンと比較する
     *  @param  もう一つのクォータニオン
     *  @return 同じベクトルの場合：true
     *  @return 違うベクトルの場合：false
     *
     ****************************************************************/
    template<typename T>
    bool S_Quaternion<T>::operator==(const S_Quaternion<T>& rAnother) const
    {
        return std::abs(t_ - rAnother.t_) < static_cast<T>(s_EPSILON)
            && std::abs(x_ - rAnother.x_) < static_cast<T>(s_EPSILON)
            && std::abs(y_ - rAnother.y_) < static_cast<T>(s_EPSILON)
            && std::abs(z_ - rAnother.z_) < static_cast<T>(s_EPSILON);
    }


    /*************************************************************//**
     *
     *  @brief  もう一つのクォータニオンと比較する
     *  @param  もう一つのクォータニオン
     *  @return 違うベクトルの場合：true
     *  @return 同じベクトルの場合：false
     *
     ****************************************************************/
    template<typename T>
    bool S_Quaternion<T>::operator!=(const S_Quaternion<T>& rAnother) const
    {
        return std::abs(t_ - rAnother.t_) > static_cast<T>(s_EPSILON)
            || std::abs(x_ - rAnother.x_) > static_cast<T>(s_EPSILON)
            || std::abs(y_ - rAnother.y_) > static_cast<T>(s_EPSILON)
            || std::abs(z_ - rAnother.z_) > static_cast<T>(s_EPSILON);
    }



#pragma endregion


#pragma region T型との演算子のオーバーロード


    /*************************************************************//**
     *
     *  @brief  T型の値を乗算したクォータニオンを求める
     *  @param  T型の値
     *  @return 乗算したクォータニオン
     *
     ****************************************************************/
    template<typename T>
    const S_Quaternion<T> S_Quaternion<T>::operator*(T value) const
    {
        return S_Quaternion(t_ * value, x_ * value, y_ * value, z_ * value);
    }


    /*************************************************************//**
     *
     *  @brief  T型の値を各成分に乗算する
     *  @param  T型の値
     *  @return 乗算後のクォータニオン
     *
     ****************************************************************/
    template<typename T>
    const S_Quaternion<T>& S_Quaternion<T>::operator*=(T value)
    {
        t_ *= value;
        x_ *= value;
        y_ *= value;
        z_ *= value;

        return (*this);
    }


#pragma endregion


#pragma region キャスト演算子のオーバーロード


    /*************************************************************//**
     *
     *  @brief  S_Vector3型へキャストする
     *  @param  なし
     *  @return 3Dベクトル
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T>::operator S_Vector3<T>() const
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
    S_Quaternion<T>::operator std::string() const
    {
        return GetConvertToString();
    }


#pragma endregion



    /* 明示的インスタンス化 */
    template struct S_Quaternion<float>;
    template struct S_Quaternion<double>;


    /*************************************************************//**
     *
     *  @brief  クォータニオンの線形補間を行う
     *  @param  開始時のクォータニオン
     *  @param  終了時のクォータニオン
     *  @param  補間係数
     *  @return 線形補間したクォータニオン
     *
     ****************************************************************/
    template<typename T>
    S_Quaternion<T> s_LerpQuaternion(const S_Quaternion<T>& rStartQuaternion,
                                     const S_Quaternion<T>& rEndQuaternion,
                                     T coefficient)
    {
        S_Quaternion<T> lerpPoint;

        lerpPoint.t_ = (rEndQuaternion.t_ - rStartQuaternion.t_) * coefficient + rStartQuaternion.t_;
        lerpPoint.x_ = (rEndQuaternion.x_ - rStartQuaternion.x_) * coefficient + rStartQuaternion.x_;
        lerpPoint.y_ = (rEndQuaternion.y_ - rStartQuaternion.y_) * coefficient + rStartQuaternion.y_;
        lerpPoint.z_ = (rEndQuaternion.z_ - rStartQuaternion.z_) * coefficient + rStartQuaternion.z_;

        return lerpPoint;
    }

}