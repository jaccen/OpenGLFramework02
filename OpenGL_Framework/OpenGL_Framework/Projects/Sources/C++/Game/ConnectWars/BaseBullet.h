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
    class C_Shooter;
    class C_BasePlayer;
    class C_BaseOption;
    class C_BaseEnemy;
    class C_BaseObstacle;
    class C_BaseBomb;


    //-------------------------------------------------------------
    //!
    //! @brief ベースバレット
    //! @brief バレットの基底クラス
    //!
    //-------------------------------------------------------------
    class C_BaseBullet : public C_CollisionObject
    {
    public:
        C_BaseBullet(const std::string& rId, int32_t type);                                 // コンストラクタ
        virtual ~C_BaseBullet() override = 0;                                               // デストラクタ
        bool Update() override final;                                                       // 更新処理
        void Draw() override final;                                                         // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override final;                      // メッセージ処理
        void DispatchCollision(C_CollisionObject* pCollisionObject) override;               // 衝突検知を発送
        void CollisionProcess(C_BasePlayer* pPlayer) override;                              // プレイヤーとの衝突時処理
        void CollisionProcess(C_BaseOption* pOption) override;                              // オプションとの衝突時処理
        void CollisionProcess(C_BaseEnemy* pEnemy) override;                                // 敵との衝突時処理
        void CollisionProcess(C_BaseBullet* pBullet) override;                              // 弾との衝突時処理
        void CollisionProcess(C_BaseObstacle* pObstacle) override;                          // 障害物との衝突時処理
        void CollisionProcess(C_BaseBomb* pBomb) override;                                  // 障害物との衝突時処理
        virtual void Move();                                                                // 移動処理
        State::C_StateMachine<C_BaseBullet>* GetStateMachine() const;                       // ステートマシーンを取得
    protected:
        std::unique_ptr<Physics::C_CollisionShape> upCollisionShape_;                       ///< @brief 衝突形状
        std::unique_ptr<Physics::C_RigidBody> upRigidBody_;                                 ///< @brief 剛体
        std::unique_ptr<C_RigidBodyMoveLogic> upMoveLogic_;                                 ///< @brief 移動のロジック
        std::unique_ptr<State::C_StateMachine<C_BaseBullet>> upStateMachine_;               ///< @brief ステートマシーン

        virtual void DoUpdate();                                                            // 非公開の更新処理
        virtual void DoDraw();                                                              // 非公開の描画処理
        virtual bool DoMessageProcess(const Telegram& rTelegram);                           // 非公開のメッセージ処理
    };
}