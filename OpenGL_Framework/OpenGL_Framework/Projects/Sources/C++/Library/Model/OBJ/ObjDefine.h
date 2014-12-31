/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Math/MathAll.h"
#include <vector>


//-------------------------------------------------------------
//!
//! @brief モデル
//! @brief モデル関連の名前空間
//!
//-------------------------------------------------------------
namespace Model
{
    //-------------------------------------------------------------
    //!
    //! @brief OBJ
    //! @brief OBJ関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace OBJ
    {
        /* 別名 */
        using Vector2 = Math::S_Vector2<float>;             // Vector2型
        using Vector3 = Math::S_Vector3<float>;             // Vector3型
        using Vector4 = Math::S_Vector4<float>;             // Vector4型
        using Matrix3x3 = Math::S_Matrix3x3<float>;         // Matrix3x3型
        using Matrix4x4 = Math::S_Matrix4x4<float>;         // Matrix4x4型


        //-------------------------------------------------------------
        //!
        //! @brief バーテックス
        //! @brief 頂点を表す構造体
        //!
        //-------------------------------------------------------------
        struct S_Vertex
        {
            Vector3 position_;                              ///< @brief 座標
            Vector3 normal_;                                ///< @brief 法線ベクトル
            Vector2 textureCoord_;                          ///< @brief テクスチャ座標

            S_Vertex() = default;                           //!< @brief デフォルトコンストラクタ
            S_Vertex(const S_Vertex& rOther) = default;     //!< @brief デフォルトコピーコンストラクタ

            /*************************************************************//**
             *
             *  @brief  比較演算子( 等価 )のオーバーロード
             *  @param  頂点
             *
             ****************************************************************/
            bool operator ==(const S_Vertex& rOther) const
            {
                return std::memcmp(this, &rOther, sizeof(S_Vertex)) == 0;
            }
        };

        //-------------------------------------------------------------
        //!
        //! @brief マテリアル
        //! @brief マテリアルを表す構造体
        //!
        //-------------------------------------------------------------
        struct S_Material
        {
            std::string name_;                              ///< @brief 名前
            std::string ambientTextureFileName_;            ///< @brief アンビエントテクスチャのファイル名
            std::string diffuseTextureFileName_;            ///< @brief ディフューズテクスチャのファイル名
            std::string specularTextureFileName_;           ///< @brief スペキュラーテクスチャのファイル名
            Vector3 ambient_;                               ///< @brief アンビエント
            Vector3 diffuse_;                               ///< @brief ディフューズ
            Vector3 specular_;                              ///< @brief スペキュラー
            float shininess_ = 0.0f;                        ///< @brief 光沢
            float opacity_ = 0.0f;                          ///< @brief 不透明度

            S_Material() = default;                         //!< @brief デフォルトコンストラクタ

            /*************************************************************//**
             *
             *  @brief  ムーブコンストラクタ
             *  @param  マテリアル
             *
             ****************************************************************/
            S_Material(S_Material&& rrOther) :

                // 名前
                name_(std::move(rrOther.name_)),

                // 各テクスチャファイル名
                ambientTextureFileName_(std::move(rrOther.ambientTextureFileName_)),
                diffuseTextureFileName_(std::move(rrOther.diffuseTextureFileName_)),
                specularTextureFileName_(std::move(rrOther.specularTextureFileName_)),

                // マテリアルの各データ
                ambient_(rrOther.ambient_),
                diffuse_(rrOther.diffuse_),
                specular_(rrOther.specular_),
                shininess_(rrOther.shininess_),
                opacity_(rrOther.opacity_)

            {
            }
        };

        //-------------------------------------------------------------
        //!
        //! @brief メッシュ
        //! @brief メッシュを表す構造体
        //!
        //-------------------------------------------------------------
        struct S_Mesh
        {
            std::string materialName_;                      ///< @brief マテリアル名
            std::vector<S_Vertex> vertices_;                ///< @brief 頂点
            std::vector<uint16_t> indices_;                 ///< @brief インデックス

            S_Mesh() = default;                             //!< @brief デフォルトコンストラクタ

            /*************************************************************//**
             *
             *  @brief  ムーブコンストラクタ
             *  @param  メッシュ
             *
             ****************************************************************/
            S_Mesh(S_Mesh&& rrOther) :

                // マテリアル名
                materialName_(std::move(rrOther.materialName_)),

                // 頂点
                vertices_(std::move(rrOther.vertices_)),

                // インデックス
                indices_(std::move(rrOther.indices_))

            {
            }
        };
    }
}