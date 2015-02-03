/* 二重インクルード防止 */
#pragma once


//-------------------------------------------------------------
//!
//! @brief キーフレーム
//! @brief キーフレーム関連の名前空間
//!
//-------------------------------------------------------------
namespace KeyFrame
{
    /** 補間の種類 */
    enum class ecInterpolationType
    {
        CONSTANT,                                       ///< @brief 一定
        LINEAR,                                         ///< @brief 線形補間
        HERMITE,                                        ///< @brief エルミート補間
    };


    //-------------------------------------------------------------
    //!
    //! @brief キー
    //! @brief キーを表す構造体
    //!
    //-------------------------------------------------------------
    template<typename T>
    struct S_Key
    {
        ecInterpolationType interpolationType_;         ///< @brief 種類
        int32_t frame_;                                 ///< @brief フレーム数
        T value_;                                       ///< @brief 値
        T tangent_;                                     ///< @brief 接線
    };
}