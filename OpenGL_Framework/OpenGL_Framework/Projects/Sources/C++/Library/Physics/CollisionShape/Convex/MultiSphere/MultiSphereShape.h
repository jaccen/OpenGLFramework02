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
    //! @brief マルチスフィアシェイプ
    //! @brief 複数球形状を表すクラス
    //!
    //-------------------------------------------------------------
    class C_MultiSphereShape : public C_CollisionShape
    {
    public:
        C_MultiSphereShape(Vector3 centerPoints[],          // コンストラクタ
                           float radii[],
                           int32_t count);
        ~C_MultiSphereShape() override;                     // デストラクタ
    };
}