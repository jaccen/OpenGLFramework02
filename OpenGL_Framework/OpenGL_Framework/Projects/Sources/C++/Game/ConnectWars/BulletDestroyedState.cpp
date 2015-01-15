/* ヘッダファイル */
#include "BulletDestroyedState.h"
#include "BaseBullet.h"
#include "BaseHitPoint.h"


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
    C_BulletDestroyedState::C_BulletDestroyedState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BulletDestroyedState::~C_BulletDestroyedState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  開始処理を行う
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_BulletDestroyedState::Enter(C_BaseBullet* pBullet)
    {
        pBullet->SetExistanceFlag(false);
    }


    /*************************************************************//**
     *
     *  @brief  実行処理を行う
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_BulletDestroyedState::Execute(C_BaseBullet* pBullet)
    {
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_BulletDestroyedState::Exit(C_BaseBullet* pBullet)
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
    bool C_BulletDestroyedState::MessageProcess(C_BaseBullet* pBullet, const Telegram& rTelegram)
    {
        return true;
    }
}