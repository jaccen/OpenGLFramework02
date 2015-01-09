/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "RigidBodyMoveLogic.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief リギッドボディストレートムーブロジック
    //! @brief 剛体の直線移動のロジックを表すクラス
    //!
    //-------------------------------------------------------------
    class C_RigidBodyStraightMoveLogic : public C_RigidBodyMoveLogic
    {
    public:
        C_RigidBodyStraightMoveLogic(const Physics::Vector3& rApplyForce);          // コンストラクタ
        virtual ~C_RigidBodyStraightMoveLogic() override;                           // デストラクタ
    private:
        Physics::Vector3 applyForce_;                                               ///< @brief 加える力

        void DoProcess(RigidBody* pRigidBody) override;                             // 非公開の処理
    };
}