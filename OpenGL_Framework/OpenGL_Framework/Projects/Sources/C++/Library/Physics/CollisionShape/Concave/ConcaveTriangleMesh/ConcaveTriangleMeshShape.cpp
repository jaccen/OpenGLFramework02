/* ヘッダファイル */
#include "ConcaveTriangleMeshShape.h"


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
    C_ConcaveTriangleMeshShape::C_ConcaveTriangleMeshShape(Vector3 vertexPositions[],
                                                           uint32_t vertexCount) : 

        // 三角形メッシュ
        upTriangleMesh_(std::make_unique<btTriangleMesh>())

    {
        // 三角形メッシュを構築、そのデータからシェイプを作成
        for (size_t i = 0, polygonCount = vertexCount / 3; i < polygonCount; ++i)
        {
            upTriangleMesh_->addTriangle(vertexPositions[i], 
                                         vertexPositions[i + 1],
                                         vertexPositions[i + 2]);
        }

        upCollisionShape_ = std::make_unique<btBvhTriangleMeshShape>(upTriangleMesh_.get(), true);
    }


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  頂点座標
     *  @param  頂点数
     *  @param  インデックス
     *  @param  三角形の数
     *
     ****************************************************************/
    C_ConcaveTriangleMeshShape::C_ConcaveTriangleMeshShape(Vector3 vertexPositions[],
                                                           uint32_t vertexCount,
                                                           int32_t indices[],
                                                           uint32_t triangleCount) : 

        // 三角形メッシュ
        upTriangleMesh_(std::make_unique<btTriangleMesh>())

    {
        // 三角形メッシュを構築、そのデータからシェイプを作成
        for (size_t i = 0; i < triangleCount; ++i)
        {
             upTriangleMesh_->addTriangle(vertexPositions[indices[i]], 
                                          vertexPositions[indices[i + 1]],
                                          vertexPositions[indices[i + 2]]);
        }

        upCollisionShape_ = std::make_unique<btBvhTriangleMeshShape>(upTriangleMesh_.get(), true);
    }

    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_ConcaveTriangleMeshShape::~C_ConcaveTriangleMeshShape()
    {
    }
}