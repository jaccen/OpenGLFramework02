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
        C_RigidBodyStraightMoveLogic();                                             // コンストラクタ
        virtual ~C_RigidBodyStraightMoveLogic() override;                           // デストラクタ
        void SetDirection(const Physics::Vector3& rDirection) override;             // 向きを設定
        void SetMovement(float movement)  override;                                 // 移動量を設定   
        C_RigidBodyMoveLogic* DeepCopy() override;                                  // ディープコピー
    private:
        std::unique_ptr<Physics::Vector3> upDirection_;                             ///< @brief 速度
        float movement_ = 0.0f;                                                     ///< @brief 移動量

        void DoProcess(RigidBody* pRigidBody) override;                             // 非公開の処理
    };
}