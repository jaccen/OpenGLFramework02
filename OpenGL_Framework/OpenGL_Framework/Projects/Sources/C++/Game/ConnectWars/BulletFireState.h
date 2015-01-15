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
    //! @brief �o���b�g�t�@�C�A�X�e�[�g
    //! @brief �e�̔��˂���Ă����Ԃ�\���N���X
    //!
    //-------------------------------------------------------------
    class C_BulletFireState : public State::IC_State<C_BaseBullet>, 
                              public Singleton::C_Singleton<C_BulletFireState>
    {
        friend C_Singleton<C_BulletFireState>;                                              // �V���O���g���N���X���t�����h��
    public:
        void Enter(C_BaseBullet* pBullet) override;                                         // �J�n����
        void Execute(C_BaseBullet* pBullet) override;                                       // ���s����
        void Exit(C_BaseBullet* pBullet) override;                                          // �I������
        bool MessageProcess(C_BaseBullet* pBullet, const Telegram& rTelegram) override;     // ���b�Z�[�W����
    private:
        C_BulletFireState();                                                                // �R���X�g���N�^
        ~C_BulletFireState() override;                                                      // �f�X�g���N�^
    };
}