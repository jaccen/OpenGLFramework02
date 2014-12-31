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
    struct S_Matrix4x4;

    template<typename T>
    struct S_Quaternion;

    //-------------------------------------------------------------
    //!
    //! @brief マトリクス3x3
    //! @brief 3 * 3の行列を表す構造体
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    struct S_Matrix3x3
    {
        /* 定数 */
        static const uint8_t s_ELEMENT_NUMBER = 9;                                                      ///< @brief 要素数
        static const S_Matrix3x3 s_ZERO;                                                                ///< @brief ゼロ行列
        static const S_Matrix3x3 s_IDENTITY;                                                            ///< @brief 単位行列

        /* メンバ変数 */
        union
        {
            T a_[s_ELEMENT_NUMBER];                                                                     ///< @brief 9個の要素を持つ配列
            T a3x3_[3][3];                                                                              ///< @brief 3 * 3の二次元配列

            /// @brief 行列の各要素
            struct
            {
                T a11_, a12_, a13_;
                T a21_, a22_, a23_;
                T a31_, a32_, a33_;
            };
        };

        /* メンバ関数 */
        S_Matrix3x3();                                                                                  // コンストラクタ
        S_Matrix3x3(T value);                                                                           // コンストラクタ
        S_Matrix3x3(T a11, T a12, T a13,                                                                // コンストラクタ
                    T a21, T a22, T a23,
                    T a31, T a32, T a33);
        explicit S_Matrix3x3(const T a[s_ELEMENT_NUMBER]);                                              // コンストラクタ
        S_Matrix3x3(const S_Matrix3x3& rOther) = default;                                               // コピーコンストラクタ 
        ~S_Matrix3x3();                                                                                 // デストラクタ
        void Zero();                                                                                    // ゼロ行列化
        void Fill(T value);                                                                             // 各要素を特定の値に変更
        void Identity();                                                                                // 単位行列化
        void Transpose();                                                                               // 転置行列化
        void Invert();                                                                                  // 逆行列化
        S_Matrix3x3 GetTranspose() const;                                                               // 転置行列を取得
        S_Matrix3x3 GetInvert() const;                                                                  // 逆行列を取得
        S_Vector3<T> GetRow(int32_t index = 0) const;                                                   // 行を取得
        S_Vector3<T> GetColumn(int32_t index = 0) const;                                                // 列を取得
        std::string GetConvertToString() const;                                                         // 行列を文字列へ変換して取得
        void SetRow(const S_Vector3<T>& rRow, int32_t index = 0);                                       // 行を設定
        void SetColumn(const S_Vector3<T>& rColumn, int32_t index = 0);                                 // 列を設定
        
        /* 静的メンバ関数 */
        static S_Matrix3x3 s_CreateRotation(T angle);                                                   // 回転行列を作成
        static S_Matrix3x3 s_CreateRotationX(T angle);                                                  // X軸から回転行列を作成
        static S_Matrix3x3 s_CreateRotationY(T angle);                                                  // Y軸から回転行列を作成
        static S_Matrix3x3 s_CreateRotationZ(T angle);                                                  // Z軸から回転行列を作成
        static S_Matrix3x3 s_CreateRotationAxis(const S_Vector3<T>& rAxis, T angle);                    // 任意軸から回転行列を作成 
        static S_Matrix3x3 s_CreateScaling(T scalingRateX, T scalingRateY);                             // 拡縮行列を作成
        static S_Matrix3x3 s_CreateTranslation(T movementX, T movementY);                               // 平行移動行列を作成
        static S_Matrix3x3 s_ConvertMatrix4x4ToMatrix3x3(const S_Matrix4x4<T>& rMatirx);                // 4 * 4の行列を3 * 3の行列に変換
        static S_Matrix3x3 s_ConvertQuaternionToMatrix3x3(const S_Quaternion<T>& rQuaternion);          // クォータニオンから3 * 3の行列へ変換し、取得
        static S_Matrix3x3 s_CreateNormal(const S_Matrix4x4<T>& rMatrix);                               // 法線行列を作成
        static S_Matrix3x3 s_CreateLookAt(const S_Vector3<T>& rEyePoint,                                // ビュー行列を作成
                                          const S_Vector3<T>& rTargetPoint,
                                          const S_Vector3<T>& rUpVector);

        /* S_Matrix3x3型との演算子のオーバーロード */
        const S_Matrix3x3 operator+(const S_Matrix3x3& rAnother) const;                                 // +演算子のオーバーロード
        const S_Matrix3x3 operator-(const S_Matrix3x3& rAnother) const;                                 // -演算子のオーバーロード
        const S_Matrix3x3 operator*(const S_Matrix3x3& rAnother) const;                                 // *演算子のオーバーロード
        const S_Matrix3x3& operator+=(const S_Matrix3x3& rAnother);                                     // +=演算子のオーバーロード
        const S_Matrix3x3& operator-=(const S_Matrix3x3& rAnother);                                     // -=演算子のオーバーロード
        const S_Matrix3x3& operator*=(const S_Matrix3x3& rAnother);                                     // *=演算子のオーバーロード
        bool operator==(const S_Matrix3x3& rAnother) const;                                             // ==演算子のオーバーロード
        bool operator!=(const S_Matrix3x3& rAnother) const;                                             // !=演算子のオーバーロード

        /* S_Vector3型との演算子のオーバーロード */
        const S_Vector3<T> operator*(const S_Vector3<T>& rVector) const;                                // *演算子のオーバーロード

        /* キャスト演算子のオーバーロード */
        operator std::string() const;                                                                   // string型へのキャスト
    };

    /* 別名 */
    using Matrix3x3 = S_Matrix3x3<>;                                                                     // Matrix3x3型
};