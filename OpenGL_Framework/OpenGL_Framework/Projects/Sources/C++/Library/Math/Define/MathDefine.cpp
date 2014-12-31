/* ヘッダファイル */
#include "MathDefine.h"


//-------------------------------------------------------------
///
/// @brief マス
/// @brief 数学関連の名前空間
///
//-------------------------------------------------------------
namespace Math
{

    /*************************************************************//**
     *
     *  @brief  度数からラジアン値への変換を行う
     *  @param  角度( 度数 )
     *  @return 角度( ラジアン値 )
     *
     ****************************************************************/
    template<typename T>
    T ConvertDegreeToRadian(T degrees)
    {
        return degrees * static_cast<T>(s_ONE_RADIAN);
    }


    /*************************************************************//**
     *
     *  @brief  ラジアン値から度数への変換を行う
     *  @param  角度( ラジアン値 )
     *  @return 角度( 度数 )
     *
     ****************************************************************/
    template<typename T>
    T ConvertRadianToDegree(T radians)
    {
        return radians * static_cast<T>(s_STRAIGHT_DIVISION_PI);
    }


    /*************************************************************//**
     *
     *  @brief  平方根を求める
     *  @param  値
     *  @return 平方根
     *
     ****************************************************************/
    template <typename T>
    T SquareRoot(T value)
    {
        assert(value >= static_cast<T>(0));

        T lastResult = value;
        T result = value / static_cast<T>(2);

        while (result != lastResult)
        {
            lastResult = result;
            result = (result + value / result) / static_cast<T>(2);
        }

        return result;
    }


    /*************************************************************//**
     *
     *  @brief  余接を求める
     *  @param  角度( ラジアン値 )
     *  @return 余接
     *
     ****************************************************************/
    template<typename T>
    T Cotangent(T radian)
    {
        return static_cast<T>(std::cos(static_cast<double>(radian)) / std::sin(static_cast<double>(radian)));
    }


    /*************************************************************//**
     *
     *  @brief  2次元での内積を求める
     *  @param  一つ目のX座標
     *  @param  一つ目のY座標
     *  @param  二つ目のX座標
     *  @param  二つ目のY座標
     *  @return 内積
     *
     ****************************************************************/
    template<typename T>
    T DotProduct2D(T x1, T y1, T x2, T y2)
    {
        return (x1 * x2) + (y1 * y2);
    }


    /*************************************************************//**
     *
     *  @brief  3次元での内積を求める
     *  @param  一つ目のX座標
     *  @param  一つ目のY座標
     *  @param  一つ目のZ座標
     *  @param  二つ目のX座標
     *  @param  二つ目のY座標
     *  @param  二つ目のZ座標
     *  @return 内積
     *
     ****************************************************************/
    template<typename T>
    T DotProduct3D(T x1, T y1, T z1, T x2, T y2, T z2)
    {
        return (x1 * x2) + (y1 * y2) + (z1 * z2);
    }


    /*************************************************************//**
     *
     *  @brief  2次元での外積を求める
     *  @param  一つ目のX座標
     *  @param  一つ目のY座標
     *  @param  二つ目のX座標
     *  @param  二つ目のY座標
     *  @return 外積
     *
     ****************************************************************/
    template<typename T>
    T CrossProduct2D(T x1, T y1, T x2, T y2)
    {
        return (x1 * y2) - (x2 * y1);
    }


    /*************************************************************//**
     *
     *  @brief  最小値化を行う
     *  @param  一つ目の値
     *  @param  二つ目の値
     *  @return 最小値
     *
     ****************************************************************/
    template<typename T>
    T Minimize(T lhs, T rhs)
    {
        return (lhs < rhs) ? lhs : rhs;
    }


    /*************************************************************//**
     *
     *  @brief  最大値化を行う
     *  @param  一つ目の値
     *  @param  二つ目の値
     *  @return 最大値
     *
     ****************************************************************/
    template<typename T>
    T Maximize(T lhs, T rhs)
    {
        return (lhs > rhs) ? lhs : rhs;
    }


    /*************************************************************//**
     *
     *  @brief  値のクランプを行う
     *  @param  値
     *  @param  最小値
     *  @param  最大値
     *  @return クランプした値
     *
     ****************************************************************/
    template<typename T>
    T Clamp(T value, T min, T max)
    {
        return value < min ? min : (value > max ? max : value);
    }


    /*************************************************************//**
     *
     *  @brief  角度を0度から2πまでに調節する
     *  @param  角度( ラジアン値 )
     *  @return 調節した角度
     *
     ****************************************************************/
    template<typename T>
    T AdjustAngleFrom0ToPI2(T angle)
    {
        if (angle < static_cast<T>(0))
        {
            while (angle < 0) angle += static_cast<T>(s_PI2);
        }
        else
        {
            while (angle > s_PI2) angle -= static_cast<T>(s_PI2);
        }

        return angle;
    }


    /*************************************************************//**
     *
     *  @brief  二乗を行う
     *  @param  値
     *  @return 二乗した値
     *
     ****************************************************************/
    template <typename T>
    T Square(T value)
    {
        return value * value;
    }


