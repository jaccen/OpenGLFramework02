/* ヘッダファイル */
#include "Easing.h"
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


    /* デフォルトの圧力 */
    template<typename T>
    const T C_Easing<T>::s_DEFAULT_STRESS = static_cast<T>(1.70158);


#pragma endregion


    /*************************************************************//**
     *
     *  @brief  線形( 一次 )補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_Linear(T start, T end, T coefficient)
    {
        return (end - start) * coefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズインの二次補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInQuadratic(T start,
                                     T end,
                                     T coefficient)
    {
        T calculateCoefficient = Square(coefficient);
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズアウトの二次補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutQuadratic(T start,
                                      T end,
                                      T coefficient)
    {
        T calculateCoefficient = coefficient * (coefficient - static_cast<T>(2));
        return -(end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズイン・アウトの二次補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutQuadratic(T start,
                                        T end,
                                        T coefficient)
    {
        // 補間係数の2倍
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // 計算後の補間係数
        T calculateCoefficient = static_cast<T>(0);

        // 補間係数の2倍が1未満( 補間係数が0.5未満 )の場合
        if (twiceCoefficient < static_cast<T>(1))
        {
            // 補間係数を計算し、補完する
            calculateCoefficient = Square(twiceCoefficient);
            return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
        }

        // 補間係数の2倍を1減らす( 補間係数を0 ～ 1に合わせる )
        --twiceCoefficient;

        // 補間係数を計算し、補完する
        calculateCoefficient = (twiceCoefficient * (twiceCoefficient - static_cast<T>(2))) - static_cast<T>(1);
        return -(end - start) / static_cast<T>(2) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズインの三次補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInCubic(T start,
                                 T end,
                                 T coefficient)
    {
        T calculateCoefficient = Cubic(coefficient);
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズアウトの三次補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutCubic(T start,
                                  T end,
                                  T coefficient)
    {
        // 係数を1減らす
        --coefficient;

        // 補間係数を計算し、補間する
        T calculateCoefficient = Cubic(coefficient) + static_cast<T>(1);
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズイン・アウトの三次補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutCubic(T start,
                                    T end,
                                    T coefficient)
    {
        // 補間係数の2倍
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // 計算後の補間係数
        T calculateCoefficient = static_cast<T>(0);

        // 補間係数の2倍が1未満( 補間係数が0.5未満 )の場合
        if (twiceCoefficient < static_cast<T>(1))
        {
            // 補間係数を計算し、補完する
            calculateCoefficient = Cubic(twiceCoefficient);
            return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
        }

        // 補間係数の2倍を2減らす( 補間係数を-1 ～ 0に合わせる )
        twiceCoefficient -= static_cast<T>(2);

        // 補間係数を計算し、補完する
        calculateCoefficient = Cubic(twiceCoefficient) + static_cast<T>(2);
        return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズインの四次補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInQuartic(T start,
                                   T end,
                                   T coefficient)
    {
        T calculateCoefficient = std::pow(coefficient, static_cast<T>(4));
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズアウトの四次補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutQuartic(T start,
                                    T end,
                                    T coefficient)
    {
        // 係数を1減らす
        --coefficient;

        // 補間係数を計算し、補完する
        T calculateCoefficient = std::pow(coefficient, static_cast<T>(4)) - static_cast<T>(1);
        return -(end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズイン・アウトの四次補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutQuartic(T start,
                                      T end,
                                      T coefficient)
    {
        // 補間係数の2倍
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // 計算後の補間係数
        T calculateCoefficient = static_cast<T>(0);

        // 補間係数の2倍が1未満( 補間係数が0.5未満 )の場合
        if (twiceCoefficient < static_cast<T>(1))
        {
            // 補間係数を計算し、補完する
            calculateCoefficient = std::pow(twiceCoefficient, static_cast<T>(4));
            return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
        }

        // 補間係数の2倍を2減らす( 補間係数を-1 ～ 0に合わせる )
        twiceCoefficient -= static_cast<T>(2);

        // 補間係数を計算し、補完する
        calculateCoefficient = std::pow(twiceCoefficient, static_cast<T>(4)) - static_cast<T>(2);
        return -(end - start) / static_cast<T>(2) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズインの五次補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInQuintic(T start,
                                   T end,
                                   T coefficient)
    {
        T calculateCoefficient = std::pow(coefficient, static_cast<T>(5));
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズアウトの五次補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutQuintic(T start,
                                    T end,
                                    T coefficient)
    {
        // 係数を1減らす
        --coefficient;

        // 補間係数を計算し、補完する
        T calculateCoefficient = std::pow(coefficient, static_cast<T>(5)) + static_cast<T>(1);
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズイン・アウトの五次補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutQuintic(T start,
                                      T end,
                                      T coefficient)
    {
        // 補間係数の2倍
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // 計算後の補間係数
        T calculateCoefficient = static_cast<T>(0);

        // 補間係数の2倍が1未満( 補間係数が0.5未満 )の場合
        if (twiceCoefficient < static_cast<T>(1))
        {
            // 補間係数を計算し、補完する
            calculateCoefficient = std::pow(twiceCoefficient, static_cast<T>(5));
            return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
        }

        // 補間係数の2倍を2減らす( 補間係数を-1 ～ 0に合わせる )
        twiceCoefficient -= static_cast<T>(2);

        // 補間係数を計算し、補完する
        calculateCoefficient = std::pow(twiceCoefficient, static_cast<T>(5)) + static_cast<T>(2);
        return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズインのサイン補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInSine(T start,
                                T end,
                                T coefficient)
    {
        T calculateCoefficient = std::cos(static_cast<T>(s_PI_DIVISION2)* coefficient);
        return -(end - start) * calculateCoefficient + end;
    }


    /*************************************************************//**
     *
     *  @brief  イーズアウトのサイン補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutSine(T start,
                                 T end,
                                 T coefficient)
    {
        T calculateCoefficient = std::sin(static_cast<T>(s_PI_DIVISION2)* coefficient);
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズイン・アウトのサイン補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutSine(T start,
                                   T end,
                                   T coefficient)
    {
        T calculateCoefficient = std::cos(static_cast<T>(s_PI)* coefficient) - static_cast<T>(1);
        return -(end - start) / static_cast<T>(2) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズインの指数補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInExponential(T start,
                                       T end,
                                       T coefficient)
    {
        T calculateCoefficient = std::pow(static_cast<T>(2), static_cast<T>(10) * (coefficient - static_cast<T>(1)));
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズアウトの指数補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutExponential(T start,
                                        T end,
                                        T coefficient)
    {
        T calculateCoefficient = -(std::pow(static_cast<T>(2), static_cast<T>(-10) * coefficient)) + static_cast<T>(1);
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズイン・アウトの指数補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutExponential(T start,
                                          T end,
                                          T coefficient)
    {
        // 補間係数の2倍
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // 計算後の補間係数
        T calculateCoefficient = static_cast<T>(0);

        // 補間係数の2倍が1未満( 補間係数が0.5未満 )の場合
        if (twiceCoefficient < static_cast<T>(1))
        {
            // 補間係数を計算し、補完する
            calculateCoefficient = std::pow(static_cast<T>(2), static_cast<T>(10) * (twiceCoefficient - static_cast<T>(1)));
            return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
        }

        // 補間係数の2倍を1減らす( 補間係数を0 ～ 1に合わせる )
        --twiceCoefficient;

        // 補間係数を計算し、補完する
        calculateCoefficient = -(std::pow(static_cast<T>(2), static_cast<T>(-10) * twiceCoefficient)) + static_cast<T>(2);
        return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズインの円弧補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInCircular(T start,
                                    T end,
                                    T coefficient)
    {
        T calculateCoefficient = std::sqrt(static_cast<T>(1) - Square(coefficient)) - static_cast<T>(1);
        return -(end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズアウトの円弧補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutCircular(T start,
                                     T end,
                                     T coefficient)
    {
        // 補正係数を1減らす
        --coefficient;

        // 補間係数を計算し、補完する
        T calculateCoefficient = std::sqrt(static_cast<T>(1) - Square(coefficient));
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズイン・アウトの円弧補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutCircular(T start,
                                       T end,
                                       T coefficient)
    {
        // 補間係数の2倍
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // 計算後の補間係数
        T calculateCoefficient = static_cast<T>(0);

        // 補間係数の2倍が1未満( 補間係数が0.5未満 )の場合
        if (twiceCoefficient < static_cast<T>(1))
        {
            // 補間係数を計算し、補完する
            calculateCoefficient = std::sqrt(static_cast<T>(1) - Square(twiceCoefficient)) - static_cast<T>(1);
            return -(end - start) / static_cast<T>(2) * calculateCoefficient + start;
        }

        // 補間係数の2倍を2減らす( 補間係数を-1 ～ 0に合わせる )
        twiceCoefficient -= static_cast<T>(2);

        // 補間係数を計算し、補完する
        calculateCoefficient = std::sqrt(static_cast<T>(1) - Square(twiceCoefficient)) + static_cast<T>(1);
        return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズインのバック補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @param  圧力
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInBack(T start,
                                T end,
                                T coefficient,
                                T stress)
    {
        T calculateCoefficient = Square(coefficient) * ((stress + static_cast<T>(1)) * coefficient - stress);
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズアウトのバック補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @param  圧力
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutBack(T start,
                                 T end,
                                 T coefficient,
                                 T stress)
    {
        // 補間係数を1減らす
        --coefficient;

        // 補間係数を計算し、補完する
        T calculateCoefficient = (Square(coefficient) * ((stress + static_cast<T>(1)) * coefficient + stress)) + static_cast<T>(1);
        return (end - start) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズイン・アウトのバック補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @param  圧力
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutBack(T start,
                                   T end,
                                   T coefficient,
                                   T stress)
    {
        // 補間係数の2倍
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // 計算後の補間係数
        T calculateCoefficient = static_cast<T>(0);

        // 圧力を若干強める
        stress *= static_cast<T>(1.525);

        // 補間係数の2倍が1未満( 補間係数が0.5未満 )の場合
        if (twiceCoefficient < static_cast<T>(1))
        {
            // 補間係数を計算し、補完する
            calculateCoefficient = Square(twiceCoefficient) * ((stress + static_cast<T>(1)) * twiceCoefficient - stress);
            return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
        }

        // 補間係数の2倍を2減らす( 補間係数を-1 ～ 0に合わせる )
        twiceCoefficient -= static_cast<T>(2);

        // 補間係数を計算し、補完する
        calculateCoefficient = (Square(twiceCoefficient) * ((stress + static_cast<T>(1)) * twiceCoefficient + stress)) + static_cast<T>(2);
        return (end - start) / static_cast<T>(2) * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズインのバウンス補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInBounce(T start,
                                  T end,
                                  T coefficient)
    {
        // 差分
        T difference = end - start;

        // イーズアウトのバウンド補間を用いて補間する
        return difference - s_EaseOutBounce(static_cast<T>(0), difference, static_cast<T>(1) - coefficient) + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズアウトのバウンス補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutBounce(T start,
                                   T end,
                                   T coefficient)
    {
        // 2の2.75乗と分母( バウンドらしさを出すために用いるの定数 )
        const T POWER2_2DOT75 = static_cast<T>(7.5625);
        const T DENOMINATOR = static_cast<T>(2.75);

        // 差分
        T difference = end - start;

        // 計算後の補間係数
        T calculateCoefficient = static_cast<T>(0);

        /* 補間係数が約36%未満 */
        if (coefficient < static_cast<T>(1) / DENOMINATOR)
        {
            // 補間係数を計算し、補完する
            calculateCoefficient = POWER2_2DOT75 * Square(coefficient);
            return difference * calculateCoefficient + start;
        }
        /* 補間係数が約72%未満 */
        else if (coefficient < static_cast<T>(2) / DENOMINATOR)
        {
            // バウンドに応じて補間係数を減らす
            coefficient -= static_cast<T>(1.5) / DENOMINATOR;

            // 補間係数を計算し、補完する
            calculateCoefficient = (POWER2_2DOT75 * Square(coefficient)) + static_cast<T>(0.75);
            return difference * calculateCoefficient + start;
        }
        /* 補間係数が約90%未満 */
        else if (coefficient < static_cast<T>(2.5) / DENOMINATOR)
        {
            // バウンドに応じて補間係数を減らす
            coefficient -= static_cast<T>(2.25) / DENOMINATOR;

            // 補間係数を計算し、補完する
            calculateCoefficient = (POWER2_2DOT75 * Square(coefficient)) + static_cast<T>(0.9375);
            return difference * calculateCoefficient + start;
        }

        // バウンドに応じて補間係数を減らす
        coefficient -= static_cast<T>(2.625) / DENOMINATOR;

        // 補間係数を計算し、補完する
        calculateCoefficient = (POWER2_2DOT75 * Square(coefficient)) + static_cast<T>(0.984375);
        return difference * calculateCoefficient + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズイン・アウトのバウンス補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutBounce(T start,
                                     T end,
                                     T coefficient)
    {
        // 補間係数の2倍
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // 差分
        T difference = end - start;

        // 補間係数の2倍が1未満( 補間係数が0.5未満 )の場合、イーズインを用いて補間する
        if (twiceCoefficient < static_cast<T>(1)) return s_EaseInBounce(static_cast<T>(0), difference, twiceCoefficient) * static_cast<T>(0.5) + start;

        // イーズアウトを用いて補完する
        return (s_EaseOutBounce(static_cast<T>(0), difference, twiceCoefficient - static_cast<T>(1)) + difference) * static_cast<T>(0.5) + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズインのイラスティック補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInElastic(T start,
                                   T end,
                                   T coefficient)
    {
        // 補間係数が0の場合は開始値を返す
        if (coefficient == static_cast<T>(0)) return start;

        // 補間係数が1の場合は終了値を返す
        if (coefficient == static_cast<T>(1)) return end;

        // 補間係数を1減らす
        --coefficient;

        // 補間係数を計算し、補完する
        T calculateCoefficient = (end - start) * std::pow(static_cast<T>(2), static_cast<T>(10) * (coefficient));
        return -(calculateCoefficient * std::sin((coefficient - static_cast<T>(0.075)) * static_cast<T>(s_PI2) / static_cast<T>(0.3))) + start;
    }


    /*************************************************************//**
     *
     *  @brief  イーズアウトのイラスティック補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseOutElastic(T start,
                                    T end,
                                    T coefficient)
    {
        // 補間係数が0の場合は開始値を返す
        if (coefficient == static_cast<T>(0)) return start;

        // 補間係数が1の場合は終了値を返す
        if (coefficient == static_cast<T>(1)) return end;

        // 補間係数を計算し、補完する
        T calculateCoefficient = (end - start) * std::pow(static_cast<T>(2), static_cast<T>(-10) * (coefficient));
        return (calculateCoefficient * std::sin((coefficient - static_cast<T>(0.075)) * static_cast<T>(s_PI2) / static_cast<T>(0.3))) + end;
    }


    /*************************************************************//**
     *
     *  @brief  イーズイン・アウトのイラスティック補間を行う
     *  @param  開始値
     *  @param  終了値
     *  @param  補間係数( 0 ～ 1 )
     *  @return 開始時の値と終了時の値を補完した値
     *
     ****************************************************************/
    template<typename T>
    T C_Easing<T>::s_EaseInOutElastic(T start,
                                      T end,
                                      T coefficient)
    {
        // 計算後の補間係数
        T calculateCoefficient = static_cast<T>(0);

        // 補間係数が0の場合は開始値を返す
        if (coefficient == static_cast<T>(0)) return start;

        // 補間係数が1の場合は終了値を返す
        if (coefficient == static_cast<T>(1)) return end;

        // 補間係数の2倍
        T twiceCoefficient = coefficient * static_cast<T>(2);

        // 補間係数の2倍が1未満( 補間係数が0.5未満 )の場合
        if (twiceCoefficient < static_cast<T>(1))
        {
            // 補間係数の2倍を1減らす( 補間係数を-1 ～ 0に合わせる )
            --twiceCoefficient;

            // 補間係数を計算し、補完する
            calculateCoefficient = (end - start) * std::pow(static_cast<T>(2), static_cast<T>(10) * twiceCoefficient);
            return static_cast<T>(-0.5) * (calculateCoefficient * std::sin((twiceCoefficient - static_cast<T>(0.1125)) * static_cast<T>(s_PI2) / static_cast<T>(0.45))) + start;
        }

        // 補間係数の2倍を1減らす( 補間係数を0 ～ 1に合わせる )
        --twiceCoefficient;

        // 補間係数を計算し、補完する
        calculateCoefficient = (end - start) * std::pow(static_cast<T>(2), static_cast<T>(-10) * (twiceCoefficient));
        return calculateCoefficient * std::sin((twiceCoefficient - static_cast<T>(0.1125)) * static_cast<T>(s_PI2) / static_cast<T>(0.45)) * static_cast<T>(0.5) + end;
    }

    /* 明示的インスタンス化 */
    template class C_Easing<float>;
    template class C_Easing<double>;

}