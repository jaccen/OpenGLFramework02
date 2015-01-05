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
    //! @brief �v���C���[�A�h�x���g�X�e�[�g
    //! @brief �v���C���[�̏o����Ԃ�\���N���X
    //!
    //-------------------------------------------------------------
    class C_PlayerAdventState : public State::IC_State<C_BasePlayer>,
                                public Singleton::C_Singleton<C_PlayerAdventState>
    {
        friend C_Singleton<C_PlayerAdventState>;                                                        // �V���O���g���N���X���t�����h��
    public:
        void Enter(C_BasePlayer* pPlayer) override;                                                     //!< @brief �J�n����
        void Execute(C_BasePlayer* pPlayer) override;                                                   //!< @brief ���s����
        void Exit(C_BasePlayer* pPlayer) override;                                                      //!< @brief �I������
        bool MessageProcess(C_BasePlayer* pPlayer, const Telegram& rTelegram) override;                 //!< @brief ���b�Z�[�W����
    private:
        C_PlayerAdventState();                                                                          // �R���X�g���N�^
        ~C_PlayerAdventState() override;                                                                // �f�X�g���N�^
    };
}