/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "BaseUi.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"


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
    //! @brief �|�[�YUI
    //! @brief �|�[�YUI��\������N���X
    //!
    //-------------------------------------------------------------
    class C_PauseUi : public C_BaseUi
    {
    public:
        C_PauseUi(const std::string& rId, int32_t type);                    // �R���X�g���N�^
        ~C_PauseUi() override;                                              // �f�X�g���N�^
    private:
        S_WordUiData uiWords_[3];                                           ///< @brief UI����
        Sprite::SpriteCreaterWeakPtr wpBackgroundSpriteCreater_;            ///< @brief �w�i�X�v���C�g�N���G�C�^�[
        Timer::C_FrameCounter backgoundSizeFactor_;                         ///< @brief �w�i�̃T�C�Y�W��
        int32_t maxSizeCount_  = 15;                                        ///< @brief �ő�T�C�Y�J�E���g��
        bool toTitleFlag_ = false;                                          ///< @brief �^�C�g���V�[���ֈڍs�t���O
        int32_t uiWordIndex_ = 0;                                           ///< @brief UI�����̃C���f�b�N�X

        void DoUpdate() override;                                           // ����J�̍X�V����
        void DoDraw() override;                                             // ����J�̕`�揈��
        bool DoMessageProcess(const Telegram& rTelegram) override;          // ����J�̃��b�Z�[�W����
        void LoadUiWords(JSON::JsonObject* pData);                          // UI�����̃��[�h����
        void UpdateUiWords();                                               // UI�����̍X�V
        void DrawBackground();                                              // �w�i�̕`�揈��
        void DrawUiWords();                                                 // UI�����̕`�揈��
    };
}