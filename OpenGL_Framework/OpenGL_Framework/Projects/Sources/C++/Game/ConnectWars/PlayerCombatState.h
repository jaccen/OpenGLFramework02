/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "ConnectWarsDefine.h"
#include "../../Library/State/State.h"
#include "../../Library/Singleton/Singleton.h"
#include "../../Library/GameObject/Message/Telegram/Telegram.h"


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
    //! @brief �v���C���[�R���o�b�g�X�e�[�g
    //! @brief �v���C���[�̐퓬��Ԃ�\���N���X
    //!
    //-------------------------------------------------------------
    class C_PlayerCombatState : public State::IC_State<C_BasePlayer>,
                                public Singleton::C_Singleton<C_PlayerCombatState>
    {
        friend C_Singleton<C_PlayerCombatState>;                                                        // �V���O���g���N���X���t�����h��
    public:
        void Enter(C_BasePlayer* pPlayer) override;                                                     //!< @brief �J�n����
        void Execute(C_BasePlayer* pPlayer) override;                                                   //!< @brief ���s����
        void Exit(C_BasePlayer* pPlayer) override;                                                      //!< @brief �I������
        bool MessageProcess(C_BasePlayer* pPlayer, const Telegram& rTelegram) override;                 //!< @brief ���b�Z�[�W����
    private:
        C_PlayerCombatState();                                                                          // �R���X�g���N�^
        ~C_PlayerCombatState() override;                                                                // �f�X�g���N�^
    };
}