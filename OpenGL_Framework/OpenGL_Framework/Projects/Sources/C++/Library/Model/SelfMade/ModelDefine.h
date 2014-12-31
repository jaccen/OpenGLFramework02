/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Math/MathAll.h"
#include <array>
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
    //! @brief SelfMade
    //! @brief 自作関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace SelfMade
    {
        /* 別名 */
        using Vector2 = Math::S_Vector2<float>;                                 // Vector2型
        using Vector3 = Math::S_Vector3<float>;                                 // Vector3型
        using Vector4 = Math::S_Vector4<float>;                                 // Vector4型
        using Matrix3x3 = Math::S_Matrix3x3<float>;                             // Matrix3x3型
        using Matrix4x4 = Math::S_Matrix4x4<float>;                             // Matrix4x4型

        //-------------------------------------------------------------
        //!
        //! @brief ボーンウェイト
        //! @brief ボーンのウェイトを表す構造体
        //!
        //-------------------------------------------------------------
        struct S_BoneWeight
        {
            std::array<uint8_t, 4> indices_;                                    ///< @brief インデックス
            Vector4 weights_;                                                   ///< @brief ウェイト

            S_BoneWeight() = default;                                           //!< @brief デフォルトコンストラクタ

            /*************************************************************//**
             *
             *  @brief  ムーブコンストラクタ
             *  @param  ボーンウェイト
             *
             ****************************************************************/
            S_BoneWeight(S_BoneWeight&& rrOther) :

                // インデックス
                indices_(std::move(rrOther.indices_)),

                // ウェイト
                weights_(rrOther.weights_)

            {
            }
        };

        //-------------------------------------------------------------
        //!
        //! @brief バーテックス
        //! @brief 頂点を表す構造体
        //!
        //-------------------------------------------------------------
        struct S_Vertex
        {
            Vector3 position_;                                                  ///< @brief 座標
            Vector3 normal_;                                                    ///< @brief 法線ベクトル
            Vector2 textureCoord_;                                              ///< @brief テクスチャ座標
            Vector4 color_;                                                     ///< @brief 色
            Vector4 tangent_;                                                   ///< @brief 接ベクトル
            S_BoneWeight boneWeights_;                                          ///< @brief ボーンのウェイト

            S_Vertex() = default;                                               //!< @brief デフォルトコンストラクタ

            /*************************************************************//**
             *
             *  @brief  ムーブコンストラクタ
             *  @param  頂点
             *
             ****************************************************************/
            S_Vertex(S_Vertex&& rrOther) :

                // 座標
                position_(rrOther.position_),

                // 法線ベクトル
                normal_(rrOther.normal_),

                // テクスチャ座標
                textureCoord_(rrOther.textureCoord_),

                // 色
                color_(rrOther.color_),

                // 接ベクトル
                tangent_(rrOther.tangent_),

                // ボーンのウェイト
                boneWeights_(rrOther.boneWeights_)

            {
            }

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
            std::string name_;                                                  ///< @brief 名前
            Vector3 ambient_;                                                   ///< @brief アンビエント
            Vector3 diffuse_;                                                   ///< @brief ディフューズ
            Vector3 specular_;                                                  ///< @brief スペキュラー
            Vector3 emissive_;                                                  ///< @brief エミッシブ
            float shininess_ = 0.0f;                                            ///< @brief 光沢
            float opacity_ = 0.0f;                                              ///< @brief 不透明度
            float reflectivity_ = 0.0f;                                         ///< @brief 反射率
            std::string ambientTextureFileName_;                                ///< @brief アンビエントテクスチャのファイル名
            std::string diffuseTextureFileName_;                                ///< @brief ディフューズテクスチャのファイル名
            std::string specularTextureFileName_;                               ///< @brief スペキュラーテクスチャのファイル名

            S_Material() = default;                                             //!< @brief デフォルトコンストラクタ

            /*************************************************************//**
             *
             *  @brief  ムーブコンストラクタ
             *  @param  マテリアル
             *
             ****************************************************************/
            S_Material(S_Material&& rrOther) :

                // 名前
                name_(std::move(rrOther.name_)),

                // マテリアルの各データ
                ambient_(rrOther.ambient_),
                diffuse_(rrOther.diffuse_),
                specular_(rrOther.specular_),
                emissive_(rrOther.emissive_),
                shininess_(rrOther.shininess_),
                opacity_(rrOther.opacity_),
                reflectivity_(rrOther.reflectivity_),

                // 各テクスチャファイル名
                ambientTextureFileName_(std::move(rrOther.ambientTextureFileName_)),
                diffuseTextureFileName_(std::move(rrOther.diffuseTextureFileName_)),
                specularTextureFileName_(std::move(rrOther.specularTextureFileName_))

            {
            }
        };


        //-------------------------------------------------------------
        //!
        //! @brief ボーン
        //! @brief ボーンを表す構造体
        //!
        //-------------------------------------------------------------
        struct S_Bone
        {
            std::string name_;                                                  ///< @brief 名前
            std::string parentName_;                                            ///< @brief 親の名前
            Matrix4x4 inverseBaseposeMatrix_;                                   ///< @brief 基本姿勢の逆行列
            std::vector<Matrix4x4> eachFrameAnimationMatrices_;                 ///< @brief 各フレームの行列

            S_Bone() = default;                                                 //!< @brief デフォルトコンストラクタ

            /*************************************************************//**
             *
             *  @brief  ムーブコンストラクタ
             *  @param  ボーン
             *
             ****************************************************************/
            S_Bone(S_Bone&& rrOther) :

                // 名前
                name_(std::move(rrOther.name_)),

                // 親の名前
                parentName_(std::move(rrOther.parentName_)),

                // 基本姿勢の逆行列
                inverseBaseposeMatrix_(rrOther.inverseBaseposeMatrix_),

                // 各フレームのアニメーション行列
                eachFrameAnimationMatrices_(std::move(rrOther.eachFrameAnimationMatrices_))

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
            std::string name_;                                                  ///< @brief 名前
            std::string parentName_;                                            ///< @brief 親の名前
            std::string materialName_;                                          ///< @brief マテリアル名
            std::vector<S_Vertex> vertices_;                                    ///< @brief 頂点
            std::vector<uint16_t> indices_;                                     ///< @brief インデックス
            Matrix4x4 inverseBaseposeMatrix_;                                   ///< @brief 基本姿勢の逆行列
            std::vector<S_Bone> bones_;                                         ///< @brief ボーン
            std::vector<Matrix4x4> eachFrameAnimationMatrices_;                 ///< @brief 各フレームのアニメーション行列

            S_Mesh() = default;                                                 //!< @brief デフォルトコンストラクタ

            /*************************************************************//**
             *
             *  @brief  ムーブコンストラクタ
             *  @param  メッシュ
             *
             ****************************************************************/
            S_Mesh(S_Mesh&& rrOther) :

                // 名前
                name_(std::move(rrOther.name_)),

                // 親の名前
                parentName_(std::move(rrOther.parentName_)),

                // マテリアル名
                materialName_(std::move(rrOther.materialName_)),

                // 頂点
                vertices_(std::move(rrOther.vertices_)),

                // インデックス
                indices_(std::move(rrOther.indices_)),

                // 基本姿勢の逆行列
                inverseBaseposeMatrix_(rrOther.inverseBaseposeMatrix_),

                // ボーン
                bones_(std::move(rrOther.bones_)),

                // 各フレームの行列
                eachFrameAnimationMatrices_(std::move(rrOther.eachFrameAnimationMatrices_))

            {
            }
        };
    }
}