/* 二重インクルード防止 */
#pragma once


//-------------------------------------------------------------
///
/// @brief マス
/// @brief 数学関連の名前空間
///
//-------------------------------------------------------------
namespace Math
{
    namespace
    {
        const double s_PI_DIVISION4 = 0.785398163397447;                ///< @brief π / 4
        const double s_PI_DIVISION3 = 1.047197551196596;                ///< @brief π / 3
        const double s_PI_DIVISION2 = 1.570796326794895;                ///< @brief π / 2
        const double s_PI = 3.14159265358979;                           ///< @brief π
        const double s_PI2 = 6.2831853071795;                           ///< @brief 2π
        const double s_ONE_DIVISION_PI = 0.31830988618379;              ///< @brief 1 / π
        const double s_STRAIGHT_DIVISION_PI = 57.295779513082379;       ///< @brief 180 / π
        const double s_ONE_RADIAN = 0.017453292519943;                  ///< @brief 1ラジアン( π / 180 )
        const double s_ROOT2 = 1.414213562373095;                       ///< @brief √2
        const double s_ROOT3 = 1.732050807568877;                       ///< @brief √3
        const double s_EPSILON = 0.00001;                               ///< @brief 誤差値を示す極小の値
    }

    /* 度数からラジアン値へ変換 */
    template<typename T>
    T ConvertDegreeToRadian(T degrees);

    // ラジアン値から度数へ変換
    template<typename T>
    T ConvertRadianToDegree(T radians);

    /* 平方根 */
    template <typename T>
    T SquareRoot(T value);

    /* 余接 */
    template<typename T>
    T Cotangent(T radian);

    /* 2Dの内積 */
    template<typename T>
    T DotProduct2D(T x1, T y1, T x2, T y2);

    /* 3Dの内積 */
    template<typename T>
    T DotProduct3D(T x1, T y1, T z1, T x2, T y2, T z2);

    /* 2Dの外積 */
    template<typename T>
    T CrossProduct2D(T x1, T y1, T x2, T y2);

    /* 最小値化 */
    template<typename T>
    T Minimize(T lhs, T rhs);

    /* 最大値化 */
    template<typename T>
    T Maximize(T lhs, T rhs);

    /* クランプ */
    template<typename T>
    T Clamp(T value, T min, T max);

    /* 角度を0から2πまでに調節 */
    template<typename T>
    T AdjustAngleFrom0ToPI2(T angle);

    /* 二乗 */
    template<typename T>
    T Square(T value);

    /* 三乗 */
    template<typename T>
    T Cubic(T value);

    /* レナード・ジョーンズ・ポテンシャル */
    template<typename T>
    T LennardJonesPotential(T repulsionStrength,
                            T attractionStrength,
                            T distance,
                            T repulsionAttenuationCoefficient,
                            T attractionAttenuationCoefficient);

    /* シグモイド */
    template<typename T>
    T Sigmoid(T x, T gain = static_cast<T>(1.0));

    /* 1次元ガウシアン */
    template<typename T>
    T OneDimensionalGaussian(T x, T standardDeviation = static_cast<T>(1.0));

    /* 2次元ガウシアン */
    template<typename T>
    T TwoDimensionsGaussian(T x, T y, T dispersion = static_cast<T>(1.0));
}