/* ヘッダファイル */
#include "RankingController.h"
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
    C_RankingController::C_RankingController(const std::string& rId, int32_t type) : C_SceneController(rId, type)
    {
        upFade_ = std::make_unique<C_Fade>(ID::GameObject::s_pFADE, eGameObjectType::TYPE_FADE, 20, true);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_RankingController::~C_RankingController()
    {
    }


    /*************************************************************//**
     *
     *  @brief  非公開の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RankingController::DoUpdate()
    {
        if (toTitleFlag_ == true)
        {
            if (upFade_->IsFinishFadeOutFlag() == true)
            {
                auto pNextScece = newEx C_LoadScene;
                pSceneChanger_->ReplaceScene(pNextScece);

                pNextScece->SetNextSceneId(ID::Scene::s_pTITLE);
                pNextScece->SetLoadFunction(C_LoadFunction::s_LoadTitleData);
            }
        }

        upFade_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  非公開の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RankingController::DoDraw()
    {
        upFade_->Draw();
    }


    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_RankingController::DoMessageProcess(const Telegram& rTelegram)
    {
        if (Message::s_pTO_TITLE_SCENE)
        {
            toTitleFlag_ = true;
           
            assert(upFade_);
            upFade_->FadeOut();
        }

        return true;
    }
}