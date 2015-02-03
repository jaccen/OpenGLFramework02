/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "Vector3.h"


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
    //! @brief ベクター4
    //! @brief 4Dベクトルを表す構造体
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    struct S_Vector4
    {
        /* 定数 */
        static const S_Vector4 s_ZERO;                                                          ///< @brief ゼロベクトル
        static const S_Vector4 s_ONE;                                                           ///< @brief 全ての要素が1

        /* メンバ変数 */
        union
        {
            T a_[4];                                                                            ///< @brief 4つの要素を持つ配列

            struct
            {
                T x_;                                                                           ///< @brief X成分
                T y_;                                                                           ///< @brief Y成分
                T z_;                                                                           ///< @brief Z成分
                T w_;                                                                           ///< @brief W成分
            };

            struct
            {
                T red_;                                                                         ///< @brief 赤
                T green_;                                                                       ///< @brief 緑
                T blue_;                                                                        ///< @brief 青
                T alpha_;                                                                       ///< @brief アルファ
            };

            struct
            {
                S_Vector3<T> xyz_;                                                              ///< @brief X・Y・Z成分
            };
        };

        /* メンバ関数 */
        S_Vector4();                                                                            // コンストラクタ
        explicit S_Vector4(T value);                                                            // コンストラクタ
        S_Vector4(T x, T y, T z, T w);                                                          // コンストラクタ
        explicit S_Vector4(const T a[4]);                                                       // コンストラクタ
        S_Vector4(const S_Vector2<T>& rXY, T z, T w);                                           // コンストラクタ
        S_Vector4(const S_Vector3<T>& rXYZ, T w);                                               // コンストラクタ
        S_Vector4(const S_Vector4& rOther) = default;                                           // コピーコンストラクタ
        ~S_Vector4();                                                                           // デストラクタ
        void Zero();                                                                            // ゼロベクトル化
        void Fill(T value);                                                                     // 各成分を特定の値に変更
        void Normalize();                                                                       // 単位ベクトル化
        void Invert();                                                                          // ベクトルを反転
        void ClampLength(T minLength, T maxLength);                                             // ベクトルの長さでクランプ
        T GetLength() const;                                                                    // 長さを取得
        T GetLengthSquare() const;                                                              // 長さの2乗を取得
        S_Vector4 GetNormalize() const;                                                         // 単位ベクトルを取得
        S_Vector4 GetInvert() const;                                                            // 反転したベクトルを取得
        S_Vector4 GetClampLength(T minLength, T maxLength) const;                               // 長さでクランプしたベクトルを取得
        std::string GetConvertToString() const;                                                 // ベクトルを文字列へ変換して取得

        /* Swizzle */
        template<eVectorFactor factor0>
        S_Vector4 Get() const
        {
            return S_Vector4(a_[factor0], a_[factor0], a_[factor0], a_[factor0]);
        }
         
        template<eVectorFactor factor0, eVectorFactor factor1>
        S_Vector4 Get() const
        {
            return S_Vector4(a_[factor0], a_[factor1], a_[factor1], a_[factor1]);
        }
         
        template<eVectorFactor factor0, eVectorFactor factor1, eVectorFactor factor2>
        S_Vector4 Get() const
        {
            return S_Vector4(a_[factor0], a_[factor1], a_[factor2], a_[factor2]);
        }
         
        template<eVectorFactor factor0, eVectorFactor factor1, eVectorFactor factor2, eVectorFactor factor3>
        S_Vector4 Get() const
        {
            return S_Vector4(a_[factor0], a_[factor1], a_[factor2], a_[factor3]);
        }

        /* 静的メンバ関数 */
        static T s_DotProduct(const S_Vector4& rVector, const S_Vector4& rAnotherVector);       // 内積
        static S_Vector4 s_Lerp(const S_Vector4& rStartPoint,                                   // 線形補間
                                const S_Vector4& rEndPoint,
                                T coefficient);
        static S_Vector4 s_Minimize(const S_Vector4& rLhs, const S_Vector4& rRhs);              // 各成分の最小値を成分にしたベクトルを取得
        static S_Vector4 s_Maximize(const S_Vector4& rLhs, const S_Vector4& rRhs);              // 各成分の最大値を成分にしたベクトルを取得

        /* S_Vector4型との演算子のオーバーロード */
        const S_Vector4 operator+(const S_Vector4& rAnother) const;                             // +演算子のオーバーロード
        const S_Vector4 operator-(const S_Vector4& rAnother) const;                             // -演算子のオーバーロード
        const S_Vector4 operator*(const S_Vector4& rAnother) const;                             // *演算子のオーバーロード
        const S_Vector4 operator/(const S_Vector4& rAnother) const;                             // /演算子のオーバーロード
        const S_Vector4& operator+=(const S_Vector4& rAnother);                                 // +=演算子のオーバーロード
        const S_Vector4& operator-=(const S_Vector4& rAnother);                                 // -=演算子のオーバーロード
        const S_Vector4& operator*=(const S_Vector4& rAnother);                                 // *=演算子のオーバーロード
        const S_Vector4& operator/=(const S_Vector4& rAnother);                                 // /=演算子のオーバーロード
        bool operator==(const S_Vector4& rAnother) const;                                       // ==演算子のオーバーロード
        bool operator!=(const S_Vector4& rAnother) const;                                       // !=演算子のオーバーロード

        /* T型との演算子のオーバーロード */
        const S_Vector4 operator*(T value) const;                                               // *演算子のオーバーロード
        const S_Vector4 operator/(T value) const;                                               // /演算子のオーバーロード
        const S_Vector4& operator*=(T value);                                                   // *=演算子のオーバーロード
        const S_Vector4& operator/=(T value);                                                   // /=演算子のオーバーロード

        /* キャスト演算子のオーバーロード */
        operator S_Vector2<T>() const;                                                          // S_Vector2型へのキャスト
        operator S_Vector3<T>() const;                                                          // S_Vector3型へのキャスト
        operator std::string() const;                                                           // string型へのキャスト

        #pragma region T型とのフレンド演算子のオーバーロード


        /*************************************************************//**
         *
         *  @brief  T型の値とベクトルを乗算する
         *  @param  T型の値
         *  @param  ベクトル
         *  @return 乗算したベクトル
         *
         ****************************************************************/
        friend S_Vector4 operator*(T value, const S_Vector4& rVector)
        {
            return S_Vector4(rVector.x_ * value, rVector.y_ * value, rVector.z_ * value, rVector.w_ * value);
        }


        /*************************************************************//**
         *
         *  @brief  T型の値とベクトルを除算する
         *  @param  T型の値
         *  @param  ベクトル
         *  @return 除算したベクトル
         *
         ****************************************************************/
        friend S_Vector4 operator/(T value, const S_Vector4& rVector)
        {
            assert(value != static_cast<T>(0));

            return S_Vector4(rVector.x_ / value, rVector.y_ / value, rVector.z_ / value, rVector.w_ / value);
        }


        #pragma endregion
    };


    /* 別名 */
    using Vector4 = S_Vector4<>;                                                                // Vector4型
}