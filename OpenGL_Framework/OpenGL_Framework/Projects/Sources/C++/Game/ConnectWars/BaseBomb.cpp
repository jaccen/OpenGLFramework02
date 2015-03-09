/* ヘッダファイル */
#include "BaseBomb.h"
#include "CollisionProcess.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ID
     *  @param  種類
     *  @param  レベル
     *
     ****************************************************************/
    C_BaseBomb::C_BaseBomb(const std::string& rId, int32_t type, int32_t level) : C_CollisionObject(rId, type),

        // レベル
        level_(level)

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BaseBomb::~C_BaseBomb()
    {
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return タスク続行：true
     *  @return タスク終了：false
     *
     ****************************************************************/
    bool C_BaseBomb::Update()
    {
        DoUpdate();

        return existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBomb::Draw()
    {
        DoDraw();
    }


    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_BaseBomb::MessageProcess(const Telegram& rTelegram)
    {
        return DoMessageProcess(rTelegram);
    }


    /*************************************************************//**
     *
     *  @brief  衝突検知を発送する
     *  @param  衝突オブジェクト
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBomb::DispatchCollision(C_CollisionObject* pCollisionObject)
    {
        pCollisionObject->CollisionProcess(this);
    }


    /*************************************************************//**
     *
     *  @brief  プレイヤーとの衝突時処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBomb::CollisionProcess(C_BasePlayer* pPlayer)
    {
        C_CollisionProcess::s_PlayerAndBomb(pPlayer, this);
    }


    /*************************************************************//**
     *
     *  @brief  オプションとの衝突時処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBomb::CollisionProcess(C_BaseOption* pOption)
    {
        C_CollisionProcess::s_OptionAndBomb(pOption, this);
    }


    /*************************************************************//**
     *
     *  @brief  敵との衝突時処理を行う
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBomb::CollisionProcess(C_BaseEnemy* pEnemy)
    {
        C_CollisionProcess::s_EnemyAndBomb(pEnemy, this);
    }


    /*************************************************************//**
     *
     *  @brief  弾との衝突時処理を行う
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBomb::CollisionProcess(C_BaseBullet* pBullet)
    {
        C_CollisionProcess::s_BulletAndBomb(pBullet, this);
    }


    /*************************************************************//**
     *
     *  @brief  障害物との衝突時処理を行う
     *  @param  障害物
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBomb::CollisionProcess(C_BaseObstacle* pObstacle)
    {
        C_CollisionProcess::s_ObstacleAndBomb(pObstacle, this);
    }


    /*************************************************************//**
     *
     *  @brief  ボムとの衝突時処理を行う
     *  @param  ボム
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBomb::CollisionProcess(C_BaseBomb* pBomb)
    {
        C_CollisionProcess::s_BombAndBomb(this, pBomb);
    }


    /*************************************************************//**
     *
     *  @brief  シールドとの衝突時処理を行う
     *  @param  シールド
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBomb::CollisionProcess(C_BaseShield* pShield)
    {
        C_CollisionProcess::s_BombAndShield(this, pShield);
    }


    /*************************************************************//**
     *
     *  @brief  座標を取得する
     *  @param  なし
     *  @return 座標
     *
     ****************************************************************/
    const Physics::Vector3& C_BaseBomb::GetPosition() const
    {
        return upRigidBody_->GetTransform().getOrigin();
    }


    /*************************************************************//**
     *
     *  @brief  座標を設定する
     *  @param  座標
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBomb::SetPosition(const Physics::Vector3& rPosition)
    {
        Physics::Transform transform;
        transform.setIdentity();
        transform.setOrigin(rPosition);

        upRigidBody_->SetTransform(transform);
    }



    /*************************************************************//**
     *
     *  @brief  非公開の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBomb::DoDraw()
    {
    }


    /*************************************************************//**
     *
     *  @brief  非公開のメッセージ処理を行う
     *  @param  テレグラム
     *  @return なし
     *
     ****************************************************************/
    bool C_BaseBomb::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }
}