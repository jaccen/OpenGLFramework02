/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../../Math/Vector/Vector4.h"


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL関連の名前空間
//!
//-------------------------------------------------------------
namespace OpenGL
{
    /* 別名 */
    using Vector2 = Math::S_Vector2<float>;                                 // Vector2型
    using Vector3 = Math::S_Vector3<float>;                                 // Vector3型
    using Vector4 = Math::S_Vector4<float>;                                 // Vector4型


    //-------------------------------------------------------------
    //!
    //! @brief バーテックスPC
    //! @brief 座標・色を含む頂点を表す構造体
    //!
    //-------------------------------------------------------------
    struct S_VertexPC
    {
        Vector3 position_;                                                  ///< @brief 座標
        Vector4 color_;                                                     ///< @brief 色
    };


    //-------------------------------------------------------------
    //!
    //! @brief バーテックスPN
    //! @brief 座標・法線ベクトルを含む頂点を表す構造体
    //!
    //-------------------------------------------------------------
    struct S_VertexPN
    {
        Vector3 position_;                                                  ///< @brief 座標
        Vector3 normal_;                                                    ///< @brief 法線ベクトル
    };


    //-------------------------------------------------------------
    //!
    //! @brief バーテックスPNT
    //! @brief 座標・法線ベクトル・テクスチャ座標を含む頂点を表す構造体
    //!
    //-------------------------------------------------------------
    struct S_VertexPNT
    {
        Vector3 position_;                                                  ///< @brief 座標
        Vector3 normal_;                                                    ///< @brief 法線ベクトル
        Vector2 textureCoord_;                                              ///< @brief テクスチャ座標
    };


    //-------------------------------------------------------------
    //!
    //! @brief バーテックスPNTC
    //! @brief 座標・法線ベクトル・テクスチャ座標・色を含む頂点を表す構造体
    //!
    //-------------------------------------------------------------
    struct S_VertexPNTC
    {
        Vector3 position_;                                                  ///< @brief 座標
        Vector3 normal_;                                                    ///< @brief 法線ベクトル
        Vector2 textureCoord_;                                              ///< @brief テクスチャ座標
        Vector4 color_;                                                     ///< @brief 色
    };


    //-------------------------------------------------------------
    //!
    //! @brief バーテックスPNTT
    //! @brief 座標・法線ベクトル・テクスチャ座標・接ベクトルを含む頂点を表す構造体
    //!
    //-------------------------------------------------------------
    struct S_VertexPNTT
    {
        Vector3 position_;                                                  ///< @brief 座標
        Vector3 normal_;                                                    ///< @brief 法線ベクトル
        Vector2 textureCoord_;                                              ///< @brief テクスチャ座標
        Vector4 tangent_;                                                   ///< @brief 接ベクトル
    };


    //-------------------------------------------------------------
    //!
    //! @brief バーテックスPNTCT
    //! @brief 座標・法線ベクトル・テクスチャ座標・色・接ベクトルを含む頂点を表す構造体
    //!
    //-------------------------------------------------------------
    struct S_VertexPNTCT
    {
        Vector3 position_;                                                  ///< @brief 座標
        Vector3 normal_;                                                    ///< @brief 法線ベクトル
        Vector2 textureCoord_;                                              ///< @brief テクスチャ座標
        Vector4 color_;                                                     ///< @brief 色
        Vector4 tangent_;                                                   ///< @brief 接ベクトル
    };
}