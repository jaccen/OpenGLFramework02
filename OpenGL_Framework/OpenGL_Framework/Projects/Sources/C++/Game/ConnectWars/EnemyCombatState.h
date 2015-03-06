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
    class C_BaseEnemy;


    //-------------------------------------------------------------
    //!
    //! @brief �G�l�~�[�R���o�b�g�X�e�[�g
    //! @brief �G�l�~�[�̐퓬��Ԃ�\���N���X
    //!
    //-------------------------------------------------------------
    class C_EnemyCombatState : public State::IC_State<C_BaseEnemy>,
                               public Singleton::C_Singleton<C_EnemyCombatState>
    {
        friend C_Singleton<C_EnemyCombatState>;                                                         // �V���O���g���N���X���t�����h��
    public:
        void Enter(C_BaseEnemy* pEnemy) override;                                                       // �J�n����
        void Execute(C_BaseEnemy* pEnemy) override;                                                     // ���s����
        void Exit(C_BaseEnemy* pEnemy) override;                                                        // �I������
        bool MessageProcess(C_BaseEnemy* pEnemy, const Telegram& rTelegram) override;                   // ���b�Z�[�W����
    private:
        C_EnemyCombatState();                                                                           // �R���X�g���N�^
        ~C_EnemyCombatState() override;                                                                 // �f�X�g���N�^
    };
}