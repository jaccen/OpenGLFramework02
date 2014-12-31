/* ヘッダファイル */
#include "ConvexHullShape.h"


//-------------------------------------------------------------
///
/// @brief フィジックス
/// @brief 物理関連の名前空間
///
//-------------------------------------------------------------
namespace Physics
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  頂点座標
     *  @param  頂点数
     *
     ****************************************************************/
    C_ConvexHullShape::C_ConvexHullShape(Vector3 vertexPositions[], int32_t vertexCount)
    {
        upCollisionShape_ = std::make_unique<btConvexHullShape>(reinterpret_cast<btScalar*>(vertexPositions), vertexCount);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_ConvexHullShape::~C_ConvexHullShape()
    {
    }


    /*************************************************************//**
     *
     *  @brief  点を追加する
     *  @param  点
     *  @return なし
     *
     ****************************************************************/
    void C_ConvexHullShape::AddVertexPosition(const Vector3& rVertexPosition)
    {
        dynamic_cast<btConvexHullShape*>(upCollisionShape_.get())->addPoint(rVertexPosition);
    }
}