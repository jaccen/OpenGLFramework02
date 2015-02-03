/* ヘッダファイル */
#include "BulletGenerator.h"
#include "BaseBullet.h"
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
    C_BulletGenerator::C_BulletGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BulletGenerator::~C_BulletGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  生成処理を行う
     *  @param  ID
     *  @param  座標
     *  @param  パワー
     *  @param  移動のロジック
     *  @return 射撃者の種類
     *
     ****************************************************************/
    BulletPtr C_BulletGenerator::Create(const std::string& rId,
                                        const Physics::Vector3& rPosition,
                                        int32_t power,
                                        C_RigidBodyMoveLogic* pMoveLogic,
                                        int32_t shooterType)
    {
        // 弾を生成
        BulletPtr pBullet(pCreateFunctions_.at(rId)(shooterType));

        // 各設定を行う
        pBullet->SetMoveLogic(pMoveLogic);
        pBullet->GetPower()->SetValue(power);
        pBullet->SetPosition(rPosition);
        pBullet->AddStringToId(std::to_string(number));

        // タスクシステムに登録
        pTaskSystem_->Entry(pBullet, Priority::Task::Update::s_bullet, Priority::Task::Draw::s_bullet);

        ++number;

        return pBullet;
    }


    /*************************************************************//**
     *
     *  @brief  関数の登録を行う
     *  @param  ID
     *  @param  生成関数
     *  @return なし
     *
     ****************************************************************/
    void C_BulletGenerator::RegistFunction( const std::string& rId, CreateFunction pCreateFunction)
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
    void C_BulletGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }
}