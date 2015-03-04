/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "MoveLogic.h"
#include "BaseBackground.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* 別名 */
    using Background = C_BaseBackground;                                                    // Background型


    //-------------------------------------------------------------
    //!
    //! @brief バックグラウンドムーブロジック
    //! @brief 背景の移動のロジックの基底クラス
    //!
    //-------------------------------------------------------------
    class C_BackgroundMoveLogic : public IC_MoveLogic<Background>
    {
    public:
        C_BackgroundMoveLogic() = default;                                                  // コンストラクタ
        virtual ~C_BackgroundMoveLogic() override = default;                                // デストラクタ
        virtual void Process(Background* pBackground) override final;                       // 処理
        virtual void SetVelocity(const Vector3& rVelocity);                                 // 速度を設定
        virtual void SetAccelaration(const Vector3& rAccelaration);                         // 加速度を設定
        virtual void SetRotationVelocity(const Vector3& rRotationVelocity);                 // 回転速度を設定
        virtual void SetRotationAccelaration(const Vector3& rRotationAccelaration);         // 回転加速度を設定
    protected:
        virtual void DoProcess(Background* pBackground) = 0;                                ///< @brief 非公開の処理

        Vector3 velocity_;                                                                  ///< @brief 速度
        Vector3 accelaration_;                                                              ///< @brief 加速度
        Vector3 rotationVelocity_;                                                          ///< @brief 回転速度
        Vector3 rotationAccelaration_;                                                      ///< @brief 回転加速度
    };
}