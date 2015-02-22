/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "SceneController.h"


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
    //! @brief �^�C�g���R���g���[���[
    //! @brief �^�C�g���𐧌䂷�邽�߂̃N���X
    //!
    //-------------------------------------------------------------
    class C_TitleController : public C_SceneController
    {
    public:
        C_TitleController(const std::string& rId, int32_t type);                // �R���X�g���N�^
        virtual ~C_TitleController() override;                                  // �f�X�g���N�^
    private:
        bool toRankingFlag_ = false;                                            ///< @brief �����L���O�ֈڍs�t���O
        bool toStage01Flag_ = false;                                            ///< @brief �X�e�[�W01�ֈڍs�t���O

        void DoUpdate() override;                                               // ����J�̍X�V����
        void DoDraw() override;                                                 // ����J�̕`�揈��
        bool DoMessageProcess(const Telegram& rTelegram) override;              // ����J�̃��b�Z�[�W����
    };
}
