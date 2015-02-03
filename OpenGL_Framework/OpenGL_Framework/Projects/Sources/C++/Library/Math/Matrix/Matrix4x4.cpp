/* ヘッダファイル */
#include "Matrix4x4.h"
#include "Matrix3x3.h"
#include "../Vector/Vector3.h"
#include "../Vector/Vector4.h"
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
    static T s_GetDeterminant(const S_Matrix4x4<T>& rMatrix);
    
    
#pragma region 静的メンバ変数の初期化
    
    
    template<typename T>
    const T S_Matrix4x4<T>::s_ORTHOGRAPHIC_2D_NEAR = static_cast<T>(-1);
    
    
    template<typename T>
    const T S_Matrix4x4<T>::s_ORTHOGRAPHIC_2D_FAR = static_cast<T>(1);
    
    
    template<typename T>
    const S_Matrix4x4<T> S_Matrix4x4<T>::s_ZERO(static_cast<T>(0));
    
    
    template<typename T>
    const S_Matrix4x4<T> S_Matrix4x4<T>::s_IDENTITY;
    
    
#pragma endregion
    
    
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T>::S_Matrix4x4() : 
    
        // 16個の要素
        a11_(static_cast<T>(1)),
        a12_(static_cast<T>(0)),
        a13_(static_cast<T>(0)),
        a14_(static_cast<T>(0)),
    
        a21_(static_cast<T>(0)),
        a22_(static_cast<T>(1)),
        a23_(static_cast<T>(0)),
        a24_(static_cast<T>(0)),
    
        a31_(static_cast<T>(0)),
        a32_(static_cast<T>(0)),
        a33_(static_cast<T>(1)),
        a34_(static_cast<T>(0)),
    
        a41_(static_cast<T>(0)),
        a42_(static_cast<T>(0)),
        a43_(static_cast<T>(0)),
        a44_(static_cast<T>(1))
    
    {
    }
    
    
    /*************************************************************//**
     *
     *  @brief  コンストラクタ( 各要素を指定した1つの値で初期化 )
     *  @param  値
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T>::S_Matrix4x4(T value) : S_Matrix4x4(value, value, value, value, 
                                                       value, value, value, value,
                                                       value, value, value, value,
                                                       value, value, value, value)
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
     *  @param  要素10
     *  @param  要素11
     *  @param  要素12
     *  @param  要素13
     *  @param  要素14
     *  @param  要素15
     *  @param  要素16
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T>::S_Matrix4x4(T a11, T a12, T a13, T a14,
                                T a21, T a22, T a23, T a24,
                                T a31, T a32, T a33, T a34,
                                T a41, T a42, T a43, T a44) :
    
        // 16個の要素
        a11_(a11),
        a12_(a12),
        a13_(a13),
        a14_(a14),
    
        a21_(a21),
        a22_(a22),
        a23_(a23),
        a24_(a24),
    
        a31_(a31),
        a32_(a32),
        a33_(a33),
        a34_(a34),
    
        a41_(a41),
        a42_(a42),
        a43_(a43),
        a44_(a44)
    
    {
    }
    
    
    /*************************************************************//**
     *
     *  @brief  コンストラクタ( 指定した配列で要素の初期化 )
     *  @param  要素が16個の配列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T>::S_Matrix4x4(const T a[s_ELEMENT_NUMBER])
    {
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i) a_[i] = a[i];
    }
    
    
    /*************************************************************//**
     *
     *  @brief  コンストラクタ( 3 * 3行列で要素の初期化 )
     *  @param  3 * 3行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T>::S_Matrix4x4(const S_Matrix3x3<T>& rMatrix)
    {
        *this = s_ConvertMatrix3x3ToMatrix4x4(rMatrix);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T>::~S_Matrix4x4()
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
    void S_Matrix4x4<T>::Zero()
    {
        for (auto& a : a_) a = static_cast<T>(0);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  単位行列化する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix4x4<T>::Identity()
    {
        a11_ = static_cast<T>(1);
        a12_ = static_cast<T>(0);
        a13_ = static_cast<T>(0);
        a14_ = static_cast<T>(0);
    
        a21_ = static_cast<T>(0);
        a22_ = static_cast<T>(1);
        a23_ = static_cast<T>(0);
        a24_ = static_cast<T>(0);
    
        a31_ = static_cast<T>(0);
        a32_ = static_cast<T>(0);
        a33_ = static_cast<T>(1);
        a34_ = static_cast<T>(0);
    
        a41_ = static_cast<T>(0);
        a42_ = static_cast<T>(0);
        a43_ = static_cast<T>(0);
        a44_ = static_cast<T>(1);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  転置行列化する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix4x4<T>::Transpose()
    {
        std::swap(a12_, a21_);
        std::swap(a13_, a31_);
        std::swap(a14_, a41_);
        std::swap(a23_, a32_);
        std::swap(a24_, a42_);
        std::swap(a34_, a43_);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  逆行列化する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    template<typename T>
    void S_Matrix4x4<T>::Invert()
    {
        // 行列式を取得
        T determinant = s_GetDeterminant(*this);
    
        if (determinant == static_cast<T>(0)) return;
    
        // 逆行列
        S_Matrix4x4 inverseMatrix;
    
        // 行列式の逆数
        T reciprocalDeterminant = static_cast<T>(1) / determinant;
    
        // 逆行列を求める
        inverseMatrix.a11_ = ((a22_ * a33_ * a44_) + (a23_ * a34_ * a42_) + (a24_ * a32_ * a43_)
                            - (a22_ * a34_ * a43_) - (a23_ * a32_ * a44_) - (a24_ * a33_ * a42_)) * reciprocalDeterminant;
    
        inverseMatrix.a12_ = ((a12_ * a34_ * a43_) + (a13_ * a32_ * a44_) + (a14_ * a33_ * a42_)
                            - (a12_ * a33_ * a44_) - (a13_ * a34_ * a42_) - (a14_ * a32_ * a43_)) * reciprocalDeterminant;
    
        inverseMatrix.a13_ = ((a12_ * a23_ * a44_) + (a13_ * a24_ * a42_) + (a14_ * a22_ * a43_)
                            - (a12_ * a24_ * a43_) - (a13_ * a22_ * a44_) - (a14_ * a23_ * a42_)) * reciprocalDeterminant;
    
        inverseMatrix.a14_ = ((a12_ * a24_ * a33_) + (a13_ * a22_ * a34_) + (a14_ * a23_ * a32_)
                            - (a12_ * a23_ * a34_) - (a13_ * a24_ * a32_) - (a14_ * a22_ * a33_)) * reciprocalDeterminant;
    
        inverseMatrix.a21_ = ((a21_ * a34_ * a43_) + (a23_ * a31_ * a44_) + (a24_ * a33_ * a41_)
                            - (a21_ * a33_ * a44_) - (a23_ * a34_ * a41_) - (a24_ * a31_ * a43_)) * reciprocalDeterminant;
    
        inverseMatrix.a22_ = ((a11_ * a33_ * a44_) + (a13_ * a34_ * a41_) + (a14_ * a31_ * a43_)
                            - (a11_ * a34_ * a43_) - (a13_ * a31_ * a44_) - (a14_ * a33_ * a41_)) * reciprocalDeterminant;
    
        inverseMatrix.a23_ = ((a11_ * a24_ * a43_) + (a13_ * a21_ * a44_) + (a14_ * a23_ * a41_)
                            - (a11_ * a23_ * a44_) - (a13_ * a24_ * a41_) - (a14_ * a21_ * a43_)) * reciprocalDeterminant;
    
        inverseMatrix.a24_ = ((a11_ * a23_ * a34_) + (a13_ * a24_ * a31_) + (a14_ * a21_ * a33_)
                            - (a11_ * a24_ * a33_) - (a13_ * a21_ * a34_) - (a14_ * a23_ * a31_)) * reciprocalDeterminant;
    
        inverseMatrix.a31_ = ((a21_ * a32_ * a44_) + (a22_ * a34_ * a41_) + (a24_ * a31_ * a42_)
                            - (a21_ * a34_ * a42_) - (a22_ * a31_ * a44_) - (a24_ * a32_ * a41_)) * reciprocalDeterminant;
    
        inverseMatrix.a32_ = ((a11_ * a34_ * a42_) + (a12_ * a31_ * a44_) + (a14_ * a32_ * a41_)
                            - (a11_ * a32_ * a44_) - (a12_ * a34_ * a41_) - (a14_ * a31_ * a42_)) * reciprocalDeterminant;
    
        inverseMatrix.a33_ = ((a11_ * a22_ * a44_) + (a12_ * a24_ * a41_) + (a14_ * a21_ * a42_)
                            - (a11_ * a24_ * a42_) - (a12_ * a21_ * a44_) - (a14_ * a22_ * a41_)) * reciprocalDeterminant;
    
        inverseMatrix.a34_ = ((a11_ * a24_ * a32_) + (a12_ * a21_ * a34_) + (a14_ * a22_ * a31_)
                            - (a11_ * a22_ * a34_) - (a12_ * a24_ * a31_) - (a14_ * a21_ * a32_)) * reciprocalDeterminant;
    
        inverseMatrix.a41_ = ((a21_ * a33_ * a42_) + (a22_ * a31_ * a43_) + (a23_ * a32_ * a41_)
                            - (a21_ * a32_ * a43_) - (a22_ * a33_ * a41_) - (a23_ * a31_ * a42_)) * reciprocalDeterminant;
    
        inverseMatrix.a42_ = ((a11_ * a32_ * a43_) + (a12_ * a33_ * a41_) + (a13_ * a31_ * a42_)
                            - (a11_ * a33_ * a42_) - (a12_ * a31_ * a43_) - (a13_ * a32_ * a41_)) * reciprocalDeterminant;
    
        inverseMatrix.a43_ = ((a11_ * a23_ * a42_) + (a12_ * a21_ * a43_) + (a13_ * a22_ * a41_)
                            - (a11_ * a22_ * a43_) - (a12_ * a23_ * a41_) - (a13_ * a21_ * a42_)) * reciprocalDeterminant;
    
        inverseMatrix.a44_ = ((a11_ * a22_ * a33_) + (a12_ * a23_ * a31_) + (a13_ * a21_ * a32_)
                            - (a11_ * a23_ * a32_) - (a12_ * a21_ * a33_) - (a13_ * a22_ * a31_)) * reciprocalDeterminant;
       
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
    S_Matrix4x4<T> S_Matrix4x4<T>::GetTranspose() const
    {
        S_Matrix4x4 transposeMatrix(*this);
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
    S_Matrix4x4<T> S_Matrix4x4<T>::GetInvert() const
    {
        S_Matrix4x4 inverseMatrix(*this);
        inverseMatrix.Invert();
    
        return inverseMatrix;
    }


    /*************************************************************//**
     *
     *  @brief  移動量( 平行移動成分 )を取得する
     *  @param  なし
     *  @return 移動量
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Matrix4x4<T>::GetTranslationComponent() const
    {
        return S_Vector3<T>(a41_, a42_, a43_);
    }


    /*************************************************************//**
     *
     *  @brief  拡縮率( 拡縮成分 )を取得する
     *  @param  なし
     *  @return 拡縮率
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Matrix4x4<T>::GetScalingComponent() const
    {
        S_Vector3<T> scalingComponent;

        scalingComponent.x_ = S_Vector3<T>(a11_, a12_, a13_).GetLength();
        scalingComponent.y_ = S_Vector3<T>(a21_, a22_, a23_).GetLength();
        scalingComponent.z_ = S_Vector3<T>(a31_, a32_, a33_).GetLength();

        return scalingComponent;
    }


    /*************************************************************//**
     *
     *  @brief  ローカル座標のX軸を取得する
     *  @param  なし
     *  @return ローカル座標のX軸
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Matrix4x4<T>::GetLocalAxisX() const
    {
        return S_Vector3<T>(a11_, a12_, a13_).GetNormalize();
    }


    /*************************************************************//**
     *
     *  @brief  ローカル座標のY軸を取得する
     *  @param  なし
     *  @return ローカル座標のY軸
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Matrix4x4<T>::GetLocalAxisY() const
    {
        return S_Vector3<T>(a21_, a22_, a23_).GetNormalize();
    }


    /*************************************************************//**
     *
     *  @brief  ローカル座標のZ軸を取得する
     *  @param  なし
     *  @return ローカル座標のZ軸
     *
     ****************************************************************/
    template<typename T>
    S_Vector3<T> S_Matrix4x4<T>::GetLocalAxisZ() const
    {
        return S_Vector3<T>(a31_, a32_, a33_).GetNormalize();
    }
    
    
    /*************************************************************//**
     *
     *  @brief  行を取得する
     *  @param  添え字
     *  @return 行
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T> S_Matrix4x4<T>::GetRow(int32_t index) const
    {
        assert(index >= 0 && index < 4);
        return S_Vector4<T>(a_[index], a_[index + 4], a_[index + 8], a_[index + 12]);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  列を取得する
     *  @param  添え字
     *  @return 列
     *
     ****************************************************************/
    template<typename T>
    S_Vector4<T> S_Matrix4x4<T>::GetColumn(int32_t index) const
    {
        assert(index >= 0 && index < 4);
    
        index *= 4;
        return S_Vector4<T>(a_[index], a_[index + 1], a_[index + 2], a_[index + 3]);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  行列を文字列に変換して取得する
     *  @param  なし
     *  @return 文字列に変換した行列
     *
     ****************************************************************/
    template<typename T>
    std::string S_Matrix4x4<T>::GetConvertToString() const
    {
        return "|" + std::to_string(a11_) + ", " + std::to_string(a21_) + ", " + std::to_string(a31_) + ", " + std::to_string(a41_) + "|\n"
             + "|" + std::to_string(a12_) + ", " + std::to_string(a22_) + ", " + std::to_string(a32_) + ", " + std::to_string(a42_) + "|\n"
             + "|" + std::to_string(a13_) + ", " + std::to_string(a23_) + ", " + std::to_string(a33_) + ", " + std::to_string(a43_) + "|\n"
             + "|" + std::to_string(a14_) + ", " + std::to_string(a24_) + ", " + std::to_string(a34_) + ", " + std::to_string(a44_) + "|";
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
    void S_Matrix4x4<T>::SetRow(const S_Vector4<T>& rRow, int32_t index)
    {
        assert(index >= 0 && index < 4);
    
        for (int32_t i = 0; i < 4; ++i) a_[index + i * 4] = rRow.a_[i];
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
    void S_Matrix4x4<T>::SetColumn(const S_Vector4<T>& rColumn, int32_t index)
    {
        assert(index >= 0 && index < 4);
    
        for (int32_t i = 0; i < 4; ++i) a_[index + i] = rColumn.a_[i];
    }
    
    
    /*************************************************************//**
     *
     *  @brief  X軸から回転行列を作成する
     *  @param  角度( ラジアン値 )
     *  @return 回転行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationX(T angle)
    {
        S_Matrix4x4 rotationMatrix;
    
        T sine = std::sin(angle);
        T cosine = std::cos(angle);
    
        rotationMatrix.a22_ = cosine;
        rotationMatrix.a23_ = sine;
        rotationMatrix.a32_ = sine * static_cast<T>(-1);
        rotationMatrix.a33_ = cosine;
    
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
    S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationY(T angle)
    {
        S_Matrix4x4 rotationMatrix;
    
        T sine = std::sin(angle);
        T cosine = std::cos(angle);
    
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
    S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationZ(T angle)
    {
        S_Matrix4x4 rotationMatrix;
    
        T sine = std::sin(angle);
        T cosine = std::cos(angle);
    
        rotationMatrix.a11_ = cosine;
        rotationMatrix.a12_ = sine;
        rotationMatrix.a21_ = sine * static_cast<T>(-1);
        rotationMatrix.a22_ = cosine;
    
        return rotationMatrix;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  任意軸から回転行列を作成する
     *  @param  軸
     *  @param  角度( ラジアン値 )
     *  @return 回転行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationAxis(const S_Vector3<T>& rAxis, T angle)
    {
        // 回転行列
        S_Matrix4x4 rotationMatrix;
    
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
     *  @brief  3軸の回転行列を掛け合わせた行列を作成する
     *  @param  ピッチ( X軸の角度・ラジアン値 )
     *  @param  ヨー( Y軸の角度・ラジアン値 )
     *  @param  ロール( Z軸の角度・ラジアン値 )
     *  @return 回転行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationYawPitchRoll(T pitch,
                                                                T yaw,
                                                                T roll)
    {
        S_Quaternion<T> rotationQuaternion = S_Quaternion<T>::s_CreateRotationPitchYawRoll(pitch, yaw, roll);
        return s_ConvertQuaternionToMatrix4x4(rotationQuaternion);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  3軸の回転行列を掛け合わせた行列を作成する
     *  @param  ピッチ( X軸の角度・ラジアン値 )
     *  @param  ヨー( Y軸の角度・ラジアン値 )
     *  @param  ロール( Z軸の角度・ラジアン値 )
     *  @return 回転行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateRotationYawPitchRoll(const S_Vector3<T>& rRotation)
    {
        S_Quaternion<T> rotationQuaternion = S_Quaternion<T>::s_CreateRotationPitchYawRoll(rRotation);
        return s_ConvertQuaternionToMatrix4x4(rotationQuaternion);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  拡縮行列を作成する
     *  @param  X方向の拡縮率
     *  @param  Y方向の拡縮率
     *  @param  Z方向の拡縮率
     *  @return 拡縮行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateScaling(T scalingRateX, T scalingRateY, T scalingRateZ)
    {
        S_Matrix4x4 scalingMatrix;
    
        scalingMatrix.a11_ = scalingRateX;
        scalingMatrix.a22_ = scalingRateY;
        scalingMatrix.a33_ = scalingRateZ;
    
        return scalingMatrix;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  拡縮行列を作成する
     *  @param  3方向の拡縮率
     *  @return 拡縮行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateScaling(const S_Vector3<T>& rScalingRate)
    {
        return s_CreateScaling(rScalingRate.x_, rScalingRate.y_, rScalingRate.z_);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  平行移動行列を作成する
     *  @param  X方向の移動量
     *  @param  Y方向の移動量
     *  @param  Z方向の移動量
     *  @return 平行移動行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateTranslation(T movementX, T movementY, T movementZ)
    {
        S_Matrix4x4 translationMatrix;
    
        translationMatrix.a41_ = movementX;
        translationMatrix.a42_ = movementY;
        translationMatrix.a43_ = movementZ;
    
        return translationMatrix;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  平行移動行列を作成する
     *  @param  3方向の移動量
     *  @return 平行移動行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateTranslation(const S_Vector3<T>& rMovement)
    {
        return s_CreateTranslation(rMovement.x_, rMovement.y_, rMovement.z_);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  拡縮・回転・平行移動を掛け合わせた行列を作成
     *  @param  3方向の移動量
     *  @param  3方向の回転量
     *  @param  3方向の拡縮率
     *  @return アフィン変換行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateTRS(const S_Vector3<T>& rMovement, 
                                               const S_Vector3<T>& rRotation, 
                                               const S_Vector3<T>& rScalingRate)
    {
        S_Matrix4x4 TRSMatrix = s_CreateRotationYawPitchRoll(rRotation);

        TRSMatrix.a11_ *= rScalingRate.x_;
        TRSMatrix.a12_ *= rScalingRate.x_;
        TRSMatrix.a13_ *= rScalingRate.x_;

        TRSMatrix.a21_ *= rScalingRate.y_;
        TRSMatrix.a22_ *= rScalingRate.y_;
        TRSMatrix.a23_ *= rScalingRate.y_;

        TRSMatrix.a31_ *= rScalingRate.z_;
        TRSMatrix.a32_ *= rScalingRate.z_;
        TRSMatrix.a33_ *= rScalingRate.z_;
    
        TRSMatrix.a41_ = rMovement.x_;
        TRSMatrix.a42_ = rMovement.y_;
        TRSMatrix.a43_ = rMovement.z_;
    
        return TRSMatrix;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  ビュー行列を作成する
     *  @param  視点
     *  @param  注視点
     *  @param  上方向を示すベクトル
     *  @return ビュー行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateLookAt(const S_Vector3<T>& rEyePoint,
                                                  const S_Vector3<T>& rTargetPoint,
                                                  const S_Vector3<T>& rUpVector)
    {
        // ビュー行列
        S_Matrix4x4 viewMatrix;
    
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
        viewMatrix.a41_ = S_Vector3<T>::s_DotProduct(xAxis, inversionEyeVector);
    
        viewMatrix.a12_ = yAxis.x_;
        viewMatrix.a22_ = yAxis.y_;
        viewMatrix.a32_ = yAxis.z_;
        viewMatrix.a42_ = S_Vector3<T>::s_DotProduct(yAxis, inversionEyeVector);
      
        viewMatrix.a13_ = zAxis.x_;
        viewMatrix.a23_ = zAxis.y_;
        viewMatrix.a33_ = zAxis.z_;
        viewMatrix.a43_ = S_Vector3<T>::s_DotProduct(zAxis, inversionEyeVector);
    
        return viewMatrix;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  透視投影の射影行列を作成する
     *  @param  視野の垂直方向の画角( ラジアン値 )
     *  @param  アスペクト比
     *  @param  視点から最も近いクリップ面( 距離 )
     *  @param  視点から最も遠いクリップ面( 距離 )
     *  @return 透視投影の射影行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T> S_Matrix4x4<T>::s_CreatePerspectiveProjection(T fieldOfViewY,
                                                                 T aspectRatio,
                                                                 T nearClippingPlane,
                                                                 T farClippingPlane)
    {
        assert(fieldOfViewY != static_cast<T>(0));
        assert(aspectRatio > static_cast<T>(0));
        assert(farClippingPlane != nearClippingPlane);
    
        // 透視投影の射影行列
        S_Matrix4x4 perspectiveProjectionMatrix;
    
        // 視野の垂直方向の画角の半分を求める
        T halfFieldOfViewY = fieldOfViewY * static_cast<T>(0.5);
    
        // ファークリッピングプレーンとニアクリッピングプレーンの差分を求める
        T planeDifference = nearClippingPlane - farClippingPlane;
    
        // 視野の垂直方向の画角の半分の余弦を求める
        T cotHalfFovY = Cotangent(halfFieldOfViewY);
    
        // 透視投影の射影行列を求める
        perspectiveProjectionMatrix.a11_ = cotHalfFovY / aspectRatio;
        perspectiveProjectionMatrix.a22_ = cotHalfFovY;
        perspectiveProjectionMatrix.a33_ = (farClippingPlane + nearClippingPlane) / planeDifference;
        perspectiveProjectionMatrix.a34_ = static_cast<T>(-1);
        perspectiveProjectionMatrix.a43_ = static_cast<T>(2) * nearClippingPlane * farClippingPlane / planeDifference;
    
        return perspectiveProjectionMatrix;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  正投影の射影行列を作成する
     *  @param  クリップ空間の左側
     *  @param  クリップ空間の右側
     *  @param  クリップ空間の下側
     *  @param  クリップ空間の上側
     *  @param  視点から最も近いクリップ面( 距離 )
     *  @param  視点から最も遠いクリップ面( 距離 )
     *  @return 正投影の射影行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateOrthographicProjection(T clipSpaceLeft,             
                                                                  T clipSpaceRight,
                                                                  T clipSpaceBottom,
                                                                  T clipSpaceTop,
                                                                  T nearClippingPlane,
                                                                  T farClippingPlane)
    {                                                                            
        assert(clipSpaceRight != clipSpaceLeft);
        assert(clipSpaceTop != clipSpaceBottom);
        assert(nearClippingPlane != farClippingPlane);
    
        // 正投影の射影行列
        S_Matrix4x4 orthographicProjectionMatrix;
    
        // クリップ空間の幅と高さと奥行を求める
        T clipSpaceWidth = clipSpaceRight - clipSpaceLeft;
        T clipSpaceHeight = clipSpaceTop - clipSpaceBottom;
        T clipSpaceDepth = farClippingPlane - nearClippingPlane;
    
        // 正投影の射影行列を求める
        orthographicProjectionMatrix.a11_ = static_cast<T>(2) / clipSpaceWidth;
        orthographicProjectionMatrix.a22_ = static_cast<T>(2) / clipSpaceHeight;
        orthographicProjectionMatrix.a33_ = static_cast<T>(-2) / clipSpaceDepth;
    
        orthographicProjectionMatrix.a41_ = -((clipSpaceRight + clipSpaceLeft) / clipSpaceWidth);
        orthographicProjectionMatrix.a42_ = -((clipSpaceTop + clipSpaceBottom) / clipSpaceHeight);
        orthographicProjectionMatrix.a43_ = -((farClippingPlane + nearClippingPlane) / clipSpaceDepth);
    
        return orthographicProjectionMatrix;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  3 * 3行列を4 * 4の行列に変換し、取得する
     *  @param  3 * 3行列
     *  @return 4 * 4行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T> S_Matrix4x4<T>::s_ConvertMatrix3x3ToMatrix4x4(const S_Matrix3x3<T>& rMatrix)
    {
        S_Matrix4x4 convertionMatrix;
    
        convertionMatrix.a11_ = rMatrix.a11_;
        convertionMatrix.a12_ = rMatrix.a12_;
        convertionMatrix.a13_ = rMatrix.a13_;
    
        convertionMatrix.a21_ = rMatrix.a21_;
        convertionMatrix.a22_ = rMatrix.a22_;
        convertionMatrix.a23_ = rMatrix.a23_;
    
        convertionMatrix.a31_ = rMatrix.a31_;
        convertionMatrix.a32_ = rMatrix.a32_;
        convertionMatrix.a33_ = rMatrix.a33_;
    
        return convertionMatrix;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  クォータニオンを4 * 4の行列に変換し、取得する
     *  @param  クォータニオン
     *  @return 4 * 4行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T> S_Matrix4x4<T>::s_ConvertQuaternionToMatrix4x4(const S_Quaternion<T>& rQuaternion)
    {
        // 変換後の行列
        S_Matrix4x4 convertionMatrix;
    
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
    
        // クォータニオンを4 * 4の行列へ変換
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
     *  @brief  ビューポート行列を作成する
     *  @param  ウィンドウの幅
     *  @param  ウィンドウの高さ
     *  @return ビューポート行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T> S_Matrix4x4<T>::s_CreateViewport(T windowWidth, T windowHeight)
    {
        // ウィンドウの幅と高さの半分
        T halfWidth = windowWidth * static_cast<T>(0.5);
        T halfHeight = windowHeight * static_cast<T>(0.5);
    
        // ビューポート行列
        S_Matrix4x4<T> viewportMatrix(halfWidth,         static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
                                      static_cast<T>(0), halfHeight,        static_cast<T>(0), static_cast<T>(0),
                                      static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
                                      halfWidth,         halfHeight,        static_cast<T>(0), static_cast<T>(1));
    
        return viewportMatrix;
    }
    
    
    /*************************************************************//**
     *
     *  @brief  回転行列を球面線形補間する
     *  @param  開始時の回転行列
     *  @param  終了時の回転行列
     *  @param  補間係数
     *  @return 球面線形補間した回転行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T> S_Matrix4x4<T>::s_SlerpRotation(const S_Matrix4x4& rStartMatrix,
                                                   const S_Matrix4x4& rEndMatix,
                                                   T coefficient)
    {
        // 回転行列からクォータニオンを作成
        S_Quaternion<T> startQuaternion = S_Quaternion<T>::s_ConvertMatrix4x4ToQuaternion(rStartMatrix);
        S_Quaternion<T> endQuaternion = S_Quaternion<T>::s_ConvertMatrix4x4ToQuaternion(rEndMatix);
    
        // クォータニオンを球面線形補間する
        S_Quaternion<T> slerpQuaternion = S_Quaternion<T>::s_Slerp(startQuaternion, endQuaternion, coefficient);
    
        // クォータニオンを行列へ変換
        S_Matrix4x4 slerpMatrix = s_ConvertQuaternionToMatrix4x4(slerpQuaternion);
    
        return slerpMatrix;
    }
    
    
#pragma region S_Matrix4x4型との演算子のオーバーロード
    
    
    /*************************************************************//**
     *
     *  @brief  もう一つの行列を加算した行列を求める
     *  @param  もう一つの行列
     *  @return 加算した行列
     *
     ****************************************************************/
    template<typename T>
    const S_Matrix4x4<T> S_Matrix4x4<T>::operator+(const S_Matrix4x4<T>& rAnother) const
    {
        S_Matrix4x4 tempMatrix;
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
    const S_Matrix4x4<T> S_Matrix4x4<T>::operator-(const S_Matrix4x4<T>& rAnother) const
    {
        S_Matrix4x4 tempMatrix;
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
    const S_Matrix4x4<T> S_Matrix4x4<T>::operator*(const S_Matrix4x4<T>& rAnother) const
    {
        S_Matrix4x4 tempMatrix;
    
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i)
        {
            // 各行列の添え字を求める
            size_t index = i % 4;
            size_t anotherIndex = (i / 4) * 4;
    
            // 行列同士の乗算
            tempMatrix.a_[i] = a_[index]      * rAnother.a_[anotherIndex]
                             + a_[index + 4]  * rAnother.a_[anotherIndex + 1]
                             + a_[index + 8]  * rAnother.a_[anotherIndex + 2]
                             + a_[index + 12] * rAnother.a_[anotherIndex + 3];
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
    const S_Matrix4x4<T>& S_Matrix4x4<T>::operator+=(const S_Matrix4x4<T>& rAnother)
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
    const S_Matrix4x4<T>& S_Matrix4x4<T>::operator-=(const S_Matrix4x4<T>& rAnother)
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
    const S_Matrix4x4<T>& S_Matrix4x4<T>::operator*=(const S_Matrix4x4<T>& rAnother)
    {
        S_Matrix4x4 tempMatrix;
    
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i)
        {
            // 各行列の添え字を求める
            size_t index = i % 4;
            size_t anotherIndex = (i / 4) * 4;
    
            // 行列同士の乗算
            tempMatrix.a_[i] = a_[index]      * rAnother.a_[anotherIndex]
                             + a_[index +  4] * rAnother.a_[anotherIndex + 1]
                             + a_[index +  8] * rAnother.a_[anotherIndex + 2]
                             + a_[index + 12] * rAnother.a_[anotherIndex + 3];
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
    bool S_Matrix4x4<T>::operator==(const S_Matrix4x4<T>& rAnother) const
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
    bool S_Matrix4x4<T>::operator!=(const S_Matrix4x4<T>& rAnother) const
    {
        for (size_t i = 0; i < s_ELEMENT_NUMBER; ++i)
        {
            if (std::abs(a_[i] - rAnother.a_[i]) > static_cast<T>(s_EPSILON)) return true;
        }
    
        return false;
    }
    
    
    
#pragma endregion
    
    
#pragma region S_Vector4演算子とのオーバーロード
    
    
    /*************************************************************//**
     *
     *  @brief  ベクトルと乗算した値を求める
     *  @param  4つの要素を持つベクトル
     *  @return 乗算したベクトル
     *
     ****************************************************************/
    template<typename T>
    const S_Vector4<T> S_Matrix4x4<T>::operator*(const S_Vector4<T>& rVector) const
    {
        S_Vector4<T> tempVector;
        
        tempVector.x_ = a11_ * rVector.x_
                      + a21_ * rVector.y_
                      + a31_ * rVector.z_
                      + a41_ * rVector.w_;
    
        tempVector.y_ = a12_ * rVector.x_
                      + a22_ * rVector.y_
                      + a32_ * rVector.z_
                      + a42_ * rVector.w_;
    
        tempVector.z_ = a13_ * rVector.x_
                      + a23_ * rVector.y_
                      + a33_ * rVector.z_
                      + a43_ * rVector.w_;
    
        tempVector.w_ = a14_ * rVector.x_
                      + a24_ * rVector.y_
                      + a34_ * rVector.z_
                      + a44_ * rVector.w_;
    
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
    S_Matrix4x4<T>::operator S_Matrix3x3<T>() const
    {
        return S_Matrix3x3<T>::s_ConvertMatrix4x4ToMatrix3x3(*this);
    }
    
    
    /*************************************************************//**
     *
     *  @brief  string型へキャストする
     *  @param  なし
     *  @return 文字列に変換した行列
     *
     ****************************************************************/
    template<typename T>
    S_Matrix4x4<T>::operator std::string() const
    {
        return GetConvertToString();
    }
    
    
#pragma endregion
    
    
    /* 明示的インスタンス化 */
    template struct S_Matrix4x4<float>;
    template struct S_Matrix4x4<double>;
    
    
    /*************************************************************//**
     *
     *  @brief  行列式を取得する
     *  @param  行列
     *  @return 行列式
     *
     ****************************************************************/
    template<typename T>
    static T s_GetDeterminant(const S_Matrix4x4<T>& rMatrix)
    {
        return (rMatrix.a11_ * rMatrix.a22_ * rMatrix.a33_ * rMatrix.a44_) 
             + (rMatrix.a11_ * rMatrix.a23_ * rMatrix.a34_ * rMatrix.a42_)
             + (rMatrix.a11_ * rMatrix.a24_ * rMatrix.a32_ * rMatrix.a43_)
    
             + (rMatrix.a12_ * rMatrix.a21_ * rMatrix.a34_ * rMatrix.a43_)
             + (rMatrix.a12_ * rMatrix.a23_ * rMatrix.a31_ * rMatrix.a44_)
             + (rMatrix.a12_ * rMatrix.a24_ * rMatrix.a33_ * rMatrix.a41_)
    
             + (rMatrix.a13_ * rMatrix.a21_ * rMatrix.a32_ * rMatrix.a44_)
             + (rMatrix.a13_ * rMatrix.a22_ * rMatrix.a34_ * rMatrix.a41_)
             + (rMatrix.a13_ * rMatrix.a24_ * rMatrix.a31_ * rMatrix.a42_)
             
             + (rMatrix.a14_ * rMatrix.a21_ * rMatrix.a33_ * rMatrix.a42_)
             + (rMatrix.a14_ * rMatrix.a22_ * rMatrix.a31_ * rMatrix.a43_)
             + (rMatrix.a14_ * rMatrix.a23_ * rMatrix.a32_ * rMatrix.a41_)
    
             - (rMatrix.a11_ * rMatrix.a22_ * rMatrix.a34_ * rMatrix.a43_)
             - (rMatrix.a11_ * rMatrix.a23_ * rMatrix.a32_ * rMatrix.a44_)
             - (rMatrix.a11_ * rMatrix.a24_ * rMatrix.a33_ * rMatrix.a42_)
    
             - (rMatrix.a12_ * rMatrix.a21_ * rMatrix.a33_ * rMatrix.a44_)
             - (rMatrix.a12_ * rMatrix.a23_ * rMatrix.a34_ * rMatrix.a41_)
             - (rMatrix.a12_ * rMatrix.a24_ * rMatrix.a31_ * rMatrix.a43_)
    
             - (rMatrix.a13_ * rMatrix.a21_ * rMatrix.a34_ * rMatrix.a42_)
             - (rMatrix.a13_ * rMatrix.a22_ * rMatrix.a31_ * rMatrix.a44_)
             - (rMatrix.a13_ * rMatrix.a24_ * rMatrix.a32_ * rMatrix.a41_)
    
             - (rMatrix.a14_ * rMatrix.a21_ * rMatrix.a32_ * rMatrix.a43_)
             - (rMatrix.a14_ * rMatrix.a22_ * rMatrix.a33_ * rMatrix.a41_)
             - (rMatrix.a14_ * rMatrix.a23_ * rMatrix.a31_ * rMatrix.a42_);
    }

}