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
    //! @brief �Q�[���R���g���[���[
    //! @brief �Q�[���𐧌䂷�邽�߂̃N���X
    //!
    //-------------------------------------------------------------
    class C_GameController : public C_SceneController
    {
    public:
        C_GameController(const std::string& rId, int32_t type);                 // �R���X�g���N�^
        virtual ~C_GameController() override;                                   // �f�X�g���N�^
    protected:
        void DoUpdate() override;                                               // ����J�̍X�V����
        void DoDraw() override;                                                 // ����J�̕`�揈��
        bool DoMessageProcess(const Telegram& rTelegram) override;              // ����J�̃��b�Z�[�W����
    };
}
