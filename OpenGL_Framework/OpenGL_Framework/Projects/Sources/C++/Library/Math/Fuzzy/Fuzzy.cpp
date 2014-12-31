/* ヘッダファイル */
#include "Fuzzy.h"
#include "../Define/MathDefine.h"


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
    //! @brief ファジー
    //! @brief ファジー論理関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace Fuzzy
    {

 #pragma region C_Membershipクラス


        /*************************************************************//**
         *
         *  @brief  傾斜型でメンバシップ度を求める
         *  @param  値
         *  @param  開始値
         *  @param  終了値
         *  @param  ヘッジ関数
         *  @return メンバシップ度( 0から1までの値 )
         *
         ****************************************************************/
        template<typename T>
        float C_Membership<T>::s_Grade(T value, T start, T end, HedgeFunction pHedge)
        {
            if (value <= start)
            {
                return 0.0f;
            }
            else if (value >= end)
            {
                return 1.0f;
            }

            float x = static_cast<float>(value);
            float x0 = static_cast<float>(start);
            float x1 = static_cast<float>(end);
            float reciprocalDifference = 1 / (x1 - x0);

            float result = (x * reciprocalDifference) - (x0 * reciprocalDifference);

            // ヘッジ関数
            if (pHedge) result = pHedge(result);

            return ;
        }


        /*************************************************************//**
         *
         *  @brief  逆傾斜型でメンバシップ度を求める
         *  @param  値
         *  @param  開始値
         *  @param  終了値
         *  @param  ヘッジ関数
         *  @return メンバシップ度( 0から1までの値 )
         *
         ****************************************************************/
        template<typename T>
        float C_Membership<T>::s_ReverseGrade(T value, T start, T end, HedgeFunction pHedge)
        {
            if (value <= start)
            {
                return 1.0f;
            }
            else if (value >= end)
            {
                return 0.0f;
            }

            float x = static_cast<float>(value);
            float x0 = static_cast<float>(start);
            float x1 = static_cast<float>(end);
            float reciprocalDifference = 1 / (x1 - x0);

            float result = (-x * reciprocalDifference) + (x1 * reciprocalDifference);

            // ヘッジ関数
            if (pHedge) result = pHedge(result);

            return (-x * reciprocalDifference) + (x1 * reciprocalDifference);
        }


        /*************************************************************//**
         *
         *  @brief  三角形型でメンバシップ度を求める
         *  @param  値
         *  @param  開始値
         *  @param  頂点
         *  @param  終了値
         *  @param  ヘッジ関数
         *  @return メンバシップ度( 0から1までの値 )
         *
         ****************************************************************/
        template<typename T>
        float C_Membership<T>::s_Triangle(T value,
                                          T start,
                                          T top,
                                          T end,
                                          HedgeFunction pHedge)
        {
            float result = 0.0f;
            
            if (value == top)
            {
                result = 1.0f;
            }
            else if (value > start && value < top)
            {
                float x = static_cast<float>(value);
                float x0 = static_cast<float>(start);
                float x1 = static_cast<float>(top);
                float reciprocalDifference = 1 / (x1 - x0);

                result = (x * reciprocalDifference) - (x0 * reciprocalDifference);
            }
            else if (value > top && value < end)
            {
                float x = static_cast<float>(value);
                float x1 = static_cast<float>(top);
                float x2 = static_cast<float>(end);
                float reciprocalDifference = 1 / (x2 - x1);

                result = (-x * reciprocalDifference) + (x2 * reciprocalDifference);
            }

            // ヘッジ関数
            if (pHedge) result = pHedge(result);

            return result;
        }


        /*************************************************************//**
         *
         *  @brief  台形型でメンバシップ度を求める
         *  @param  値
         *  @param  下部の開始値
         *  @param  上部の開始値
         *  @param  上部の終了値
         *  @param  下部の終了値
         *  @param  ヘッジ関数
         *  @return メンバシップ度( 0から1までの値 )
         *
         ****************************************************************/
        template<typename T>
        float C_Membership<T>::s_Trapezoid(T value,
                                           T bottomStart,
                                           T topStart,
                                           T topEnd,
                                           T bottomEnd,
                                           HedgeFunction pHedge)
        {
            float result = 0.0f;

            if (value >= topStart && value <= topEnd)
            {
                result = 1.0f;
            }
            else if (value > bottomStart && value < topStart)
            {
                float x = static_cast<float>(value);
                float x0 = static_cast<float>(bottomStart);
                float x1 = static_cast<float>(topStart);
                float reciprocalDifference = 1 / (x1 - x0);

                result = (x * reciprocalDifference) - (x0 * reciprocalDifference);
            }
            else if (value > topEnd && value < bottomEnd)
            {
                float x = static_cast<float>(value);
                float x2 = static_cast<float>(topEnd);
                float x3 = static_cast<float>(bottomEnd);
                float reciprocalDifference = 1 / (x3 - x2);

                result = (-x * reciprocalDifference) + (x3 * reciprocalDifference);
            }

            // ヘッジ関数
            if (pHedge) result = pHedge(result);

            return result;
        }


#pragma endregion


#pragma region C_Heageクラス


        /*************************************************************//**
         *
         *  @brief  2乗を行う
         *  @param  値
         *  @return 2乗した値
         *
         ****************************************************************/
        float C_Heage::s_Very(float value)
        {
            return Square(value);
        }


        /*************************************************************//**
         *
         *  @brief  平方根を求める
         *  @param  値
         *  @return 値の平方根
         *
         ****************************************************************/
        float C_Heage::s_SomeWhat(float value)
        {
            return SquareRoot(value);
        }


#pragma endregion


#pragma region C_LogicalOperationクラス


        /*************************************************************//**
         *
         *  @brief  論理積を行う
         *  @param  一つ目の値
         *  @param  二つ目の値
         *  @return 論理積した値
         *
         ****************************************************************/
        float C_LogicalOperation::s_And(float lhs, float rhs)
        {
            return Minimize(lhs, rhs);
        }


        /*************************************************************//**
         *
         *  @brief  論理和を行う
         *  @param  一つ目の値
         *  @param  二つ目の値
         *  @return 論理和した値
         *
         ****************************************************************/
        float C_LogicalOperation::s_Or(float lhs, float rhs)
        {
            return Maximize(lhs, rhs);
        }


        /*************************************************************//**
         *
         *  @brief  確率的論理和を行う
         *  @param  一つ目の値
         *  @param  二つ目の値
         *  @return 確率的論理和した値
         *
         ****************************************************************/
        float C_LogicalOperation::s_ProbabilisticOr(float lhs, float rhs)
        {
            return (lhs + rhs) - (lhs * rhs);
        }


        /*************************************************************//**
         *
         *  @brief  論理否定を行う
         *  @param  値
         *  @return 論理否定した値
         *
         ****************************************************************/
        float C_LogicalOperation::s_Not(float value)
        {
            return 1.0f - value;
        }


#pragma endregion


#pragma region C_Defuzzify


        /*************************************************************//**
         *
         *  @brief  高さ法を行う
         *  @param  値
         *  @param  重み
         *  @param  要素数
         *  @return 高さ法した値
         *
         ****************************************************************/
        float C_Defuzzify::s_Height(float values[], float weights[], uint32_t elementCount)
        {
            float numerator = 0.0f, denominator = 0.0f;

            for (size_t i = 0; i < elementCount; ++i)
            {
                numerator += values[i] * weights[i];
                denominator += values[i];
            }

            return numerator / denominator;
        }


#pragma endregion


    }
}