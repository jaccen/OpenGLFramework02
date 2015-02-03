/* ��d�C���N���[�h�h�~ */
#pragma once


/* �}�N����` */
#define USE_GENERAL_MEMORY_POOL


/* �w�b�_�t�@�C�� */
#include "../List/MemoryList.h"
#include "../../Thread/Mutex/Mutex.h"


//-------------------------------------------------------------
//!
//! @brief ������
//! @brief �������֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Memory
{
    //-------------------------------------------------------------
    //!
    //! @brief �������}�l�[�W���[
    //! @brief �������̊Ǘ����s���N���X
    //! @brief �� ���̃w�b�_���O��USE_GENERAL_MEMORY_POOL�}�N����
    //! @brief    ��`���邱�Ƃɂ��ėp�������v�[���ɂă������̊m�ۂ��s���悤�ɂȂ�
    //!
    //-------------------------------------------------------------
    class C_MemoryManager
    {
    public:
        /* �������̊��蓖�� */
        static void* s_MemoryAlloc(size_t size, const char* pFileName, int32_t lineNumber);

        /* �������̉�����s�� */
        static void s_MemoryFree(void* pFreePointer);

        /* ������Ă��Ȃ����������o�� */
        static void s_PrintNoDeleteMemory();

        /* �������[�p�̃~���[�e�b�N�X���쐬 */
        static void s_CreateMemoryMutex();

        /* �������[�p�̃~���[�e�b�N�X��j�� */
        static void s_DestoryMemoryMutex();

        /* �������[�p�̃~���[�e�b�N�X���擾 */
        static Thread::C_Mutex* s_GetMemoryMutex();
    };
}


#pragma region new�Edelete���Z�q�̃I�[�o�[���[�h


/*************************************************************//**
 *
 *  @brief  new���Z�q�̃I�[�o�[���[�h
 *  @param  �������̃T�C�Y
 *  @return ���蓖�Ă�ꂽ�������̃|�C���^
 *
 ****************************************************************/
inline void* operator new(std::size_t size)
{
    void* pPointer = nullptr;

    if (Memory::C_MemoryManager::s_GetMemoryMutex())
    {
        Memory::C_MemoryManager::s_GetMemoryMutex()->Lock();
        pPointer = Memory::C_MemoryManager::s_MemoryAlloc(size, "Unknown", 0);
        Memory::C_MemoryManager::s_GetMemoryMutex()->Unlock();
    }
    else
    {
        pPointer = Memory::C_MemoryManager::s_MemoryAlloc(size, "Unknown", 0);
    }

    return pPointer;
}


/*************************************************************//**
 *
 *  @brief  new���Z�q�̃I�[�o�[���[�h
 *  @param  �������̃T�C�Y
 *  @param  �t�@�C����
 *  @param  �s��
 *  @return ���蓖�Ă�ꂽ�������̃|�C���^
 *
 ****************************************************************/
inline void* operator new(std::size_t size, const char* pFileName, int32_t lineNumber)
{
    void* pPointer = nullptr;

    if (Memory::C_MemoryManager::s_GetMemoryMutex())
    {
        Memory::C_MemoryManager::s_GetMemoryMutex()->Lock();
        pPointer = Memory::C_MemoryManager::s_MemoryAlloc(size, pFileName, lineNumber);
        Memory::C_MemoryManager::s_GetMemoryMutex()->Unlock();
    }
    else
    {
        pPointer = Memory::C_MemoryManager::s_MemoryAlloc(size, pFileName, lineNumber);
    }

    return pPointer;
}


/*************************************************************//**
 *
 *  @brief  new[]���Z�q�̃I�[�o�[���[�h
 *  @param  �������̃T�C�Y
 *  @param  �t�@�C����
 *  @param  �s��
 *  @return ���蓖�Ă�ꂽ�������̃|�C���^
 *
 ****************************************************************/
inline void* operator new[](std::size_t size, const char* pFileName, int32_t lineNumber)
{
    void* pPointer = nullptr;

    if (Memory::C_MemoryManager::s_GetMemoryMutex())
    {
        Memory::C_MemoryManager::s_GetMemoryMutex()->Lock();
        pPointer = ::operator new(size, pFileName, lineNumber);
        Memory::C_MemoryManager::s_GetMemoryMutex()->Unlock();
    }
    else
    {
        pPointer = ::operator new(size, pFileName, lineNumber);
    }

    return pPointer;
}


/*************************************************************//**
 *
 *  @brief  delete���Z�q�̃I�[�o�[���[�h
 *  @param  ������郁�����̃|�C���^
 *  @return �Ȃ�
 *
 ****************************************************************/
inline void operator delete(void* pDeletePointer) 
{
    if (Memory::C_MemoryManager::s_GetMemoryMutex())
    {
        Memory::C_MemoryManager::s_GetMemoryMutex()->Lock();
        Memory::C_MemoryManager::s_MemoryFree(pDeletePointer);
        Memory::C_MemoryManager::s_GetMemoryMutex()->Unlock();
    }
    else
    {
        Memory::C_MemoryManager::s_MemoryFree(pDeletePointer);
    }
}


/*************************************************************//**
 *
 *  @brief  delete[]���Z�q�̃I�[�o�[���[�h
 *  @param  ������郁�����̃|�C���^
 *  @return �Ȃ�
 *
 ****************************************************************/
inline void operator delete[](void* pDeletePointer)
{
    if (Memory::C_MemoryManager::s_GetMemoryMutex())
    {
        Memory::C_MemoryManager::s_GetMemoryMutex()->Lock();
        ::operator delete(pDeletePointer);
        Memory::C_MemoryManager::s_GetMemoryMutex()->Unlock();
    }
    else
    {
        ::operator delete(pDeletePointer);
    }
}


/*************************************************************//**
 *
 *  @brief  delete���Z�q�̃I�[�o�[���[�h( ��O���p )
 *  @param  ������郁�����̃|�C���^
 *  @param  �t�@�C����
 *  @param  �s��
 *  @return �Ȃ�
 *
 ****************************************************************/
inline void operator delete(void* pDeletePointer, const char* pFileName, int32_t lineNumber) 
{
    if (Memory::C_MemoryManager::s_GetMemoryMutex())
    {
        Memory::C_MemoryManager::s_GetMemoryMutex()->Lock();
        Memory::C_MemoryManager::s_MemoryFree(pDeletePointer);
        Memory::C_MemoryManager::s_GetMemoryMutex()->Unlock();
    }
    else
    {
        Memory::C_MemoryManager::s_MemoryFree(pDeletePointer);
    }
}


/*************************************************************//**
 *
 *  @brief  delete[]���Z�q�̃I�[�o�[���[�h( ��O���p )
 *  @param  ������郁�����̃|�C���^
 *  @param  �t�@�C����
 *  @param  �s��
 *  @return �Ȃ�
 *
 ****************************************************************/
inline void operator delete[](void* pDeletePointer, const char* pFileName, int32_t lineNumber)
{
    if (Memory::C_MemoryManager::s_GetMemoryMutex())
    {
        Memory::C_MemoryManager::s_GetMemoryMutex()->Lock();
        ::operator delete(pDeletePointer);
        Memory::C_MemoryManager::s_GetMemoryMutex()->Unlock();
    }
    else
    {
        ::operator delete(pDeletePointer);
    }

}


#pragma endregion