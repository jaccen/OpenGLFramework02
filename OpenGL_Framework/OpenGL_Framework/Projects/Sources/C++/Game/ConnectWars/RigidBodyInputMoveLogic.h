/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "RigidBodyMoveLogic.h"


/* 前方宣言 */
namespace Input
{
    class C_KeyboardManager;
    class C_GamepadManager;
}


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
    //! @brief リギッドボディインプットムーブロジック
    //! @brief 剛体の入力移動のロジックを表すクラス
    //!
    //-------------------------------------------------------------
    class C_RigidBodyInputMoveLogic : public C_RigidBodyMoveLogic
    {
    public:
        C_RigidBodyInputMoveLogic(float movement = 1.0f, float movementScale = 1.0f);       // コンストラクタ
        ~C_RigidBodyInputMoveLogic() override;                                              // デストラクタ
        void SetDirection(const Physics::Vector3& rDirection) override {};                  // 向きを設定
        void SetMovement(float movement) override;                                          // 移動量を設定
        C_RigidBodyMoveLogic* DeepCopy() override;                                          // ディープコピー
        void SetMovementScale(float movementScale);                                         // 移動量のスケールを設定
    private:
        float movement_ = 1.0f;                                                             ///< @brief 移動量
        float movementScale_ = 1.0f;                                                        ///< @brief 移動量のスケール
        Input::C_KeyboardManager* pKeyboardManager_ = nullptr;                              ///< @brief キーボードマネージャー
        Input::C_GamepadManager* pGamepadManager_ = nullptr;                                ///< @brief ゲームパッドマネージャー

        void DoProcess(RigidBody* pRigidBody) override;                                     // 非公開の処理
    };
}