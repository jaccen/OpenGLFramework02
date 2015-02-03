/* ヘッダファイル */
#include "EnemyGenerator.h"
#include "BaseEnemy.h"
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
    C_EnemyGenerator::C_EnemyGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_EnemyGenerator::~C_EnemyGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  生成処理を行う
     *  @param  ID
     *  @param  座標
     *  @return 射撃者の種類
     *
     ****************************************************************/
    EnemyPtr C_EnemyGenerator::Create(const std::string& rId)
    {
        // 敵を生成
        EnemyPtr pEnemy(pCreateFunctions_.at(rId)());

        // 各設定を行う
        pEnemy->SetCreateDataWithJson(&(*pEnemyData_)["EnemyData"][0]);
        pEnemy->AddStringToId(std::to_string(number));

        // タスクシステムに登録
        pTaskSystem_->Entry(pEnemy, Priority::Task::Update::s_bullet, Priority::Task::Draw::s_bullet);

        ++number;

        return pEnemy;
    }


    /*************************************************************//**
     *
     *  @brief  関数の登録を行う
     *  @param  ID
     *  @param  生成関数
     *  @return なし
     *
     ****************************************************************/
    void C_EnemyGenerator::RegistFunction( const std::string& rId, CreateFunction pCreateFunction)
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
    void C_EnemyGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }


    /*************************************************************//**
     *
     *  @brief  敵データを設定する
     *  @param  敵データ
     *  @return なし
     *
     ****************************************************************/
    void C_EnemyGenerator::SetEnemyData(const JSON::JsonObjectPtr& prEnemyData)
    {
        pEnemyData_ = prEnemyData;
    }
}