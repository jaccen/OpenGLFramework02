/* ヘッダファイル */
#include "InfinitePlaneShape.h"


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
     *  @param  法線
     *  @param  厚さ
     *
     ****************************************************************/
    C_InfinitePlaneShape::C_InfinitePlaneShape(const Vector3& rNormal, float thickness)
    {
        upCollisionShape_ = std::make_unique<btStaticPlaneShape>(rNormal, thickness);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_InfinitePlaneShape::~C_InfinitePlaneShape()
    {
    }
}