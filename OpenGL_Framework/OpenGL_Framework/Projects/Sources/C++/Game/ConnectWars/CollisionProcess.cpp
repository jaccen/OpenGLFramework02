/* ヘッダファイル */
#include "CollisionProcess.h"
#include "ConnectWarsDefine.h"
#include "BasePlayer.h"
#include "BaseOption.h"
#include "BaseEnemy.h"
#include "BaseBullet.h"
#include "BaseObstacle.h"
#include "BaseBomb.h"
#include "../../Library/Debug/Helper/DebugHelper.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* プロトタイプ宣言 */
    static void s_DamageToTarget(C_CollisionObject* pAttacker, C_CollisionObject* pTarget);


    /*************************************************************//**
     *
     *  @brief  プレイヤー同士の衝突時処理を行う
     *  @param  プレイヤー
     *  @param  もう一つのプレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_PlayerAndPlayer(C_BasePlayer* pPlayer, C_BasePlayer* pAnotherPlayer)
    {
        StrongAssert(false && "[ C_CollisionProcess::s_PlayerAndPlayer ] プレイヤーが2体以上になることはありえません。\n");
    }


    /*************************************************************//**
     *
     *  @brief  プレイヤーとオプションの衝突時処理を行う
     *  @param  プレイヤー
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_PlayerAndOption(C_BasePlayer* pPlayer, C_BaseOption* pOption)
    {
        if (pOption->IsOnceConnectFlag() == false)
        {
            // 一度連結したか判断するフラグを設定
            pOption->SetOnceConnectFlag(true);

            // プレイヤーからのオフセットを求める
            auto playerPosition = pPlayer->GetRigidBody()->GetTransform().getOrigin();
            auto optionTransform = pOption->GetRigidBody()->GetTransform();

            Physics::Vector3 offsetFromPlayer = optionTransform.getOrigin() - playerPosition;
            offsetFromPlayer = offsetFromPlayer.normalize();

            offsetFromPlayer = offsetFromPlayer * pPlayer->GetRadius()
                             + offsetFromPlayer * pOption->GetRadius();
            offsetFromPlayer *= Connect::s_OffsetFactor;
            pOption->SetOffsetFromPlayer(offsetFromPlayer);

            // オプションの座標を設定
            optionTransform.setOrigin(playerPosition + offsetFromPlayer);
            pOption->GetRigidBody()->SetTransform(optionTransform);

            // 新規連結処理
            pPlayer->NewConnect();
            pOption->NewConnect();

            // 連結の効果を処理
            pOption->ConnectEffect();

            // オプション数を1増加
            pPlayer->AddOptionCount(1);
        }
    }


    /*************************************************************//**
     *
     *  @brief  プレイヤーと敵の衝突時処理を行う
     *  @param  プレイヤー
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_PlayerAndEnemy(C_BasePlayer* pPlayer, C_BaseEnemy* pEnemy)
    {
        s_DamageToTarget(pPlayer, pEnemy);
        s_DamageToTarget(pEnemy, pPlayer);
    }


    /*************************************************************//**
     *
     *  @brief  プレイヤーと弾の衝突時処理を行う
     *  @param  プレイヤー
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_PlayerAndBullet(C_BasePlayer* pPlayer, C_BaseBullet* pBullet)
    {
        assert(pBullet->GetShooterType() == TYPE_ENEMY);
        
        s_DamageToTarget(pPlayer, pBullet);
        s_DamageToTarget(pBullet, pPlayer);
    }


    /*************************************************************//**
     *
     *  @brief  プレイヤーと障害物の衝突時処理を行う
     *  @param  プレイヤー
     *  @param  障害物
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_PlayerAndObstacle(C_BasePlayer* pPlayer, C_BaseObstacle* pObstacle)
    {
        s_DamageToTarget(pPlayer, pObstacle);
        s_DamageToTarget(pObstacle, pPlayer);
    }


    /*************************************************************//**
     *
     *  @brief  プレイヤーとボムの衝突時処理を行う
     *  @param  プレイヤー
     *  @param  ボム
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_PlayerAndBomb(C_BasePlayer* pPlayer, C_BaseBomb* pBomb)
    {
        StrongAssert(false && "[ C_CollisionProcess::s_PlayerAndBomb ] プレイヤーとボムが衝突することはありえません。\n");
    }


    /*************************************************************//**
     *
     *  @brief  オプション同士の衝突時処理を行う
     *  @param  オプション
     *  @param  もう一つのオプション
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_OptionAndOption(C_BaseOption* pOption, C_BaseOption* pAnotherOption)
    {
        // どちらも一度も連結していない場合は何もしない
        if (pOption->IsOnceConnectFlag() == false && pAnotherOption->IsOnceConnectFlag() == false) return;

        // 各オプションを追加
        pOption->AddConnectOption(pAnotherOption);
        pAnotherOption->AddConnectOption(pOption);
    }


    /*************************************************************//**
     *
     *  @brief  オプションと敵の衝突時処理を行う
     *  @param  オプション
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_OptionAndEnemy(C_BaseOption* pOption, C_BaseEnemy* pEnemy)
    {
        s_DamageToTarget(pOption, pEnemy);
        s_DamageToTarget(pEnemy, pOption);
    }


    /*************************************************************//**
     *
     *  @brief  オプションと弾の衝突時処理を行う
     *  @param  オプション
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_OptionAndBullet(C_BaseOption* pOption, C_BaseBullet* pBullet)
    {
        assert(pBullet->GetShooterType() == TYPE_ENEMY);

        s_DamageToTarget(pOption, pBullet);
        s_DamageToTarget(pBullet, pOption);
    }


    /*************************************************************//**
     *
     *  @brief  オプションと障害物の衝突時処理を行う
     *  @param  オプション
     *  @param  障害物
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_OptionAndObstacle(C_BaseOption* pOption, C_BaseObstacle* pObstacle)
    {
        s_DamageToTarget(pOption, pObstacle);
        s_DamageToTarget(pObstacle, pOption);
    }


    /*************************************************************//**
     *
     *  @brief  オプションとボムの衝突時処理を行う
     *  @param  オプション
     *  @param  ボム
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_OptionAndBomb(C_BaseOption* pOption, C_BaseBomb* pBomb)
    {
        StrongAssert(false && "[ C_CollisionProcess::s_OptionAndBomb ] オプションとボムが衝突することはありえません。\n");
    }


    /*************************************************************//**
     *
     *  @brief  敵同士の衝突時処理を行う
     *  @param  敵
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_EnemyAndEnemy(C_BaseEnemy* pEnemy, C_BaseEnemy* pAnotherEnemy)
    {
        StrongAssert(false && "[ C_CollisionProcess::s_EnemyAndEnemy ] 敵同士が衝突することはありえません。\n");
    }


    /*************************************************************//**
     *
     *  @brief  敵と弾の衝突時処理を行う
     *  @param  敵
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_EnemyAndBullet(C_BaseEnemy* pEnemy, C_BaseBullet* pBullet)
    {
        assert(pBullet->GetShooterType() == TYPE_PLAYER || pBullet->GetShooterType() == TYPE_OPTION);

        s_DamageToTarget(pEnemy, pBullet);
        s_DamageToTarget(pBullet, pEnemy);
    }


    /*************************************************************//**
     *
     *  @brief  敵と障害物の衝突時処理を行う
     *  @param  敵
     *  @param  障害物
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_EnemyAndObstacle(C_BaseEnemy* pEnemy, C_BaseObstacle* pObstacle)
    {
        s_DamageToTarget(pEnemy, pObstacle);
        s_DamageToTarget(pObstacle, pEnemy);
    }


    /*************************************************************//**
     *
     *  @brief  敵とボムの衝突時処理を行う
     *  @param  敵
     *  @param  ボム
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_EnemyAndBomb(C_BaseEnemy* pEnemy, C_BaseBomb* pBomb)
    {
        // s_DamageToTarget(pEnemy, pBomb);
        s_DamageToTarget(pBomb, pEnemy);
    }


    /*************************************************************//**
     *
     *  @brief  弾同士の衝突時処理を行う
     *  @param  弾
     *  @param  もう一つの弾
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_BulletAndBullet(C_BaseBullet* pBullet, C_BaseBullet* pAnotherBullet)
    {
        StrongAssert(false && "[ C_CollisionProcess::s_BulletAndBullet ] 弾同士が衝突することはありえません。\n");
    }


    /*************************************************************//**
     *
     *  @brief  弾と障害物の衝突時処理を行う
     *  @param  弾
     *  @param  障害物
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_BulletAndObstale(C_BaseBullet* pBullet, C_BaseObstacle* pObstacle)
    {
        s_DamageToTarget(pBullet, pObstacle);
        s_DamageToTarget(pObstacle, pBullet);
    }


    /*************************************************************//**
     *
     *  @brief  弾とボムの衝突時処理を行う
     *  @param  弾
     *  @param  ボム
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_BulletAndBomb(C_BaseBullet* pBullet, C_BaseBomb* pBomb)
    {
        assert(pBullet->GetShooterType() == TYPE_ENEMY);

        // s_DamageToTarget(pBullet, pBomb);
        s_DamageToTarget(pBomb, pBullet);
    }


    /*************************************************************//**
     *
     *  @brief  障害物同士の衝突時処理を行う
     *  @param  障害物
     *  @param  もう一つの障害物
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_ObstacleAndObstacle(C_BaseObstacle* pObstacle, C_BaseObstacle* pAnotherObstacle)
    {
        s_DamageToTarget(pObstacle, pAnotherObstacle);
        s_DamageToTarget(pAnotherObstacle, pObstacle);
    }


    /*************************************************************//**
     *
     *  @brief  障害物とボムの衝突時処理を行う
     *  @param  障害物
     *  @param  ボム
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_ObstacleAndBomb(C_BaseObstacle* pObstacle, C_BaseBomb* pBomb)
    {
        // s_DamageToTarget(pObstacle, pBomb);
        s_DamageToTarget(pBomb, pObstacle);
    }


    /*************************************************************//**
     *
     *  @brief  ボム同士の衝突時処理を行う
     *  @param  ボム
     *  @param  もう一つのボム
     *  @return なし
     *
     ****************************************************************/
    void C_CollisionProcess::s_BombAndBomb(C_BaseBomb* pBomb, C_BaseBomb* pAnotherBomb)
    {
    }


    /*************************************************************//**
     *
     *  @brief  対象者へダメージを与える
     *  @param  攻撃者
     *  @param  対象者
     *  @return なし
     *
     ****************************************************************/
    void s_DamageToTarget(C_CollisionObject* pAttacker, C_CollisionObject* pTarget)
    {
        if (pTarget->IsInvincibleFlag() == false)
        {
            pTarget->GetHitPoint()->Subtract(pAttacker->GetPower()->GetValue());
        }
    }
}