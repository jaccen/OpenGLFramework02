/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "RigidBodyMoveLogic.h"
#include "../../Library/Physics/PhysicsDefine.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* 前方宣言 */
    class C_CollisionObject;


    //-------------------------------------------------------------
    //!
    //! @brief リギッドボディコネクトムーブロジック
    //! @brief 剛体の連結時の移動のロジックを表すクラス
    //!
    //-------------------------------------------------------------
    class C_RigidBodyConnectMoveLogic : public C_RigidBodyMoveLogic
    {
    public:
        C_RigidBodyConnectMoveLogic(C_CollisionObject* pTarget,                         // コンストラクタ
                                    const Physics::Vector3& rOffsetFromTarget);             
        virtual ~C_RigidBodyConnectMoveLogic() override;                                // デストラクタ
        void SetDirection(const Physics::Vector3& rDirection) override {};              // 向きを設定
        void SetMovement(float movement) override {};                                   // 移動量を設定
        C_RigidBodyMoveLogic* DeepCopy() override;                                      // ディープコピー
    private:
        C_CollisionObject* pTarget_ = nullptr;                                          ///< @brief ターゲット
        std::unique_ptr<Physics::Vector3> upOffsetFromTarget_;                          ///< @brief ターゲットからのオフセット

        void DoProcess(RigidBody* pRigidBody) override;                                 // 非公開の処理
    };
}