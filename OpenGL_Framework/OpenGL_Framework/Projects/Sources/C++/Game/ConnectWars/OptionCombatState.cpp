/* ヘッダファイル */
#include "OptionCombatState.h"
#include "BaseOption.h"
#include "BaseHitPoint.h"
#include "OptionDestroyedState.h"


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
    C_OptionCombatState::C_OptionCombatState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_OptionCombatState::~C_OptionCombatState()
    {
    }


    /*************************************************************//**
     *
     *  @brief  開始処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_OptionCombatState::Enter(C_BaseOption* pOption)
    {
    }


    /*************************************************************//**
     *
     *  @brief  実行処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_OptionCombatState::Execute(C_BaseOption* pOption)
    {
        if (pOption->GetHitPoint()->CheckRemainValue() == false || pOption->IsConnectFlag() == false)
        {
            pOption->GetStateMachine()->ChangeState(C_OptionDestroyedState::s_GetInstance());
        }

        pOption->Shot();
        pOption->Move();
        pOption->ResetConnect();
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_OptionCombatState::Exit(C_BaseOption* pOption)
    {
    }
	

    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  オプション
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_OptionCombatState::MessageProcess(C_BaseOption* pOption, const Telegram& rTelegram)
    {
        return true;
    }
}