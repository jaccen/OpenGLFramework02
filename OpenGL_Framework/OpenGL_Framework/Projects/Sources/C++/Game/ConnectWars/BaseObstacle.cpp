/* ヘッダファイル */
#include "BaseObstacle.h"
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
    C_BaseObstacle::C_BaseObstacle(const std::string& rId, int32_t type) : C_CollisionObject(rId, type)
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BaseObstacle::~C_BaseObstacle()
    {
    }


    /*************************************************************//**
     *
     *  @brief  障害物の更新処理を行う
     *  @param  なし
     *  @return タスク続行：true
     *  @return タスク終了：false
     *
     ****************************************************************/
    bool C_BaseObstacle::Update()
    {
        DoUpdate();

        return C_GameObject::existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  障害物の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseObstacle::Draw()
    {
        DoDraw();
    }


    /*************************************************************//**
     *
     *  @brief  障害物のメッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_BaseObstacle::MessageProcess(const Telegram& rTelegram)
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
    void C_BaseObstacle::DispatchCollision(C_CollisionObject* pCollisionObject)
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
    void C_BaseObstacle::CollisionProcess(C_BasePlayer* pPlayer)
    {
        C_CollisionProcess::s_PlayerAndObstacle(pPlayer, this);
    }


    /*************************************************************//**
     *
     *  @brief  オプションとの衝突時処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_BaseObstacle::CollisionProcess(C_BaseOption* pOption)
    {
        C_CollisionProcess::s_OptionAndObstacle(pOption, this);
    }


    /*************************************************************//**
     *
     *  @brief  敵との衝突時処理を行う
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_BaseObstacle::CollisionProcess(C_BaseEnemy* pEnemy)
    {
        C_CollisionProcess::s_EnemyAndObstacle(pEnemy, this);
    }


    /*************************************************************//**
     *
     *  @brief  弾との衝突時処理を行う
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_BaseObstacle::CollisionProcess(C_BaseBullet* pBullet)
    {
        C_CollisionProcess::s_BulletAndObstale(pBullet, this);
    }


    /*************************************************************//**
     *
     *  @brief  障害物との衝突時処理を行う
     *  @param  障害物
     *  @return なし
     *
     ****************************************************************/
    void C_BaseObstacle::CollisionProcess(C_BaseObstacle* pObstacle)
    {
        C_CollisionProcess::s_ObstacleAndObstacle(this, pObstacle);
    }


    /*************************************************************//**
     *
     *  @brief  移動処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseObstacle::Move()
    {
    }


    /*************************************************************//**
     *
     *  @brief  非公開の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseObstacle::DoUpdate()
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
    void C_BaseObstacle::DoDraw()
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
    bool C_BaseObstacle::DoMessageProcess(const Telegram& rTelegram)
    {
        if (upStateMachine_->MessageProcess(rTelegram) == false) return false;

        return true;
    }
}