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
    class C_BasePlayer;


    //-------------------------------------------------------------
    //!
    //! @brief �v���C���[�{���`���[�W�X�e�[�g
    //! @brief �v���C���[�̃{�����`���[�W���Ă����Ԃ�\���N���X
    //!
    //-------------------------------------------------------------
    class C_PlayerBombChargeState : public State::IC_State<C_BasePlayer>,
                                    public Singleton::C_Singleton<C_PlayerBombChargeState>
    {
        friend C_Singleton<C_PlayerBombChargeState>;                                                // �V���O���g���N���X���t�����h��
    public:
        void Enter(C_BasePlayer* pPlayer) override;                                                 // �J�n����
        void Execute(C_BasePlayer* pPlayer) override;                                               // ���s����
        void Exit(C_BasePlayer* pPlayer) override;                                                  // �I������
        bool MessageProcess(C_BasePlayer* pPlayer, const Telegram& rTelegram) override;             // ���b�Z�[�W����
    private:
        Timer::C_FrameCounter frameCounter_;                                                        ///< @brief �t���[���J�E���^�[

        C_PlayerBombChargeState();                                                                  // �R���X�g���N�^
        ~C_PlayerBombChargeState() override;                                                        // �f�X�g���N�^
    };
}