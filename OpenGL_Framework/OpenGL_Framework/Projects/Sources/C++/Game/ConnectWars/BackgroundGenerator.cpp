/* ヘッダファイル */
#include "BackgroundGenerator.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"
#include "BaseBackground.h"


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
    C_BackgroundGenerator::C_BackgroundGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BackgroundGenerator::~C_BackgroundGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  生成処理を行う
     *  @param  ID
     *  @param  座標
     *  @param  生存フレーム数
     *  @return 背景
     *
     ****************************************************************/
    BackgroundPtr C_BackgroundGenerator::Create(const std::string& rId, const Vector3& rPosition, int32_t lifeFrame)
    {
        // 背景を生成し、座標を設定
        BackgroundPtr pBackground(pCreateFunctions_.at(rId)());
        pBackground->SetPosition(rPosition);
        pBackground->AddStringToId(std::to_string(number));
        pBackground->SetLifeFrame(lifeFrame);

        // タスクシステムに登録
        pTaskSystem_->Entry(pBackground, Priority::Task::Update::s_background, Priority::Task::Draw::s_background);

        ++number;
        
        return pBackground;
    }


    /*************************************************************//**
     *
     *  @brief  関数の登録を行う
     *  @param  ID
     *  @param  生成関数
     *  @return なし
     *
     ****************************************************************/
    void C_BackgroundGenerator::RegistFunction(const std::string& rId, CreateFunction pCreateFunction)
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
    void C_BackgroundGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }


    /*************************************************************//**
     *
     *  @brief  背景データを設定する
     *  @param  背景データ
     *  @return なし
     *
     ****************************************************************/
    void C_BackgroundGenerator::SetBackgroundData(const JSON::JsonObjectPtr& prBackgroundData)
    {
        pBackgroundData_ = prBackgroundData;
    }
}