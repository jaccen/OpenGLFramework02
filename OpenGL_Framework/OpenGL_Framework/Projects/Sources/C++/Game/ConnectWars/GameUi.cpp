/* �w�b�_�t�@�C�� */
#include "GameUi.h"
#include "UiFont.h"
#include "../../Library/Window/Manager/WindowManager.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "../../Library/GameObject/Message/Dispatcher/MessageDispatcher.h"


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
    C_GameUi::C_GameUi(const std::string& rId, int32_t type) : C_BaseUi(rId, type)
    {
        assert(Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pGAME_UI));
        wpUiSpriteCreater_ = Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pGAME_UI).get();

        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pGAME_UI_DATA));
        auto pGameUiData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pGAME_UI_DATA).get();

        LoadUiWords(&(*pGameUiData)["GameUiData"]);
        LoadUiSpriteData(&(*pGameUiData)["GameUiData"]);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_GameUi::~C_GameUi()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameUi::DoUpdate()
    {
        UpdateUiWords();
        UpdateUiSprite();

        if (playerUiData_.hp_ > 0)
        {
        }
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameUi::DoDraw()
    {
        DrawUiWords();
        DrawUiSprite();
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̃��b�Z�[�W�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    bool C_GameUi::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }


    /*************************************************************//**
     *
     *  @brief  UI������̃��[�h�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameUi::LoadUiWords(JSON::JsonObject* pData)
    {
        uiWords_[0].words_ = (*pData)["Life"]["Words"].GetValue<JSON::String>();
        uiWords_[0].position_.x_ = static_cast<float>((*pData)["Life"]["Position"][0].GetValue<JSON::Real>());
        uiWords_[0].position_.y_ = static_cast<float>((*pData)["Life"]["Position"][1].GetValue<JSON::Real>());
        uiWords_[0].size_.x_ = static_cast<float>((*pData)["Life"]["Size"][0].GetValue<JSON::Real>());
        uiWords_[0].size_.y_ = static_cast<float>((*pData)["Life"]["Size"][1].GetValue<JSON::Real>());
        uiWords_[0].color_.red_ = static_cast<float>((*pData)["Life"]["Color"][0].GetValue<JSON::Real>());
        uiWords_[0].color_.green_ = static_cast<float>((*pData)["Life"]["Color"][1].GetValue<JSON::Real>());
        uiWords_[0].color_.blue_ = static_cast<float>((*pData)["Life"]["Color"][2].GetValue<JSON::Real>());
        uiWords_[0].color_.alpha_ = static_cast<float>((*pData)["Life"]["Color"][3].GetValue<JSON::Real>());
        uiWords_[0].wordOffset_ = static_cast<float>((*pData)["Life"]["WordOffset"].GetValue<JSON::Real>());
    
        uiWords_[1].words_ = (*pData)["Score"]["Words"].GetValue<JSON::String>();
        uiWords_[1].position_.x_ = static_cast<float>((*pData)["Score"]["Position"][0].GetValue<JSON::Real>());
        uiWords_[1].position_.y_ = static_cast<float>((*pData)["Score"]["Position"][1].GetValue<JSON::Real>());
        uiWords_[1].size_.x_ = static_cast<float>((*pData)["Score"]["Size"][0].GetValue<JSON::Real>());
        uiWords_[1].size_.y_ = static_cast<float>((*pData)["Score"]["Size"][1].GetValue<JSON::Real>());
        uiWords_[1].color_.red_ = static_cast<float>((*pData)["Score"]["Color"][0].GetValue<JSON::Real>());
        uiWords_[1].color_.green_ = static_cast<float>((*pData)["Score"]["Color"][1].GetValue<JSON::Real>());
        uiWords_[1].color_.blue_ = static_cast<float>((*pData)["Score"]["Color"][2].GetValue<JSON::Real>());
        uiWords_[1].color_.alpha_ = static_cast<float>((*pData)["Score"]["Color"][3].GetValue<JSON::Real>());
        uiWords_[1].wordOffset_ = static_cast<float>((*pData)["Score"]["WordOffset"].GetValue<JSON::Real>());
    }


    /*************************************************************//**
     *
     *  @brief  UI�X�v���C�g�f�[�^�̃��[�h�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameUi::LoadUiSpriteData(JSON::JsonObject* pData)
    {
        imageUis_[0].position_.x_ = static_cast<float>((*pData)["HitPointBar"]["Position"][0].GetValue<JSON::Real>());
        imageUis_[0].position_.y_ = static_cast<float>((*pData)["HitPointBar"]["Position"][1].GetValue<JSON::Real>());
        imageUis_[0].size_.x_ = static_cast<float>((*pData)["HitPointBar"]["Size"][0].GetValue<JSON::Real>());
        imageUis_[0].size_.y_ = static_cast<float>((*pData)["HitPointBar"]["Size"][1].GetValue<JSON::Real>());
        imageUis_[0].color_.red_ = static_cast<float>((*pData)["HitPointBar"]["Color"][0].GetValue<JSON::Real>());
        imageUis_[0].color_.green_ = static_cast<float>((*pData)["HitPointBar"]["Color"][1].GetValue<JSON::Real>());
        imageUis_[0].color_.blue_ = static_cast<float>((*pData)["HitPointBar"]["Color"][2].GetValue<JSON::Real>());
        imageUis_[0].color_.alpha_ = static_cast<float>((*pData)["HitPointBar"]["Color"][3].GetValue<JSON::Real>());
        imageUis_[0].textureUpperLeft_.x_ = static_cast<float>((*pData)["HitPointBar"]["TextureUpperLeft"][0].GetValue<JSON::Real>());
        imageUis_[0].textureUpperLeft_.y_ = static_cast<float>((*pData)["HitPointBar"]["TextureUpperLeft"][1].GetValue<JSON::Real>());
        imageUis_[0].textureLowerRight_.x_ = static_cast<float>((*pData)["HitPointBar"]["TextureLowerRight"][0].GetValue<JSON::Real>());
        imageUis_[0].textureLowerRight_.y_ = static_cast<float>((*pData)["HitPointBar"]["TextureLowerRight"][1].GetValue<JSON::Real>());

        imageUis_[1].position_.x_ = static_cast<float>((*pData)["PlayerHpGauge"]["Position"][0].GetValue<JSON::Real>());
        imageUis_[1].position_.y_ = static_cast<float>((*pData)["PlayerHpGauge"]["Position"][1].GetValue<JSON::Real>());
        imageUis_[1].size_.x_ = static_cast<float>((*pData)["PlayerHpGauge"]["Size"][0].GetValue<JSON::Real>());
        imageUis_[1].size_.y_ = static_cast<float>((*pData)["PlayerHpGauge"]["Size"][1].GetValue<JSON::Real>());
        imageUis_[1].color_.red_ = static_cast<float>((*pData)["PlayerHpGauge"]["Color"][0].GetValue<JSON::Real>());
        imageUis_[1].color_.green_ = static_cast<float>((*pData)["PlayerHpGauge"]["Color"][1].GetValue<JSON::Real>());
        imageUis_[1].color_.blue_ = static_cast<float>((*pData)["PlayerHpGauge"]["Color"][2].GetValue<JSON::Real>());
        imageUis_[1].color_.alpha_ = static_cast<float>((*pData)["PlayerHpGauge"]["Color"][3].GetValue<JSON::Real>());
        imageUis_[1].textureUpperLeft_.x_ = static_cast<float>((*pData)["PlayerHpGauge"]["TextureUpperLeft"][0].GetValue<JSON::Real>());
        imageUis_[1].textureUpperLeft_.y_ = static_cast<float>((*pData)["PlayerHpGauge"]["TextureUpperLeft"][1].GetValue<JSON::Real>());
        imageUis_[1].textureLowerRight_.x_ = static_cast<float>((*pData)["PlayerHpGauge"]["TextureLowerRight"][0].GetValue<JSON::Real>());
        imageUis_[1].textureLowerRight_.y_ = static_cast<float>((*pData)["PlayerHpGauge"]["TextureLowerRight"][1].GetValue<JSON::Real>());

        imageUis_[2].position_.x_ = static_cast<float>((*pData)["PlayerIcon"]["Position"][0].GetValue<JSON::Real>());
        imageUis_[2].position_.y_ = static_cast<float>((*pData)["PlayerIcon"]["Position"][1].GetValue<JSON::Real>());
        imageUis_[2].size_.x_ = static_cast<float>((*pData)["PlayerIcon"]["Size"][0].GetValue<JSON::Real>());
        imageUis_[2].size_.y_ = static_cast<float>((*pData)["PlayerIcon"]["Size"][1].GetValue<JSON::Real>());
        imageUis_[2].color_.red_ = static_cast<float>((*pData)["PlayerIcon"]["Color"][0].GetValue<JSON::Real>());
        imageUis_[2].color_.green_ = static_cast<float>((*pData)["PlayerIcon"]["Color"][1].GetValue<JSON::Real>());
        imageUis_[2].color_.blue_ = static_cast<float>((*pData)["PlayerIcon"]["Color"][2].GetValue<JSON::Real>());
        imageUis_[2].color_.alpha_ = static_cast<float>((*pData)["PlayerIcon"]["Color"][3].GetValue<JSON::Real>());
        imageUis_[2].textureUpperLeft_.x_ = static_cast<float>((*pData)["PlayerIcon"]["TextureUpperLeft"][0].GetValue<JSON::Real>());
        imageUis_[2].textureUpperLeft_.y_ = static_cast<float>((*pData)["PlayerIcon"]["TextureUpperLeft"][1].GetValue<JSON::Real>());
        imageUis_[2].textureLowerRight_.x_ = static_cast<float>((*pData)["PlayerIcon"]["TextureLowerRight"][0].GetValue<JSON::Real>());
        imageUis_[2].textureLowerRight_.y_ = static_cast<float>((*pData)["PlayerIcon"]["TextureLowerRight"][1].GetValue<JSON::Real>());
    }


    /*************************************************************//**
     *
     *  @brief  UI������̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameUi::UpdateUiWords()
    {
    }


    /*************************************************************//**
     *
     *  @brief  UI�X�v���C�g�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameUi::UpdateUiSprite()
    {
    }


    /*************************************************************//**
     *
     *  @brief  UI������̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameUi::DrawUiWords()
    {
        // ���C�t�̕`��
        C_UiFont::s_GetInstance()->Draw(uiWords_[0].words_, uiWords_[0].position_, 0.0f, uiWords_[0].size_, uiWords_[0].wordOffset_);

        // �X�R�A�̕`��
        C_UiFont::s_GetInstance()->Draw(uiWords_[1].words_, uiWords_[1].position_, 0.0f, uiWords_[1].size_, uiWords_[1].wordOffset_);

        int32_t tempScore = playerUiData_.score_;

        for (size_t i = 8; i > 0; --i)
        {
            int32_t digit = tempScore % 10;
            tempScore /= 10;

            C_UiFont::s_GetInstance()->Draw(std::to_string(digit), uiWords_[1].position_ + Vector2(95.0f + (i * (uiWords_[1].size_.x_ + uiWords_[1].wordOffset_ + 3.0f)), 0.0f), 0.0f, uiWords_[1].size_, uiWords_[1].wordOffset_);
        
            if (tempScore == 0) break;
        }
    }


    /*************************************************************//**
     *
     *  @brief  UI�X�v���C�g�̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_GameUi::DrawUiSprite()
    {
        if (wpUiSpriteCreater_.expired() == false)
        {
            auto pUiSpriteCreater = wpUiSpriteCreater_.lock();
            Sprite::S_CreateData createData;

            // �̗̓o�[�̕`��
            createData.position_.xy_ = imageUis_[0].position_;
            createData.size_ = imageUis_[0].size_;
            createData.color_ = imageUis_[0].color_;
            createData.textureUpperLeft_ = imageUis_[0].textureUpperLeft_;
            createData.textureLowerRight_ = imageUis_[0].textureLowerRight_;

            pUiSpriteCreater->Entry(createData);

            float playerHpFactor = (static_cast<float>(playerUiData_.hp_) / static_cast<float>(playerUiData_.maxHp_));

            // �̗̓Q�[�W�̕`��
            createData.position_.xy_ = imageUis_[1].position_;
            createData.size_ = imageUis_[1].size_;
            createData.size_.x_ = createData.size_.x_ * playerHpFactor;
            createData.position_.x_ = createData.position_.x_ - (imageUis_[1].size_.x_ - createData.size_.x_) * 0.5f;
            createData.color_ = imageUis_[1].color_;
            createData.textureUpperLeft_ = imageUis_[1].textureUpperLeft_;
            createData.textureLowerRight_ = imageUis_[1].textureLowerRight_;
            createData.textureLowerRight_.x_ = createData.textureLowerRight_.x_ * playerHpFactor;

            pUiSpriteCreater->Entry(createData);

            // �v���C���[�A�C�R��( ���C�t )�̕`��
            for (int32_t i = 0; i < playerUiData_.remainLife_; ++i)
            {
                createData.position_.xy_ = imageUis_[2].position_;
                createData.position_.x_ = createData.position_.x_ + imageUis_[2].size_.x_ * i;
                createData.size_ = imageUis_[2].size_;
                createData.color_ = imageUis_[2].color_;
                createData.textureUpperLeft_ = imageUis_[2].textureUpperLeft_;
                createData.textureLowerRight_ = imageUis_[2].textureLowerRight_;

                pUiSpriteCreater->Entry(createData);
            }
        }
        
    }

}