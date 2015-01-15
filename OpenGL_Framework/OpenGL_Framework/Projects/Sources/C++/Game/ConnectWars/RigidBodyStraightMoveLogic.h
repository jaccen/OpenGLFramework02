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
        C_RigidBodyStraightMoveLogic(const Physics::Vector3& rVelocity);            // コンストラクタ
        virtual ~C_RigidBodyStraightMoveLogic() override;                           // デストラクタ
        C_RigidBodyMoveLogic* DeepCopy() override;                                  // ディープコピー
        void SetVelocity(const Physics::Vector3& rVelocity);                        // 加える力を設定
    private:
        std::unique_ptr<Physics::Vector3> upVelocity_;                              ///< @brief 速度

        void DoProcess(RigidBody* pRigidBody) override;                             // 非公開の処理
    };
}