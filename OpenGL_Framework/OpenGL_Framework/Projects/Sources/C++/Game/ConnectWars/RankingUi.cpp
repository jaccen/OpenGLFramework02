/* ヘッダファイル */
#include "RankingUi.h"
#include "UiFont.h"
#include "../../Library/Window/Manager/WindowManager.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "../../Library/GameObject/Message/Dispatcher/MessageDispatcher.h"
#include "../../Library/Input/Keyboard/KeyboardManager.h"
#include "../../Library/Input/Gamepad/Manager/GamepadManager.h"


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
     *  @param  ランキング登録フラグ
     *  @param  新しいスコア
     *
     ****************************************************************/
    C_RankingUi::C_RankingUi(const std::string& rId, int32_t type, bool rankingEntryFlag, int32_t newScore) : C_BaseUi(rId, type)
    {
        assert(Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pRANKING_BACKGROUND));
        wpBackgroundSpriteCreater_ = Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pRANKING_BACKGROUND).get();

        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pRANKING_UI_DATA));
        auto pRankingUIData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pRANKING_UI_DATA).get();

        LoadRankingEntryWords(&(*pRankingUIData)["RankingUiData"]);
        LoadRankingWords(&(*pRankingUIData)["RankingUiData"]);
        LoadRankingData();

        if (rankingEntryFlag == true)
        {
            newRecordData_.rank_ = -1;

            for (int32_t i = 4; i >= 0; --i)
            {
                if (newScore > rankingDatas_[i].scoreData_.score_)
                {
                    newRecordData_.rank_ = i;
                    newRecordData_.score_ = newScore;
                }
                else
                {
                    break;
                }
            }

            if (newRecordData_.rank_ != -1)
            {
                switch (newRecordData_.rank_)
                {
                case 0:

                    newRecordData_.rankWords_ = "1st";

                    break;
                case 1:

                    newRecordData_.rankWords_ = "2nd";

                    break;
                case 2:

                    newRecordData_.rankWords_ = "3rd";
                    
                    break;
                case 3:

                    newRecordData_.rankWords_ = "4th";

                    break;
                case 4:

                    newRecordData_.rankWords_ = "5th";

                    break;
                }

                rankingEntryFlag_ = rankingEntryFlag;
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_RankingUi::~C_RankingUi()
    {
        SaveRankingData();
    }


    /*************************************************************//**
     *
     *  @brief  非公開の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RankingUi::DoUpdate()
    {
        UpdateRankingEntry();
        UpdateRanking();
    }


    /*************************************************************//**
     *
     *  @brief  非公開の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RankingUi::DoDraw()
    {
        DrawBackground();
        DrawRankingEntry();
        DrawRanking();
    }


    /*************************************************************//**
     *
     *  @brief  非公開のメッセージ処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    bool C_RankingUi::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }


    /*************************************************************//**
     *
     *  @brief  ランキング登録文字のロード処理を行う
     *  @param  データ
     *  @return なし
     *
     ****************************************************************/
    void C_RankingUi::LoadRankingEntryWords(JSON::JsonObject* pData)
    {
        rankingEntryWords_[0].words_ = (*pData)["NewRecord"]["Words"].GetValue<JSON::String>();
        rankingEntryWords_[0].position_.x_ = static_cast<float>((*pData)["NewRecord"]["Position"][0].GetValue<JSON::Real>());
        rankingEntryWords_[0].position_.y_ = static_cast<float>((*pData)["NewRecord"]["Position"][1].GetValue<JSON::Real>());
        rankingEntryWords_[0].size_.x_ = static_cast<float>((*pData)["NewRecord"]["Size"][0].GetValue<JSON::Real>());
        rankingEntryWords_[0].size_.y_ = static_cast<float>((*pData)["NewRecord"]["Size"][1].GetValue<JSON::Real>());
        rankingEntryWords_[0].color_.red_ = static_cast<float>((*pData)["NewRecord"]["Color"][0].GetValue<JSON::Real>());
        rankingEntryWords_[0].color_.green_ = static_cast<float>((*pData)["NewRecord"]["Color"][1].GetValue<JSON::Real>());
        rankingEntryWords_[0].color_.blue_ = static_cast<float>((*pData)["NewRecord"]["Color"][2].GetValue<JSON::Real>());
        rankingEntryWords_[0].color_.alpha_ = static_cast<float>((*pData)["NewRecord"]["Color"][3].GetValue<JSON::Real>());
        rankingEntryWords_[0].wordOffset_ = static_cast<float>((*pData)["NewRecord"]["WordOffset"].GetValue<JSON::Real>());
    }


    /*************************************************************//**
     *
     *  @brief  ランキング文字のロード処理を行う
     *  @param  データ
     *  @return なし
     *
     ****************************************************************/
    void C_RankingUi::LoadRankingWords(JSON::JsonObject* pData)
    {
        rankingWords_[0].words_ = (*pData)["Ranking"]["Words"].GetValue<JSON::String>();
        rankingWords_[0].position_.x_ = static_cast<float>((*pData)["Ranking"]["Position"][0].GetValue<JSON::Real>());
        rankingWords_[0].position_.y_ = static_cast<float>((*pData)["Ranking"]["Position"][1].GetValue<JSON::Real>());
        rankingWords_[0].size_.x_ = static_cast<float>((*pData)["Ranking"]["Size"][0].GetValue<JSON::Real>());
        rankingWords_[0].size_.y_ = static_cast<float>((*pData)["Ranking"]["Size"][1].GetValue<JSON::Real>());
        rankingWords_[0].color_.red_ = static_cast<float>((*pData)["Ranking"]["Color"][0].GetValue<JSON::Real>());
        rankingWords_[0].color_.green_ = static_cast<float>((*pData)["Ranking"]["Color"][1].GetValue<JSON::Real>());
        rankingWords_[0].color_.blue_ = static_cast<float>((*pData)["Ranking"]["Color"][2].GetValue<JSON::Real>());
        rankingWords_[0].color_.alpha_ = static_cast<float>((*pData)["Ranking"]["Color"][3].GetValue<JSON::Real>());
        rankingWords_[0].wordOffset_ = static_cast<float>((*pData)["Ranking"]["WordOffset"].GetValue<JSON::Real>());

        rankingWords_[1].words_ = (*pData)["1st"]["Words"].GetValue<JSON::String>();
        rankingWords_[1].position_.x_ = static_cast<float>((*pData)["1st"]["Position"][0].GetValue<JSON::Real>());
        rankingWords_[1].position_.y_ = static_cast<float>((*pData)["1st"]["Position"][1].GetValue<JSON::Real>());
        rankingWords_[1].size_.x_ = static_cast<float>((*pData)["1st"]["Size"][0].GetValue<JSON::Real>());
        rankingWords_[1].size_.y_ = static_cast<float>((*pData)["1st"]["Size"][1].GetValue<JSON::Real>());
        rankingWords_[1].color_.red_ = static_cast<float>((*pData)["1st"]["Color"][0].GetValue<JSON::Real>());
        rankingWords_[1].color_.green_ = static_cast<float>((*pData)["1st"]["Color"][1].GetValue<JSON::Real>());
        rankingWords_[1].color_.blue_ = static_cast<float>((*pData)["1st"]["Color"][2].GetValue<JSON::Real>());
        rankingWords_[1].color_.alpha_ = static_cast<float>((*pData)["1st"]["Color"][3].GetValue<JSON::Real>());
        rankingWords_[1].wordOffset_ = static_cast<float>((*pData)["1st"]["WordOffset"].GetValue<JSON::Real>());

        rankingWords_[2].words_ = (*pData)["2nd"]["Words"].GetValue<JSON::String>();
        rankingWords_[2].position_.x_ = static_cast<float>((*pData)["2nd"]["Position"][0].GetValue<JSON::Real>());
        rankingWords_[2].position_.y_ = static_cast<float>((*pData)["2nd"]["Position"][1].GetValue<JSON::Real>());
        rankingWords_[2].size_.x_ = static_cast<float>((*pData)["2nd"]["Size"][0].GetValue<JSON::Real>());
        rankingWords_[2].size_.y_ = static_cast<float>((*pData)["2nd"]["Size"][1].GetValue<JSON::Real>());
        rankingWords_[2].color_.red_ = static_cast<float>((*pData)["2nd"]["Color"][0].GetValue<JSON::Real>());
        rankingWords_[2].color_.green_ = static_cast<float>((*pData)["2nd"]["Color"][1].GetValue<JSON::Real>());
        rankingWords_[2].color_.blue_ = static_cast<float>((*pData)["2nd"]["Color"][2].GetValue<JSON::Real>());
        rankingWords_[2].color_.alpha_ = static_cast<float>((*pData)["2nd"]["Color"][3].GetValue<JSON::Real>());
        rankingWords_[2].wordOffset_ = static_cast<float>((*pData)["2nd"]["WordOffset"].GetValue<JSON::Real>());

        rankingWords_[3].words_ = (*pData)["3rd"]["Words"].GetValue<JSON::String>();
        rankingWords_[3].position_.x_ = static_cast<float>((*pData)["3rd"]["Position"][0].GetValue<JSON::Real>());
        rankingWords_[3].position_.y_ = static_cast<float>((*pData)["3rd"]["Position"][1].GetValue<JSON::Real>());
        rankingWords_[3].size_.x_ = static_cast<float>((*pData)["3rd"]["Size"][0].GetValue<JSON::Real>());
        rankingWords_[3].size_.y_ = static_cast<float>((*pData)["3rd"]["Size"][1].GetValue<JSON::Real>());
        rankingWords_[3].color_.red_ = static_cast<float>((*pData)["3rd"]["Color"][0].GetValue<JSON::Real>());
        rankingWords_[3].color_.green_ = static_cast<float>((*pData)["3rd"]["Color"][1].GetValue<JSON::Real>());
        rankingWords_[3].color_.blue_ = static_cast<float>((*pData)["3rd"]["Color"][2].GetValue<JSON::Real>());
        rankingWords_[3].color_.alpha_ = static_cast<float>((*pData)["3rd"]["Color"][3].GetValue<JSON::Real>());
        rankingWords_[3].wordOffset_ = static_cast<float>((*pData)["3rd"]["WordOffset"].GetValue<JSON::Real>());

        rankingWords_[4].words_ = (*pData)["4th"]["Words"].GetValue<JSON::String>();
        rankingWords_[4].position_.x_ = static_cast<float>((*pData)["4th"]["Position"][0].GetValue<JSON::Real>());
        rankingWords_[4].position_.y_ = static_cast<float>((*pData)["4th"]["Position"][1].GetValue<JSON::Real>());
        rankingWords_[4].size_.x_ = static_cast<float>((*pData)["4th"]["Size"][0].GetValue<JSON::Real>());
        rankingWords_[4].size_.y_ = static_cast<float>((*pData)["4th"]["Size"][1].GetValue<JSON::Real>());
        rankingWords_[4].color_.red_ = static_cast<float>((*pData)["4th"]["Color"][0].GetValue<JSON::Real>());
        rankingWords_[4].color_.green_ = static_cast<float>((*pData)["4th"]["Color"][1].GetValue<JSON::Real>());
        rankingWords_[4].color_.blue_ = static_cast<float>((*pData)["4th"]["Color"][2].GetValue<JSON::Real>());
        rankingWords_[4].color_.alpha_ = static_cast<float>((*pData)["4th"]["Color"][3].GetValue<JSON::Real>());
        rankingWords_[4].wordOffset_ = static_cast<float>((*pData)["4th"]["WordOffset"].GetValue<JSON::Real>());

        rankingWords_[5].words_ = (*pData)["5th"]["Words"].GetValue<JSON::String>();
        rankingWords_[5].position_.x_ = static_cast<float>((*pData)["5th"]["Position"][0].GetValue<JSON::Real>());
        rankingWords_[5].position_.y_ = static_cast<float>((*pData)["5th"]["Position"][1].GetValue<JSON::Real>());
        rankingWords_[5].size_.x_ = static_cast<float>((*pData)["5th"]["Size"][0].GetValue<JSON::Real>());
        rankingWords_[5].size_.y_ = static_cast<float>((*pData)["5th"]["Size"][1].GetValue<JSON::Real>());
        rankingWords_[5].color_.red_ = static_cast<float>((*pData)["5th"]["Color"][0].GetValue<JSON::Real>());
        rankingWords_[5].color_.green_ = static_cast<float>((*pData)["5th"]["Color"][1].GetValue<JSON::Real>());
        rankingWords_[5].color_.blue_ = static_cast<float>((*pData)["5th"]["Color"][2].GetValue<JSON::Real>());
        rankingWords_[5].color_.alpha_ = static_cast<float>((*pData)["5th"]["Color"][3].GetValue<JSON::Real>());
        rankingWords_[5].wordOffset_ = static_cast<float>((*pData)["5th"]["WordOffset"].GetValue<JSON::Real>());
    }


    /*************************************************************//**
     *
     *  @brief  ランキングデータのロード処理を行う
     *  @param  データ
     *  @return なし
     *
     ****************************************************************/
    void C_RankingUi::LoadRankingData()
    {
        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pRANKING_DATA));
        auto pRankingData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pRANKING_DATA).get();

        for (size_t i = 0; i < 5; ++i)
        {
            rankingDatas_[i].nameData_.words_ = (*pRankingData)["RankingData"][i]["Name"]["Words"].GetValue<JSON::String>();
            rankingDatas_[i].nameData_.position_.x_ = static_cast<float>((*pRankingData)["RankingData"][i]["Name"]["Position"][0].GetValue<JSON::Real>());
            rankingDatas_[i].nameData_.position_.y_ = static_cast<float>((*pRankingData)["RankingData"][i]["Name"]["Position"][1].GetValue<JSON::Real>());
            rankingDatas_[i].nameData_.size_.x_ = static_cast<float>((*pRankingData)["RankingData"][i]["Name"]["Size"][0].GetValue<JSON::Real>());
            rankingDatas_[i].nameData_.size_.y_ = static_cast<float>((*pRankingData)["RankingData"][i]["Name"]["Size"][1].GetValue<JSON::Real>());
            rankingDatas_[i].nameData_.color_.red_ = static_cast<float>((*pRankingData)["RankingData"][i]["Name"]["Color"][0].GetValue<JSON::Real>());
            rankingDatas_[i].nameData_.color_.green_ = static_cast<float>((*pRankingData)["RankingData"][i]["Name"]["Color"][1].GetValue<JSON::Real>());
            rankingDatas_[i].nameData_.color_.blue_ = static_cast<float>((*pRankingData)["RankingData"][i]["Name"]["Color"][2].GetValue<JSON::Real>());
            rankingDatas_[i].nameData_.color_.alpha_ = static_cast<float>((*pRankingData)["RankingData"][i]["Name"]["Color"][3].GetValue<JSON::Real>());
            rankingDatas_[i].nameData_.wordOffset_ = static_cast<float>((*pRankingData)["RankingData"][i]["Name"]["WordOffset"].GetValue<JSON::Real>());

            rankingDatas_[i].scoreData_.score_ = (*pRankingData)["RankingData"][i]["Score"]["Score"].GetValue<JSON::Integer>();
            rankingDatas_[i].scoreData_.scoreStringData_.words_ = std::to_string(rankingDatas_[i].scoreData_.score_);
            rankingDatas_[i].scoreData_.scoreStringData_.position_.x_ = static_cast<float>((*pRankingData)["RankingData"][i]["Score"]["Position"][0].GetValue<JSON::Real>());
            rankingDatas_[i].scoreData_.scoreStringData_.position_.y_ = static_cast<float>((*pRankingData)["RankingData"][i]["Score"]["Position"][1].GetValue<JSON::Real>());
            rankingDatas_[i].scoreData_.scoreStringData_.size_.x_ = static_cast<float>((*pRankingData)["RankingData"][i]["Score"]["Size"][0].GetValue<JSON::Real>());
            rankingDatas_[i].scoreData_.scoreStringData_.size_.y_ = static_cast<float>((*pRankingData)["RankingData"][i]["Score"]["Size"][1].GetValue<JSON::Real>());
            rankingDatas_[i].scoreData_.scoreStringData_.color_.red_ = static_cast<float>((*pRankingData)["RankingData"][i]["Score"]["Color"][0].GetValue<JSON::Real>());
            rankingDatas_[i].scoreData_.scoreStringData_.color_.green_ = static_cast<float>((*pRankingData)["RankingData"][i]["Score"]["Color"][1].GetValue<JSON::Real>());
            rankingDatas_[i].scoreData_.scoreStringData_.color_.blue_ = static_cast<float>((*pRankingData)["RankingData"][i]["Score"]["Color"][2].GetValue<JSON::Real>());
            rankingDatas_[i].scoreData_.scoreStringData_.color_.alpha_ = static_cast<float>((*pRankingData)["RankingData"][i]["Score"]["Color"][3].GetValue<JSON::Real>());
            rankingDatas_[i].scoreData_.scoreStringData_.wordOffset_ = static_cast<float>((*pRankingData)["RankingData"][i]["Score"]["WordOffset"].GetValue<JSON::Real>());
        }
    }


    /*************************************************************//**
     *
     *  @brief  ランキングデータのセーヌ処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RankingUi::SaveRankingData()
    {
        JSON::JsonObject rankingData;

        for (size_t i = 0; i < 5; ++i)
        {
            rankingData["RankingData"][i]["Name"]["Words"] = rankingDatas_[i].nameData_.words_;
            rankingData["RankingData"][i]["Name"]["Position"][0] = rankingDatas_[i].nameData_.position_.x_;
            rankingData["RankingData"][i]["Name"]["Position"][1] = rankingDatas_[i].nameData_.position_.y_;
            rankingData["RankingData"][i]["Name"]["Size"][0] = rankingDatas_[i].nameData_.size_.x_;
            rankingData["RankingData"][i]["Name"]["Size"][1] = rankingDatas_[i].nameData_.size_.y_;
            rankingData["RankingData"][i]["Name"]["Color"][0] = rankingDatas_[i].nameData_.color_.red_;
            rankingData["RankingData"][i]["Name"]["Color"][1] = rankingDatas_[i].nameData_.color_.green_;
            rankingData["RankingData"][i]["Name"]["Color"][2] = rankingDatas_[i].nameData_.color_.blue_;
            rankingData["RankingData"][i]["Name"]["Color"][3] = rankingDatas_[i].nameData_.color_.alpha_;
            rankingData["RankingData"][i]["Name"]["WordOffset"] = rankingDatas_[i].nameData_.wordOffset_;

            rankingData["RankingData"][i]["Score"]["Score"] = rankingDatas_[i].scoreData_.score_;
            rankingData["RankingData"][i]["Score"]["Position"][0] = rankingDatas_[i].scoreData_.scoreStringData_.position_.x_;
            rankingData["RankingData"][i]["Score"]["Position"][1] = rankingDatas_[i].scoreData_.scoreStringData_.position_.y_;
            rankingData["RankingData"][i]["Score"]["Size"][0] = rankingDatas_[i].scoreData_.scoreStringData_.size_.x_;
            rankingData["RankingData"][i]["Score"]["Size"][1] = rankingDatas_[i].scoreData_.scoreStringData_.size_.y_;
            rankingData["RankingData"][i]["Score"]["Color"][0] = rankingDatas_[i].scoreData_.scoreStringData_.color_.red_;
            rankingData["RankingData"][i]["Score"]["Color"][1] = rankingDatas_[i].scoreData_.scoreStringData_.color_.green_;
            rankingData["RankingData"][i]["Score"]["Color"][2] = rankingDatas_[i].scoreData_.scoreStringData_.color_.blue_;
            rankingData["RankingData"][i]["Score"]["Color"][3] = rankingDatas_[i].scoreData_.scoreStringData_.color_.alpha_;
            rankingData["RankingData"][i]["Score"]["WordOffset"] = rankingDatas_[i].scoreData_.scoreStringData_.wordOffset_;
        }

        JSON::JsonObject::s_WriteToJsonFile(rankingData, Path::JSON::s_pRANKING_DATA);
    }


    /*************************************************************//**
     *
     *  @brief  ランキング登録の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RankingUi::UpdateRankingEntry()
    {
        static const int32_t s_GAMEPAD_ENABLE_PUT_STICK = 10000;

        static auto isUpButtonFunction = [&]()
        {
            if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_UP) == 1
             || Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_CROSS_UP) == 1
             || (Input::C_GamepadManager::s_GetInstance()->GetStickYComponent(Input::C_Gamepad::STICK_LEFT) < -s_GAMEPAD_ENABLE_PUT_STICK
              && Input::C_GamepadManager::s_GetInstance()->GetStickPushingCount(Input::C_Gamepad::STICK_LEFT) == 1))
            {
                return true;
            }

            return false;
        };

        static auto isDownButtonFunction = [&]()
        {
             if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_DOWN) == 1
             || Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_CROSS_DOWN) == 1
             || (Input::C_GamepadManager::s_GetInstance()->GetStickYComponent(Input::C_Gamepad::STICK_LEFT) > s_GAMEPAD_ENABLE_PUT_STICK
              && Input::C_GamepadManager::s_GetInstance()->GetStickPushingCount(Input::C_Gamepad::STICK_LEFT) == 1))
            {
                return true;
            }

            return false;
        };

        static auto isDecisionButtonFunction = [&]()
        {
            if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_Z) == 1
             || Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_FOUR_DOWN) == 1)
            {
                return true;
            }

            return false;
        };

        static auto isUndecisionButtonFunction = [&]()
        {
            if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_X) == 1
             || Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_FOUR_RIGHT) == 1)
            {
                return true;
            }

            return false;
        };

        if (rankingEntryFlag_ == true)
        {
            if (isUpButtonFunction() == true)
            {
                --newRecordData_.newWord_;

                if (newRecordData_.newWord_ == '"') --newRecordData_.newWord_;

                if (newRecordData_.newWord_ < '!')
                {
                    newRecordData_.newWord_ = '~';
                }
            }

            if (isDownButtonFunction() == true)
            {
                ++newRecordData_.newWord_;

                if (newRecordData_.newWord_ == '"') ++newRecordData_.newWord_;

                if (newRecordData_.newWord_ > '~')
                {
                    newRecordData_.newWord_ = '!';
                }
            }

            if (isDecisionButtonFunction() == true)
            {
                newRecordData_.name_ += newRecordData_.newWord_;

                if (newRecordData_.name_.size() >= 3)
                {
                    rankingDatas_[newRecordData_.rank_].nameData_.words_ = newRecordData_.name_;
                    rankingDatas_[newRecordData_.rank_].scoreData_.score_ = newRecordData_.score_;
                    rankingDatas_[newRecordData_.rank_].scoreData_.scoreStringData_.words_ = std::to_string(newRecordData_.score_);

                    rankingEntryFlag_ = false;
                }
            }

            if (isUndecisionButtonFunction() == true)
            {
                if (newRecordData_.name_.size() > 0) newRecordData_.name_.pop_back();
            }
        }

        rankingEntryCounter_.CountUp();
    }


    /*************************************************************//**
     *
     *  @brief  ランキングの更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RankingUi::UpdateRanking()
    {
        static auto isUndecisionButtonFunction = [&]()
        {
            if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_X) == 1
             || Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_FOUR_RIGHT) == 1)
            {
                return true;
            }

            return false;
        };

        if (toTitleFlag_ == false || rankingEntryFlag_ == false)
        {
            if (isUndecisionButtonFunction() == true)
            {
                GameObject::Message::C_MessageDispatcher::s_GetInstance()->Send(ID::GameObject::s_pUI, ID::GameObject::s_pSCENE_CONTROLLER, Message::s_pTO_TITLE_SCENE);
                toTitleFlag_ = true;
            }

            if (rankingMoveCounter_.GetCount() < maxCount_) rankingMoveCounter_.CountUp();
        }
    }


    /*************************************************************//**
     *
     *  @brief  背景の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RankingUi::DrawBackground()
    {
        if (wpBackgroundSpriteCreater_.expired() == false)
        {
            auto pBackgroundSpriteCreater = wpBackgroundSpriteCreater_.lock();

            assert(Window::C_WindowManager::s_GetInstance()->GetWindow());
            auto pMainWindow = Window::C_WindowManager::s_GetInstance()->GetWindow().get();

            Sprite::S_CreateData createData;
            createData.position_.x_ = static_cast<float>(pMainWindow->GetWidth()) / 2.0f;
            createData.position_.y_ = static_cast<float>(pMainWindow->GetHeight()) / 2.0f;
            createData.size_.x_ = static_cast<float>(pMainWindow->GetWidth());
            createData.size_.y_ = static_cast<float>(pMainWindow->GetHeight());
            createData.color_.Fill(1.0f);
            createData.textureLowerRight_.x_ = static_cast<float>(pMainWindow->GetWidth());
            createData.textureLowerRight_.y_ = static_cast<float>(pMainWindow->GetHeight());

            pBackgroundSpriteCreater->Entry(createData);
        }
    }


    /*************************************************************//**
     *
     *  @brief  ランキング登録の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RankingUi::DrawRankingEntry()
    {
        if (rankingEntryFlag_ == true)
        {
            // ニューレコード文字列の描画
            if (rankingEntryCounter_.GetCount() % 40 < 25)
            {
                C_UiFont::s_GetInstance()->Draw(rankingEntryWords_[0].words_, rankingEntryWords_[0].position_, 0.0f, rankingEntryWords_[0].size_, rankingEntryWords_[0].wordOffset_);
            }

            C_UiFont::s_GetInstance()->Draw(newRecordData_.rankWords_, Vector2(330.0f, 300.0f), 0.0f, Vector2(40.0f), -10.0f);

            const float LEFT_SIDE_POSITION = -250.0f;
            Vector2 scorePosition = Vector2(470.0f, 300.0f);
            std::string scoreString = std::to_string(newRecordData_.score_);

            // 10桁にそろえるように位置を調節
            scorePosition.x_ += (10.0f - scoreString.size()) * (40.0f - 10.0f);
            C_UiFont::s_GetInstance()->Draw(scoreString, scorePosition, 0.0f, Vector2(40.0f), -10.0f);

            C_UiFont::s_GetInstance()->Draw(newRecordData_.name_, Vector2(420.0f, 450.0f), 0.0f, Vector2(65.0f), 35.0f);

            std::string newWord;
            newWord += newRecordData_.newWord_;
            C_UiFont::s_GetInstance()->Draw(newWord, Vector2(420.0f + static_cast<float>(newRecordData_.name_.size()) * 100.0f, 450.0f), 0.0f, Vector2(65.0f), 35.0f);

            C_UiFont::s_GetInstance()->DrawArrow(Vector2(420.0f + static_cast<float>(newRecordData_.name_.size()) * 100.0f, 375.0f), static_cast<float>(-Math::s_PI_DIVISION2), Vector2(30.0f));
            C_UiFont::s_GetInstance()->DrawArrow(Vector2(420.0f + static_cast<float>(newRecordData_.name_.size()) * 100.0f, 525.0f), static_cast<float>(Math::s_PI_DIVISION2), Vector2(30.0f));
        }
    }


    /*************************************************************//**
     *
     *  @brief  ランキングの描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_RankingUi::DrawRanking()
    {
        // ランキング文字列の描画
        C_UiFont::s_GetInstance()->Draw(rankingWords_[0].words_, rankingWords_[0].position_, 0.0f, rankingWords_[0].size_, rankingWords_[0].wordOffset_);

        if (rankingEntryFlag_ == false)
        {
            const float LEFT_SIDE_POSITION = -250.0f;
            float lerpCoeffcient = static_cast<float>(rankingMoveCounter_.GetCount()) / static_cast<float>(maxCount_);

            for (size_t i = 1; i < 6; ++i)
            {
                C_UiFont::s_GetInstance()->Draw(rankingWords_[i].words_, Vector2::s_Lerp(Vector2(LEFT_SIDE_POSITION, rankingWords_[i].position_.y_), rankingWords_[i].position_, lerpCoeffcient), 0.0f, rankingWords_[i].size_, rankingWords_[i].wordOffset_);
            }

            for (size_t i = 0; i < 5; ++i)
            {
                Vector2 scorePosition = Vector2::s_Lerp(Vector2(LEFT_SIDE_POSITION, rankingDatas_[i].scoreData_.scoreStringData_.position_.y_), rankingDatas_[i].scoreData_.scoreStringData_.position_, lerpCoeffcient);
                
                // 10桁にそろえるように位置を調節
                scorePosition.x_ += (10.0f - static_cast<float>(rankingDatas_[i].scoreData_.scoreStringData_.words_.size())) * (rankingDatas_[i].scoreData_.scoreStringData_.size_.x_ + rankingDatas_[i].scoreData_.scoreStringData_.wordOffset_);

                C_UiFont::s_GetInstance()->Draw(rankingDatas_[i].scoreData_.scoreStringData_.words_,
                                                scorePosition,
                                                0.0f,
                                                rankingDatas_[i].scoreData_.scoreStringData_.size_,
                                                rankingDatas_[i].scoreData_.scoreStringData_.wordOffset_);

                C_UiFont::s_GetInstance()->Draw(rankingDatas_[i].nameData_.words_, 
                                                Vector2::s_Lerp(Vector2(LEFT_SIDE_POSITION, rankingDatas_[i].nameData_.position_.y_), rankingDatas_[i].nameData_.position_, lerpCoeffcient), 
                                                0.0f, 
                                                rankingDatas_[i].nameData_.size_, 
                                                rankingDatas_[i].nameData_.wordOffset_);
            }
        }
    }
}