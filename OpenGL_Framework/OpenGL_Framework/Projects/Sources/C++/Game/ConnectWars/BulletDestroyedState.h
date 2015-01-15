/*  /* ��d�C���N���[�h�h�~ */
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
    class C_BaseBullet;


    //-------------------------------------------------------------
    //!
    //! @brief �o���b�g�f�X�g���C�h�X�e�[�g
    //! @brief �e�̔j�󂳂ꂽ��Ԃ�\���N���X
    //!
    //-------------------------------------------------------------
    class C_BulletDestroyedState : public State::IC_State<C_BaseBullet>, 
                                   public Singleton::C_Singleton<C_BulletDestroyedState>
    {
        friend C_Singleton<C_BulletDestroyedState>;                                         // �V���O���g���N���X���t�����h��
    public:
        void Enter(C_BaseBullet* pBullet) override;                                         // �J�n����
        void Execute(C_BaseBullet* pBullet) override;                                       // ���s����
        void Exit(C_BaseBullet* pBullet) override;                                          // �I������
        bool MessageProcess(C_BaseBullet* pBullet, const Telegram& rTelegram) override;     // ���b�Z�[�W����
    private:
        C_BulletDestroyedState();                                                           // �R���X�g���N�^
        ~C_BulletDestroyedState() override;                                                 // �f�X�g���N�^
    };
}