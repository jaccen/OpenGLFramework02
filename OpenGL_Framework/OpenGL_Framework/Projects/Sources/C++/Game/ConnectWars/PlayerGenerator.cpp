/* ヘッダファイル */
#include "PlayerGenerator.h"
#include "NormalPlayer.h"
#include "../../Library/GameObject/Manager/GameObjectManager.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"
#include "../../Library/Debug/Helper/DebugHelper.h"


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
    C_PlayerGenerator::C_PlayerGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PlayerGenerator::~C_PlayerGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  生成処理を行う
     *  @param  障害物のID
     *  @param  座標
     *  @return プレイヤー
     *
     ****************************************************************/
    PlayerPtr C_PlayerGenerator::Create(const std::string& rId)
    {
        // 各プレイヤーを生成
        PlayerPtr pPlayer;

        if (rId == ID::Generator::Player::s_pNORMAL)
        {
            pPlayer = std::make_shared<C_NormalPlayer>(ID::GameObject::s_pPLAYER, TYPE_PLAYER);
        }
        else
        {
            StrongAssert(false);
        }

        // タスクシステムに登録
        pTaskSystem_->Entry(pPlayer, Priority::Task::Update::s_player, Priority::Task::Draw::s_player);

        // ゲームオブジェクトマネージャーに登録
        GameObject::C_GameObjectManager::s_GetInstance()->Entry(pPlayer);

        return pPlayer;
    }


    /*************************************************************//**
     *
     *  @brief  タスクシステムを設定する
     *  @param  タスクシステム
     *  @return なし
     *
     ****************************************************************/
    void C_PlayerGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }
}