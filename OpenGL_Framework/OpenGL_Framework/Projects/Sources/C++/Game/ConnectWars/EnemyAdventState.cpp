/* ヘッダファイル */
#include "EnemyAdventState.h"
#include "EnemyCombatState.h"
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
    C_EnemyAdventState::C_EnemyAdventState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_EnemyAdventState::~C_EnemyAdventState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  開始処理を行う
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_EnemyAdventState::Enter(C_BaseEnemy* pEnemy)
    {
    }


    /*************************************************************//**
     *
     *  @brief  実行処理を行う
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_EnemyAdventState::Execute(C_BaseEnemy* pEnemy)
    {
        if (pEnemy->IsFinishAdvent() == true)
        {
            pEnemy->GetStateMachine()->ChangeState(C_EnemyCombatState::s_GetInstance());
        }
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_EnemyAdventState::Exit(C_BaseEnemy* pEnemy)
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
    bool C_EnemyAdventState::MessageProcess(C_BaseEnemy* pEnemy, const Telegram& rTelegram)
    {
        return true;
    }
}