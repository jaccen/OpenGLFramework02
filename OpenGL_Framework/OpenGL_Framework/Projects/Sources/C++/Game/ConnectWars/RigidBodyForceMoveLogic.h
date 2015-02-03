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
    //! @brief リギッドボディフォースムーブロジック
    //! @brief 剛体の力での移動のロジックを表すクラス
    //!
    //-------------------------------------------------------------
    class C_RigidBodyForceMoveLogic : public C_RigidBodyMoveLogic
    {
    public:
        C_RigidBodyForceMoveLogic(const Physics::Vector3& rFirstAddForce,           // コンストラクタ
                                  const Physics::Vector3& rFirstAddTorque);
        virtual ~C_RigidBodyForceMoveLogic() override;                              // デストラクタ
        void SetDirection(const Physics::Vector3& rDirection) override;             // 向きを設定
        void SetMovement(float movement) override;                                  // 移動量を設定
        C_RigidBodyMoveLogic* DeepCopy() override;                                  // ディープコピー
        void SetAddTorque(const Physics::Vector3& rAddTorque);                      // 加えるトルクを設定
    private:
        std::unique_ptr<Physics::Vector3> upFirstAddForce_;                         ///< @brief 最初に加える力
        std::unique_ptr<Physics::Vector3> upFirstAddTorque_;                        ///< @brief 最初に加えるトルク
        std::unique_ptr<Physics::Vector3> upAddTorque_;                             ///< @brief 加えるトルク
        bool firstAddForceFlag_ = false;                                            ///< @brief 最初に加える力を加えたか判断するフラグ
        bool firstAddTorqueFlag_ = false;                                           ///< @brief 最初に加えるトルクを加えたか判断するフラグ
        std::unique_ptr<Physics::Vector3> upDirection_;                             ///< @brief 速度
        float movement_ = 0.0f;                                                     ///< @brief 移動量

        void DoProcess(RigidBody* pRigidBody) override;                             // 非公開の処理
    };
}