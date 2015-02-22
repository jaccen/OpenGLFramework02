/* �w�b�_�t�@�C�� */
#include "Fade.h"
#include "ConnectWarsDefine.h"
#include "../../Library/Window/Manager/WindowManager.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  ID
     *  @param  ���
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
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_Fade::~C_Fade()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �^�X�N���s�Ftrue
     *  @return �^�X�N�I���Ffalse
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
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
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
     *  @brief  ���b�Z�[�W�������s��
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_Fade::MessageProcess(const Telegram& rTelegram)
    {
        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �t�F�[�h�C�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
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
     *  @brief  �t�F�[�h�A�E�g���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
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
     *  @brief  �e�t���O�̃��Z�b�g���s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
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
     *  @brief  �t�F�[�h�t���[����ݒ肷��
     *  @param  �t�F�[�h�t���[��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_Fade::SetFadeFrame(int32_t fadeFrame)
    {
        fadeFrame_ = fadeFrame;
    }


    /*************************************************************//**
     *
     *  @brief  �t�F�[�h�C�������t���O���擾����
     *  @param  �Ȃ�
     *  @return �t�F�[�h�C�������t���O
     *
     ****************************************************************/
    bool C_Fade::IsFinishFadeInFlag() const
    {
        return finishFadeInFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  �t�F�[�h�A�E�g�����t���O���擾����
     *  @param  �Ȃ�
     *  @return �t�F�[�h�A�E�g�����t���O
     *
     ****************************************************************/
    bool C_Fade::IsFinishFadeOutFlag() const
    {
        return finishFadeOutFlag_;
    }
}