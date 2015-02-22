/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Library/Singleton/Assert/AssertSingleton.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "ConnectWarsDefine.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief UI�t�H���g
    //! @brief UI�p�̃t�H���g��`�悷��N���X
    //! @brief �� �g�p����ꍇ�A�t�H���g�p��UI�X�v���C�g���쐬��ɐ������邱��
    //!
    //-------------------------------------------------------------
    class C_UiFont : public Singleton::C_AssertSingleton<C_UiFont>
    {
    public:
        C_UiFont();                                                                 // �R���X�g���N�^
        ~C_UiFont() override;                                                       // �f�X�g���N�^
        void Draw(const std::string& rWords,                                        // �`�揈��
                  const Vector2& rPosition,
                  float angle,
                  const Vector2& rSize,
                  float wordOffset = 0.0f,
                  const Vector4& rColor = Vector4::s_ONE);
        void DrawArrow(const Vector2& rPosition,                                    // ���̕`��
                       float angle,
                       const Vector2& rSize,
                       const Vector4& rColor = Vector4::s_ONE);
    private:
        Sprite::SpriteCreaterWeakPtr wpSpriteCreater_;                              ///< @brief �X�v���C�g�N���G�C�^�[
    };
}