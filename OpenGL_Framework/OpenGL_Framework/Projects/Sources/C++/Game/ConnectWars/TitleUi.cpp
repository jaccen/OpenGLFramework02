/* ヘッダファイル */
#include "TitleUi.h"
#include "UiFont.h"
#include "../../Library/Input/Keyboard/KeyboardManager.h"
#include "../../Library/Input/Gamepad/Manager/GamepadManager.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/GameObject/Message/Dispatcher/MessageDispatcher.h"
#include "../../Library/Window/Manager/WindowManager.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /** 初期項目 */
    enum eInitialItem
    {
        START,
        RANKING,
        CONFIG,
    };


    /** ステージ項目 */
    enum eStageItem
    {
        STAGE_01,
        STAGE_02,
        STAGE_03,
    };


    /** コンフィグ項目 */
    enum eConfigItem
    {
        PLAYER_LIFE,
        SOUND_SE,
        SOUND_BGM,
        BUTTOM_SHOT,
        BUTTON_BOMB,
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ID
     *  @param  種類
     *
     ****************************************************************/
    C_TitleUi::C_TitleUi(const std::string& rId, int32_t type) : C_BaseUi(rId, type)
    {
        assert(Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pTITLE_UI));
        assert(Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pTITLE_BACKGROUND));
        wpUiSpriteCreater_ = Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pTITLE_UI).get();
        wpBackgroundSpriteCreater_ = Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pTITLE_BACKGROUND).get();

        // 各データをロード
        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pTITLE_UI_DATA));
        auto pTitleUiData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pTITLE_UI_DATA).get();

        LoadImageUis(&(*pTitleUiData)["TitleUiData"]);
        LoadInitialItems(&(*pTitleUiData)["TitleUiData"]);
        LoadStaeSelectItems(&(*pTitleUiData)["TitleUiData"]);
        LoadConfigItems(&(*pTitleUiData)["TitleUiData"]);
        LoadConfigData();
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_TitleUi::~C_TitleUi()
    {
        SaveConfigData();
    }


    /*************************************************************//**
     *
     *  @brief  非公開の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TitleUi::DoUpdate()
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

        static auto isRightButtonFunction = [&]()
        {
            if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_RIGHT) == 1
             || Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_CROSS_RIGHT) == 1
             || (Input::C_GamepadManager::s_GetInstance()->GetStickYComponent(Input::C_Gamepad::STICK_RIGHT) > s_GAMEPAD_ENABLE_PUT_STICK
              && Input::C_GamepadManager::s_GetInstance()->GetStickPushingCount(Input::C_Gamepad::STICK_RIGHT) == 1))
            {
                return true;
            }

            return false;
        };

        static auto isLeftButtonFunction = [&]()
        {
            if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_LEFT) == 1
             || Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_CROSS_LEFT) == 1
             || (Input::C_GamepadManager::s_GetInstance()->GetStickYComponent(Input::C_Gamepad::STICK_LEFT) < -s_GAMEPAD_ENABLE_PUT_STICK
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

        static auto getDownButton = [&]()->int32_t
        {
            if (Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_FOUR_DOWN) == 1)
            {
                return Input::C_Gamepad::BUTTON_FOUR_DOWN;
            }
            else if (Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_FOUR_UP) == 1)
            {
                return Input::C_Gamepad::BUTTON_FOUR_UP;
            }
            else if (Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_FOUR_RIGHT) == 1)
            {
                return Input::C_Gamepad::BUTTON_FOUR_RIGHT;
            }
            else if (Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_FOUR_LEFT) == 1)
            {
                return Input::C_Gamepad::BUTTON_FOUR_LEFT;
            }
            else if (Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_SELECT) == 1)
            {
                return Input::C_Gamepad::BUTTON_SELECT;
            }
            else if (Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_START) == 1)
            {
                return Input::C_Gamepad::BUTTON_START;
            }
            else if (Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_SHOULDER_1_RIGHT) == 1)
            {
                return Input::C_Gamepad::BUTTON_SHOULDER_1_RIGHT;
            }
            else if (Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_SHOULDER_1_LEFT) == 1)
            {
                return Input::C_Gamepad::BUTTON_SHOULDER_1_LEFT;
            }
            else if (Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_SHOULDER_2_RIGHT) == 1)
            {
                return Input::C_Gamepad::BUTTON_SHOULDER_2_RIGHT;
            }
            else if (Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(Input::C_Gamepad::BUTTON_SHOULDER_2_LEFT) == 1)
            {
                return Input::C_Gamepad::BUTTON_SHOULDER_2_LEFT;
            }

            return -1;
        };


        // 初期項目の選択中
        if (drawStageSelectItemFlag_ == false && drawConfigItemFlag_ == false)
        {
            if (isUpButtonFunction() == true)
            {
                initialItemNumber_ += 2;
                initialItemNumber_ %= 3;
            }
            if (isDownButtonFunction() == true)
            {
                ++initialItemNumber_;
                initialItemNumber_ %= 3;
            }

            if (isDecisionButtonFunction() == true)
            {
                switch (initialItemNumber_)
                {
                case START:

                    drawStageSelectItemFlag_ = true;
                    stageSelectItemNumber_ = 0;

                    break;
                case RANKING:

                    GameObject::Message::C_MessageDispatcher::s_GetInstance()->Send(ID::GameObject::s_pUI, ID::GameObject::s_pSCENE_CONTROLLER, Message::s_pTO_RANKING_SCENE);
                    updateLockFlag_ = true;

                    break;
                case CONFIG:

                    drawConfigItemFlag_ = true;
                    configItemNumber_ = 0;

                    break;
                default:

                    StrongAssert(false && "[ C_TitleUi::DoUpdate ] : 項目外です。");

                    break;
                }
            }
        }
        else
        {
            // ステージセレクト項目の選択中
            if (drawStageSelectItemFlag_ == true)
            {
                if (isUpButtonFunction() == true)
                {
                    stageSelectItemNumber_ += 2;
                    stageSelectItemNumber_ %= 3;
                }
                else if (isDownButtonFunction() == true)
                {
                    ++stageSelectItemNumber_;
                    stageSelectItemNumber_ %= 3;
                }
                else if (isDecisionButtonFunction() == true)
                {
                    switch (stageSelectItemNumber_)
                    {
                    case STAGE_01:

                        GameObject::Message::C_MessageDispatcher::s_GetInstance()->Send(ID::GameObject::s_pUI, ID::GameObject::s_pSCENE_CONTROLLER, Message::s_pTO_GAME_01_SCENE);
                        updateLockFlag_ = true;

                        break;
                    case STAGE_02:
                        
                        GameObject::Message::C_MessageDispatcher::s_GetInstance()->Send(ID::GameObject::s_pUI, ID::GameObject::s_pSCENE_CONTROLLER, Message::s_pTO_GAME_02_SCENE);
                        updateLockFlag_ = true;
                        
                        break;
                    case STAGE_03:
                        
                        GameObject::Message::C_MessageDispatcher::s_GetInstance()->Send(ID::GameObject::s_pUI, ID::GameObject::s_pSCENE_CONTROLLER, Message::s_pTO_GAME_03_SCENE);
                        updateLockFlag_ = true;

                        break;
                    }
                }
                else if (isUndecisionButtonFunction() == true)
                {
                    drawStageSelectItemFlag_ = false;
                }
            }
            // コンフィグ項目の選択中
            else
            {
                if (isUpButtonFunction() == true)
                {
                    configItemNumber_ += 4;
                    configItemNumber_ %= 5;
                }
                else if (isDownButtonFunction() == true)
                {
                    ++configItemNumber_;
                    configItemNumber_ %= 5;
                }
                else if (isRightButtonFunction() == true)
                {
                    switch (configItemNumber_)
                    {
                    case PLAYER_LIFE:

                        ++configData_.playerLife_;
                        if (configData_.playerLife_ > 5) configData_.playerLife_ = 5;

                        break;
                    case SOUND_SE:

                        ++configData_.SE_;
                        if (configData_.SE_ > 5) configData_.SE_ = 5;
                        
                        break;
                    case SOUND_BGM:

                        ++configData_.BGM_;
                        if (configData_.BGM_ > 5) configData_.BGM_ = 5;

                        break;
                    }
                }
                else if (isLeftButtonFunction() == true)
                {
                    switch (configItemNumber_)
                    {
                    case PLAYER_LIFE:

                        --configData_.playerLife_;
                        if (configData_.playerLife_ < 1) configData_.playerLife_ = 1;

                        break;
                    case SOUND_SE:

                        --configData_.SE_;
                        if (configData_.SE_ < 1) configData_.SE_ = 1;
                        
                        break;
                    case SOUND_BGM:

                        --configData_.BGM_;
                        if (configData_.BGM_ < 1) configData_.BGM_ = 1;

                        break;
                    }
                }
                else if (getDownButton() != -1)
                {
                    switch (configItemNumber_)
                    {
                    case BUTTOM_SHOT:

                        configData_.shotButton_ = getDownButton();
                        
                        break;
                    case BUTTON_BOMB:

                        configData_.bombButton_ = getDownButton();
                        
                        break;
                    default:

                        if (getDownButton() == Input::C_Gamepad::BUTTON_FOUR_RIGHT)
                        {
                            drawConfigItemFlag_ = false;
                        }
                        
                        break;
                    }
                }
                else if (Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(Input::KeyCode::SDL_SCANCODE_X) == 1)
                {
                    drawConfigItemFlag_ = false;
                }
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  非公開の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TitleUi::DoDraw()
    {
        DrawImageUiAndBackground();
        DrawInitialItems();
        DrawStageSelectItems();
        DrawConfigItems();
    }


    /*************************************************************//**
     *
     *  @brief  非公開のメッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_TitleUi::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }


    /*************************************************************//**
     *
     *  @brief  画像UIのロード処理を行う
     *  @param  データ
     *  @return なし
     *
     ****************************************************************/
    void C_TitleUi::LoadImageUis(JSON::JsonObject* pData)
    {
        imageUis_[0].position_.x_ = static_cast<float>((*pData)["Logo"]["Position"][0].GetValue<JSON::Real>());
        imageUis_[0].position_.y_ = static_cast<float>((*pData)["Logo"]["Position"][1].GetValue<JSON::Real>());
        imageUis_[0].size_.x_ = static_cast<float>((*pData)["Logo"]["Size"][0].GetValue<JSON::Real>());
        imageUis_[0].size_.y_ = static_cast<float>((*pData)["Logo"]["Size"][1].GetValue<JSON::Real>());
        imageUis_[0].color_.red_ = static_cast<float>((*pData)["Logo"]["Color"][0].GetValue<JSON::Real>());
        imageUis_[0].color_.green_ = static_cast<float>((*pData)["Logo"]["Color"][1].GetValue<JSON::Real>());
        imageUis_[0].color_.blue_ = static_cast<float>((*pData)["Logo"]["Color"][2].GetValue<JSON::Real>());
        imageUis_[0].color_.alpha_ = static_cast<float>((*pData)["Logo"]["Color"][3].GetValue<JSON::Real>());
        imageUis_[0].textureUpperLeft_.x_ = static_cast<float>((*pData)["Logo"]["TextureUpperLeft"][0].GetValue<JSON::Real>());
        imageUis_[0].textureUpperLeft_.y_ = static_cast<float>((*pData)["Logo"]["TextureUpperLeft"][1].GetValue<JSON::Real>());
        imageUis_[0].textureLowerRight_.x_ = static_cast<float>((*pData)["Logo"]["TextureLowerRight"][0].GetValue<JSON::Real>());
        imageUis_[0].textureLowerRight_.y_ = static_cast<float>((*pData)["Logo"]["TextureLowerRight"][1].GetValue<JSON::Real>());

        imageUis_[1].position_.x_ = static_cast<float>((*pData)["Sheet"]["Position"][0].GetValue<JSON::Real>());
        imageUis_[1].position_.y_ = static_cast<float>((*pData)["Sheet"]["Position"][1].GetValue<JSON::Real>());
        imageUis_[1].size_.x_ = static_cast<float>((*pData)["Sheet"]["Size"][0].GetValue<JSON::Real>());
        imageUis_[1].size_.y_ = static_cast<float>((*pData)["Sheet"]["Size"][1].GetValue<JSON::Real>());
        imageUis_[1].color_.red_ = static_cast<float>((*pData)["Sheet"]["Color"][0].GetValue<JSON::Real>());
        imageUis_[1].color_.green_ = static_cast<float>((*pData)["Sheet"]["Color"][1].GetValue<JSON::Real>());
        imageUis_[1].color_.blue_ = static_cast<float>((*pData)["Sheet"]["Color"][2].GetValue<JSON::Real>());
        imageUis_[1].color_.alpha_ = static_cast<float>((*pData)["Sheet"]["Color"][3].GetValue<JSON::Real>());
        imageUis_[1].textureUpperLeft_.x_ = static_cast<float>((*pData)["Sheet"]["TextureUpperLeft"][0].GetValue<JSON::Real>());
        imageUis_[1].textureUpperLeft_.y_ = static_cast<float>((*pData)["Sheet"]["TextureUpperLeft"][1].GetValue<JSON::Real>());
        imageUis_[1].textureLowerRight_.x_ = static_cast<float>((*pData)["Sheet"]["TextureLowerRight"][0].GetValue<JSON::Real>());
        imageUis_[1].textureLowerRight_.y_ = static_cast<float>((*pData)["Sheet"]["TextureLowerRight"][1].GetValue<JSON::Real>());
    }


    /*************************************************************//**
     *
     *  @brief  初期項目のロード処理を行う
     *  @param  データ
     *  @return なし
     *
     ****************************************************************/
    void C_TitleUi::LoadInitialItems(JSON::JsonObject* pData)
    {
        initialItems_[0].words_ = (*pData)["Start"]["Words"].GetValue<JSON::String>();
        initialItems_[0].position_.x_ = static_cast<float>((*pData)["Start"]["Position"][0].GetValue<JSON::Real>());
        initialItems_[0].position_.y_ = static_cast<float>((*pData)["Start"]["Position"][1].GetValue<JSON::Real>());
        initialItems_[0].size_.x_ = static_cast<float>((*pData)["Start"]["Size"][0].GetValue<JSON::Real>());
        initialItems_[0].size_.y_ = static_cast<float>((*pData)["Start"]["Size"][1].GetValue<JSON::Real>());
        initialItems_[0].color_.red_ = static_cast<float>((*pData)["Start"]["Color"][0].GetValue<JSON::Real>());
        initialItems_[0].color_.green_ = static_cast<float>((*pData)["Start"]["Color"][1].GetValue<JSON::Real>());
        initialItems_[0].color_.blue_ = static_cast<float>((*pData)["Start"]["Color"][2].GetValue<JSON::Real>());
        initialItems_[0].color_.alpha_ = static_cast<float>((*pData)["Start"]["Color"][3].GetValue<JSON::Real>());
        initialItems_[0].wordOffset_ = static_cast<float>((*pData)["Start"]["WordOffset"].GetValue<JSON::Real>());

        initialItems_[1].words_ = (*pData)["Ranking"]["Words"].GetValue<JSON::String>();
        initialItems_[1].position_.x_ = static_cast<float>((*pData)["Ranking"]["Position"][0].GetValue<JSON::Real>());
        initialItems_[1].position_.y_ = static_cast<float>((*pData)["Ranking"]["Position"][1].GetValue<JSON::Real>());
        initialItems_[1].size_.x_ = static_cast<float>((*pData)["Ranking"]["Size"][0].GetValue<JSON::Real>());
        initialItems_[1].size_.y_ = static_cast<float>((*pData)["Ranking"]["Size"][1].GetValue<JSON::Real>());
        initialItems_[1].color_.red_ = static_cast<float>((*pData)["Ranking"]["Color"][0].GetValue<JSON::Real>());
        initialItems_[1].color_.green_ = static_cast<float>((*pData)["Ranking"]["Color"][1].GetValue<JSON::Real>());
        initialItems_[1].color_.blue_ = static_cast<float>((*pData)["Ranking"]["Color"][2].GetValue<JSON::Real>());
        initialItems_[1].color_.alpha_ = static_cast<float>((*pData)["Ranking"]["Color"][3].GetValue<JSON::Real>());
        initialItems_[1].wordOffset_ = static_cast<float>((*pData)["Ranking"]["WordOffset"].GetValue<JSON::Real>());

        initialItems_[2].words_ = (*pData)["Config"]["Words"].GetValue<JSON::String>();
        initialItems_[2].position_.x_ = static_cast<float>((*pData)["Config"]["Position"][0].GetValue<JSON::Real>());
        initialItems_[2].position_.y_ = static_cast<float>((*pData)["Config"]["Position"][1].GetValue<JSON::Real>());
        initialItems_[2].size_.x_ = static_cast<float>((*pData)["Config"]["Size"][0].GetValue<JSON::Real>());
        initialItems_[2].size_.y_ = static_cast<float>((*pData)["Config"]["Size"][1].GetValue<JSON::Real>());
        initialItems_[2].color_.red_ = static_cast<float>((*pData)["Config"]["Color"][0].GetValue<JSON::Real>());
        initialItems_[2].color_.green_ = static_cast<float>((*pData)["Config"]["Color"][1].GetValue<JSON::Real>());
        initialItems_[2].color_.blue_ = static_cast<float>((*pData)["Config"]["Color"][2].GetValue<JSON::Real>());
        initialItems_[2].color_.alpha_ = static_cast<float>((*pData)["Config"]["Color"][3].GetValue<JSON::Real>());
        initialItems_[2].wordOffset_ = static_cast<float>((*pData)["Config"]["WordOffset"].GetValue<JSON::Real>());
    }


    /*************************************************************//**
     *
     *  @brief  ステージセレクト項目のロード処理を行う
     *  @param  データ
     *  @return なし
     *
     ****************************************************************/
    void C_TitleUi::LoadStaeSelectItems(JSON::JsonObject* pData)
    {
        stageSelectItems_[0].words_ = (*pData)["StageSelect"]["Words"].GetValue<JSON::String>();
        stageSelectItems_[0].position_.x_ = static_cast<float>((*pData)["StageSelect"]["Position"][0].GetValue<JSON::Real>());
        stageSelectItems_[0].position_.y_ = static_cast<float>((*pData)["StageSelect"]["Position"][1].GetValue<JSON::Real>());
        stageSelectItems_[0].size_.x_ = static_cast<float>((*pData)["StageSelect"]["Size"][0].GetValue<JSON::Real>());
        stageSelectItems_[0].size_.y_ = static_cast<float>((*pData)["StageSelect"]["Size"][1].GetValue<JSON::Real>());
        stageSelectItems_[0].color_.red_ = static_cast<float>((*pData)["StageSelect"]["Color"][0].GetValue<JSON::Real>());
        stageSelectItems_[0].color_.green_ = static_cast<float>((*pData)["StageSelect"]["Color"][1].GetValue<JSON::Real>());
        stageSelectItems_[0].color_.blue_ = static_cast<float>((*pData)["StageSelect"]["Color"][2].GetValue<JSON::Real>());
        stageSelectItems_[0].color_.alpha_ = static_cast<float>((*pData)["StageSelect"]["Color"][3].GetValue<JSON::Real>());
        stageSelectItems_[0].wordOffset_ = static_cast<float>((*pData)["StageSelect"]["WordOffset"].GetValue<JSON::Real>());

        stageSelectItems_[1].words_ = (*pData)["Stage01"]["Words"].GetValue<JSON::String>();
        stageSelectItems_[1].position_.x_ = static_cast<float>((*pData)["Stage01"]["Position"][0].GetValue<JSON::Real>());
        stageSelectItems_[1].position_.y_ = static_cast<float>((*pData)["Stage01"]["Position"][1].GetValue<JSON::Real>());
        stageSelectItems_[1].size_.x_ = static_cast<float>((*pData)["Stage01"]["Size"][0].GetValue<JSON::Real>());
        stageSelectItems_[1].size_.y_ = static_cast<float>((*pData)["Stage01"]["Size"][1].GetValue<JSON::Real>());
        stageSelectItems_[1].color_.red_ = static_cast<float>((*pData)["Stage01"]["Color"][0].GetValue<JSON::Real>());
        stageSelectItems_[1].color_.green_ = static_cast<float>((*pData)["Stage01"]["Color"][1].GetValue<JSON::Real>());
        stageSelectItems_[1].color_.blue_ = static_cast<float>((*pData)["Stage01"]["Color"][2].GetValue<JSON::Real>());
        stageSelectItems_[1].color_.alpha_ = static_cast<float>((*pData)["Stage01"]["Color"][3].GetValue<JSON::Real>());
        stageSelectItems_[1].wordOffset_ = static_cast<float>((*pData)["Stage01"]["WordOffset"].GetValue<JSON::Real>());

        stageSelectItems_[2].words_ = (*pData)["Stage02"]["Words"].GetValue<JSON::String>();
        stageSelectItems_[2].position_.x_ = static_cast<float>((*pData)["Stage02"]["Position"][0].GetValue<JSON::Real>());
        stageSelectItems_[2].position_.y_ = static_cast<float>((*pData)["Stage02"]["Position"][1].GetValue<JSON::Real>());
        stageSelectItems_[2].size_.x_ = static_cast<float>((*pData)["Stage02"]["Size"][0].GetValue<JSON::Real>());
        stageSelectItems_[2].size_.y_ = static_cast<float>((*pData)["Stage02"]["Size"][1].GetValue<JSON::Real>());
        stageSelectItems_[2].color_.red_ = static_cast<float>((*pData)["Stage02"]["Color"][0].GetValue<JSON::Real>());
        stageSelectItems_[2].color_.green_ = static_cast<float>((*pData)["Stage02"]["Color"][1].GetValue<JSON::Real>());
        stageSelectItems_[2].color_.blue_ = static_cast<float>((*pData)["Stage02"]["Color"][2].GetValue<JSON::Real>());
        stageSelectItems_[2].color_.alpha_ = static_cast<float>((*pData)["Stage02"]["Color"][3].GetValue<JSON::Real>());
        stageSelectItems_[2].wordOffset_ = static_cast<float>((*pData)["Stage02"]["WordOffset"].GetValue<JSON::Real>());

        stageSelectItems_[3].words_ = (*pData)["Stage03"]["Words"].GetValue<JSON::String>();
        stageSelectItems_[3].position_.x_ = static_cast<float>((*pData)["Stage03"]["Position"][0].GetValue<JSON::Real>());
        stageSelectItems_[3].position_.y_ = static_cast<float>((*pData)["Stage03"]["Position"][1].GetValue<JSON::Real>());
        stageSelectItems_[3].size_.x_ = static_cast<float>((*pData)["Stage03"]["Size"][0].GetValue<JSON::Real>());
        stageSelectItems_[3].size_.y_ = static_cast<float>((*pData)["Stage03"]["Size"][1].GetValue<JSON::Real>());
        stageSelectItems_[3].color_.red_ = static_cast<float>((*pData)["Stage03"]["Color"][0].GetValue<JSON::Real>());
        stageSelectItems_[3].color_.green_ = static_cast<float>((*pData)["Stage03"]["Color"][1].GetValue<JSON::Real>());
        stageSelectItems_[3].color_.blue_ = static_cast<float>((*pData)["Stage03"]["Color"][2].GetValue<JSON::Real>());
        stageSelectItems_[3].color_.alpha_ = static_cast<float>((*pData)["Stage03"]["Color"][3].GetValue<JSON::Real>());
        stageSelectItems_[3].wordOffset_ = static_cast<float>((*pData)["Stage03"]["WordOffset"].GetValue<JSON::Real>());
    }


    /*************************************************************//**
     *
     *  @brief  コンフィグ項目のロード処理を行う
     *  @param  データ
     *  @return なし
     *
     ****************************************************************/
    void C_TitleUi::LoadConfigItems(JSON::JsonObject* pData)
    {
        configItems_[0].words_ = (*pData)["PlayerLife"]["Words"].GetValue<JSON::String>();
        configItems_[0].position_.x_ = static_cast<float>((*pData)["PlayerLife"]["Position"][0].GetValue<JSON::Real>());
        configItems_[0].position_.y_ = static_cast<float>((*pData)["PlayerLife"]["Position"][1].GetValue<JSON::Real>());
        configItems_[0].size_.x_ = static_cast<float>((*pData)["PlayerLife"]["Size"][0].GetValue<JSON::Real>());
        configItems_[0].size_.y_ = static_cast<float>((*pData)["PlayerLife"]["Size"][1].GetValue<JSON::Real>());
        configItems_[0].color_.red_ = static_cast<float>((*pData)["PlayerLife"]["Color"][0].GetValue<JSON::Real>());
        configItems_[0].color_.green_ = static_cast<float>((*pData)["PlayerLife"]["Color"][1].GetValue<JSON::Real>());
        configItems_[0].color_.blue_ = static_cast<float>((*pData)["PlayerLife"]["Color"][2].GetValue<JSON::Real>());
        configItems_[0].color_.alpha_ = static_cast<float>((*pData)["PlayerLife"]["Color"][3].GetValue<JSON::Real>());
        configItems_[0].wordOffset_ = static_cast<float>((*pData)["PlayerLife"]["WordOffset"].GetValue<JSON::Real>());

        configItems_[1].words_ = (*pData)["Sound"]["Words"].GetValue<JSON::String>();
        configItems_[1].position_.x_ = static_cast<float>((*pData)["Sound"]["Position"][0].GetValue<JSON::Real>());
        configItems_[1].position_.y_ = static_cast<float>((*pData)["Sound"]["Position"][1].GetValue<JSON::Real>());
        configItems_[1].size_.x_ = static_cast<float>((*pData)["Sound"]["Size"][0].GetValue<JSON::Real>());
        configItems_[1].size_.y_ = static_cast<float>((*pData)["Sound"]["Size"][1].GetValue<JSON::Real>());
        configItems_[1].color_.red_ = static_cast<float>((*pData)["Sound"]["Color"][0].GetValue<JSON::Real>());
        configItems_[1].color_.green_ = static_cast<float>((*pData)["Sound"]["Color"][1].GetValue<JSON::Real>());
        configItems_[1].color_.blue_ = static_cast<float>((*pData)["Sound"]["Color"][2].GetValue<JSON::Real>());
        configItems_[1].color_.alpha_ = static_cast<float>((*pData)["Sound"]["Color"][3].GetValue<JSON::Real>());
        configItems_[1].wordOffset_ = static_cast<float>((*pData)["Sound"]["WordOffset"].GetValue<JSON::Real>());

        configItems_[2].words_ = (*pData)["SE"]["Words"].GetValue<JSON::String>();
        configItems_[2].position_.x_ = static_cast<float>((*pData)["SE"]["Position"][0].GetValue<JSON::Real>());
        configItems_[2].position_.y_ = static_cast<float>((*pData)["SE"]["Position"][1].GetValue<JSON::Real>());
        configItems_[2].size_.x_ = static_cast<float>((*pData)["SE"]["Size"][0].GetValue<JSON::Real>());
        configItems_[2].size_.y_ = static_cast<float>((*pData)["SE"]["Size"][1].GetValue<JSON::Real>());
        configItems_[2].color_.red_ = static_cast<float>((*pData)["SE"]["Color"][0].GetValue<JSON::Real>());
        configItems_[2].color_.green_ = static_cast<float>((*pData)["SE"]["Color"][1].GetValue<JSON::Real>());
        configItems_[2].color_.blue_ = static_cast<float>((*pData)["SE"]["Color"][2].GetValue<JSON::Real>());
        configItems_[2].color_.alpha_ = static_cast<float>((*pData)["SE"]["Color"][3].GetValue<JSON::Real>());
        configItems_[2].wordOffset_ = static_cast<float>((*pData)["SE"]["WordOffset"].GetValue<JSON::Real>());

        configItems_[3].words_ = (*pData)["BGM"]["Words"].GetValue<JSON::String>();
        configItems_[3].position_.x_ = static_cast<float>((*pData)["BGM"]["Position"][0].GetValue<JSON::Real>());
        configItems_[3].position_.y_ = static_cast<float>((*pData)["BGM"]["Position"][1].GetValue<JSON::Real>());
        configItems_[3].size_.x_ = static_cast<float>((*pData)["BGM"]["Size"][0].GetValue<JSON::Real>());
        configItems_[3].size_.y_ = static_cast<float>((*pData)["BGM"]["Size"][1].GetValue<JSON::Real>());
        configItems_[3].color_.red_ = static_cast<float>((*pData)["BGM"]["Color"][0].GetValue<JSON::Real>());
        configItems_[3].color_.green_ = static_cast<float>((*pData)["BGM"]["Color"][1].GetValue<JSON::Real>());
        configItems_[3].color_.blue_ = static_cast<float>((*pData)["BGM"]["Color"][2].GetValue<JSON::Real>());
        configItems_[3].color_.alpha_ = static_cast<float>((*pData)["BGM"]["Color"][3].GetValue<JSON::Real>());
        configItems_[3].wordOffset_ = static_cast<float>((*pData)["BGM"]["WordOffset"].GetValue<JSON::Real>());

        configItems_[4].words_ = (*pData)["ButtonSetting"]["Words"].GetValue<JSON::String>();
        configItems_[4].position_.x_ = static_cast<float>((*pData)["ButtonSetting"]["Position"][0].GetValue<JSON::Real>());
        configItems_[4].position_.y_ = static_cast<float>((*pData)["ButtonSetting"]["Position"][1].GetValue<JSON::Real>());
        configItems_[4].size_.x_ = static_cast<float>((*pData)["ButtonSetting"]["Size"][0].GetValue<JSON::Real>());
        configItems_[4].size_.y_ = static_cast<float>((*pData)["ButtonSetting"]["Size"][1].GetValue<JSON::Real>());
        configItems_[4].color_.red_ = static_cast<float>((*pData)["ButtonSetting"]["Color"][0].GetValue<JSON::Real>());
        configItems_[4].color_.green_ = static_cast<float>((*pData)["ButtonSetting"]["Color"][1].GetValue<JSON::Real>());
        configItems_[4].color_.blue_ = static_cast<float>((*pData)["ButtonSetting"]["Color"][2].GetValue<JSON::Real>());
        configItems_[4].color_.alpha_ = static_cast<float>((*pData)["ButtonSetting"]["Color"][3].GetValue<JSON::Real>());
        configItems_[4].wordOffset_ = static_cast<float>((*pData)["ButtonSetting"]["WordOffset"].GetValue<JSON::Real>());

        configItems_[5].words_ = (*pData)["Shot"]["Words"].GetValue<JSON::String>();
        configItems_[5].position_.x_ = static_cast<float>((*pData)["Shot"]["Position"][0].GetValue<JSON::Real>());
        configItems_[5].position_.y_ = static_cast<float>((*pData)["Shot"]["Position"][1].GetValue<JSON::Real>());
        configItems_[5].size_.x_ = static_cast<float>((*pData)["Shot"]["Size"][0].GetValue<JSON::Real>());
        configItems_[5].size_.y_ = static_cast<float>((*pData)["Shot"]["Size"][1].GetValue<JSON::Real>());
        configItems_[5].color_.red_ = static_cast<float>((*pData)["Shot"]["Color"][0].GetValue<JSON::Real>());
        configItems_[5].color_.green_ = static_cast<float>((*pData)["Shot"]["Color"][1].GetValue<JSON::Real>());
        configItems_[5].color_.blue_ = static_cast<float>((*pData)["Shot"]["Color"][2].GetValue<JSON::Real>());
        configItems_[5].color_.alpha_ = static_cast<float>((*pData)["Shot"]["Color"][3].GetValue<JSON::Real>());
        configItems_[5].wordOffset_ = static_cast<float>((*pData)["Shot"]["WordOffset"].GetValue<JSON::Real>());

        configItems_[6].words_ = (*pData)["Bomb"]["Words"].GetValue<JSON::String>();
        configItems_[6].position_.x_ = static_cast<float>((*pData)["Bomb"]["Position"][0].GetValue<JSON::Real>());
        configItems_[6].position_.y_ = static_cast<float>((*pData)["Bomb"]["Position"][1].GetValue<JSON::Real>());
        configItems_[6].size_.x_ = static_cast<float>((*pData)["Bomb"]["Size"][0].GetValue<JSON::Real>());
        configItems_[6].size_.y_ = static_cast<float>((*pData)["Bomb"]["Size"][1].GetValue<JSON::Real>());
        configItems_[6].color_.red_ = static_cast<float>((*pData)["Bomb"]["Color"][0].GetValue<JSON::Real>());
        configItems_[6].color_.green_ = static_cast<float>((*pData)["Bomb"]["Color"][1].GetValue<JSON::Real>());
        configItems_[6].color_.blue_ = static_cast<float>((*pData)["Bomb"]["Color"][2].GetValue<JSON::Real>());
        configItems_[6].color_.alpha_ = static_cast<float>((*pData)["Bomb"]["Color"][3].GetValue<JSON::Real>());
        configItems_[6].wordOffset_ = static_cast<float>((*pData)["Bomb"]["WordOffset"].GetValue<JSON::Real>());
    }


    /*************************************************************//**
     *
     *  @brief  コンフィグデータのロード処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TitleUi::LoadConfigData()
    {
        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pCONFIG_DATA));
        auto pConfigData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pCONFIG_DATA).get();

        configData_.playerLife_ = (*pConfigData)["ConfigData"]["PlayerLife"].GetValue<JSON::Integer>();
        configData_.SE_ = (*pConfigData)["ConfigData"]["SE"].GetValue<JSON::Integer>();
        configData_.BGM_ = (*pConfigData)["ConfigData"]["BGM"].GetValue<JSON::Integer>();
        configData_.shotButton_ = (*pConfigData)["ConfigData"]["Shot"].GetValue<JSON::Integer>();
        configData_.bombButton_ = (*pConfigData)["ConfigData"]["Bomb"].GetValue<JSON::Integer>();
    }


    /*************************************************************//**
     *
     *  @brief  コンフィグデータのセーブ処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TitleUi::SaveConfigData()
    {
        JSON::JsonObject newConfigData;

        newConfigData["ConfigData"]["PlayerLife"] = configData_.playerLife_;
        newConfigData["ConfigData"]["SE"] = configData_.SE_;
        newConfigData["ConfigData"]["BGM"] = configData_.BGM_;
        newConfigData["ConfigData"]["Shot"] = configData_.shotButton_;
        newConfigData["ConfigData"]["Bomb"] = configData_.bombButton_;

        JSON::JsonObject::s_WriteToJsonFile(newConfigData, Path::JSON::s_pCONFIG_DATA);
    }


    /*************************************************************//**
     *
     *  @brief  画像UIの描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TitleUi::DrawImageUiAndBackground()
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

        if (wpUiSpriteCreater_.expired() == false)
        {
            for (size_t i = 0; i < 2; ++i)
            {
                if (i == 1)
                {
                    if (drawStageSelectItemFlag_ == true || drawConfigItemFlag_ == true)
                    {
                        auto pUiSpriteCreater = wpUiSpriteCreater_.lock();

                        Sprite::S_CreateData createData;
                        createData.position_.xy_ = imageUis_[i].position_;
                        createData.size_ = imageUis_[i].size_;
                        createData.color_ = imageUis_[i].color_;
                        createData.textureUpperLeft_ = imageUis_[i].textureUpperLeft_;
                        createData.textureLowerRight_ = imageUis_[i].textureLowerRight_;

                        pUiSpriteCreater->Entry(createData);
                    }
                }
                else
                {
                    auto pUiSpriteCreater = wpUiSpriteCreater_.lock();

                    Sprite::S_CreateData createData;
                    createData.position_.xy_ = imageUis_[i].position_;
                    createData.size_ = imageUis_[i].size_;
                    createData.color_ = imageUis_[i].color_;
                    createData.textureUpperLeft_ = imageUis_[i].textureUpperLeft_;
                    createData.textureLowerRight_ = imageUis_[i].textureLowerRight_;

                    pUiSpriteCreater->Entry(createData);
                }
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  初期項目の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TitleUi::DrawInitialItems()
    {
        if (drawStageSelectItemFlag_ == false && drawConfigItemFlag_ == false)
        {
            for (auto& rInitialItem : initialItems_)
            {
                C_UiFont::s_GetInstance()->Draw(rInitialItem.words_, rInitialItem.position_, 0.0f, rInitialItem.size_, rInitialItem.wordOffset_, rInitialItem.color_);
            }

            auto arrowData = initialItems_[0];
            arrowData.position_.x_ -= 50.0f;
            arrowData.position_.y_ += initialItemNumber_ * (initialItems_[1].position_.y_ - initialItems_[0].position_.y_);
            C_UiFont::s_GetInstance()->DrawArrow(arrowData.position_, 0.0f, arrowData.size_, arrowData.color_);
        }
        else
        {
            for (auto& rInitialItem : initialItems_)
            {
                C_UiFont::s_GetInstance()->Draw(rInitialItem.words_, rInitialItem.position_, 0.0f, rInitialItem.size_, rInitialItem.wordOffset_, rInitialItem.color_ - Vector4(0.2f));
            }

            auto arrowData = initialItems_[0];
            arrowData.position_.x_ -= 50.0f;
            arrowData.position_.y_ += initialItemNumber_ * (initialItems_[1].position_.y_ - initialItems_[0].position_.y_);
            C_UiFont::s_GetInstance()->DrawArrow(arrowData.position_, 0.0f, arrowData.size_, arrowData.color_ - Vector4(0.2f));
        }
    }


    /*************************************************************//**
     *
     *  @brief  ステージセレクト項目の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TitleUi::DrawStageSelectItems()
    {
        if (drawStageSelectItemFlag_ == true)
        {
            for (auto& rStageSelectItem : stageSelectItems_)
            {
                C_UiFont::s_GetInstance()->Draw(rStageSelectItem.words_, rStageSelectItem.position_, 0.0f, rStageSelectItem.size_, rStageSelectItem.wordOffset_, rStageSelectItem.color_);
            }

            auto arrowData = stageSelectItems_[1];
            arrowData.position_.x_ -= 50.0f;
            arrowData.position_.y_ += stageSelectItemNumber_ * (stageSelectItems_[2].position_.y_ - stageSelectItems_[1].position_.y_);
            C_UiFont::s_GetInstance()->DrawArrow(arrowData.position_, 0.0f, arrowData.size_, arrowData.color_);
        }
    }


    /*************************************************************//**
     *
     *  @brief  コンフィグ項目の描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TitleUi::DrawConfigItems()
    {
        if (drawConfigItemFlag_ == true)
        {
            for (auto& rConfigItem : configItems_)
            {
                C_UiFont::s_GetInstance()->Draw(rConfigItem.words_, rConfigItem.position_, 0.0f, rConfigItem.size_, rConfigItem.wordOffset_, rConfigItem.color_);
            }

            S_WordUiData drawUiData;

            drawUiData = configItems_[0];
            drawUiData.words_ = std::to_string(configData_.playerLife_);
            drawUiData.position_.x_ += 320.0f;
            C_UiFont::s_GetInstance()->Draw(drawUiData.words_, drawUiData.position_, 0.0f, drawUiData.size_, drawUiData.wordOffset_, drawUiData.color_);

            drawUiData = configItems_[2];
            drawUiData.words_ = std::to_string(configData_.SE_);
            drawUiData.position_.x_ += 200.0f;
            C_UiFont::s_GetInstance()->Draw(drawUiData.words_, drawUiData.position_, 0.0f, drawUiData.size_, drawUiData.wordOffset_, drawUiData.color_);

            drawUiData = configItems_[3];
            drawUiData.words_ = std::to_string(configData_.BGM_);
            drawUiData.position_.x_ += 220.0f;
            C_UiFont::s_GetInstance()->Draw(drawUiData.words_, drawUiData.position_, 0.0f, drawUiData.size_, drawUiData.wordOffset_, drawUiData.color_);
            
            drawUiData = configItems_[5];
            drawUiData.words_ = std::to_string(configData_.shotButton_);
            drawUiData.position_.x_ += 340.0f;
            C_UiFont::s_GetInstance()->Draw(drawUiData.words_, drawUiData.position_, 0.0f, drawUiData.size_, drawUiData.wordOffset_, drawUiData.color_);

            drawUiData = configItems_[6];
            drawUiData.words_ = std::to_string(configData_.bombButton_);
            drawUiData.position_.x_ += 340.0f;
            C_UiFont::s_GetInstance()->Draw(drawUiData.words_, drawUiData.position_, 0.0f, drawUiData.size_, drawUiData.wordOffset_, drawUiData.color_);
        
            switch (configItemNumber_)
            {
            case PLAYER_LIFE:

                C_UiFont::s_GetInstance()->DrawArrow(configItems_[0].position_ + Vector2(260.0f, 0.0f), static_cast<float>(Math::s_PI), configItems_[0].size_, configItems_[0].color_);
                C_UiFont::s_GetInstance()->DrawArrow(configItems_[0].position_ + Vector2(380.0f, 0.0f), 0.0f, configItems_[0].size_, configItems_[0].color_);

                break;
            case SOUND_SE:

                C_UiFont::s_GetInstance()->DrawArrow(configItems_[2].position_ + Vector2(140.0f, 0.0f), static_cast<float>(Math::s_PI), configItems_[0].size_, configItems_[0].color_);
                C_UiFont::s_GetInstance()->DrawArrow(configItems_[2].position_ + Vector2(260.0f, 0.0f), 0.0f, configItems_[0].size_, configItems_[0].color_);

                break;
            case SOUND_BGM:

                C_UiFont::s_GetInstance()->DrawArrow(configItems_[3].position_ + Vector2(160.0f, 0.0f), static_cast<float>(Math::s_PI), configItems_[0].size_, configItems_[0].color_);
                C_UiFont::s_GetInstance()->DrawArrow(configItems_[3].position_ + Vector2(280.0f, 0.0f), 0.0f, configItems_[0].size_, configItems_[0].color_);

                break;
            case BUTTOM_SHOT:

                C_UiFont::s_GetInstance()->DrawArrow(configItems_[5].position_ + Vector2(135.0f, 0.0f), 0.0f, configItems_[0].size_, configItems_[0].color_);

                break;
            case BUTTON_BOMB:

                C_UiFont::s_GetInstance()->DrawArrow(configItems_[6].position_ + Vector2(135.0f, 0.0f), 0.0f, configItems_[0].size_, configItems_[0].color_);

                break;
            default:

                StrongAssert(false && "[ C_TitleUi::DoUpdate ] : 項目外です。");

                break;
            }
        }
    }
}