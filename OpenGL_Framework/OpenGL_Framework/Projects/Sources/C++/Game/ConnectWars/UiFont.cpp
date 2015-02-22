/* �w�b�_�t�@�C�� */
#include "UiFont.h"


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
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_UiFont::C_UiFont()
    {
        assert(Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pUI_FONT));
        wpSpriteCreater_ = Sprite::C_SpriteCreaterManager::s_GetInstance()->GetSpriteCreater(ID::Sprite::s_pUI_FONT).get();
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_UiFont::~C_UiFont()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  ����
     *  @param  ���W
     *  @param  �p�x
     *  @param  �T�C�Y
     *  @param  �F
     *  @param  �����̃I�t�Z�b�g
     *
     ****************************************************************/
    void C_UiFont::Draw(const std::string& rWords,
                        const Vector2& rPosition,
                        float angle,
                        const Vector2& rSize,
                        float wordOffset,
                        const Vector4& rColor)
    {
        if (wpSpriteCreater_.expired() == false)
        {
            auto pSpriteCreater = wpSpriteCreater_.lock();
            Sprite::S_CreateData spriteData;

            spriteData.position_.xy_ = rPosition;
            spriteData.angle_ = angle;
            spriteData.size_ = rSize;
            spriteData.color_ = rColor;

            for (size_t i = 0, wordSize = rWords.size(); i < wordSize; ++i)
            {
                if (rWords[i] >= '!' && rWords[i] <= '~')
                {
                    uint32_t wordNumber = rWords[i] - '!';

                    spriteData.textureUpperLeft_.x_ = 64.0f * static_cast<float>(wordNumber % 20);
                    spriteData.textureUpperLeft_.y_ = 64.0f * static_cast<float>((wordNumber) / 20);

                    spriteData.textureLowerRight_.x_ = spriteData.textureUpperLeft_.x_ + 64.0f;
                    spriteData.textureLowerRight_.y_ = spriteData.textureUpperLeft_.y_ + 64.0f;

                    spriteData.position_.x_ = rPosition.x_ + (spriteData.size_.x_ + wordOffset) * static_cast<float>(i);
                    pSpriteCreater->Entry(spriteData);
                }
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  ���̕`�揈�����s��
     *  @param  ����
     *  @param  ���W
     *  @param  �p�x
     *  @param  �T�C�Y
     *  @param  �F
     *  @param  �����̃I�t�Z�b�g
     *
     ****************************************************************/
    void C_UiFont::DrawArrow(const Vector2& rPosition,
                             float angle,
                             const Vector2& rSize,
                             const Vector4& rColor)
    {
        if (wpSpriteCreater_.expired() == false)
        {
            auto pSpriteCreater = wpSpriteCreater_.lock();
            Sprite::S_CreateData spriteData;

            spriteData.position_ .xy_= rPosition;
            spriteData.angle_ = angle;
            spriteData.size_ = rSize;
            spriteData.color_ = rColor;

            spriteData.textureUpperLeft_.x_ = 64.0f * 14.0f;
            spriteData.textureUpperLeft_.y_ = 64.0f * 4.0f;

            spriteData.textureLowerRight_.x_ = 64.0f * 15.0f;
            spriteData.textureLowerRight_.y_ = 64.0f * 5.0f;

            pSpriteCreater->Entry(spriteData);
        }
    }
}