#include "Thread.h"


//-------------------------------------------------------------
//!
//! @brief �X���b�h
//! @brief �X���b�h�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Thread
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_Thread::C_Thread()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_Thread::~C_Thread()
    {
        if (pThreadData_) Join();
    }


    /*************************************************************//**
     *
     *  @brief  �X���b�h���쐬����
     *  @param  ���s����֐�
     *  @param  ���O
     *  @param  �֐��ɓn���f�[�^
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_Thread::Create(ThreadFunction pThreadFunction,
                          const std::string& rName,
                          void* pFunctionData)
    {
        assert(pThreadData_ == nullptr);

        pThreadData_ = SDL_CreateThread(pThreadFunction, rName.c_str(), pFunctionData);
    }


    /*************************************************************//**
     *
     *  @brief  �X���b�h�̏I���̑ҋ@���s��
     *  @param  �Ȃ�
     *  @return ���s�����֐��̖߂�l
     *
     ****************************************************************/
    int32_t C_Thread::Join()
    {
        assert(pThreadData_);

        int32_t functionReturnValue = 0;
        ::SDL_WaitThread(pThreadData_, &functionReturnValue);
        pThreadData_ = nullptr;

        return functionReturnValue;
    }


    /*************************************************************//**
     *
     *  @brief  �X���b�h�̊Ǘ��̕������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_Thread::Detach()
    {
        assert(pThreadData_);

        ::SDL_DetachThread(pThreadData_);
        pThreadData_ = nullptr;
    }
}