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
    //! @brief �G�l�~�[�A�h�x���g�X�e�[�g
    //! @brief �G�l�~�[�̏o����Ԃ�\���N���X
    //!
    //-------------------------------------------------------------
    class C_EnemyAdventState : public State::IC_State<C_BaseEnemy>,
                               public Singleton::C_Singleton<C_EnemyAdventState>
    {
        friend C_Singleton<C_EnemyAdventState>;                                                         // �V���O���g���N���X���t�����h��
    public:
        void Enter(C_BaseEnemy* pEnemy) override;                                                       // �J�n����
        void Execute(C_BaseEnemy* pEnemy) override;                                                     // ���s����
        void Exit(C_BaseEnemy* pEnemy) override;                                                        // �I������
        bool MessageProcess(C_BaseEnemy* pEnemy, const Telegram& rTelegram) override;                   // ���b�Z�[�W����
    private:
        C_EnemyAdventState();                                                                           // �R���X�g���N�^
        ~C_EnemyAdventState() override;                                                                 // �f�X�g���N�^
    };
}