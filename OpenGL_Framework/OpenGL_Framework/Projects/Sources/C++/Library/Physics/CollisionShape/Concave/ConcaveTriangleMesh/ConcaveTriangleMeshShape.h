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
    //! @brief コンケーブトライアングルメッシュシェイプ
    //! @brief 凹面三角メッシュ形状を表すクラス
    //!
    //-------------------------------------------------------------
    class C_ConcaveTriangleMeshShape : public C_CollisionShape
    {
    public:
        C_ConcaveTriangleMeshShape(Vector3 vertexPositions[],               // コンストラクタ
                                   uint32_t vertexCount);
        C_ConcaveTriangleMeshShape(Vector3 vertexPositions[],               // コンストラクタ
                                   uint32_t vertexCount,
                                   int32_t indices[],
                                   uint32_t triangleCount);
        ~C_ConcaveTriangleMeshShape() override;                             // デストラクタ
    private:
        std::unique_ptr<btTriangleMesh> upTriangleMesh_;                    ///< @brief 三角形メッシュ
    };
}