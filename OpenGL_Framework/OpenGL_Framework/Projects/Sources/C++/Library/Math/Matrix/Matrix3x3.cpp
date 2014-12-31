/* ヘッダファイル */
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "../Vector/Vector3.h"
#include "../Quaternion/Quaternion.h"
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
    static T s_GetDeterminant(const S_Matrix3x3<T>& rMatrix);


#pragma region 静的メンバ変数の初期化


    template<typename T>
    const S_Matrix3x3<T> S_Matrix3x3<T>::s_ZERO(static_cast<T>(0));


    template<typename T>
    const S_Matrix3x3<T> S_Matrix3x3<T>::s_IDENTITY;


#pragma endregion


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T>::S_Matrix3x3() :

        // 9個の要素
        a11_(static_cast<T>(1)),
        a12_(static_cast<T>(0)),
        a13_(static_cast<T>(0)),

        a21_(static_cast<T>(0)),
        a22_(static_cast<T>(1)),
        a23_(static_cast<T>(0)),

        a31_(static_cast<T>(0)),
        a32_(static_cast<T>(0)),
        a33_(static_cast<T>(1))

    {
    }


    /*************************************************************//**
     *
     *  @brief  コンストラクタ( 各要素を指定した1つの値で初期化 )
     *  @param  値
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T>::S_Matrix3x3(T value) : S_Matrix3x3(value, value, value,
                                                       value, value, value,
                                                       value, value, value)
    {
    }


    /*************************************************************//**
     *
     *  @brief  コンストラクタ( 指定した値で各要素の初期化 )
     *  @param  要素1
     *  @param  要素2
     *  @param  要素3
     *  @param  要素4
     *  @param  要素5
     *  @param  要素6
     *  @param  要素7
     *  @param  要素8
     *  @param  要素9
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T>::S_Matrix3x3(T a11, T a12, T a13,
                                T a21, T a22, T a23,
                                T a31, T a32, T a33) :

        // 9個の要素
        a11_(a11),
        a12_(a12),
        a13_(a13),

        a21_(a21),
        a22_(a22),
        a23_(a23),

        a31_(a31),
        a32_(a32),
        a33_(a33)

    {
    }


    /*************************************************************//**
     *
     *  @brief  コンストラクタ( 指定した配列で要素の初期化 )
     *  @param  要素が9個の配列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T>::S_Matrix3x3(const T a[s_ELEMENT_NUMBER])
    {
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i) a_[i] = a[i];
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T>::~S_Matrix3x3()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ゼロ行列化する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix3x3<T>::Zero()
    {
        for (auto& a : a_) a = static_cast<T>(0);
    }


    /*************************************************************//**
     *
     *  @brief  各要素を特定の値に変更する
     *  @param  値
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix3x3<T>::Fill(T value)
    {
        for (auto& a : a_) a = value;
    }


    /*************************************************************//**
     *
     *  @brief  単位行列化する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix3x3<T>::Identity()
    {
        a11_ = static_cast<T>(1);
        a12_ = static_cast<T>(0);
        a13_ = static_cast<T>(0);

        a21_ = static_cast<T>(0);
        a22_ = static_cast<T>(1);
        a23_ = static_cast<T>(0);

        a31_ = static_cast<T>(0);
        a32_ = static_cast<T>(0);
        a33_ = static_cast<T>(1);
    }


    /*************************************************************//**
     *
     *  @brief  転置行列化する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix3x3<T>::Transpose()
    {
        std::swap(a12_, a21_);
        std::swap(a13_, a31_);
        std::swap(a23_, a32_);
    }


    /*************************************************************//**
     *
     *  @brief  逆行列化する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix3x3<T>::Invert()
    {
        // 行列式を取得
        T determinant = s_GetDeterminant(*this);

        if (determinant == static_cast<T>(0)) return;

        // 逆行列
        S_Matrix3x3 inverseMatrix;

        // 行列式の逆数
        T reciprocalDeterminant = static_cast<T>(1) / determinant;

        // 逆行列を求める
        inverseMatrix.a11_ = (a22_ * a33_ - a23_ * a32_) * reciprocalDeterminant;
        inverseMatrix.a12_ = (a13_ * a32_ - a12_ * a33_) * reciprocalDeterminant;
        inverseMatrix.a13_ = (a12_ * a23_ - a13_ * a22_) * reciprocalDeterminant;
        inverseMatrix.a21_ = (a23_ * a31_ - a21_ * a33_) * reciprocalDeterminant;
        inverseMatrix.a22_ = (a11_ * a33_ - a13_ * a31_) * reciprocalDeterminant;
        inverseMatrix.a23_ = (a13_ * a21_ - a11_ * a23_) * reciprocalDeterminant;
        inverseMatrix.a31_ = (a21_ * a32_ - a22_ * a31_) * reciprocalDeterminant;
        inverseMatrix.a32_ = (a12_ * a31_ - a11_ * a32_) * reciprocalDeterminant;
        inverseMatrix.a33_ = (a11_ * a22_ - a12_ * a21_) * reciprocalDeterminant;

        // 逆行列を代入
        (*this) = inverseMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  転置行列を取得する
     *  @param  なし
     *  @return 転置行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::GetTranspose() const
    {
        S_Matrix3x3 transposeMatrix(*this);
        transposeMatrix.Transpose();

        return transposeMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  逆行列を取得する
     *  @param  なし
     *  @return 逆行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::GetInvert() const
    {
        S_Matrix3x3 inverseMatrix(*this);
        inverseMatrix.Invert();

        return inverseMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  行を取得する
     *  @param  添え字
     *  @return 行
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Matrix3x3<T>::GetRow(int32_t index) const
    {
        assert(index >= 0 && index < 3);
        return S_Vector3<T>(a_[index], a_[index + 3], a_[index + 6]);
    }


    /*************************************************************//**
     *
     *  @brief  列を取得する
     *  @param  添え字
     *  @return 列
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Matrix3x3<T>::GetColumn(int32_t index) const
    {
        assert(index >= 0 && index < 3);

        index *= 3;
        return S_Vector3<T>(a_[index], a_[index + 1], a_[index + 2]);
    }


    /*************************************************************//**
     *
     *  @brief  行列を文字列に変換して取得する
     *  @param  なし
     *  @return 文字列に変換した行列
     *
     ****************************************************************/
    template<typename T>
    std::string S_Matrix3x3<T>::GetConvertToString() const
    {
        return "|" + std::to_string(a11_) + ", " + std::to_string(a21_) + ", " + std::to_string(a31_) + "|\n"
             + "|" + std::to_string(a12_) + ", " + std::to_string(a22_) + ", " + std::to_string(a32_) + "|\n"
             + "|" + std::to_string(a13_) + ", " + std::to_string(a23_) + ", " + std::to_string(a33_) + "|";
    }


    /*************************************************************//**
     *
     *  @brief  行を設定する
     *  @param  列
     *  @param  添え字
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix3x3<T>::SetRow(const S_Vector3<T>& rRow, int32_t index)
    {
        assert(index >= 0 && index < 3);

        for (int32_t i = 0; i < 3; ++i) a_[index + i * 3] = rRow.a_[i];
    }


    /*************************************************************//**
     *
     *  @brief  列を設定する
     *  @param  列
     *  @param  添え字
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix3x3<T>::SetColumn(const S_Vector3<T>& rColumn, int32_t index)
    {
        assert(index >= 0 && index < 3);

        for (int32_t i = 0; i < 3; ++i) a_[index + i] = rColumn.a_[i];
    }


    /*************************************************************//**
     *
     *  @brief  回転行列を作成する
     *  @param  角度( ラジアン値 )
     *  @return 回転行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotation(T angle)
    {
        // 回転行列
        S_Matrix3x3 rotationMatrix;

        // サインとコサインを求める
        T sine = std::sin(angle);
        T cosine = std::cos(angle);

        // 回転行列を求める
        rotationMatrix.a11_ = cosine;
        rotationMatrix.a12_ = sine;
        rotationMatrix.a21_ = sine * static_cast<T>(-1);
        rotationMatrix.a22_ = cosine;

        return rotationMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  X軸から回転行列を作成する
     *  @param  角度( ラジアン値 )
     *  @return 回転行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotationX(T angle)
    {
        // 回転行列
        S_Matrix3x3 rotationMatrix;

        // サインとコサインを求める
        T sine = std::sin(angle);
        T cosine = std::cos(angle);

        // 回転行列を求める
        rotationMatrix.a22_ = cosine;
        rotationMatrix.a23_ = sine;
        rotationMatrix.a32_ = sine * static_cast<T>(-1);
        rotationMatrix.a33_ = cosine;;

        return rotationMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  Y軸から回転行列を作成する
     *  @param  角度( ラジアン値 )
     *  @return 回転行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotationY(T angle)
    {
        // 回転行列
        S_Matrix3x3 rotationMatrix;

        // サインとコサインを求める
        T sine = std::sin(angle);
        T cosine = std::cos(angle);

        // 回転行列を求める
        rotationMatrix.a11_ = cosine;
        rotationMatrix.a13_ = sine * static_cast<T>(-1);
        rotationMatrix.a31_ = sine;
        rotationMatrix.a33_ = cosine;

        return rotationMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  Z軸から回転行列を作成する
     *  @param  角度( ラジアン値 )
     *  @return 回転行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotationZ(T angle)
    {
        // 回転行列
        S_Matrix3x3 rotationMatrix;

        // サインとコサインを求める
        T sine = std::sin(angle);
        T cosine = std::cos(angle);

        // 回転行列を求める
        rotationMatrix.a11_ = cosine;
        rotationMatrix.a12_ = sine;
        rotationMatrix.a21_ = sine * static_cast<T>(-1);
        rotationMatrix.a22_ = cosine;

        return rotationMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  任意軸から回転行列を作成する
     *  @param  角度( ラジアン値 )
     *  @return 回転行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateRotationAxis(const S_Vector3<T>& rAxis, T angle)
    {
        // 回転行列
        S_Matrix3x3 rotationMatrix;

        // サインとコサインを求める
        T sine = std::sin(angle);
        T cosine = std::cos(angle);

        // 1 - cosine の値を求める
        T oneMinusCosine = static_cast<T>(1) - cosine;

        // 軸の各値のサインを求める
        T axisXsine = rAxis.x_ * sine;
        T axisYsine = rAxis.y_ * sine;
        T axisZsine = rAxis.z_ * sine;

        // 軸の成分と 1 - cosine をかけた値を求める
        T oneMinusCosineX = rAxis.x_ * oneMinusCosine;
        T oneMinusCosineY = rAxis.y_ * oneMinusCosine;
        T oneMinusCosineZ = rAxis.z_ * oneMinusCosine;

        // 回転行列を求める
        rotationMatrix.a11_ = (rAxis.x_ * oneMinusCosineX) + cosine;
        rotationMatrix.a21_ = (rAxis.x_ * oneMinusCosineY) - axisZsine;
        rotationMatrix.a31_ = (rAxis.x_ * oneMinusCosineZ) + axisYsine;

        rotationMatrix.a12_ = (rAxis.y_ * oneMinusCosineX) + axisZsine;
        rotationMatrix.a22_ = (rAxis.y_ * oneMinusCosineY) + cosine;
        rotationMatrix.a32_ = (rAxis.y_ * oneMinusCosineZ) - axisXsine;

        rotationMatrix.a13_ = (rAxis.z_ * oneMinusCosineX) - axisYsine;
        rotationMatrix.a23_ = (rAxis.z_ * oneMinusCosineY) + axisXsine;
        rotationMatrix.a33_ = (rAxis.z_ * oneMinusCosineZ) + cosine;

        return rotationMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  拡縮行列を作成する
     *  @param  X方向の拡大率
     *  @param  Y方向の拡大率
     *  @return 拡縮行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateScaling(T rateX, T rateY)
    {
        S_Matrix3x3 scalingMatrix;

        scalingMatrix.a11_ = rateX;
        scalingMatrix.a22_ = rateY;

        return scalingMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  平行移動行列を作成する
     *  @param  X方向の移動量
     *  @param  Y方向の移動量
     *  @return 平行移動行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateTranslation(T movementX, T movementY)
    {
        S_Matrix3x3 toranslationMatrix;

        toranslationMatrix.a31_ = movementX;
        toranslationMatrix.a32_ = movementY;

        return toranslationMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  4 * 4の行列を3 * 3の行列に変換し、取得する
     *  @param  4 * 4の行列
     *  @return 3 * 3の行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_ConvertMatrix4x4ToMatrix3x3(const S_Matrix4x4<T>& rMatrix4)
    {
        // 変換後の行列
        S_Matrix3x3 convertedMatrix;

        // 4 * 4行列を3 * 3に変換
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i)
        {
            size_t shiftIndex = i / 3;
            convertedMatrix.a_[i] = rMatrix4.a_[i + shiftIndex];
        }

        return convertedMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  クォータニオンを3 * 3の行列に変換し、取得する
     *  @param  クォータニオン
     *  @return 3 * 3行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_ConvertQuaternionToMatrix3x3(const S_Quaternion<T>& rQuaternion)
    {
        // 変換後の行列
        S_Matrix3x3 convertionMatrix;

        // 各成分の掛け合わせた値を求める
        T xx = Square(rQuaternion.x_);
        T xy = rQuaternion.x_ * rQuaternion.y_;
        T xz = rQuaternion.x_ * rQuaternion.z_;
        T xt = rQuaternion.x_ * rQuaternion.t_;

        T yy = Square(rQuaternion.y_);
        T yz = rQuaternion.y_ * rQuaternion.z_;
        T yt = rQuaternion.y_ * rQuaternion.t_;

        T zz = Square(rQuaternion.z_);
        T zt = rQuaternion.z_ * rQuaternion.t_;

        // クォータニオンを3 * 3の行列へ変換
        convertionMatrix.a11_ = static_cast<T>(1) - static_cast<T>(2) * (yy + zz);
        convertionMatrix.a12_ = static_cast<T>(2) * (xy + zt);
        convertionMatrix.a13_ = static_cast<T>(2) * (xz - yt);

        convertionMatrix.a21_ = static_cast<T>(2) * (xy - zt);
        convertionMatrix.a22_ = static_cast<T>(1) - static_cast<T>(2) * (xx + zz);
        convertionMatrix.a23_ = static_cast<T>(2) * (yt + xt);

        convertionMatrix.a31_ = static_cast<T>(2) * (xz + yt);
        convertionMatrix.a32_ = static_cast<T>(2) * (yz - xt);
        convertionMatrix.a33_ = static_cast<T>(1) - static_cast<T>(2) * (xx + yy);

        return convertionMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  法線行列を作成する
     *  @param  4 * 4の行列
     *  @return 法線行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateNormal(const S_Matrix4x4<T>& rMatrix)
    {
        S_Matrix3x3 normalMatrix(s_ConvertMatrix4x4ToMatrix3x3(rMatrix));

        normalMatrix.Invert();
        normalMatrix.Transpose();

        return normalMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  ビュー行列を作成する
     *  @param  視点
     *  @param  注視点
     *  @param  上方向
     *  @return 法線行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T> S_Matrix3x3<T>::s_CreateLookAt(const S_Vector3<T>& rEyePoint,
                                                  const S_Vector3<T>& rTargetPoint,
                                                  const S_Vector3<T>& rUpVector)
    {
        // ビュー行列
        S_Matrix3x3 viewMatrix;

        // Z軸を求める
        S_Vector3<T> zAxis = rTargetPoint - rEyePoint;
        zAxis.Normalize();

        // X軸を求める
        S_Vector3<T> xAxis = S_Vector3<T>::s_CrossProduct(zAxis, rUpVector);
        xAxis.Normalize();

        // Y軸を求める
        S_Vector3<T> yAxis = S_Vector3<T>::s_CrossProduct(xAxis, zAxis);
        yAxis.Normalize();

        // 視点を反転したベクトル
        S_Vector3<T> inversionEyeVector(rEyePoint.GetInvert());

        // Z軸を反転する
        zAxis.Invert();

        // ビュー行列を求める
        viewMatrix.a11_ = xAxis.x_;
        viewMatrix.a21_ = xAxis.y_;
        viewMatrix.a31_ = xAxis.z_;

        viewMatrix.a12_ = yAxis.x_;
        viewMatrix.a22_ = yAxis.y_;
        viewMatrix.a32_ = yAxis.z_;

        viewMatrix.a13_ = zAxis.x_;
        viewMatrix.a23_ = zAxis.y_;
        viewMatrix.a33_ = zAxis.z_;

        return viewMatrix;
    }


#pragma region S_Matrix3x3型との演算子のオーバーロード


    /*************************************************************//**
     *
     *  @brief  もう一つの行列を加算した行列を求める
     *  @param  もう一つの行列
     *  @return 加算した行列
     *
     ****************************************************************/
    template<typename T>
    const S_Matrix3x3<T> S_Matrix3x3<T>::operator+(const S_Matrix3x3<T>& rAnother) const
    {
        S_Matrix3x3 tempMatrix;
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i) tempMatrix.a_[i] = a_[i] + rAnother.a_[i];

        return tempMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  もう一つの行列で減算した行列を求める
     *  @param  もう一つの行列
     *  @return 減算した行列
     *
     ****************************************************************/
    template<typename T>
    const S_Matrix3x3<T> S_Matrix3x3<T>::operator-(const S_Matrix3x3<T>& rAnother) const
    {
        S_Matrix3x3 tempMatrix;
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i) tempMatrix.a_[i] = a_[i] - rAnother.a_[i];

        return tempMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  もう一つの行列を乗算した行列を求める
     *  @param  もう一つの行列
     *  @return 乗算した行列
     *
     ****************************************************************/
    template<typename T>
    const S_Matrix3x3<T> S_Matrix3x3<T>::operator*(const S_Matrix3x3<T>& rAnother) const
    {
        // 仮の行列
        S_Matrix3x3 tempMatrix;

        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i)
        {
            // 各行列の添え字を求める
            size_t index = i % 3;
            size_t anotherIndex = (i / 3) * 3;

            // 行列同士の乗算
            tempMatrix.a_[i] = a_[index] * rAnother.a_[anotherIndex]
                             + a_[index + 3] * rAnother.a_[anotherIndex + 1]
                             + a_[index + 6] * rAnother.a_[anotherIndex + 2];
        }

        return tempMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  もう一つの行列を加算する
     *  @param  もう一つの行列
     *  @return 加算後の行列( 自分自身 )
     *
     ****************************************************************/
    template<typename T>
    const S_Matrix3x3<T>& S_Matrix3x3<T>::operator+=(const S_Matrix3x3<T>& rAnother)
    {
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i) a_[i] += rAnother.a_[i];

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  もう一つの行列で減算する
     *  @param  もう一つの行列
     *  @return 減算後の行列( 自分自身 )
     *
     ****************************************************************/
    template<typename T>
    const S_Matrix3x3<T>& S_Matrix3x3<T>::operator-=(const S_Matrix3x3<T>& rAnother)
    {
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i) a_[i] -= rAnother.a_[i];

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  もう一つの行列を乗算する
     *  @param  もう一つの行列
     *  @return 乗算後の行列( 自分自身 )
     *
     ****************************************************************/
    template<typename T>
    const S_Matrix3x3<T>& S_Matrix3x3<T>::operator*=(const S_Matrix3x3<T>& rAnother)
    {
        // 仮の行列
        S_Matrix3x3 tempMatrix;

        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i)
        {
            // 各行列の添え字を求める
            size_t index = i % 3;
            size_t anotherIndex = (i / 3) * 3;

            // 行列同士の乗算
            tempMatrix.a_[i] = a_[index] * rAnother.a_[anotherIndex]
                             + a_[index + 3] * rAnother.a_[anotherIndex + 1]
                             + a_[index + 6] * rAnother.a_[anotherIndex + 2];
        }

        // 仮の行列を代入
        (*this) = tempMatrix;

        return (*this);
    }


    /*************************************************************//**
     *
     *  @brief  もう一つの行列と比較する
     *  @param  もう一つの行列
     *  @return 同じ行列の場合：true
     *  @return 違う行列の場合：false
     *
     ****************************************************************/
    template<typename T>
    bool S_Matrix3x3<T>::operator==(const S_Matrix3x3<T>& rAnother) const
    {
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i)
        {
            if (std::abs(a_[i] - rAnother.a_[i]) > static_cast<T>(s_EPSILON)) return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  もう一つの行列と比較する
     *  @param  もう一つの行列
     *  @return 違う行列の場合：true
     *  @return 同じ行列の場合：false
     *
     ****************************************************************/
    template<typename T>
    bool S_Matrix3x3<T>::operator!=(const S_Matrix3x3<T>& rAnother) const
    {
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i)
        {
            if (std::abs(a_[i] - rAnother.a_[i]) > static_cast<T>(s_EPSILON)) return true;
        }

        return false;
    }


