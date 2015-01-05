/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Math/Vector/Vector3.h"
#include "../../Texture/TextureDefine.h"
#include <vector>


//-------------------------------------------------------------
//!
//! @brief マテリアル
//! @brief マテリアル関連の名前空間
//!
//-------------------------------------------------------------
namespace Material
{
    /* 前方宣言 */
    struct S_Material;


    /* 別名 */
    using Vector3 = Math::S_Vector3<float>;                             // Vector3型
    using MaterialPtr = std::shared_ptr<S_Material>;                    // MaterialPtr型


    //-------------------------------------------------------------
    //!
    //! @brief マテリアル
    //! @brief マテリアルの基底構造体
    //!
    //-------------------------------------------------------------
    struct S_Material
    {
        std::vector<Texture::TextureHandle> textureHandles_;            ///< @brief テクスチャハンドル
    };
}