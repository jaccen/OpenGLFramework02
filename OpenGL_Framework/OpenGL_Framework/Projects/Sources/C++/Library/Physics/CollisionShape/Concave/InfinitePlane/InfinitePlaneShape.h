/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../CollisionShape.h"
#include "../../../PhysicsDefine.h"


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
    //! @brief インフィニットプレインシェイプ
    //! @brief 無限平面形状を表すクラス
    //!
    //-------------------------------------------------------------
    class C_InfinitePlaneShape : public C_CollisionShape
    {
    public:
        C_InfinitePlaneShape(const Vector3& rNormal, float thickness);          // コンストラクタ
        ~C_InfinitePlaneShape() override;                                       // デストラクタ
    };
}