/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "CollisionObject.h"
#include "BasePower.h"
#include "../../Library/State/Machine/StateMachine.h"
#include "../../Library/Physics/Body/Rigid/Rigidbody.h"


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
    class C_BaseShield;


    //-------------------------------------------------------------
    //!
    //! @brief ベースボム
    //! @brief ボムの基底クラス
    //!
    //-------------------------------------------------------------
    class C_BaseBomb : public C_CollisionObject
    {
    public:
        C_BaseBomb(const std::string& rId, int32_t type, int32_t level);                            // コンストラクタ
        ~C_BaseBomb() override;                                                                     // デストラクタ
        bool Update() override final;                                                               // 更新処理
        void Draw() override final;                                                                 // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override final;                              // メッセージ処理
        virtual void DispatchCollision(C_CollisionObject* pCollisionObject) override final;         // 衝突検知を発送
        virtual void CollisionProcess(C_BasePlayer* pPlayer) override;                              // プレイヤーとの衝突時処理
        virtual void CollisionProcess(C_BaseOption* pOption) override;                              // オプションとの衝突時処理
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) override;                                // 敵との衝突時処理
        virtual void CollisionProcess(C_BaseBullet* pBullet) override;                              // 弾との衝突時処理
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) override;                          // 障害物との衝突時処理
        virtual void CollisionProcess(C_BaseBomb* pBomb) override;                                  // ボムとの衝突時処理
        virtual void CollisionProcess(C_BaseShield* pShield) override;                              // シールドとの衝突時処理
        void MoveLimitCheck() override{};                                                           // 移動制限を確認
        virtual const Physics::Vector3& GetPosition() const override;                               // 座標を取得  
        virtual void SetPosition(const Physics::Vector3& rPosition) override;                       // 座標を設定
    protected:
        std::unique_ptr<State::C_StateMachine<C_BaseBomb>> upStateMachine_;                         ///< @brief ステートマシーン
        std::unique_ptr<Physics::C_RigidBody> upRigidBody_;                                         ///< @brief 剛体
        int32_t level_ = 0;                                                                         ///< @brief レベル

        virtual void DoUpdate() = 0;                                                                // 非公開の更新処理
        virtual void DoDraw();                                                                      // 非公開の描画処理
        virtual bool DoMessageProcess(const Telegram& rTelegram);                                   // 非公開のメッセージ処理
    };
}