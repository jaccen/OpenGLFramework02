/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "MoveLogic.h"
#include "../../Library/Physics/Body/Rigid/Rigidbody.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* 別名 */
    using RigidBody = Physics::C_RigidBody;                                 // RIgidBody型


    //-------------------------------------------------------------
    //!
    //! @brief リギッドボディムーブロジック
    //! @brief 剛体の移動のロジックの基底クラス
    //!
    //-------------------------------------------------------------
    class C_RigidBodyMoveLogic : public IC_MoveLogic<RigidBody>
    {
    public:
        C_RigidBodyMoveLogic() = default;                                   //!< @brief コンストラクタ
        virtual ~C_RigidBodyMoveLogic() override = default;                 //!< @brief デストラクタ
        void Process(RigidBody* pRigidBody) override final;                 //!< @brief 処理
    private:
        virtual void DoProcess(RigidBody* pRigidBody) = 0;                  // 非公開の処理
    };
}