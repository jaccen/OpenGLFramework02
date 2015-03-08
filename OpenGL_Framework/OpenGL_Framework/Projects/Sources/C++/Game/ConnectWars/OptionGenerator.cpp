/* ヘッダファイル */
#include "OptionGenerator.h"
#include "../../Library/GameObject/Manager/GameObjectManager.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"
#include "BaseOption.h"


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
    C_OptionGenerator::C_OptionGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_OptionGenerator::~C_OptionGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  生成処理を行う
     *  @param  ID
     *  @param  座標
     *  @return オプション
     *
     ****************************************************************/
    OptionPtr C_OptionGenerator::Create(const std::string& rId, const Physics::Vector3& rPosition)
    {
        // オプションを生成し、座標を設定
        OptionPtr pOption(pCreateFunctions_.at(rId)());
        pOption->SetPosition(rPosition);
        pOption->AddStringToId(std::to_string(number));

        // タスクシステムに登録
        pTaskSystem_->Entry(pOption, Priority::Task::Update::s_option, Priority::Task::Draw::s_option);

        // ゲームオブジェクトマネージャーに登録
        GameObject::C_GameObjectManager::s_GetInstance()->Entry(pOption);

        ++number;
        
        return pOption;
    }


    /*************************************************************//**
     *
     *  @brief  関数の登録を行う
     *  @param  ID
     *  @param  生成関数
     *  @return なし
     *
     ****************************************************************/
    void C_OptionGenerator::RegistFunction(const std::string& rId, CreateFunction pCreateFunction)
    {
        pCreateFunctions_.emplace(rId, pCreateFunction);
    }


    /*************************************************************//**
     *
     *  @brief  タスクシステムを設定する
     *  @param  タスクシステム
     *  @return なし
     *
     ****************************************************************/
    void C_OptionGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }
}