/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "CollisionObject.h"
/*
#include "MoveLogic.h"
#include "RotateLogic.h"
#include "BaseHitPoint.h"
#include "BaseGun.h"
#include "BasePower.h"
*/


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* 前方宣言 */
    class C_BaseOption;
    class C_BaseEnemy;
    class C_BaseBullet;
    class C_BaseObstacle;
    class C_BaseBomb;


    //-------------------------------------------------------------
    //!
    //! @brief シューター
    //! @brief 弾を撃つオブジェクト
    //!
    //-------------------------------------------------------------
    class C_Shooter : public C_CollisionObject
    {
    public:
        C_Shooter(const std::string& rId, int32_t type);                                        // コンストラクタ
        virtual~C_Shooter() override;                                                           // デストラクタ
        virtual bool Update() override = 0;                                                     // 更新処理
        virtual void Draw() override = 0;                                                       // 描画処理
        virtual bool MessageProcess(const Telegram& rTelegram) override = 0;                    // メッセージ処理
        virtual void DispatchCollision(C_CollisionObject* pCollisionObject) override = 0;       // 衝突を発送
        virtual void Move() = 0;                                                                // 移動処理
        virtual void Shot() = 0;                                                                // 射撃処理
        virtual void CollisionProcess(C_BasePlayer* pPlayer) = 0;                               // プレイヤーとの衝突時処理
        virtual void CollisionProcess(C_BaseOption* pOption) = 0;                               // オプションとの衝突時処理
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) = 0;                                 // 敵との衝突時処理
        virtual void CollisionProcess(C_BaseBullet* pBullet) = 0;                               // 弾との衝突時処理
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) = 0;                           // 障害物との衝突時処理
        virtual void CollisionProcess(C_BaseBomb* pBomb) = 0;                                   // ボムとの衝突時処理

        /* ゲッター */
        //C_BaseHitPoint* GetHitPoint() const;                                                  // ヒットポイントを取得
        //C_BasePower* GetPower() const;                                                        // 攻撃力を取得
        //bool IsInvincibleFlag() const;                                                        // 無敵フラグを取得

        /* セッター */
        //void SetInvincibleFlag(bool invincibleFlag);                                          // 無敵フラグを設定
    protected:
        //std::unique_ptr<C_MoveLogic> upMoveLogic_;                                            ///< @brief 移動のロジック
        //std::unique_ptr<C_RotateLogic> upRotateLogic_;                                        ///< @brief 回転のロジック
        //std::unique_ptr<C_BaseHitPoint> upHitPoint_;                                          ///< @brief ヒットポイント
        //std::unique_ptr<C_BasePower> upPower_;                                                ///< @brief 攻撃力
        //bool invincibleFlag_ = false;                                                         ///< @brief 無敵フラグ
    };
}