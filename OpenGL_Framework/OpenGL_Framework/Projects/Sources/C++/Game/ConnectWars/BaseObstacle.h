/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "CollisionObject.h"
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


    //-------------------------------------------------------------
    //!
    //! @brief ベースオブスタクル
    //! @brief 障害物の基底クラス
    //!
    //-------------------------------------------------------------
    class C_BaseObstacle : public C_CollisionObject
    {
    public:
        C_BaseObstacle(const std::string& rId, int32_t type);                       // コンストラクタ
        virtual ~C_BaseObstacle() override;                                         // デストラクタ
        bool Update() override final;                                               // 更新処理
        void Draw() override final;                                                 // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override final;              // メッセージ処理
        void DispatchCollision(C_CollisionObject* pCollisionObject) override;       // 衝突検知を発送
        void CollisionProcess(C_BasePlayer* pPlayer) override;                      // プレイヤーとの衝突時処理
        void CollisionProcess(C_BaseOption* pOption) override;                      // オプションとの衝突時処理
        void CollisionProcess(C_BaseEnemy* pEnemy) override;                        // 敵との衝突時処理
        void CollisionProcess(C_BaseBullet* pBullet) override;                      // 弾との衝突時処理
        void CollisionProcess(C_BaseObstacle* pObstacle) override;                  // 障害物との衝突時処理
        virtual void Move();                                                        // 移動処理
    protected:
        std::unique_ptr<State::C_StateMachine<C_BaseObstacle>> upStateMachine_;     ///< @brief ステートマシーン

        virtual void DoUpdate();                                                    // 非公開の更新処理
        virtual void DoDraw();                                                      // 非公開の描画処理
        virtual bool DoMessageProcess(const Telegram& rTelegram);                   // 非公開のメッセージ処理
    };
}