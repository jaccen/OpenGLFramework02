/* ヘッダファイル */
#include "BoxShape.h"
#include "../../../PhysicsDefine.h"


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
     *  @param  幅の半分
     *  @param  高さの半分
     *  @param  奥行の半分
     *
     ****************************************************************/
    C_BoxShape::C_BoxShape(float halfWidth, float halfHeight, float halfDepth)
    {
        upCollisionShape_ = std::make_unique<btBoxShape>(Vector3(halfWidth, halfHeight, halfDepth));
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BoxShape::~C_BoxShape()
    {
    }
}