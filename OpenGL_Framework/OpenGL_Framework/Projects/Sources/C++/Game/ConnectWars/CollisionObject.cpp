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
    C_CollisionObject::C_CollisionObject(const std::string& rId, int32_t type) :

        // 衝突点
        upCollisionPoint_(std::make_unique<Physics::Vector3>(0.0f, 0.0f, 0.0f))

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
     *  @brief  ヒットポイントを取得する
     *  @param  なし
     *  @return ヒットポイント
     *
     ****************************************************************/
    C_BaseHitPoint* C_CollisionObject::GetHitPoint() const
    {
        return upHitPoint_.get();
    }


    /*************************************************************//**
     *
     *  @brief  パワーを取得する
     *  @param  なし
     *  @return パワー
     *
     ****************************************************************/
    C_BasePower* C_CollisionObject::GetPower() const
    {
        return upPower_.get();
    }


    /*************************************************************//**
     *
     *  @brief  無敵フラグを取得する
     *  @param  なし
     *  @return 無敵フラグ
     *
     ****************************************************************/
    bool C_CollisionObject::IsInvincibleFlag() const
    {
        return invincibleFlag_;
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
        *upCollisionPoint_ = rCollisionPoint;
    }


    /*************************************************************//**
     *
     *  @brief  無敵フラグを設定する
     *  @param  無敵フラグ
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionObject::SetInvincibleFlag(bool invincibleFlag)
    {
        invincibleFlag_ = invincibleFlag;
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
        return *upCollisionPoint_;
    }
}