/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../GameObject/Message/Telegram/Telegram.h"


//-------------------------------------------------------------
//!
//! @brief �X�e�[�g
//! @brief ��Ԋ֘A�̖��O���
//!
//-------------------------------------------------------------
namespace State
{
    //-------------------------------------------------------------
    //!
    //! @brief �X�e�[�g( �C���^�[�t�F�[�X )
    //! @brief �X�e�[�g�̃C���^�[�t�F�[�X
    //!
    //-------------------------------------------------------------
    template<class T>
    class IC_State
    {
    public:
        IC_State() = default;                                                                   //!< @brief �R���X�g���N�^
        virtual ~IC_State() = default;                                                          //!< @brief �f�X�g���N�^
        virtual void Enter(T* pEntity) = 0;                                                     //!< @brief �J�n����
        virtual void Execute(T* pEntity) = 0;                                                   //!< @brief ���s����
        virtual void Exit(T* pEntity) = 0;                                                      //!< @brief �I������
        virtual bool MessageProcess(T* pEntity,                                                 //!< @brief ���b�Z�[�W����
                                    const GameObject::Message::S_Telegram& rTelegram) = 0;
    };
}
