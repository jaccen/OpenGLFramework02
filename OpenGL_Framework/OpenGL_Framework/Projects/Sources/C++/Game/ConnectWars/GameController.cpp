/* ヘッダファイル */
#include "GameController.h"


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
     *  @param  ID
     *  @param  種類
     *
     ****************************************************************/
    C_GameController::C_GameController(const std::string& rId, int32_t type) : C_GameObject(rId, type)
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_GameController::~C_GameController()
    {
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return タスク続行：true
     *  @return タスク終了：false
     *
     ****************************************************************/
    bool C_GameController::Update()
    {
        if (waitFlag_ == false)
        {
            frameCounter_.CountUp();
        }

        return C_GameObject::existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_GameController::Draw()
    {
    }


    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_GameController::MessageProcess(const Telegram& rTelegram)
    {
        return true;
    }


    /*************************************************************//**
     *
     *  @brief  待機状態を有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_GameController::EnableWait(bool validFlag)
    {
        waitFlag_ = validFlag;
    }


    /*************************************************************//**
     *
     *  @brief  現在のフレーム数を取得する
     *  @param  なし
     *  @return 現在のフレーム数
     *
     ****************************************************************/
    int32_t C_GameController::GetNowFrame() const
    {
        return frameCounter_.GetCount();
    }
}