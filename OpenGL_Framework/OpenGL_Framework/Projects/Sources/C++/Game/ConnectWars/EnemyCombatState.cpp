/* ヘッダファイル */
#include "EnemyAdventState.h"
#include "EnemyCombatState.h"
#include "EnemyDestroyedState.h"
#include "BaseEnemy.h"


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
    C_EnemyCombatState::C_EnemyCombatState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_EnemyCombatState::~C_EnemyCombatState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  開始処理を行う
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_EnemyCombatState::Enter(C_BaseEnemy* pEnemy)
    {
    }


    /*************************************************************//**
     *
     *  @brief  実行処理を行う
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_EnemyCombatState::Execute(C_BaseEnemy* pEnemy)
    {
        // ヒットポイントがなくなった場合、破壊された状態へ変更
        if (pEnemy->GetHitPoint()->CheckRemainValue() == false)
        {
            pEnemy->GetStateMachine()->ChangeState(C_EnemyDestroyedState::s_GetInstance());
        }

        pEnemy->Move();
        pEnemy->Shot();
        pEnemy->MoveLimitCheck();
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_EnemyCombatState::Exit(C_BaseEnemy* pEnemy)
    {
    }


    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  敵
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_EnemyCombatState::MessageProcess(C_BaseEnemy* pEnemy, const Telegram& rTelegram)
    {
        return true;
    }
}