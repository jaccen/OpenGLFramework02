/* ヘッダファイル */
#include "CollisionCallback.h"
#include "CollisionObject.h"


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
     *  @brief  接触( 衝突 )時の処理を行う
     *  @param  マニフォールドポイント
     *  @param  ボディ
     *  @param  もう一つのボディ
     *  @return なし
     *
     ****************************************************************/
    bool C_CollisionCallback::s_ContactProcess(btManifoldPoint& rManifoldPoint, void* pBody, void* pAnotherBody)
    {
        // 衝突オブジェクトへキャストし、独自のデータを取得
        auto pCollisionObject = reinterpret_cast<btCollisionObject*>(pBody);
        auto pAnotherCollisionObject = reinterpret_cast<btCollisionObject*>(pAnotherBody);
        auto pUserData = reinterpret_cast<C_CollisionObject*>(pCollisionObject->getUserPointer());
        auto pAnotherUserData= reinterpret_cast<C_CollisionObject*>(pAnotherCollisionObject->getUserPointer());

        // IDが登録されていない場合は衝突時の処理を行う
        if (pUserData->CheckCollidedObjectId(pAnotherUserData->GetId()) == false)
        {
            // IDを登録
            pUserData->EntryCollidedObjectId(pAnotherUserData->GetId());
            pAnotherUserData->EntryCollidedObjectId(pUserData->GetId());

            // 衝突点を設定
            pUserData->SetCollisionPoint(rManifoldPoint.getPositionWorldOnA());
            pAnotherUserData->SetCollisionPoint(rManifoldPoint.getPositionWorldOnB());

            // 衝突検知を発行
            pUserData->DispatchCollision(pAnotherUserData);
        }

        return true;
    }
}