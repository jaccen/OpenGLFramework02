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
    //! @brief �|�[�Y�R���g���[���[
    //! @brief �|�[�Y�𐧌䂷�邽�߂̃N���X
    //!
    //-------------------------------------------------------------
    class C_PauseController : public C_SceneController
    {
    public:
        C_PauseController(const std::string& rId, int32_t type);                // �R���X�g���N�^
        virtual ~C_PauseController() override;                                  // �f�X�g���N�^
    private:
        bool toTitleFlag_ = false;                                              ///< @brief �^�C�g���ֈڍs�t���O

        void DoUpdate() override;                                               // ����J�̍X�V����
        void DoDraw() override;                                                 // ����J�̕`�揈��
        bool DoMessageProcess(const Telegram& rTelegram) override;              // ����J�̃��b�Z�[�W����
    };
}
