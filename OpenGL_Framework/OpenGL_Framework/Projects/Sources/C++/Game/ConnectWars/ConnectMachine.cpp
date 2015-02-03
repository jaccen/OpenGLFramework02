/* ヘッダファイル */
#include "ConnectMachine.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
#pragma region 静的メンバ変数の初期化


    /* 自爆遅延フレーム数の間隔 */
    uint32_t C_ConnectMachine::s_ownCrashDerayFrameInterval = 10;


#pragma endregion



    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ID
     *  @param  種類
     *  @param  座標
     *
     ****************************************************************/
    C_ConnectMachine::C_ConnectMachine(const std::string& rId, int32_t type) : C_Shooter(rId, type)
    {
        // オプション4個分のメモリをあらかじめ確保しておく
        pConnectOptionList_.reserve(4);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_ConnectMachine::~C_ConnectMachine()
    {
    }


    /*************************************************************//**
     *
     *  @brief  連結しているオプションのリストを取得する
     *  @param  なし
     *  @return 連結しているオプションのリスト
     *
     ****************************************************************/
    std::vector<C_BaseOption*>* C_ConnectMachine::GetConnectOptionList()
    {
        return &pConnectOptionList_;
    }


    /*************************************************************//**
     *
     *  @brief  剛体を取得する
     *  @param  なし
     *  @return 剛体
     *
     ****************************************************************/
    Physics::C_RigidBody* C_ConnectMachine::GetRigidBody() const
    {
        return upRigidBody_.get();
    }


    /*************************************************************//**
     *
     *  @brief  半径を取得する
     *  @param  なし
     *  @return 半径
     *
     ****************************************************************/
    float C_ConnectMachine::GetRadius() const
    {
        return radius_;
    }


    /*************************************************************//**
     *
     *  @brief  座標を取得する
     *  @param  なし
     *  @return 座標
     *
     ****************************************************************/
    const Physics::Vector3& C_ConnectMachine::GetPosition() const
    {
        return upRigidBody_->GetTransform().getOrigin();
    }


    /*************************************************************//**
     *
     *  @brief  座標を設定する
     *  @param  座標
     *  @return なし
     *
     ****************************************************************/
    void C_ConnectMachine::SetPosition(const Physics::Vector3& rPosition)
    {
        auto transform = upRigidBody_->GetTransform();
        transform.setOrigin(rPosition);
        upRigidBody_->SetTransform(transform);
    }


    /*************************************************************//**
     *
     *  @brief  回転量を取得する
     *  @param  なし
     *  @return 回転量
     *
     ****************************************************************/
    const Physics::Matrix3x3& C_ConnectMachine::GetRotation() const
    {
        return upRigidBody_->GetTransform().getBasis();
    }


    /*************************************************************//**
     *
     *  @brief  自爆遅延フレーム数の間隔を設定する
     *  @param  自爆遅延フレーム数の間隔
     *  @return なし
     *
     ****************************************************************/
    void C_ConnectMachine::s_SetOwnCrashDerayFrameInterval(uint32_t ownCrashDerayFrameInterval)
    {
        s_ownCrashDerayFrameInterval = ownCrashDerayFrameInterval;
    }
}