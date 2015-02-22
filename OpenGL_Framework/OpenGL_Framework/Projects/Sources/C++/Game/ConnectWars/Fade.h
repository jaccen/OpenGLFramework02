/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectWarsDefine.h"
#include "../../Library/GameObject/GameObject.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"


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
    //! @brief �t�F�[�h
    //! @brief �t�F�[�h�C���E�A�E�g�����邽�߂̃N���X
    //!
    //-------------------------------------------------------------
    class C_Fade : public GameObject::C_GameObject
    {
    public:
        C_Fade(const std::string& rId,                                  // �R���X�g���N�^
               int32_t type,    
               int32_t fadeFrame = 60,
               bool createFadeInFlag = true);           
        ~C_Fade() override;                                             // �f�X�g���N�^
        bool Update() override;                                         // �X�V����
        void Draw() override;                                           // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override;        // ���b�Z�[�W����
        void FadeIn();                                                  // �t�F�[�h�C��
        void FadeOut();                                                 // �t�F�[�h�A�E�g
        void ResetFlag();                                               // �t���O�����Z�b�g
        void SetFadeFrame(int32_t fadeFrame);                           // �t�F�[�h�t���[����ݒ�
        bool IsFinishFadeInFlag() const;                                // �t�F�[�h�C�������t���O���擾
        bool IsFinishFadeOutFlag() const;                               // �t�F�[�h�A�E�g�����t���O���擾
    private:
        bool fadeInFlag_ = false;                                       ///< @brief �t�F�[�h�C���t���O
        bool finishFadeInFlag_ = false;                                 ///< @brief �t�F�[�h�C�������t���O
        bool fadeOutFlag_ = false;                                      ///< @brief �t�F�[�h�A�E�g�t���O
        bool finishFadeOutFlag_ = false;                                ///< @brief �t�F�[�h�A�E�g�����t���O
        int32_t elapsedFadeFrame_ = 0;                                  ///< @brief �o�߃t�F�[�h�t���[��
        int32_t fadeFrame_ = 0;                                         ///< @brief �t�F�[�h�t���[��
        Sprite::SpriteCreaterWeakPtr wpSpriteCreater_;                  ///< @brief �X�v���C�g�N���G�C�^�[
        Vector4 color_;                                                 ///< @brief �F
    };
}