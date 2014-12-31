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
    //! @brief コンバックスハルシェイプ
    //! @brief 凸包形状を表すクラス
    //!
    //-------------------------------------------------------------
    class C_ConvexHullShape : public C_CollisionShape
    {
    public:
        C_ConvexHullShape(Vector3 vertexPositions[], int32_t vertexCount);          // コンストラクタ
        ~C_ConvexHullShape() override;                                              // デストラクタ
        void AddVertexPosition(const Vector3& rVertexPosition);                     // 頂点座標を追加
    };
}