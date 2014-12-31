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
    /* 前方宣言 */
    template<typename T>
    struct S_Vector3;

    template<typename T>
    struct S_Vector4;

    template<typename T>
    struct S_Quaternion;

    template <typename T>
    struct S_Matrix3x3;

    //-------------------------------------------------------------
    //!
    //! @brief マトリクス4x4
    //! @brief 4 * 4の行列を表す構造体
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    struct S_Matrix4x4
    {
        /* 定数 */
        static const uint8_t s_ELEMENT_NUMBER = 16;                                                                 ///< @brief 要素数
        static const T s_ORTHOGRAPHIC_2D_NEAR;                                                                      ///< @brief 2D用の正投影の射影行列を作成時の視点から最も近いクリップ面
        static const T s_ORTHOGRAPHIC_2D_FAR;                                                                       ///< @brief 2D用の正投影の射影行列を作成時の視点から最も遠いクリップ面
        static const S_Matrix4x4 s_ZERO;                                                                            ///< @brief ゼロ行列
        static const S_Matrix4x4 s_IDENTITY;                                                                        ///< @brief 単位行列

        /* メンバ変数 */
        union
        {
            T a_[s_ELEMENT_NUMBER];                                                                                 ///< @brief 16個の要素を持つ配列
            T a4x4_[4][4];                                                                                          ///< @brief 4 * 4の二次元配列

            /// @brief 行列の各要素
            struct
            {
                T a11_, a12_, a13_, a14_;
                T a21_, a22_, a23_, a24_;
                T a31_, a32_, a33_, a34_;
                T a41_, a42_, a43_, a44_;
            };
        };

        /* メンバ関数 */
        S_Matrix4x4();                                                                                              // コンストラクタ
        S_Matrix4x4(T value);                                                                                       // コンストラクタ
        S_Matrix4x4(T a11, T a12, T a13, T a14,                                                                     // コンストラクタ
                    T a21, T a22, T a23, T a24,
                    T a31, T a32, T a33, T a34,
                    T a41, T a42, T a43, T a44);
        explicit S_Matrix4x4(const T a[s_ELEMENT_NUMBER]);                                                          // コンストラクタ
        S_Matrix4x4(const S_Matrix3x3<T>& rMatrix);                                                                 // コンストラクタ
        S_Matrix4x4(const S_Matrix4x4& rOther) = default;                                                           // コピーコンストラクタ
        ~S_Matrix4x4();                                                                                             // デストラクタ
        void Zero();                                                                                                // ゼロ行列化
        void Identity();                                                                                            // 単位行列化
        void Transpose();                                                                                           // 転置行列化
        void Invert();                                                                                              // 逆行列化
        S_Matrix4x4 GetTranspose() const;                                                                           // 転置行列を取得
        S_Matrix4x4 GetInvert() const;                                                                              // 逆行列を取得
        S_Vector3<T> GetTranslationComponent() const;                                                               // 平行移動成分を取得
        S_Vector3<T> GetScalingComponent() const;                                                                   // 拡縮成分を取得
        S_Vector3<T> GetLocalAxisX() const;                                                                         // ローカル座標のX軸を取得
        S_Vector3<T> GetLocalAxisY() const;                                                                         // ローカル座標のY軸を取得
        S_Vector3<T> GetLocalAxisZ() const;                                                                         // ローカル座標のZ軸を取得
        S_Vector4<T> GetRow(int32_t index = 0) const;                                                               // 行を取得
        S_Vector4<T> GetColumn(int32_t index = 0) const;                                                            // 列を取得
        std::string GetConvertToString() const;                                                                     // 行列を文字列へ変換して取得
        void SetRow(const S_Vector4<T>& rRow, int32_t index = 0);                                                   // 行を設定
        void SetColumn(const S_Vector4<T>& rColumn, int32_t index = 0);                                             // 列を設定
        
        /* 静的メンバ関数 */
        static S_Matrix4x4 s_CreateRotationX(T angle);                                                              // X軸から回転行列を作成
        static S_Matrix4x4 s_CreateRotationY(T angle);                                                              // Y軸から回転行列を作成
        static S_Matrix4x4 s_CreateRotationZ(T angle);                                                              // Z軸から回転行列を作成
        static S_Matrix4x4 s_CreateRotationAxis(const S_Vector3<T>& rAxis, T angle);                                // 任意軸から回転行列を作成
        static S_Matrix4x4 s_CreateRotationYawPitchRoll(T pitch,                                                    // 3軸の回転を反映した回転行列を作成
                                                        T yaw,
                                                        T roll);
        static S_Matrix4x4 s_CreateRotationYawPitchRoll(const S_Vector3<T>& rRotation);                             // 3軸の回転を反映した回転行列を作成
        static S_Matrix4x4 s_CreateScaling(T scalingRateX, T scalingRateY, T scalingRateZ);                         // 拡縮行列を作成
        static S_Matrix4x4 s_CreateScaling(const S_Vector3<T>& rScalingRate);                                       // 拡縮行列を作成
        static S_Matrix4x4 s_CreateTranslation(T movementX,                                                         // 平行移動行列を作成
                                               T movementY,
                                               T movementZ);
        static S_Matrix4x4 s_CreateTranslation(const S_Vector3<T>& rMovement);                                      // 平行移動行列を作成
        static S_Matrix4x4 s_CreateTRS(const S_Vector3<T>& rMovement,                                               // 拡縮・回転・平行移動を掛け合わせた行列を作成 
                                       const S_Vector3<T>& rRotation,
                                       const S_Vector3<T>& rScalingRate);
        static S_Matrix4x4 s_CreateLookAt(const S_Vector3<T>& rEyePoint,                                            // ビュー行列を作成
                                          const S_Vector3<T>& rTargetPoint,
                                          const S_Vector3<T>& rUpVector);
        static S_Matrix4x4 s_CreatePerspectiveProjection(T fieldOfViewY,                                            // 透視投影の射影行列を作成
                                                         T aspectRatio,
                                                         T nearClippingPlane,
                                                         T farClippingPlane);
        static S_Matrix4x4 s_CreateOrthographicProjection(T clipSpaceLeft,                                          // 正投影の射影行列を作成
                                                          T clipSpaceRight,
                                                          T clipSpaceBottom,
                                                          T clipSpaceTop,
                                                          T nearClippingPlane = s_ORTHOGRAPHIC_2D_NEAR,
                                                          T farClippingPlane = s_ORTHOGRAPHIC_2D_FAR);
        static S_Matrix4x4 s_ConvertMatrix3x3ToMatrix4x4(const S_Matrix3x3<T>& rMatrix);                            // 3 * 3行列から4 * 4の行列へ変換し、取得
        static S_Matrix4x4 s_ConvertQuaternionToMatrix4x4(const S_Quaternion<T>& rQuaternion);                      // クォータニオンから4 * 4の行列へ変換し、取得
        static S_Matrix4x4 s_CreateViewport(T windowWidth, T windowHeight);                                         // ビューポート行列を作成 
        static S_Matrix4x4 s_SlerpRotation(const S_Matrix4x4& rStartMatrix,                                         // 回転行列を球面線形補間
                                           const S_Matrix4x4& rEndMatix,
                                           T coefficient);

        /* S_Matrix4x4型との演算子のオーバーロード */
        const S_Matrix4x4 operator+(const S_Matrix4x4& rAnother) const;                                             // +演算子のオーバーロード
        const S_Matrix4x4 operator-(const S_Matrix4x4& rAnother) const;                                             // -演算子のオーバーロード
        const S_Matrix4x4 operator*(const S_Matrix4x4& rAnother) const;                                             // *演算子のオーバーロード
        const S_Matrix4x4& operator+=(const S_Matrix4x4& rAnother);                                                 // +=演算子のオーバーロード
        const S_Matrix4x4& operator-=(const S_Matrix4x4& rAnother);                                                 // -=演算子のオーバーロード
        const S_Matrix4x4& operator*=(const S_Matrix4x4& rAnother);                                                 // *=演算子のオーバーロード
        bool operator==(const S_Matrix4x4& rAnother) const;                                                         // ==演算子のオーバーロード
        bool operator!=(const S_Matrix4x4& rAnother) const;                                                         // !=演算子のオーバーロード

        /* S_Vector4との演算子のオーバーロード */
        const S_Vector4<T> operator*(const S_Vector4<T>& rVector) const;                                            // *演算子のオーバーロード

        /* キャスト演算子のオーバーロード */
        operator S_Matrix3x3<T>() const;                                                                            // S_Matrix3x3型へのキャスト
        operator std::string() const;                                                                               // string型へのキャスト
    };

    /* 別名 */
    using Matrix4x4 = S_Matrix4x4<>;                                                                                // Matrix4x4型
};