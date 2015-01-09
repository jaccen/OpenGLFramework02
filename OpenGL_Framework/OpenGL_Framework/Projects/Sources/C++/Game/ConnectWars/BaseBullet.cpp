/* ヘッダファイル */
#include "BaseBullet.h"
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
     *
     ****************************************************************/
    C_BaseBullet::C_BaseBullet(const std::string& rId, int32_t type) : C_CollisionObject(rId, type),

        // ステートマシーン
        upStateMachine_(std::make_unique<State::C_StateMachine<C_BaseBullet>>(this))

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BaseBullet::~C_BaseBullet()
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
    bool C_BaseBullet::Update()
    {
        DoUpdate();

        return C_GameObject::existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBullet::Draw()
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
    bool C_BaseBullet::MessageProcess(const Telegram& rTelegram)
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
    void C_BaseBullet::DispatchCollision(C_CollisionObject* pCollisionObject)
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
    void C_BaseBullet::CollisionProcess(C_BasePlayer* pPlayer)
    {
        C_CollisionProcess::s_PlayerAndBullet(pPlayer, this);
    }


    /*************************************************************//**
     *
     *  @brief  オプションとの衝突時処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBullet::CollisionProcess(C_BaseOption* pOption)
    {
        C_CollisionProcess::s_OptionAndBullet(pOption, this);
    }


    /*************************************************************//**
     *
     *  @brief  敵との衝突時処理を行う
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBullet::CollisionProcess(C_BaseEnemy* pEnemy)
    {
        C_CollisionProcess::s_EnemyAndBullet(pEnemy, this);
    }


    /*************************************************************//**
     *
     *  @brief  弾との衝突時処理を行う
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBullet::CollisionProcess(C_BaseBullet* pBullet)
    {
        C_CollisionProcess::s_BulletAndBullet(this, pBullet);
    }


    /*************************************************************//**
     *
     *  @brief  障害物との衝突時処理を行う
     *  @param  障害物
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBullet::CollisionProcess(C_BaseObstacle* pObstacle)
    {
        C_CollisionProcess::s_BulletAndObstale(this, pObstacle);
    }


    /*************************************************************//**
     *
     *  @brief  ボムとの衝突時処理を行う
     *  @param  ボム
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBullet::CollisionProcess(C_BaseBomb* pBomb)
    {
        C_CollisionProcess::s_BulletAndBomb(this, pBomb);
    }


    /*************************************************************//**
     *
     *  @brief  移動処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBullet::Move()
    {
        upMoveLogic_->Process(upRigidBody_.get());
    }


    /*************************************************************//**
     *
     *  @brief  射撃者の種類を取得する
     *  @param  なし
     *  @return 射撃者の種類
     *
     ****************************************************************/
    int32_t C_BaseBullet::GetShooterType() const
    {
        return shooterType_;
    }


    /*************************************************************//**
     *
     *  @brief  ステートマシーンを取得する
     *  @param  なし
     *  @return ステートマシーン
     *
     ****************************************************************/
    State::C_StateMachine<C_BaseBullet>* C_BaseBullet::GetStateMachine() const
    {
        return upStateMachine_.get();
    }


    /*************************************************************//**
     *
     *  @brief  非公開の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBullet::DoUpdate()
    {
        upStateMachine_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  非公開の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBullet::DoDraw()
    {
    }


    /*************************************************************//**
     *
     *  @brief  非公開のメッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_BaseBullet::DoMessageProcess(const Telegram& rTelegram)
    {
        if (upStateMachine_->MessageProcess(rTelegram) == false) return false;

        return true;
    }
}