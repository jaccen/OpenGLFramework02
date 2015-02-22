/* ヘッダファイル */
#include "Fade.h"
#include "ConnectWarsDefine.h"
#include "../../Library/Window/Manager/WindowManager.h"


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
    C_Fade::C_Fade(const std::string& rId,
                   int32_t type,
                   int32_t fadeFrame,
                   bool createFadeInFlag) : C_GameObject(rId, type),

        fadeFrame_(fadeFrame),
        fadeInFlag_(createFadeInFlag)

    {
        assert(Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pFADE));
        wpSpriteCreater_ = Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pFADE).get();
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_Fade::~C_Fade()
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
    bool C_Fade::Update()
    {
        if (fadeInFlag_ == true)
        {
            ++elapsedFadeFrame_;

            if (elapsedFadeFrame_ > fadeFrame_)
            {
                elapsedFadeFrame_ = fadeFrame_;
                finishFadeInFlag_ = true;
            }
        }
        else if (fadeOutFlag_ == true)
        {
            ++elapsedFadeFrame_;

            if (elapsedFadeFrame_ > fadeFrame_)
            {
                elapsedFadeFrame_ = fadeFrame_;
                finishFadeOutFlag_ = true;
            }
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
    void C_Fade::Draw()
    {
        if (fadeInFlag_ == true)
        {
            if (wpSpriteCreater_.expired() == false)
            {
                auto pSpriteCreater = wpSpriteCreater_.lock();

                assert(Window::C_WindowManager::s_GetInstance()->GetWindow());
                auto pMainWindow = Window::C_WindowManager::s_GetInstance()->GetWindow().get();

                Sprite::S_CreateData createData;

                createData.position_.x_ = static_cast<float>(pMainWindow->GetWidth()) / 2.0f;
                createData.position_.y_ = static_cast<float>(pMainWindow->GetHeight()) / 2.0f;
                createData.size_.x_ = static_cast<float>(pMainWindow->GetWidth());
                createData.size_.y_ = static_cast<float>(pMainWindow->GetHeight());
                createData.color_.alpha_ = 1.0f - static_cast<float>(elapsedFadeFrame_) / static_cast<float>(fadeFrame_);
                createData.textureLowerRight_.Fill(1.0f);
                
                pSpriteCreater->Entry(createData);
            }
        }
        else if (fadeOutFlag_ == true)
        {
            if (wpSpriteCreater_.expired() == false)
            {
                auto pSpriteCreater = wpSpriteCreater_.lock();

                assert(Window::C_WindowManager::s_GetInstance()->GetWindow());
                auto pMainWindow = Window::C_WindowManager::s_GetInstance()->GetWindow().get();

                Sprite::S_CreateData createData;

                createData.position_.x_ = static_cast<float>(pMainWindow->GetWidth()) / 2.0f;
                createData.position_.y_ = static_cast<float>(pMainWindow->GetHeight()) / 2.0f;
                createData.size_.x_ = static_cast<float>(pMainWindow->GetWidth());
                createData.size_.y_ = static_cast<float>(pMainWindow->GetHeight());
                createData.color_.alpha_ = static_cast<float>(elapsedFadeFrame_) / static_cast<float>(fadeFrame_);
                createData.textureLowerRight_.Fill(1.0f);
                
                pSpriteCreater->Entry(createData);
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_Fade::MessageProcess(const Telegram& rTelegram)
    {
        return true;
    }


    /*************************************************************//**
     *
     *  @brief  フェードインを行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_Fade::FadeIn()
    {
        fadeInFlag_ = true;
        fadeOutFlag_ = false;
        elapsedFadeFrame_ = 0;
    }


    /*************************************************************//**
     *
     *  @brief  フェードアウトを行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_Fade::FadeOut()
    {
        fadeOutFlag_ = true;
        fadeInFlag_ = false;
        elapsedFadeFrame_ = 0;
    }


    /*************************************************************//**
     *
     *  @brief  各フラグのリセットを行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_Fade::ResetFlag()
    {
        fadeInFlag_ = false;
        fadeOutFlag_ = false;
        finishFadeInFlag_ = false;
        finishFadeOutFlag_ = false;
    }


    /*************************************************************//**
     *
     *  @brief  フェードフレームを設定する
     *  @param  フェードフレーム
     *  @return なし
     *
     ****************************************************************/
    void C_Fade::SetFadeFrame(int32_t fadeFrame)
    {
        fadeFrame_ = fadeFrame;
    }


    /*************************************************************//**
     *
     *  @brief  フェードイン完了フラグを取得する
     *  @param  なし
     *  @return フェードイン完了フラグ
     *
     ****************************************************************/
    bool C_Fade::IsFinishFadeInFlag() const
    {
        return finishFadeInFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  フェードアウト完了フラグを取得する
     *  @param  なし
     *  @return フェードアウト完了フラグ
     *
     ****************************************************************/
    bool C_Fade::IsFinishFadeOutFlag() const
    {
        return finishFadeOutFlag_;
    }
}