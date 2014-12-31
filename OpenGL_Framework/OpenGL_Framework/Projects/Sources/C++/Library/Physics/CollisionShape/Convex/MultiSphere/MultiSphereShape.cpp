/* ヘッダファイル */
#include "MultiSphereShape.h"


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
     *  @param  中心点
     *  @param  半径
     *  @param  数
     *
     ****************************************************************/
    C_MultiSphereShape::C_MultiSphereShape(Vector3 centerPoints[],
                                           float radii[],
                                           int32_t count)
    {
        upCollisionShape_ = std::make_unique<btMultiSphereShape>(centerPoints, radii, count);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_MultiSphereShape::~C_MultiSphereShape()
    {
    }
}