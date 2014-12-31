/* ヘッダファイル */
#include "CapsuleShape.h"


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
     *  @param  ( 球部分の )半径
     *  @param  ( 円柱部分の )高さ
     *  @param  向き
     *
     ****************************************************************/
    C_CapsuleShape::C_CapsuleShape(float radius,
                                   float height,
                                   ecDirection direction)
    {
        if (direction == ecDirection::X)
        {
            upCollisionShape_ = std::make_unique<btCapsuleShapeX>(radius, height);
        }
        else if (direction == ecDirection::Z)
        {
            upCollisionShape_ = std::make_unique<btCapsuleShapeZ>(radius, height);
        }
        else
        {
            upCollisionShape_ = std::make_unique<btCapsuleShape>(radius, height);
        }
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_CapsuleShape::~C_CapsuleShape()
    {
    }
}