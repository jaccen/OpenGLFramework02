/* ヘッダファイル */
#include "ConeShape.h"


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
     *  @param  ( 底面の )半径
     *  @param  高さ
     *  @param  向き
     *
     ****************************************************************/
    C_ConeShape::C_ConeShape(float radius, 
                             float height,
                             ecDirection direction)
    {
        if (direction == ecDirection::X)
        {
            upCollisionShape_ = std::make_unique<btCylinderShapeX>(Vector3(height, radius, radius));
        }
        else if (direction == ecDirection::Z)
        {
            upCollisionShape_ = std::make_unique<btCylinderShape>(Vector3(radius, radius, height));
        }
        else
        {
            upCollisionShape_ = std::make_unique<btCylinderShape>(Vector3(radius, height, radius));
        }
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_ConeShape::~C_ConeShape()
    {
    }
}