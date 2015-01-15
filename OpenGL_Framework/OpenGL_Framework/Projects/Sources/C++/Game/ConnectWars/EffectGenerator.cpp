/* ヘッダファイル */
#include "EffectGenerator.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"
#include "BaseEffect.h"


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
    C_EffectGenerator::C_EffectGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_EffectGenerator::~C_EffectGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  生成処理を行う
     *  @param  ID
     *  @param  座標
     *  @return エフェクト
     *
     ****************************************************************/
    EffectPtr C_EffectGenerator::Create(const std::string& rId, const Vector3& rPosition)
    {
        // エフェクトを生成し、座標を設定
        EffectPtr pEffect(pCreateFunctions_.at(rId)());
        pEffect->SetPosition(rPosition);
        pEffect->AddStringToId(std::to_string(number));

        // タスクシステムに登録
        pTaskSystem_->Entry(pEffect, Priority::Task::Update::s_effect, Priority::Task::Draw::s_effect);

        ++number;
        
        return pEffect;
    }


    /*************************************************************//**
     *
     *  @brief  関数の登録を行う
     *  @param  ID
     *  @param  生成関数
     *  @return なし
     *
     ****************************************************************/
    void C_EffectGenerator::RegistFunction(const std::string& rId, CreateFunction pCreateFunction)
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
    void C_EffectGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }
}