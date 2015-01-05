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
        using State = IC_State<T>;                                                                      // State�^

        C_StateMachine(T* pOwner, State* pCurrentState = nullptr, State* pGlobalState = nullptr);       // �R���X�g���N�^
        virtual ~C_StateMachine();                                                                      // �f�X�g���N�^
        void Update() const;                                                                            // �X�V����
        bool MessageProcess(const GameObject::Message::S_Telegram& rTelegram) const;                    // ���b�Z�[�W����
        void ChangeState(State* pNewState);                                                             // �V�����X�e�[�g�ɕύX
        void RevertToPreviousState();                                                                   // �ȑO�̃X�e�[�g�ɕύX
        bool CheckCurrentState(const State& rState) const;                                              // ���݂̃X�e�[�g���m�F
        State* GetCurrentState() const;                                                                 // ���݂̃X�e�[�g���擾
        State* GetPreviousState() const;                                                                // �ȑO�̃X�e�[�g���擾
        State* GetGlobalState() const;                                                                  // �O���[�o���X�e�[�g���擾
        void SetCurrentState(State* pCurrentState);                                                     // ���݂̃X�e�[�g��ݒ�
        void SetPreviousState(State* pPreviousState);                                                   // �ȑO�̃X�e�[�g��ݒ�
        void SetGlobalState(State* pGlobalState);                                                       // �O���[�o���X�e�[�g��ݒ�
    private:
        T* pOwner_ = nullptr;                                                                           ///< @brief �I�[�i�[
        State* pCurrentState_ = nullptr;                                                                ///< @brief ���݂̃X�e�[�g
        State* pPreviousState_ = nullptr;                                                               ///< @brief �ȑO�̃X�e�[�g
        State* pGlobalState_ = nullptr;                                                                 ///< @brief �O���[�o���X�e�[�g
    };
}


/* ���� */
#include "StateMachineImpl.h"
