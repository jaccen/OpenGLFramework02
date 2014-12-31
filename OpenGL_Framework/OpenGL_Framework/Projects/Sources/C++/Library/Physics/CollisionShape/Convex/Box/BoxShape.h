/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../CollisionShape.h"


//-------------------------------------------------------------
///
/// @brief フィジックス
/// @brief 物理関連の名前空間
///
//-------------------------------------------------------------
namespace Physics
{
    //-------------------------------------------------------------
    //!
    //! @brief ボックスシェイプ
    //! @brief ボックス形状を表すクラス
    //!
    //-------------------------------------------------------------
    class C_BoxShape : public C_CollisionShape
    {
    public:
        C_BoxShape(float halfWidth, float halfHeight, float halfDepth);     //!< @brief コンストラクタ
        ~C_BoxShape() override;                                             //!< @brief デストラクタ
    };
}