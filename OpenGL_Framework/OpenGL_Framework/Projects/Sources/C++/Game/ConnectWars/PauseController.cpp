/* ヘッダファイル */
#include "PauseController.h"
#include "LoadScene.h"
#include "LoadFunction.h"
#include "../../Library/Debug/Helper/DebugHelper.h"


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
    C_PauseController::C_PauseController(const std::string& rId, int32_t type) : C_SceneController(rId, type)
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PauseController::~C_PauseController()
    {
    }


    /*************************************************************//**
     *
     *  @brief  非公開の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PauseController::DoUpdate()
    {
        if (toTitleFlag_ == true)
        {
            auto pNextScece = newEx C_LoadScene;
            pSceneChanger_->ReplaceScene(pNextScece);

            pNextScece->SetNextSceneId(ID::Scene::s_pTITLE);
            pNextScece->SetLoadFunction(C_LoadFunction::s_LoadTitleData);
        }

    }


    /*************************************************************//**
     *
     *  @brief  非公開の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PauseController::DoDraw()
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
    bool C_PauseController::DoMessageProcess(const Telegram& rTelegram)
    {
        if (rTelegram.message_ == Message::s_pTO_TITLE_SCENE)
        {
            toTitleFlag_ = true;
        }
        else if (rTelegram.message_ == Message::s_pRESUME_GAME)
        {

        }
        else if (rTelegram.message_ == Message::s_pRESTART_GAME)
        {

        }
        return true;
    }
}