/* ヘッダファイル */
#include "BulletFireState.h"
#include "BaseBullet.h"
#include "BaseHitPoint.h"
#include "BulletDestroyedState.h"


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
     *  @param  なし
     *
     ****************************************************************/
    C_BulletFireState::C_BulletFireState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BulletFireState::~C_BulletFireState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  開始処理を行う
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_BulletFireState::Enter(C_BaseBullet* pBullet)
    {
    }


    /*************************************************************//**
     *
     *  @brief  実行処理を行う
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_BulletFireState::Execute(C_BaseBullet* pBullet)
    {
        if (pBullet->GetHitPoint()->CheckRemainValue() == false)
        {
            pBullet->GetStateMachine()->ChangeState(C_BulletDestroyedState::s_GetInstance());
        }

        pBullet->Move();
        pBullet->MoveLimitCheck();
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_BulletFireState::Exit(C_BaseBullet* pBullet)
    {
    }


    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  弾
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_BulletFireState::MessageProcess(C_BaseBullet* pBullet, const Telegram& rTelegram)
    {
        return true;
    }
}