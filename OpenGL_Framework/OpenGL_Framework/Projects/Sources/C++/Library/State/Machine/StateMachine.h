/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../State.h"
#include "../../GameObject/Message/Telegram/Telegram.h"


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
    //! @brief �X�e�[�g�}�V�[��
    //! @brief ��ԑJ�ڂ��Ǘ�����N���X
    //!
    //-------------------------------------------------------------
    template<typename T>
    class C_StateMachine
    {
    public:
         /* �ʖ� */
        using StatePtr = IC_State<T>*;                                                                  // StatePtr�^

        C_StateMachine(T* pOwner);																		// �R���X�g���N�^
        virtual ~C_StateMachine();                                                                      // �f�X�g���N�^
        void Update() const;                                                                            // �X�V����
        bool MessageProcess(const GameObject::Message::S_Telegram& rTelegram) const;                    // ���b�Z�[�W����
        void ChangeState(StatePtr pNewState);															// �V�����X�e�[�g�ɕύX
        void RevertToPreviousState();                                                                   // �ȑO�̃X�e�[�g�ɕύX
		bool CheckCurrentState(StatePtr pState) const;													// ���݂̃X�e�[�g���m�F
        StatePtr GetCurrentState() const;																// ���݂̃X�e�[�g���擾
        StatePtr GetPreviousState() const;																// �ȑO�̃X�e�[�g���擾
        StatePtr GetGlobalState() const;																// �O���[�o���X�e�[�g���擾
        void SetCurrentState(StatePtr pCurrentState);													// ���݂̃X�e�[�g��ݒ�
        void SetPreviousState(StatePtr pPreviousState);													// �ȑO�̃X�e�[�g��ݒ�
        void SetGlobalState(StatePtr pGlobalState);														// �O���[�o���X�e�[�g��ݒ�
    private:
        T* pOwner_ = nullptr;                                                                           ///< @brief �I�[�i�[
        StatePtr pCurrentState_ = nullptr;																///< @brief ���݂̃X�e�[�g
        StatePtr pPreviousState_ = nullptr;																///< @brief �ȑO�̃X�e�[�g
        StatePtr pGlobalState_ = nullptr;																///< @brief �O���[�o���X�e�[�g
    };
}


/* ���� */
#include "StateMachineImpl.h"
