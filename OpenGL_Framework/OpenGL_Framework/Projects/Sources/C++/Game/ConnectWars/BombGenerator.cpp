/* ヘッダファイル */
#include "BombGenerator.h"
#include "BaseBomb.h"
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
    C_BombGenerator::C_BombGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BombGenerator::~C_BombGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  生成処理を行う
     *  @param  ID
     *  @param  座標
     *  @param  レベル
     *  @return ボム
     *
     ****************************************************************/
    BombPtr C_BombGenerator::Create(const std::string& rId, const Physics::Vector3& rPosition, int32_t level)
    {
        // 敵を生成
        BombPtr pBomb(pCreateFunctions_.at(rId)());

        // 各設定を行う
        pBomb->SetPosition(rPosition);
        pBomb->SetLevel(level);

        // タスクシステムに登録
        pTaskSystem_->Entry(pBomb, Priority::Task::Update::s_bomb, Priority::Task::Draw::s_bomb);
        ++number;

        return pBomb;
    }


    /*************************************************************//**
     *
     *  @brief  関数の登録を行う
     *  @param  ID
     *  @param  生成関数
     *  @return なし
     *
     ****************************************************************/
    void C_BombGenerator::RegistFunction( const std::string& rId, CreateFunction pCreateFunction)
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
    void C_BombGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }
}