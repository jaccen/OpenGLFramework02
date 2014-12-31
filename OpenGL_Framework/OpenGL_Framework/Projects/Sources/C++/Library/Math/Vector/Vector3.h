/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "Vector2.h"
#include <tuple>


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
    //! @brief ベクター3
    //! @brief 3Dベクトルを表す構造体
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    struct S_Vector3
    {
        /* 定数 */
        static const S_Vector3 s_RIGHT_DIRECTION;                                                                   ///< @brief 右向き ( 1,  0,  0)
        static const S_Vector3 s_LEFT_DIRECTION;                                                                    ///< @brief 左向き (-1,  0,  0)
        static const S_Vector3 s_UP_DIRECTION;                                                                      ///< @brief 上向き ( 0,  1,  0)
        static const S_Vector3 s_DOWN_DIRECTION;                                                                    ///< @brief 下向き ( 0, -1,  0)
        static const S_Vector3 s_FRONT_DIRECTION;                                                                   ///< @brief 前向き ( 0,  0,  1)
        static const S_Vector3 s_BACK_DIRECTION;                                                                    ///< @brief 後向き ( 0,  0, -1)
        static const S_Vector3 s_ZERO;                                                                              ///< @brief ゼロベクトル
        static const S_Vector3 s_ONE;                                                                               ///< @brief 全ての要素が1

        /* メンバ変数 */
        union
        {
            T a_[3];                                                                                                ///< @brief 3つの要素を持つ配列

            struct
            {
                T x_;                                                                                               ///< @brief X成分
                T y_;                                                                                               ///< @brief Y成分
                T z_;                                                                                               ///< @brief Z成分
            };

            struct
            {
                T u_;                                                                                               ///< @brief U成分
                T v_;                                                                                               ///< @brief V成分
                T w_;                                                                                               ///< @brief W成分
            };

            struct
            {
                T red_;                                                                                             ///< @brief 赤
                T green_;                                                                                           ///< @brief 緑
                T blue_;                                                                                            ///< @brief 青
            };

            struct
            {
                T width_;                                                                                           ///< @brief 幅
                T height_;                                                                                          ///< @brief 高さ
                T depth_;                                                                                           ///< @brief 奥行き
            };

            struct
            {
                S_Vector2<T> xy_;                                                                                   ///< @brief X・Y成分
            };
        };

        /* メンバ関数 */
        S_Vector3();                                                                                                // コンストラクタ
        explicit S_Vector3(T value);                                                                                // コンストラクタ
        S_Vector3(T x, T y, T z);                                                                                   // コンストラクタ
        explicit S_Vector3(const T a[3]);                                                                           // コンストラクタ
        S_Vector3(const S_Vector2<T>& rXY, T z);                                                                    // コンストラクタ
        S_Vector3(const S_Vector3& rOther) = default;                                                               // コピーコンストラクタ
        ~S_Vector3();                                                                                               // デストラクタ
        void Zero();                                                                                                // ゼロベクトル化
        void Fill(T value);                                                                                         // 各成分を特定の値に変更
        void Normalize();                                                                                           // 単位ベクトル化
        void Invert();                                                                                              // ベクトルを反転
        void RotateX(T angle);                                                                                      // X軸からベクトルを回転
        void RotateY(T angle);                                                                                      // Y軸からベクトルを回転
        void RotateZ(T angle);                                                                                      // Z軸からベクトルを回転
        void RotateAxis(const S_Vector3<T>& rAxis, T angle);                                                        // 任意軸からベクトルを回転
        void ClampLength(T minLength, T maxLength);                                                                 // 長さでベクトルをクランプ
        T GetLength() const;                                                                                        // 長さを取得
        T GetLengthSquare() const;                                                                                  // 長さの2乗を取得
        S_Vector3 GetNormalize() const;                                                                             // 単位ベクトルを取得
        S_Vector3 GetInvert() const;                                                                                // 反転したベクトルを取得
        S_Vector3 GetRotateX(T angle) const;                                                                        // X軸から回転したベクトルを取得
        S_Vector3 GetRotateY(T angle) const;                                                                        // Y軸から回転したベクトルを取得
        S_Vector3 GetRotateZ(T angle) const;                                                                        // Z軸から回転したベクトルを取得
        S_Vector3 GetRotateAxis(const S_Vector3<T>& rAxis, T angle) const;                                          // 任意軸から回転したベクトルを取得
        S_Vector3 GetClampLength(T minLength, T maxLength) const;                                                   // 長さでクランプしたベクトルを取得
        std::string GetConvertToString() const;                                                                     // ベクトルを文字列へ変換して取得

        /* 静的メンバ変数 */
        static T s_DotProduct(const S_Vector3& rLhs, const S_Vector3& rRhs);                                        // 内積
        static S_Vector3 s_CrossProduct(const S_Vector3& rLhs, const S_Vector3& rRhs);                              // 外積
        static T s_ScalarTripleProduct(const S_Vector3& rA,                                                         // スカラー三重積
                                       const S_Vector3& rB,
                                       const S_Vector3& rC);
        static S_Vector3 s_VectorTripleProduct(const S_Vector3& rA,                                                 // ベクトル三重積
                                               const S_Vector3& rB,
                                               const S_Vector3& rC);
        static S_Vector3 s_Lerp(const S_Vector3& rStartPoint,                                                       // 線形補間
                                const S_Vector3& rEndPoint,
                                T coefficient);
        static S_Vector3 s_Slerp(const S_Vector3& rStartPoint,                                                      // 球面線形補間
                                 const S_Vector3& rEndPoint,
                                 T coefficient);
        static S_Vector3 s_Hermite(const S_Vector3& rStartPoint,                                                    // エルミート補間
                                   const S_Vector3& rStartTangent,
                                   const S_Vector3& rEndPoint,
                                   const S_Vector3& rEndTangent,
                                   T coefficient);
        static S_Vector3 s_CatmullRomSpline(const S_Vector3& rPreviousStartPoint,                                   // Catmull-Romスプライン補間
                                            const S_Vector3& rStartPoint,                       
                                            const S_Vector3& rEndPoint,
                                            const S_Vector3& rNextEndPoint,
                                            T coefficient);
        static S_Vector3 s_Bezier(const S_Vector3& rStartPoint,                                                     // ベジェ補間
                                  const S_Vector3& rEndPoint,
                                  const S_Vector3& rControlPoint1,
                                  const S_Vector3& rControlPoint2,
                                  T coefficient);
        static S_Vector3 s_InterceptPoint(const S_Vector3& rPosition,                                               // 迎撃ポイントを取得
                                          const S_Vector3& rVelocity,
                                          const S_Vector3& rAnotherPosition,
                                          const S_Vector3& rAnotherVelocity);
        static T s_AngleBetweenVectors(const S_Vector3& rLhs, const S_Vector3& rRhs);                               // ベクトル間の角度を取得
        static T s_DistanceBetweenVectors(const S_Vector3& rLhs, const S_Vector3& rRhs);                            // ベクトル間の距離を取得
        static S_Vector3 s_Minimize(const S_Vector3& rLhs, const S_Vector3& rRhs);                                  // 各成分の最小値を成分にしたベクトルを取得
        static S_Vector3 s_Maximize(const S_Vector3& rLhs, const S_Vector3& rRhs);                                  // 各成分の最大値を成分にしたベクトルを取得
        static S_Vector3 s_MoveTowards(const S_Vector3& rStartPoint,                                                // 2点間からの距離分だけ進んだ点を取得
                                       const S_Vector3& rEndPoint,
                                       T distance);
        static S_Vector3 s_Project(const S_Vector3& rVector, const S_Vector3& rNormal);                             // 投影ベクトルを取得
        static S_Vector3 s_Reflect(const S_Vector3& rVector, const S_Vector3& rNormal);                             // 反射ベクトルを取得
        static S_Vector3 s_Refract(const S_Vector3& rIncidentVector,                                                // 屈折ベクトルを取得
                                   const S_Vector3& rNormal, 
                                   T refractiveIndex);
        static S_Vector3 s_Slide(const S_Vector3& rVector, const S_Vector3& rNormal);                               // 滑りベクトルを取得
        static S_Vector3 s_CreateNormal(const S_Vector3& rPositionA,                                                // 法線ベクトルを作成
                                        const S_Vector3& rPositionB,
                                        const S_Vector3& rPositionC);
        static std::tuple<S_Vector3, S_Vector3> s_CreateTangentAndBinormal(const S_Vector3& rPositionA,             // 接線ベクトルと従法線を作成( 直行化はされてない )
                                                                           const S_Vector2<T>& rTextureCoordA,
                                                                           const S_Vector3& rPositionB,
                                                                           const S_Vector2<T>& rTextureCoordB,
                                                                           const S_Vector3& rPositionC,
                                                                           const S_Vector2<T>& rTextureCoordC);
        static S_Vector3 s_CenterOfGravityWith3Points(const S_Vector3& rA,                                          // 3点から重心を取得
                                                      const S_Vector3& rB,
                                                      const S_Vector3& rC);
        

        /* S_Vector3型との演算子のオーバーロード */
        const S_Vector3 operator+(const S_Vector3& rAnother) const;                                                 // +演算子のオーバーロード
        const S_Vector3 operator-(const S_Vector3& rAnother) const;                                                 // -演算子のオーバーロード
        const S_Vector3 operator*(const S_Vector3& rAnother) const;                                                 // *演算子のオーバーロード
        const S_Vector3 operator/(const S_Vector3& rAnother) const;                                                 // /演算子のオーバーロード
        const S_Vector3& operator+=(const S_Vector3& rAnother);                                                     // +=演算子のオーバーロード
        const S_Vector3& operator-=(const S_Vector3& rAnother);                                                     // -=演算子のオーバーロード
        const S_Vector3& operator*=(const S_Vector3& rAnother);                                                     // *=演算子のオーバーロード
        const S_Vector3& operator/=(const S_Vector3& rAnother);                                                     // /=演算子のオーバーロード
        bool operator==(const S_Vector3& rAnother) const;                                                           // ==演算子のオーバーロード
        bool operator!=(const S_Vector3& rAnother) const;                                                           // !=演算子のオーバーロード

        /* T型との演算子のオーバーロード */
        const S_Vector3 operator*(T value) const;                                                                   // *演算子のオーバーロード
        const S_Vector3 operator/(T value) const;                                                                   // /演算子のオーバーロード
        const S_Vector3& operator*=(T value);                                                                       // *=演算子のオーバーロード
        const S_Vector3& operator/=(T value);                                                                       // /=演算子のオーバーロード

        /* キャスト演算子のオーバーロード */
        operator S_Vector2<T>() const;                                                                              // S_Vector2型へのキャスト
        operator std::string() const;                                                                               // string型へのキャスト


        #pragma region T型とのフレンド演算子のオーバーロード


        /*************************************************************//**
         *
         *  @brief  T型の値とベクトルを乗算する
         *  @param  T型の値
         *  @param  ベクトル
         *  @return 乗算したベクトル
         *
         ****************************************************************/
        friend const S_Vector3 operator*(T value, const S_Vector3& rVector)
        {
            return S_Vector3(rVector.x_ * value, rVector.y_ * value, rVector.z_ * value);
        }


        /*************************************************************//**
         *
         *  @brief  T型の値とベクトルを除算する
         *  @param  T型の値
         *  @param  ベクトル
         *  @return 除算したベクトル
         *
         ****************************************************************/
        friend const S_Vector3 operator/(T value, const S_Vector3& rVector)
        {
            assert(value != static_cast<T>(0));

            return S_Vector3(rVector.x_ / value, rVector.y_ / value, rVector.z_ / value);
        }


        #pragma endregion
    };

    /* 別名 */
    using Vector3 = S_Vector3<>;                                                                                    // Vector3型
}
