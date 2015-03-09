/* ヘッダファイル */
#include "BaseShield.h"
#include "CollisionProcess.h"
#include "BulletFireState.h"


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
     *  @param  射撃者の種類
     *  @param  ターゲット
     *
     ****************************************************************/
    C_BaseShield::C_BaseShield(const std::string& rId,
                               int32_t type,  
                               int32_t shooterType,
                               C_CollisionObject* pTarget) : C_CollisionObject(rId, type)
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BaseShield::~C_BaseShield()
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
    bool C_BaseShield::Update()
    {
        // 非公開の更新処理
        DoUpdate();

        // 衝突オブジェクトのIDをリセット
        ResetCollidedObjectId();

        return C_GameObject::existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseShield::Draw()
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
    bool C_BaseShield::MessageProcess(const Telegram& rTelegram)
    {
        if (DoMessageProcess(rTelegram) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  衝突検知の発行を行う
     *  @param  衝突オブジェクト
     *  @return なし
     *
     ****************************************************************/
    void C_BaseShield::DispatchCollision(C_CollisionObject* pCollisionObject)
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
    void C_BaseShield::CollisionProcess(C_BasePlayer* pPlayer)
    {
        C_CollisionProcess::s_PlayerAndShield(pPlayer, this);
    }


    /*************************************************************//**
     *
     *  @brief  オプションとの衝突時処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_BaseShield::CollisionProcess(C_BaseOption* pOption)
    {
        C_CollisionProcess::s_OptionAndShield(pOption, this);
    }


    /*************************************************************//**
     *
     *  @brief  敵との衝突時処理を行う
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_BaseShield::CollisionProcess(C_BaseEnemy* pEnemy)
    {
        C_CollisionProcess::s_EnemyAndShield(pEnemy, this);
    }


    /*************************************************************//**
     *
     *  @brief  弾との衝突時処理を行う
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_BaseShield::CollisionProcess(C_BaseBullet* pBullet)
    {
        C_CollisionProcess::s_BulletAndShield(pBullet, this);
    }


    /*************************************************************//**
     *
     *  @brief  障害物との衝突時処理を行う
     *  @param  障害物
     *  @return なし
     *
     ****************************************************************/
    void C_BaseShield::CollisionProcess(C_BaseObstacle* pObstacle)
    {
        C_CollisionProcess::s_ObstacleAndShield(pObstacle, this);
    }


    /*************************************************************//**
     *
     *  @brief  ボムとの衝突時処理を行う
     *  @param  ボム
     *  @return なし
     *
     ****************************************************************/
    void C_BaseShield::CollisionProcess(C_BaseBomb* pBomb)
    {
        C_CollisionProcess::s_BombAndShield(pBomb, this);
    }


    /*************************************************************//**
     *
     *  @brief  ボムとの衝突時処理を行う
     *  @param  ボム
     *  @return なし
     *
     ****************************************************************/
    void C_BaseShield::CollisionProcess(C_BaseShield* pShield)
    {
        C_CollisionProcess::s_ShieldAndShield(this, pShield);
    }


    /*************************************************************//**
     *
     *  @brief  移動処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseShield::Move()
    {
        upMoveLogic_->Process(upRigidBody_.get());
    }


    /*************************************************************//**
     *
     *  @brief  座標を取得する
     *  @param  なし
     *  @return 座標
     *
     ****************************************************************/
    const Physics::Vector3& C_BaseShield::GetPosition() const
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
    void C_BaseShield::SetPosition(const Physics::Vector3& rPosition)
    {
        auto transform = upRigidBody_->GetTransform();
        transform.setOrigin(rPosition);
        upRigidBody_->SetTransform(transform);
    }


    /*************************************************************//**
     *
     *  @brief  非公開の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseShield::DoUpdate()
    {
        Move();
    }


    /*************************************************************//**
     *
     *  @brief  非公開のメッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_BaseShield::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }
}