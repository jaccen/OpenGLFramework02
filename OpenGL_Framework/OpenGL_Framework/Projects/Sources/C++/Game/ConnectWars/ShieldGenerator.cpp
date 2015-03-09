/* ヘッダファイル */
#include "ShieldGenerator.h"
#include "BaseShield.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"


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
    C_ShieldGenerator::C_ShieldGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_ShieldGenerator::~C_ShieldGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  生成処理を行う
     *  @param  ID
     *  @param  座標
     *  @param  射撃者の種類
     *  @return シールド
     *
     ****************************************************************/
    ShieldPtr C_ShieldGenerator::Create(const std::string& rId,
                                        const Physics::Vector3& rPosition,
                                        int32_t shooterType,
                                        C_CollisionObject* pTarget)
    {
        // シールドを生成
        ShieldPtr pShield(pCreateFunctions_.at(rId)(shooterType, pTarget));

        // 各設定を行う
        pShield->SetPosition(rPosition);
        pShield->AddStringToId(std::to_string(number));

        // タスクシステムに登録
        pTaskSystem_->Entry(pShield, Priority::Task::Update::s_shield, Priority::Task::Draw::s_shield);

        ++number;

        return pShield;
    }


    /*************************************************************//**
     *
     *  @brief  関数の登録を行う
     *  @param  ID
     *  @param  生成関数
     *  @return なし
     *
     ****************************************************************/
    void C_ShieldGenerator::RegistFunction( const std::string& rId, CreateFunction pCreateFunction)
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
    void C_ShieldGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }
}