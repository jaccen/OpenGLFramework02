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
    //! @brief �����L���O�R���g���[���[
    //! @brief �����L���O�𐧌䂷�邽�߂̃N���X
    //!
    //-------------------------------------------------------------
    class C_RankingController : public C_SceneController
    {
    public:
        C_RankingController(const std::string& rId, int32_t type);              // �R���X�g���N�^
        virtual ~C_RankingController() override;                                // �f�X�g���N�^
    private:
        bool toTitleFlag_ = false;                                              ///< @brief �^�C�g���ֈڍs�t���O

        void DoUpdate() override;                                               // ����J�̍X�V����
        void DoDraw() override;                                                 // ����J�̕`�揈��
        bool DoMessageProcess(const Telegram& rTelegram) override;              // ����J�̃��b�Z�[�W����
    };
}
