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
    //! @brief ファジー
    //! @brief ファジー理論関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace Fuzzy
    {
        /* 型変換 */
        using HedgeFunction = float(*)(float);                                                              // HedgeFunction型を宣言

        //-------------------------------------------------------------
        //!
        //! @brief メンバシップ
        //! @brief メンバシップ関数をまとめたユーティリティクラス
        //!
        //-------------------------------------------------------------
        template<typename T = float>
        class C_Membership
        {
        public:
            static float s_Grade(T value, T start, T end, HedgeFunction pHedge = nullptr);                  // 傾斜型
            static float s_ReverseGrade(T value, T start, T end,  HedgeFunction pHedge = nullptr);          // 逆傾斜型
            static float s_Triangle(T value,                                                                // 三角形型
                                    T start,
                                    T top,
                                    T end,
                                    HedgeFunction pHedge = nullptr);
            static float s_Trapezoid(T value,                                                               // 台形型
                                     T bottomStart,
                                     T topStart,
                                     T topEnd,
                                     T bottomEnd,
                                     HedgeFunction pHedge = nullptr);
        }; 


        //-------------------------------------------------------------
        //!
        //! @brief ヘッジ
        //! @brief ヘッジ関数をまとめたユーティリティクラス
        //!
        //-------------------------------------------------------------
        class C_Heage
        {
        public:
            static float s_Very(float value);                                                               // 2乗
            static float s_SomeWhat(float value);                                                           // 平方根
        };


        //-------------------------------------------------------------
        //!
        //! @brief ロジカルオペレーション
        //! @brief 論理演算関数をまとめたユーティリティクラス
        //!
        //-------------------------------------------------------------
        class C_LogicalOperation
        {
        public:
            static float s_And(float lhs, float rhs);                                                       // 論理積
            static float s_Or(float lhs, float rhs);                                                        // 論理和
            static float s_ProbabilisticOr(float lhs, float rhs);                                           // 確率的論理和
            static float s_Not(float value);                                                                // 論理否定
        };


        //-------------------------------------------------------------
        //!
        //! @brief デファジフィ
        //! @brief 非ファジー化を行う関数をまとめたユーティリティクラス
        //!
        //-------------------------------------------------------------
        class C_Defuzzify
        {
        public:
            static float s_Height(float values[], float weights[], uint32_t elementCount);                  // 高さ法
        };
    }
}