    /*************************************************************//**
     *
     *  @brief  三乗を行う
     *  @param  値
     *  @return 三乗した値
     *
     ****************************************************************/
    template <typename T>
    T Cubic(T value)
    {
        return value * value * value;
    }


    /*************************************************************//**
     *
     *  @brief  2つの原子間の位置エネルギーを求める
     *  @param  斥力強度
     *  @param  引力強度
     *  @param  距離
     *  @param  斥力減衰係数
     *  @param  引力減衰係数
     *  @return 位置エネルギー
     *
     ****************************************************************/
    template<typename T>
    T LennardJonesPotential(T repulsionStrength,
        T attractionStrength,
        T distance,
        T repulsionAttenuationCoefficient,
        T attractionAttenuationCoefficient)
    {
        return (repulsionStrength / std::pow(distance, repulsionAttenuationCoefficient))
            - (attractionStrength / std::pow(distance, attractionAttenuationCoefficient));
    }


    /*************************************************************//**
     *
     *  @brief  シグモイド関数から値を求める
     *  @param  値
     *  @param  ゲイン
     *  @return 0から1までの値
     *
     ****************************************************************/
    template<typename T>
    T Sigmoid(T x, T gain)
    {
        assert(gain);

        return static_cast<T>(1.0) / (static_cast<T>(1.0) + std::exp(-x * gain));
    }


    /*************************************************************//**
     *
     *  @brief  一次元ガウシアン関数から値を求める
     *  @param  値
     *  @param  標準偏差( σ )
     *  @return 0から1までの値
     *
     ****************************************************************/
    template<typename T>
    T OneDimensionalGaussian(T x, T standardDeviation)
    {
        const T ROOT_PI2 = static_cast<T>(2.506628274631);

        T leftSide = static_cast<T>(1.0) / (ROOT_PI2 * standardDeviation);
        T rightSide = std::exp(-Square(x) / (static_cast<T>(2.0) * Square(standardDeviation)));
        T result = leftSide * rightSide;

        return result;
    }


    /*************************************************************//**
     *
     *  @brief  二次元ガウシアン関数から値を求める
     *  @param  値1
     *  @param  値2
     *  @param  分散( σ^2 )
     *  @return 0から1までの値
     *
     ****************************************************************/
    template<typename T>
    T TwoDimensionsGaussian(T x, T y, T dispersion)
    {
        T leftSide = static_cast<T>(1.0) / (static_cast<T>(s_PI2) * dispersion);
        T rightSide = std::exp(-(Square(x) + Square(y)) / (static_cast<T>(2.0) * Square(dispersion)));
        T result = leftSide * rightSide;

        return result;
    }


#pragma region 明示的インスタンス化


    /* 度数からラジアン値へ変換 */
    template float ConvertDegreeToRadian(float);
    template double ConvertDegreeToRadian(double);


    /* ラジアン値から度数へ変換 */
    template float ConvertRadianToDegree(float);
    template double ConvertRadianToDegree(double);


    /* 平方根 */
    template int32_t SquareRoot(int32_t);
    template float SquareRoot(float);
    template double SquareRoot(double);


    /* 余接 */
    template float Cotangent(float);
    template double Cotangent(double);


    /* 2Dの内積 */
    template float DotProduct2D(float, float, float, float);
    template double DotProduct2D(double, double, double, double);


    /* 3Dの内積 */
    template float DotProduct3D(float, float, float, float, float, float);
    template double DotProduct3D(double, double, double, double, double, double);


    /* 2Dの外積 */
    template float CrossProduct2D(float, float, float, float);
    template double CrossProduct2D(double, double, double, double);


    /* 最小値を判別 */
    template uint32_t Minimize(uint32_t, uint32_t);
    template int32_t Minimize(int32_t, int32_t);
    template float Minimize(float, float);
    template double Minimize(double, double);


    /* 最大値を判別 */
    template uint32_t Maximize(uint32_t, uint32_t);
    template int32_t Maximize(int32_t, int32_t);
    template float Maximize(float, float);
    template double Maximize(double, double);


    /* クランプ */
    template int32_t Clamp(int32_t, int32_t, int32_t);
    template float Clamp(float, float, float);
    template double Clamp(double, double, double);


    /* 角度を0から2πまでに調節 */
    template float AdjustAngleFrom0ToPI2(float);
    template double AdjustAngleFrom0ToPI2(double);


    /* 二乗 */
    template int32_t Square(int32_t);
    template float Square(float);
    template double Square(double);


    /* 三乗 */
    template int32_t Cubic(int32_t);
    template float Cubic(float);
    template double Cubic(double);


    /* レナード・ジョーンズ・ポテンシャル */
    template float LennardJonesPotential(float, float, float, float, float);
    template double LennardJonesPotential(double, double, double, double, double);


    /* シグモイド */
    template float Sigmoid(float, float);
    template double Sigmoid(double, double);


    /* 1次元ガウシアン */
    template float OneDimensionalGaussian(float, float);
    template double OneDimensionalGaussian(double, double);


    /* 2次元ガウシアン */
    template float TwoDimensionsGaussian(float, float, float);
    template double TwoDimensionsGaussian(double, double, double);


#pragma endregion

}