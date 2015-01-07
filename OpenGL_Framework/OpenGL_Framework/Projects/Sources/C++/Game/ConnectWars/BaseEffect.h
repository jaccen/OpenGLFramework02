/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectWarsDefine.h"
#include "../../Library/GameObject/GameObject.h"


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
    //! @brief �x�[�X�G�t�F�N�g
    //! @brief �G�t�F�N�g�̊��N���X
    //!
    //-------------------------------------------------------------
    class C_BaseEffect : public GameObject::C_GameObject
    {
    public:
        C_BaseEffect(const std::string& rId, int32_t type);                     // �R���X�g���N�^
        virtual ~C_BaseEffect() override;                                       // �f�X�g���N�^
        bool Update() override;                                                 // �X�V����
        void Draw() override;                                                   // �`�揈��
        bool MessageProcess(const Telegram& rTelegram) override;                // ���b�Z�[�W����
    protected:
        virtual void DoUpdate() = 0;                                            // ����J�̍X�V����
        virtual void DoDraw() = 0;                                              // ����J�̕`�揈��
        virtual bool DoMessageProcess(const Telegram& rTelegram) = 0;           // ����J�̃��b�Z�[�W����
    };
}
