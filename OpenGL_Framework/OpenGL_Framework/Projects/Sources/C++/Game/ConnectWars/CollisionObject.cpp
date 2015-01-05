/* ヘッダファイル */
#include "CollisionObject.h"
#include <algorithm>


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ID
     *  @param  種類
     *
     ****************************************************************/
    C_CollisionObject::C_CollisionObject(const std::string& rId, int32_t type)
    {
        // 4つ分のIDのメモリを確保
        collidedObjectIdList_.reserve(4);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_CollisionObject::~C_CollisionObject()
    {
    }


    /*************************************************************//**
     *
     *  @brief  衝突したオブジェクトのIDが存在するか確認を行う
     *  @param  ID
     *  @return 存在する場合  ：true
     *  @return 存在しない場合：false
     *
     ****************************************************************/
    bool C_CollisionObject::CheckCollidedObjectId(const std::string& rId)
    {
        auto iterator = std::find(collidedObjectIdList_.begin(), collidedObjectIdList_.end(), rId);
        if (iterator == collidedObjectIdList_.end()) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  衝突したオブジェクトのIDの登録を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionObject::EntryCollidedObjectId(const std::string& rId)
    {
        collidedObjectIdList_.push_back(rId);
    }


    /*************************************************************//**
     *
     *  @brief  衝突点を設定する
     *  @param  衝突点
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionObject::SetCollisionPoint(const Physics::Vector3& rCollisionPoint)
    {
        collisionPoint_ = rCollisionPoint;
    }


    /*************************************************************//**
     *
     *  @brief  衝突したオブジェクトのIDのリセットを行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionObject::ResetCollidedObjectId()
    {
        collidedObjectIdList_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  衝突点を取得する
     *  @param  なし
     *  @return 衝突点
     *
     ****************************************************************/
    const Physics::Vector3& C_CollisionObject::GetCollisionPoint() const
    {
        return collisionPoint_;
    }
}