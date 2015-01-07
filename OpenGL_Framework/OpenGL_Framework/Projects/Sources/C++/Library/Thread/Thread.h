/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include <SDL_thread.h>


//-------------------------------------------------------------
//!
//! @brief �X���b�h
//! @brief �X���b�h�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Thread
{
    /* �ʖ� */
    using ThreadData = SDL_Thread;                                  // ThreadData�^
    using ThreadFunction = SDL_ThreadFunction;                      // ThreadFunction�^


    //-------------------------------------------------------------
    //!
    //! @brief �X���b�h
    //! @brief �X���b�h��\���N���X
    //!
    //-------------------------------------------------------------
    class C_Thread
    {
    public:
        C_Thread();                                                 // �R���X�g���N�^
        ~C_Thread();                                                // �f�X�g���N�^
        void Create(ThreadFunction pThreadFunction,                 // �X���b�h�̍쐬
                    const std::string& rName, 
                    void* pFunctionData = nullptr);
        int32_t Join();                                             // �X���b�h�̏I���̑ҋ@
        void Detach();                                              // �X���b�h�̊Ǘ������
    private:
        ThreadData* pThreadData_ = nullptr;                         ///< @brief �X���b�h���
    };
}