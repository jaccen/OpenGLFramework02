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
    using RigidBody = Physics::C_RigidBody;                                     // RigidBody型


    //-------------------------------------------------------------
    //!
    //! @brief リギッドボディムーブロジック
    //! @brief 剛体の移動のロジックの基底クラス
    //!
    //-------------------------------------------------------------
    class C_RigidBodyMoveLogic : public IC_MoveLogic<RigidBody>
    {
    public:
        C_RigidBodyMoveLogic() = default;                                       // コンストラクタ
        virtual ~C_RigidBodyMoveLogic() override = default;                     // デストラクタ
        virtual void Process(RigidBody* pRigidBody) override final;             // 処理
        virtual void SetDirection(const Physics::Vector3& rDirection) = 0;      //!< @brief 向きを設定
        virtual void SetMovement(float movement) = 0;                           //!< @brief 移動量を設定   
        virtual C_RigidBodyMoveLogic* DeepCopy() = 0;                           //!< @brief ディープコピー
    private:
        virtual void DoProcess(RigidBody* pRigidBody) = 0;                      //!< @brief 非公開の処理
    };
}