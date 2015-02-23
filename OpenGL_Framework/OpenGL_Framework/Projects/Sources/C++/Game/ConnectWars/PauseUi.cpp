/* ヘッダファイル */
#include "PauseUi.h"
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
    /** 項目 */
    enum eItem
    {
        RESUME,
        RESTART,
        TITLE,
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ID
     *  @param  種類
     *
     ****************************************************************/
    C_PauseUi::C_PauseUi(const std::string& rId, int32_t type) : C_BaseUi(rId, type)
    {
        assert(Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pPAUSE_BACKGROUND));
        wpBackgroundSpriteCreater_ = Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pPAUSE_BACKGROUND).get();

        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pPAUSE_UI_DATA));
        auto pPauseUiData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pPAUSE_UI_DATA).get();

        LoadUiWords(&(*pPauseUiData)["PauseUiData"]);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PauseUi::~C_PauseUi()
    {
    }


    /*************************************************************//**
     *
     *  @brief  非公開の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PauseUi::DoUpdate()
    {
        UpdateUiWords();
    }


    /*************************************************************//**
     *
     *  @brief  非公開の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PauseUi::DoDraw()
    {
        DrawBackground();
        DrawUiWords();
    }


    /*************************************************************//**
     *
     *  @brief  非公開のメッセージ処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    bool C_PauseUi::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }


    /*************************************************************//**
     *
     *  @brief  UI文字列のロード処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PauseUi::LoadUiWords(JSON::JsonObject* pData)
    {
        uiWords_[0].words_ = (*pData)["Resume"]["Words"].GetValue<JSON::String>();
        uiWords_[0].position_.x_ = static_cast<float>((*pData)["Resume"]["Position"][0].GetValue<JSON::Real>());
        uiWords_[0].position_.y_ = static_cast<float>((*pData)["Resume"]["Position"][1].GetValue<JSON::Real>());
        uiWords_[0].size_.x_ = static_cast<float>((*pData)["Resume"]["Size"][0].GetValue<JSON::Real>());
        uiWords_[0].size_.y_ = static_cast<float>((*pData)["Resume"]["Size"][1].GetValue<JSON::Real>());
        uiWords_[0].color_.red_ = static_cast<float>((*pData)["Resume"]["Color"][0].GetValue<JSON::Real>());
        uiWords_[0].color_.green_ = static_cast<float>((*pData)["Resume"]["Color"][1].GetValue<JSON::Real>());
        uiWords_[0].color_.blue_ = static_cast<float>((*pData)["Resume"]["Color"][2].GetValue<JSON::Real>());
        uiWords_[0].color_.alpha_ = static_cast<float>((*pData)["Resume"]["Color"][3].GetValue<JSON::Real>());
        uiWords_[0].wordOffset_ = static_cast<float>((*pData)["Resume"]["WordOffset"].GetValue<JSON::Real>());
    
        uiWords_[1].words_ = (*pData)["Restart"]["Words"].GetValue<JSON::String>();
        uiWords_[1].position_.x_ = static_cast<float>((*pData)["Restart"]["Position"][0].GetValue<JSON::Real>());
        uiWords_[1].position_.y_ = static_cast<float>((*pData)["Restart"]["Position"][1].GetValue<JSON::Real>());
        uiWords_[1].size_.x_ = static_cast<float>((*pData)["Restart"]["Size"][0].GetValue<JSON::Real>());
        uiWords_[1].size_.y_ = static_cast<float>((*pData)["Restart"]["Size"][1].GetValue<JSON::Real>());
        uiWords_[1].color_.red_ = static_cast<float>((*pData)["Restart"]["Color"][0].GetValue<JSON::Real>());
        uiWords_[1].color_.green_ = static_cast<float>((*pData)["Restart"]["Color"][1].GetValue<JSON::Real>());
        uiWords_[1].color_.blue_ = static_cast<float>((*pData)["Restart"]["Color"][2].GetValue<JSON::Real>());
        uiWords_[1].color_.alpha_ = static_cast<float>((*pData)["Restart"]["Color"][3].GetValue<JSON::Real>());
        uiWords_[1].wordOffset_ = static_cast<float>((*pData)["Restart"]["WordOffset"].GetValue<JSON::Real>());

        uiWords_[2].words_ = (*pData)["Title"]["Words"].GetValue<JSON::String>();
        uiWords_[2].position_.x_ = static_cast<float>((*pData)["Title"]["Position"][0].GetValue<JSON::Real>());
        uiWords_[2].position_.y_ = static_cast<float>((*pData)["Title"]["Position"][1].GetValue<JSON::Real>());
        uiWords_[2].size_.x_ = static_cast<float>((*pData)["Title"]["Size"][0].GetValue<JSON::Real>());
        uiWords_[2].size_.y_ = static_cast<float>((*pData)["Title"]["Size"][1].GetValue<JSON::Real>());
        uiWords_[2].color_.red_ = static_cast<float>((*pData)["Title"]["Color"][0].GetValue<JSON::Real>());
        uiWords_[2].color_.green_ = static_cast<float>((*pData)["Title"]["Color"][1].GetValue<JSON::Real>());
        uiWords_[2].color_.blue_ = static_cast<float>((*pData)["Title"]["Color"][2].GetValue<JSON::Real>());
        uiWords_[2].color_.alpha_ = static_cast<float>((*pData)["Title"]["Color"][3].GetValue<JSON::Real>());
        uiWords_[2].wordOffset_ = static_cast<float>((*pData)["Title"]["WordOffset"].GetValue<JSON::Real>());
    }


    /*************************************************************//**
     *
     *  @brief  UI文字列の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PauseUi::UpdateUiWords()
    {
        static const int32_t s_GAMEPAD_ENABLE_PUT_STICK = 10000;

        // 各ボタン入力の取得関数
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

        static auto isPauseButtonFunction = [&]()
        {
            if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_C) == 1
             || Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_START) == 1)
            {
                return true;
            }

            return false;
        };

        if (backgoundSizeFactor_.GetCount() < maxSizeCount_)
        {
            backgoundSizeFactor_.CountUp();
        }
        else
        {
            if (isUpButtonFunction() == true)
            {
                uiWordIndex_ += 2;
                uiWordIndex_ %= 3;
            }

            if (isDownButtonFunction() == true)
            {
                ++uiWordIndex_;
                uiWordIndex_ %= 3;
            }

            if (isDecisionButtonFunction() == true)
            {
                switch (uiWordIndex_)
                {
                case RESUME:

                    GameObject::Message::C_MessageDispatcher::s_GetInstance()->Send(ID::GameObject::s_pPAUSE_UI, ID::GameObject::s_pPAUSE_CONTROLLER, Message::s_pRESUME_GAME);
                    updateLockFlag_ = true;
                    
                    break;
                case RESTART:

                    GameObject::Message::C_MessageDispatcher::s_GetInstance()->Send(ID::GameObject::s_pPAUSE_UI, ID::GameObject::s_pPAUSE_CONTROLLER, Message::s_pRESTART_GAME);
                    updateLockFlag_ = true;

                    break;
                case TITLE:

                    GameObject::Message::C_MessageDispatcher::s_GetInstance()->Send(ID::GameObject::s_pPAUSE_UI, ID::GameObject::s_pPAUSE_CONTROLLER, Message::s_pTO_TITLE_SCENE);
                    updateLockFlag_ = true;

                    break;
                }


                updateLockFlag_ = true;
            }
            else if (isPauseButtonFunction() == true)
            {
                GameObject::Message::C_MessageDispatcher::s_GetInstance()->Send(ID::GameObject::s_pPAUSE_UI, ID::GameObject::s_pPAUSE_CONTROLLER, Message::s_pRESUME_GAME);
                updateLockFlag_ = true;
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  背景の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PauseUi::DrawBackground()
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
            createData.size_.y_ = 300.0f * static_cast<float>(backgoundSizeFactor_.GetCount()) / static_cast<float>(maxSizeCount_);
            createData.color_.Fill(1.0f);
            createData.textureLowerRight_.x_ = static_cast<float>(pMainWindow->GetWidth());
            createData.textureLowerRight_.y_ = 300.0f;

            pBackgroundSpriteCreater->Entry(createData);
        }
    }


    /*************************************************************//**
     *
     *  @brief  UI文字列の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PauseUi::DrawUiWords()
    {
        if (backgoundSizeFactor_.GetCount() >= maxSizeCount_)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                C_UiFont::s_GetInstance()->Draw(uiWords_[i].words_, uiWords_[i].position_, 0.0f, uiWords_[i].size_, uiWords_[i].wordOffset_);
            }

            C_UiFont::s_GetInstance()->DrawArrow(uiWords_[uiWordIndex_].position_ + Vector2(-60.0f, 0.0f), 0.0f, uiWords_[uiWordIndex_].size_);
        }
    }
}