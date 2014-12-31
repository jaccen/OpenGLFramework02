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
    //! @brief ベクター2
    //! @brief 2Dベクトルを表す構造体
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    struct S_Vector2
    {
        /* 定数 */
        static const S_Vector2 s_RIGHT_DIRECTION;                                               ///< @brief 右向き ( 1,  0)
        static const S_Vector2 s_LEFT_DIRECTION;                                                ///< @brief 左向き (-1,  0)
        static const S_Vector2 s_UP_DIRECTION;                                                  ///< @brief 上向き ( 0,  1)
        static const S_Vector2 s_DOWN_DIRECTION;                                                ///< @brief 下向き ( 0, -1)
        static const S_Vector2 s_ZERO;                                                          ///< @brief ゼロベクトル
        static const S_Vector2 s_ONE;                                                           ///< @brief 全ての要素が1

        /* メンバ変数 */
        union
        {
            T a_[2];                                                                            ///< @brief 2つの要素を持つ配列

            struct
            {
                T x_;                                                                           ///< @brief X成分
                T y_;                                                                           ///< @brief Y成分
            };

            struct
            {
                T u_;                                                                           ///< @brief U成分
                T v_;                                                                           ///< @brief V成分
            };

            struct
            {
                T width_;                                                                       ///< @brief 幅
                T height_;                                                                      ///< @brief 高さ
            };
        };

        /* メンバ関数 */
        S_Vector2();                                                                            // コンストラクタ
        explicit S_Vector2(T value);                                                            // コンストラクタ
        S_Vector2(T x, T y);                                                                    // コンストラクタ
        explicit S_Vector2(const T a[2]);                                                       // コンストラクタ
        S_Vector2(const S_Vector2& rOhter) = default;                                           // コピーコンストラクタ
        ~S_Vector2();                                                                           // デストラクタ
        void Zero();                                                                            // ゼロベクトル化
        void Fill(T value);                                                                     // 各成分を特定の値に変更
        void Normalize();                                                                       // 単位ベクトル化
        void Invert();                                                                          // ベクトルを反転
        void Perpendicular();                                                                   // 垂直なベクトルに変換
        void Rotate(T angle);                                                                   // ベクトルを回転
        void ClampLength(T minLength, T maxLength);                                             // 長さでベクトルをクランプ
        T GetLength() const;                                                                    // 長さを取得
        T GetLengthSquare() const;                                                              // 長さの2乗を取得
        S_Vector2 GetNormalize() const;                                                         // 単位ベクトルを取得
        S_Vector2 GetInvert() const;                                                            // 反転したベクトルを取得
        S_Vector2 GetPerpendicular() const;                                                     // 垂直なベクトルを取得
        S_Vector2 GetRotate(T angle) const;                                                     // 回転したベクトルを取得
        T GetAngle() const;                                                                     // ベクトルの角度を取得
        S_Vector2 GetClampLength(T minLength, T maxLength) const;                               // 長さでクランプしたベクトルを取得
        std::string GetConvertToString() const;                                                 // ベクトルを文字列へ変換して取得

        /* 静的メンバ関数 */
        static T s_DotProduct(const S_Vector2& rLhs, const S_Vector2& rRhs);                    // 内積
        static T s_CrossProduct(const S_Vector2& rLhs, const S_Vector2& rRhs);                  // 外積
        static S_Vector2 s_Lerp(const S_Vector2& rStartPoint,                                   // 線形補間
                                const S_Vector2& rEndPoint,
                                T coefficient);
        static S_Vector2 s_Slerp(const S_Vector2& rStartPoint,                                  // 球面線形補間
                                 const S_Vector2& rEndPoint,
                                 T coefficient);
        static S_Vector2 s_Hermite(const S_Vector2& rStartPoint,                                // エルミート補間
                                   const S_Vector2& rStartTangent,
                                   const S_Vector2& rEndPoint,
                                   const S_Vector2& rEndTangent,
                                   T coefficient);
        static S_Vector2 s_CatmullRomSpline(const S_Vector2& rPreviousStartPoint,               // Catmull-Romスプライン補間
                                            const S_Vector2& rStartPoint,                       
                                            const S_Vector2& rEndPoint,
                                            const S_Vector2& rNextEndPoint,
                                            T coefficient);
        static S_Vector2 s_Bezier(const S_Vector2& rStartPoint,                                 // ベジェ補間
                                  const S_Vector2& rEndPoint,
                                  const S_Vector2& rControlPoint1,
                                  const S_Vector2& rControlPoint2,
                                  T coefficient);
        static S_Vector2 s_CreateWithAngle(T angle, T length = static_cast<T>(1.0));            // 角度からベクトルを作成
        static S_Vector2 s_InterceptPoint(const S_Vector2& rPosition,                           // 迎撃ポイントを取得
                                          const S_Vector2& rVelocity,
                                          const S_Vector2& rAnotherPosition,
                                          const S_Vector2& rAnotherVelocity);
        static T s_AngleBetweenVectors(const S_Vector2& rLhs, const S_Vector2& rRhs);           // ベクトル間の角度を取得
        static T s_DistanceBetweenVectors(const S_Vector2& rLhs, const S_Vector2& rRhs);        // ベクトル間の距離を取得
        static S_Vector2 s_Minimize(const S_Vector2& rLhs, const S_Vector2& rRhs);              // 各成分の最小値を成分にしたベクトルを取得
        static S_Vector2 s_Maximize(const S_Vector2& rLhs, const S_Vector2& rRhs);              // 各成分の最大値を成分にしたベクトルを取得
        static S_Vector2 s_MoveTowards(const S_Vector2& rStartPoint,                            // 2点間からの距離分だけ進んだ点を取得
                                       const S_Vector2& rEndPoint,
                                       T distance);
        static S_Vector2 s_Project(const S_Vector2& rVector, const S_Vector2& rNormal);         // 投影ベクトルを取得
        static S_Vector2 s_Reflect(const S_Vector2& rVector, const S_Vector2& rNormal);         // 反射ベクトルを取得
        static S_Vector2 s_Refract(const S_Vector2& rIncidentVector,                            // 屈折ベクトルを取得
                                   const S_Vector2& rNormal, 
                                   T refractiveIndex);
        static S_Vector2 s_Slide(const S_Vector2& rVector, const S_Vector2& rNormal);           // 滑りベクトルを取得
        static S_Vector2 s_CenterOfGravityWith3Points(const S_Vector2& rA,                      // 3点から重心を取得
                                                      const S_Vector2& rB,
                                                      const S_Vector2& rC);
            

        /* S_Vector2型との演算子のオーバーロード */
        const S_Vector2 operator+(const S_Vector2& rAnother) const;                             // +演算子のオーバーロード
        const S_Vector2 operator-(const S_Vector2& rAnother) const;                             // -演算子のオーバーロード
        const S_Vector2 operator*(const S_Vector2& rAnother) const;                             // *演算子のオーバーロード
        const S_Vector2 operator/(const S_Vector2& rAnother) const;                             // /演算子のオーバーロード
        const S_Vector2& operator+=(const S_Vector2& rAnother);                                 // +=演算子のオーバーロード
        const S_Vector2& operator-=(const S_Vector2& rAnother);                                 // -=演算子のオーバーロード
        const S_Vector2& operator*=(const S_Vector2& rAnother);                                 // *=演算子のオーバーロード
        const S_Vector2& operator/=(const S_Vector2& rAnother);                                 // /=演算子のオーバーロード
        bool operator==(const S_Vector2& rAnother) const;                                       // ==演算子のオーバーロード
        bool operator!=(const S_Vector2& rAnother) const;                                       // !=演算子のオーバーロード

        /* T型との演算子のオーバーロード */
        const S_Vector2 operator*(T value) const;                                               // *演算子のオーバーロード
        const S_Vector2 operator/(T value) const;                                               // /演算子のオーバーロード
        const S_Vector2& operator*=(T value);                                                   // *=演算子のオーバーロード
        const S_Vector2& operator/=(T value);                                                   // /=演算子のオーバーロード

        /* キャスト演算子のオーバーロード */
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
        friend const S_Vector2 operator*(T value, const S_Vector2& rVector)
        {
            return S_Vector2(rVector.x_ * value, rVector.y_ * value);
        }


        /*************************************************************//**
         *
         *  @brief  T型の値とベクトルを乗算する
         *  @param  T型の値
         *  @param  ベクトル
         *  @return 乗算したベクトル
         *
         ****************************************************************/
        friend const S_Vector2 operator/(T value, const S_Vector2& rVector)
        {
            assert(value != static_cast<T>(0));

            return S_Vector2(rVector.x_ / value, rVector.y_ / value);
        }


        #pragma endregion
    };

    /* 別名 */
    using Vector2 = S_Vector2<>;                                                                // Vector2型
}