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
    //-------------------------------------------------------------
    //!
    //! @brief イージング
    //! @brief イージングの関数をまとめたユーティリティクラス
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    class C_Easing
    {
    public:
        /* 定数 */
        static const T s_DEFAULT_STRESS;                ///< @brief デフォルトの圧力

        /* 線形( 一次 )補間 */
        static T s_Linear(T start,
                          T end,
                          T coefficient);

        /* イーズインの二次補間 */
        static T s_EaseInQuadratic(T start,
                                   T end,
                                   T coefficient);

        /* イーズアウトの二次補間 */
        static T s_EaseOutQuadratic(T start,
                                    T end,
                                    T coefficient);

        /* イーズイン・アウトの二次補間 */
        static T s_EaseInOutQuadratic(T start,
                                      T end,
                                      T coefficient);

        /* イーズインの三次補間 */
        static T s_EaseInCubic(T start,
                               T end,
                               T coefficient);

        /* イーズアウトの三次補間 */
        static T s_EaseOutCubic(T start,
                                T end,
                                T coefficient);

        /* イーズイン・アウトの三次補間 */
        static T s_EaseInOutCubic(T start,
                                  T end,
                                  T coefficient);

        /* イーズインの四次補間 */
        static T s_EaseInQuartic(T start,
                                 T end,
                                 T coefficient);

        /* イーズアウトの四次補間 */
        static T s_EaseOutQuartic(T start,
                                  T end,
                                  T coefficient);

        /* イーズイン・アウトの四次補間 */
        static T s_EaseInOutQuartic(T start,
                                    T end,
                                    T coefficient);

        /* イーズインの五次補間 */
        static T s_EaseInQuintic(T start,
                                 T end,
                                 T coefficient);

        /* イーズアウトの五次補間 */
        static T s_EaseOutQuintic(T start,
                                  T end,
                                  T coefficient);

        /* イーズイン・アウトの五次補間 */
        static T s_EaseInOutQuintic(T start,
                                    T end,
                                    T coefficient);

        /* イーズインのサイン補間 */
        static T s_EaseInSine(T start,
                              T end,
                              T coefficient);

        /* イーズアウトのサイン補間 */
        static T s_EaseOutSine(T start,
                               T end,
                               T coefficient);

        /* イーズイン・アウトのサイン補間 */
        static T s_EaseInOutSine(T start,
                                 T end,
                                 T coefficient);

        /* イーズインの指数補間 */
        static T s_EaseInExponential(T start,
                                     T end,
                                     T coefficient);

        /* イーズアウトの指数補間 */
        static T s_EaseOutExponential(T start,
                                      T end,
                                      T coefficient);

        /* イーズイン・アウトの指数補間 */
        static T s_EaseInOutExponential(T start,
                                        T end,
                                        T coefficient);

        /* イーズインの円弧補間 */
        static T s_EaseInCircular(T start,
                                  T end,
                                  T coefficient);

        /* イーズアウトの円弧補間 */
        static T s_EaseOutCircular(T start,
                                   T end,
                                   T coefficient);

        /* イーズイン・アウトの円弧補間 */
        static T s_EaseInOutCircular(T start,
                                     T end,
                                     T coefficient);

        /* イーズインのバック補間 */
        static T s_EaseInBack(T start,
                              T end,
                              T coefficient,
                              T stress = s_DEFAULT_STRESS);

        /* イーズアウトのバック補間 */
        static T s_EaseOutBack(T start,
                               T end,
                               T coefficient,
                               T stress = s_DEFAULT_STRESS);

        /* イーズイン・アウトのバック補間 */
        static T s_EaseInOutBack(T start,
                                 T end,
                                 T coefficient,
                                 T stress = s_DEFAULT_STRESS);

        /* イーズインのバウンス補間 */
        static T s_EaseInBounce(T start,
                                T end,
                                T coefficient);

        /* イーズアウトのバウンス補間 */
        static T s_EaseOutBounce(T start,
                                 T end,
                                 T coefficient);

        /* イーズイン・アウトのバウンス補間 */
        static T s_EaseInOutBounce(T start,
                                   T end,
                                   T coefficient);

        /* イーズインのイラスティック補間 */
        static T s_EaseInElastic(T start,
                                 T end,
                                 T coefficient);

        /* イーズアウトのイラスティック補間 */
        static T s_EaseOutElastic(T start,
                                  T end,
                                  T coefficient);

        /* イーズイン・アウトのイラスティック補間 */
        static T s_EaseInOutElastic(T start,
                                    T end,
                                    T coefficient);
    };
}