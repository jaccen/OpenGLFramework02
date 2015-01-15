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
    class C_BasePlayer;


    //-------------------------------------------------------------
    //!
    //! @brief �v���C���[�f�X�g���C�h�X�e�[�g
    //! @brief �v���C���[�̔j�󂳂ꂽ��Ԃ�\���N���X
    //!
    //-------------------------------------------------------------
    class C_PlayerDestroyedState : public State::IC_State<C_BasePlayer>,
                                   public Singleton::C_Singleton<C_PlayerDestroyedState>
    {
        friend C_Singleton<C_PlayerDestroyedState>;                                             // �V���O���g���N���X���t�����h��
    public:
        void Enter(C_BasePlayer* pPlayer) override;                                             // �J�n����
        void Execute(C_BasePlayer* pPlayer) override;                                           // ���s����
        void Exit(C_BasePlayer* pPlayer) override;                                              // �I������
        bool MessageProcess(C_BasePlayer* pPlayer, const Telegram& rTelegram) override;         // ���b�Z�[�W����
    private:
        C_PlayerDestroyedState();                                                               // �R���X�g���N�^
        ~C_PlayerDestroyedState() override;                                                     // �f�X�g���N�^
    };
}