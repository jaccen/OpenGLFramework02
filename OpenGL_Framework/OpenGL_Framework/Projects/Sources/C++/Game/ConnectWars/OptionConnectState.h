/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectWarsDefine.h"
#include "../../Library/State/State.h"
#include "../../Library/Singleton/Singleton.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* �O���錾 */
    class C_BaseOption;


    //-------------------------------------------------------------
    //!
    //! @brief �I�v�V�����R�l�N�g�X�e�[�g
    //! @brief �I�v�V�����̘A����Ԃ�\���N���X
    //!
    //-------------------------------------------------------------
    class C_OptionConnectState : public State::IC_State<C_BaseOption>,
                                 public Singleton::C_Singleton<C_OptionConnectState>
    {
        friend C_Singleton<C_OptionConnectState>;                                           // �V���O���g���N���X���t�����h��
    public:
        void Enter(C_BaseOption* pOption) override;                                         // �J�n����
        void Execute(C_BaseOption* pOption) override;                                       // ���s����
        void Exit(C_BaseOption* pOption) override;                                          // �I������
        bool MessageProcess(C_BaseOption* pOption, const Telegram& rTelegram) override;     // ���b�Z�[�W����
    private:
        C_OptionConnectState();                                                             // �R���X�g���N�^
        ~C_OptionConnectState() override;                                                   // �f�X�g���N�^
    };
}