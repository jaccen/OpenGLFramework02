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
    /** �X�R�A�f�[�^ */
    struct S_ScoreData
    {
        int32_t score_ = 0;
        S_WordUiData scoreStringData_;
    };

    /** �����L���O�f�[�^ */
    struct S_RankingData
    {
        S_WordUiData nameData_;
        S_ScoreData scoreData_;
    };


    /** �V�L�^�f�[�^ */
    struct S_NewRecordData
    {
        int32_t rank_ = -1;
        std::string rankWords_;
        int32_t score_ = 0;
        std::string name_;
        char newWord_ = 'A';
    };


    //-------------------------------------------------------------
    //!
    //! @brief �����L���OUI
    //! @brief �����L���OUI��\������N���X
    //!
    //-------------------------------------------------------------
    class C_RankingUi : public C_BaseUi
    {
    public:
        C_RankingUi(const std::string& rId, int32_t type, bool rankingEntryFlag = false, int32_t newScore = 0);     // �R���X�g���N�^
        ~C_RankingUi() override;                                                                                    // �f�X�g���N�^
    private:
        S_WordUiData rankingEntryWords_[1];                                                                         ///< @brief �����L���O�o�^����
        S_WordUiData rankingWords_[6];                                                                              ///< @brief �����L���O����
        S_RankingData rankingDatas_[5];                                                                             ///< @brief �����L���O�f�[�^
        Sprite::SpriteCreaterWeakPtr wpBackgroundSpriteCreater_;                                                    ///< @brief �w�i�X�v���C�g�N���G�C�^�[
        bool rankingEntryFlag_ = false;                                                                             ///< @brief �����L���O�o�^�t���O
        Timer::C_FrameCounter rankingEntryCounter_;                                                                 ///< @brief �����L���O�o�^�J�E���^�[
        Timer::C_FrameCounter rankingMoveCounter_;                                                                  ///< @brief �����L���O�ړ��̃J�E���^�[
        int32_t maxCount_ = 30;                                                                                     ///< @brief �ő�J�E���g��
        S_NewRecordData newRecordData_;                                                                             ///< @brief �V�L�^�f�[�^
        bool toTitleFlag_ = false;                                                                                  ///< @brief �^�C�g���V�[���ֈڍs�t���O

        void DoUpdate() override;                                                                                   // ����J�̍X�V����
        void DoDraw() override;                                                                                     // ����J�̕`�揈��
        bool DoMessageProcess(const Telegram& rTelegram) override;                                                  // ����J�̃��b�Z�[�W����
        void LoadRankingEntryWords(JSON::JsonObject* pData);                                                        // �����L���O�o�^���ڂ̃��[�h����
        void LoadRankingWords(JSON::JsonObject* pData);                                                             // �����L���O���ڂ̃��[�h����
        void LoadRankingData();                                                                                     // �����L���O�f�[�^�̃��[�h����
        void SaveRankingData();                                                                                     // �����L���O�f�[�^�̃Z�[�u����
        void UpdateRankingEntry();                                                                                  // �����L���O�o�^�̍X�V
        void UpdateRanking();                                                                                       // �����L���O�̍X�V
        void DrawBackground();                                                                                      // �w�i�̕`�揈��
        void DrawRankingEntry();                                                                                    // �����L���O�o�^�̕`�揈��
        void DrawRanking();                                                                                         // �����L���O�̕`�揈��
        void DrawNewEntryScore();                                                                                   // �V�����X�R�A�̓o�^�̕`��
    };
}