/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Vector/Vector3.h"


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
    struct S_Matrix3x3;

    template<typename T>
    struct S_Matrix4x4;

    //-------------------------------------------------------------
    //!
    //! @brief クォータニオン
    //! @brief クォータニオンを表す構造体
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    struct S_Quaternion
    {
        /* 定数 */
        static const S_Quaternion s_IDENTITY;                                                               ///< @brief 単位クォータニオン

        /* メンバ変数 */
        union
        {
            T a_[4];                                                                                        ///< brief 4つの要素を持つ配列

            struct
            {
                T t_;                                                                                       ///< @brief T成分
                T x_;                                                                                       ///< @brief X成分
                T y_;                                                                                       ///< @brief Y成分
                T z_;                                                                                       ///< @brief Z成分
            };

            struct
            {
                T t_;                                                                                       ///< @brief T成分
                S_Vector3<T> xyz_;                                                                          ///< @brief X・Y・Z成分
            };
        };

        /* メンバ関数 */
        S_Quaternion();                                                                                     // コンストラクタ
        explicit S_Quaternion(T value);                                                                     // コンストラクタ
        S_Quaternion(T t, T x, T y, T z);                                                                   // コンストラクタ
        S_Quaternion(T t, const S_Vector3<T>& rXYZ);                                                        // コンストラクタ
        S_Quaternion(const S_Quaternion& rOther) = default;                                                 // コピーコンストラクタ
        ~S_Quaternion();                                                                                    // デストラクタ
        void Fill(T value);                                                                                 // 各成分を特定の値に変更
        void Identity();                                                                                    // 単位クォータニオン化
        void Normalize();                                                                                   // 正規化
        void Invert();                                                                                      // 逆クォータニオン化
        T GetLength() const;                                                                                // 長さを取得
        T GetLengthSquare() const;                                                                          // 長さの2乗を取得
        S_Quaternion GetNormalize() const;                                                                  // 正規化したクォータニオンを取得
        S_Quaternion GetInvert() const;                                                                     // 逆クォータニオンを取得
        T GetAngleFromXAxis() const;                                                                        // X軸からの角度を取得
        T GetAngleFromYAxis() const;                                                                        // Y軸からの角度を取得
        T GetAngleFromZAxis() const;                                                                        // Z軸からの角度を取得
        std::tuple<S_Vector3<T>, T> GetAxisAndAngle() const;                                                // 軸と角度を取得
        std::string GetConvertToString() const;                                                             // クォータニオンを文字列に変換して取得

        /* 静的メンバ関数 */
        static T s_DotProduct(const S_Quaternion<T>& rLhs, const S_Quaternion<T>& rRhs);                    // 内積
        static S_Quaternion s_CreateRotationAxis(const S_Vector3<T>& rAxis,                                 // 任意軸からクォータニオンを作成
                                                 T angle);
        static S_Quaternion s_CreateRotationPitchYawRoll(T pitch,                                           // 3軸の回転を反映したクォータニオンを作成
                                                         T yaw,
                                                         T roll);
        static S_Quaternion s_CreateRotationPitchYawRoll(const S_Vector3<T>& rRotation);                    // 3軸の回転を反映したクォータニオンを作成
        static S_Quaternion s_CreateLookRotation(const S_Vector3<T>& rDirection,                            // 任意の向きへ向くためのクォータニオンを作成
                                                 const S_Vector3<T>& rUpVector);
        static S_Quaternion s_CreateFromToRotation(const S_Vector3<T>& rFromDirection,                      // 向きから向きへ回転させるクォータニオンを作成 
                                                   const S_Vector3<T>& rToDirection);
        static S_Quaternion s_ConvertMatrix3x3ToQuaternion(const S_Matrix3x3<T>& rMatrix);                  // 3 * 3の行列からクォータニオンへ変換して取得
        static S_Quaternion s_ConvertMatrix4x4ToQuaternion(const S_Matrix4x4<T>& rMatrix);                  // 4 * 4の行列からクォータニオンへ変換して取得
        static S_Quaternion s_Lerp(const S_Quaternion& rStart,                                              // 線形補間
                                   const S_Quaternion& rEnd,
                                   T coefficient);
        static S_Quaternion s_Slerp(const S_Quaternion& rStart,                                             // 球面線形補間
                                    const S_Quaternion& rEnd,
                                    T coefficient);

        /* S_Quaternion型との演算子のオーバーロード */
        const S_Quaternion operator+(const S_Quaternion& rAnother) const;                                   // +演算子のオーバーロード
        const S_Quaternion& operator+=(const S_Quaternion& rAnother);                                       // +=演算子のオーバーロード
        const S_Quaternion operator-(const S_Quaternion& rAnother) const;                                   // -演算子のオーバーロード
        const S_Quaternion& operator-=(const S_Quaternion& rAnother);                                       // -=演算子のオーバーロード
        const S_Quaternion operator*(const S_Quaternion& rAnother) const;                                   // *演算子のオーバーロード
        const S_Quaternion& operator*=(const S_Quaternion& rAnother);                                       // *=演算子のオーバーロード
        bool operator==(const S_Quaternion& rAnother) const;                                                // ==演算子のオーバーロード
        bool operator!=(const S_Quaternion& rAnother) const;                                                // !=演算子のオーバーロード

        /* T型との演算子のオーバーロード */
        const S_Quaternion operator*(T value) const;                                                        // *演算子のオーバーロード
        const S_Quaternion& operator*=(T value);                                                            // *=演算子のオーバーロード

        /* キャスト演算子のオーバーロード */
        operator S_Vector3<T>() const;                                                                      // S_Vector3型へのキャスト
        operator std::string() const;                                                                       // string型へのキャスト

        #pragma region T型とのフレンド演算子のオーバーロード


        /*************************************************************//**
         *
         *  @brief  T型の値とクォータニオンを乗算する
         *  @param  T型の値
         *  @param  クォータニオン
         *  @return 乗算したクォータニオン
         *
         ****************************************************************/
        friend const S_Quaternion operator*(T value,
                                            const S_Quaternion& rQuaternion)
        {
            return S_Quaternion(rQuaternion.t_ * value,
                                rQuaternion.x_ * value,
                                rQuaternion.y_ * value,
                                rQuaternion.z_ * value);
        }


        #pragma endregion
    };

    /* 別名 */
    using Quaternion = S_Quaternion<>;                                                                      // Quaternion型
}