#pragma endregion


#pragma region S_Vector3型との演算子のオーバーロード


    /*************************************************************//**
     *
     *  @brief  ベクトルと乗算した値を求める
     *  @param  3Dベクトル
     *  @return 乗算したベクトル
     *
     ****************************************************************/
    template<typename T>
    const S_Vector3<T> S_Matrix3x3<T>::operator*(const S_Vector3<T>& rVector) const
    {
        S_Vector3<T> tempVector;

        tempVector.x_ = a11_ * rVector.x_
                      + a21_ * rVector.y_
                      + a31_ * rVector.z_;

        tempVector.y_ = a12_ * rVector.x_
                      + a22_ * rVector.y_
                      + a32_ * rVector.z_;

        tempVector.z_ = a13_ * rVector.x_
                      + a23_ * rVector.y_
                      + a33_ * rVector.z_;

        return tempVector;
    }


#pragma endregion


#pragma region キャスト演算子のオーバーロード


    /*************************************************************//**
     *
     *  @brief  string型へキャストする
     *  @param  なし
     *  @return 文字列に変換した行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix3x3<T>::operator std::string() const
    {
        return GetConvertToString();
    }


#pragma endregion


    /* 明示的インスタンス化 */
    template struct S_Matrix3x3<float>;
    template struct S_Matrix3x3<double>;


    /*************************************************************//**
     *
     *  @brief  行列式を取得する
     *  @param  行列
     *  @return 行列式
     *
     ****************************************************************/
    template<typename T>
    static T s_GetDeterminant(const S_Matrix3x3<T>& rMatrix)
    {
        return (rMatrix.a11_ * rMatrix.a22_ * rMatrix.a33_)
             + (rMatrix.a21_ * rMatrix.a32_ * rMatrix.a13_)
             + (rMatrix.a31_ * rMatrix.a12_ * rMatrix.a23_)
             - (rMatrix.a11_ * rMatrix.a32_ * rMatrix.a23_)
             - (rMatrix.a31_ * rMatrix.a22_ * rMatrix.a13_)
             - (rMatrix.a21_ * rMatrix.a12_ * rMatrix.a33_);
    }

}