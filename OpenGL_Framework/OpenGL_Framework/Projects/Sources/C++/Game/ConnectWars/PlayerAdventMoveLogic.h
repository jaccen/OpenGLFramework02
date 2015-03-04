/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "RigidBodyMoveLogic.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"


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
    class C_PlayerAdventMoveLogic : public C_RigidBodyMoveLogic
    {
    public:
        C_PlayerAdventMoveLogic();                                                      // コンストラクタ
        ~C_PlayerAdventMoveLogic() override;                                            // デストラクタ
        void SetDirection(const Physics::Vector3& rDirection) override {};              // 向きを設定
        void SetMovement(float movement) override;                                      // 移動量を設定
        C_RigidBodyMoveLogic* DeepCopy() override;                                      // ディープコピー
        bool IsMoveFinish() const;                                                      // 移動終了か確認
    private:
        float movement_ = 1.0f;                                                         ///< @brief 移動量
        Timer::C_FrameCounter frameCounter_;                                            ///< @brief フレームカウンター
        int32_t finishCount = 40;                                                       ///< @brief 終了カウント数

        void DoProcess(RigidBody* pRigidBody) override;                                 // 非公開の処理
    };
}