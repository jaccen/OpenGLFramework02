/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectWarsDefine.h"
#include "../../Library/State/State.h"
#include "../../Library/Singleton/Singleton.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"


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
    //! @brief �I�v�V�����I�D���N���b�V���X�e�[�g
    //! @brief �I�v�V�����̎�����Ԃ�\���N���X
    //!
    //-------------------------------------------------------------
    class C_OptionOwnCrashState : public State::IC_State<C_BaseOption>,
                                  public Singleton::C_Singleton<C_OptionOwnCrashState>
    {
        friend C_Singleton<C_OptionOwnCrashState>;                                          // �V���O���g���N���X���t�����h��
    public:
        void Enter(C_BaseOption* pOption) override;                                         // �J�n����
        void Execute(C_BaseOption* pOption) override;                                       // ���s����
        void Exit(C_BaseOption* pOption) override;                                          // �I������
        bool MessageProcess(C_BaseOption* pOption, const Telegram& rTelegram) override;     // ���b�Z�[�W����
    private:
        C_OptionOwnCrashState();                                                            // �R���X�g���N�^
        ~C_OptionOwnCrashState() override;                                                  // �f�X�g���N�^
    };
}