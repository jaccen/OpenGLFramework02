/* 二重インクルード防止 */
#include "CollisionShape.h"


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
    C_CollisionShape::C_CollisionShape()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_CollisionShape::~C_CollisionShape()
    {
    }


    /*************************************************************//**
     *
     *  @brief  衝突形状を取得する
     *  @param  なし
     *  @return 衝突形状
     *
     ****************************************************************/
    btCollisionShape* C_CollisionShape::GetCollisionShape() const
    {
        return upCollisionShape_.get();
    }


    /*************************************************************//**
     *
     *  @brief  形状の種類を取得する
     *  @param  なし
     *  @return 形状の種類
     *
     ****************************************************************/
    int32_t C_CollisionShape::GetShapeType() const
    {
        return upCollisionShape_->getShapeType();
    }


    /*************************************************************//**
     *
     *  @brief  衝突マージンを取得する
     *  @param  なし
     *  @return 衝突マージン
     *
     ****************************************************************/
    float C_CollisionShape::GetCollisionMargin() const
    {
        return upCollisionShape_->getMargin();
    }


    /*************************************************************//**
     *
     *  @brief  衝突マージンを設定する
     *  @param  衝突マージン
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionShape::SetCollisionMargin(float collisionMargin)
    {
        upCollisionShape_->setMargin(collisionMargin);
    }
}