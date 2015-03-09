/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "CollisionObject.h"
#include "RigidBodyMoveLogic.h"
#include "../../Library/State/Machine/StateMachine.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* 前方宣言 */
    class C_BasePlayer;
    class C_BaseOption;
    class C_BaseEnemy;
    class C_BaseBullet;
    class C_BaseObstacle;
    class C_BaseBomb;
    class C_BaseGun;


    //-------------------------------------------------------------
    //!
    //! @brief ベースシールド
    //! @brief シールドの基底クラス
    //!
    //-------------------------------------------------------------
    class C_BaseShield : public C_CollisionObject
    {
    public:
        C_BaseShield(const std::string& rId,                                                            // コンストラクタ
                     int32_t type,  
                     int32_t shooterType,
                     C_CollisionObject* pTarget);                                             
        virtual ~C_BaseShield() override = 0;                                                           // デストラクタ
        bool Update() override final;                                                                   // 更新処理
        void Draw() override final;                                                                     // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override final;                                  // メッセージ処理
        void DispatchCollision(C_CollisionObject* pCollisionObject) override final;                     // 衝突を発送
        virtual void CollisionProcess(C_BasePlayer* pPlayer) override;                                  // プレイヤーとの衝突時処理
        virtual void CollisionProcess(C_BaseOption* pOption) override;                                  // オプションとの衝突時処理
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) override;                                    // 敵との衝突時処理
        virtual void CollisionProcess(C_BaseBullet* pBullet) override;                                  // 弾との衝突時処理
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) override;                              // 障害物との衝突時処理
        virtual void CollisionProcess(C_BaseBomb* pBomb) override;                                      // ボムとの衝突時処理
        virtual void CollisionProcess(C_BaseShield* pShield) override;                                  // シールドとの衝突時処理
        virtual void Move();                                                                            // 移動処理
        virtual void MoveLimitCheck() {};                                                               // 移動制限を確認
        const Physics::Vector3& GetPosition() const override;                                           // 座標を取得
        void SetPosition(const Physics::Vector3& rPosition) override;                                   // 座標を設定
    protected:
        std::unique_ptr<Physics::C_RigidBody> upRigidBody_;                                             ///< @brief 剛体
        std::unique_ptr<C_RigidBodyMoveLogic> upMoveLogic_;                                             ///< @brief 移動のロジック
        int32_t shooterType_ = 0;                                                                       ///< @brief 射撃者の種類

        virtual void DoUpdate();                                                                        // 非公開の更新処理
        virtual void DoDraw() = 0;                                                                      // 非公開の描画処理
        virtual bool DoMessageProcess(const Telegram& rTelegram);                                       // 非公開のメッセージ処理
    };
}