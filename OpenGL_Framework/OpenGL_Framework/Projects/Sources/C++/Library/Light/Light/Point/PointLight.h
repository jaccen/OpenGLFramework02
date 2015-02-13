/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Light.h"


//-------------------------------------------------------------
//!
//! @brief ライト
//! @brief ライト関連の名前空間
//!
//-------------------------------------------------------------
namespace Light
{
    //-------------------------------------------------------------
    //!
    //! @brief ポイントライト
    //! @brief 点光源を表す構造体
    //!
    //-------------------------------------------------------------
    struct S_PointLight : public S_Light
    {
        Vector3 position_;                          ///< @brief 座標
        float constantAttenuation_;                 ///< @brief 一定減衰率
        float linearAttenuation_;                   ///< @brief 一次減衰率
        float quadraticAttenuation_;                ///< @brief 二次減衰率
        Vector3 diffuse_;                           ///< @brief ディフューズ
	    Vector3 ambient_;                           ///< @brief アンビエント
	    Vector3 specular_;                          ///< @brief スペキュラ
    };
}