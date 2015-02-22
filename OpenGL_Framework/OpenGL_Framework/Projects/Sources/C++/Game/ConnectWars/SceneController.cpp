/* ヘッダファイル */
#include "SceneController.h"


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
    C_SceneController::C_SceneController(const std::string& rId, int32_t type) : C_GameObject(rId, type)
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SceneController::~C_SceneController()
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
    bool C_SceneController::Update()
    {
        if (waitFlag_ == false) frameCounter_.CountUp();

        DoUpdate();

        return C_GameObject::existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SceneController::Draw()
    {
        DoDraw();
    }


    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SceneController::MessageProcess(const Telegram& rTelegram)
    {
        return DoMessageProcess(rTelegram);
    }


    /*************************************************************//**
     *
     *  @brief  待機状態を有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_SceneController::EnableWait(bool validFlag)
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
    int32_t C_SceneController::GetNowFrame() const
    {
        return frameCounter_.GetCount();
    }


    /*************************************************************//**
     *
     *  @brief  シーンチェンジャーを設定する
     *  @param  シーンチェンジャー
     *  @return なし
     *
     ****************************************************************/
    void C_SceneController::SetSceneChanger(Scene::IC_SceneChanger* pSceneChanger)
    {
        pSceneChanger_ = pSceneChanger;
    }
}