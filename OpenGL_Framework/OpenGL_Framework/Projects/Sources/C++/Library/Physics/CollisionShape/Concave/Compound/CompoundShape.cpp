/* ヘッダファイル */
#include "CompoundShape.h"


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
     *  @param  なし
     *
     ****************************************************************/
    C_CompoundShape::C_CompoundShape()
    {
        upCollisionShape_ = std::make_unique<btCompoundShape>();
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_CompoundShape::~C_CompoundShape()
    {
    }


    /*************************************************************//**
     *
     *  @brief  子形状を追加する
     *  @param  子形状
     *  @param  トランスフォーム
     *  @return なし
     *
     ****************************************************************/
    void C_CompoundShape::AddChildShape(C_CollisionShape* pChildShape,
                                        const Transform& rTransform)
    {
        upChildShapes_.emplace_back(pChildShape);
        dynamic_cast<btCompoundShape*>(upCollisionShape_.get())->addChildShape(rTransform, pChildShape->GetCollisionShape());
    }
}