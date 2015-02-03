/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Material.h"


//-------------------------------------------------------------
//!
//! @brief マテリアル
//! @brief マテリアル関連の名前空間
//!
//-------------------------------------------------------------
namespace Material
{
    //-------------------------------------------------------------
    //!
    //! @brief フォンマテリアル
    //! @brief フォンマテリアルを表す構造体
    //!
    //-------------------------------------------------------------
    struct S_PhongMaterial : public S_Material
    {
        Vector3 ambient_;                       ///< @brief アンビエント
        Vector3 diffuse_;                       ///< @brief ディフューズ
        Vector3 specular_;                      ///< @brief スペキュラー
        Vector3 emissive_;                      ///< @brief エミッシブ
        float shininess_ = 0.0f;                ///< @brief 光沢
        float opacity_ = 0.0f;                  ///< @brief 不透明度
        float reflectivity_ = 0.0f;             ///< @brief 反射率
    };
}