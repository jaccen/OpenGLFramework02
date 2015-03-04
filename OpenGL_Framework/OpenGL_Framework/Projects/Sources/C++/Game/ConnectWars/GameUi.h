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
    /** �v���C���[UI�f�[�^ */
    struct S_PlayerUiData
    {
        int32_t remainLife_ = 5;                ///< @brief �c�@
        int32_t hp_ = 1000;                     ///< @brief �̗�
        int32_t maxHp_ = 1000;                  ///< @brief �ő�̗�
        int32_t score_ = 10;                    ///< @brief �X�R�A
    };


    //-------------------------------------------------------------
    //!
    //! @brief �Q�[��UI
    //! @brief �Q�[��UI��\������N���X
    //!
    //-------------------------------------------------------------
    class C_GameUi : public C_BaseUi
    {
    public:
        C_GameUi(const std::string& rId, int32_t type);                     // �R���X�g���N�^
        ~C_GameUi() override;                                               // �f�X�g���N�^
    private:
        S_WordUiData uiWords_[2];                                           ///< @brief UI����
        S_ImageUiData imageUis_[3];                                         ///< @brief �摜UI�f�[�^
        Sprite::SpriteCreaterWeakPtr wpUiSpriteCreater_;                    ///< @brief UI�X�v���C�g�N���G�C�^�[
        S_PlayerUiData playerUiData_;                                       ///< @brief �v���C���[UI�f�[�^
        bool toNextStageFlag_ = false;                                      ///< @brief ���̃X�e�[�W�ֈڍs�t���O
        bool toRankingFlag_ = false;                                        ///< @brief �����L���O�ֈڍs�t���O

        void DoUpdate() override;                                           // ����J�̍X�V����
        void DoDraw() override;                                             // ����J�̕`�揈��
        bool DoMessageProcess(const Telegram& rTelegram) override;          // ����J�̃��b�Z�[�W����
        void LoadUiWords(JSON::JsonObject* pData);                          // UI�����̃��[�h����
        void LoadUiSpriteData(JSON::JsonObject* pData);                     // UI�X�v���C�g�f�[�^�̃��[�h����
        void UpdateUiWords();                                               // UI�����̍X�V����
        void UpdateUiSprite();                                              // UI�X�v���C�g�̍X�V����
        void DrawUiWords();                                                 // UI�����̕`�揈��
        void DrawUiSprite();                                                // UI�X�v���C�g�̕`�揈��
    };
}