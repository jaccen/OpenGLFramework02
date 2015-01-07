/* ��d�C���N���[�h�h�~ */
#pragma once


/* �}�N����` */
#define USE_GENERAL_MEMORY_POOL


/* �w�b�_�t�@�C�� */
#include "../List/MemoryList.h"


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
    return Memory::C_MemoryManager::s_MemoryAlloc(size, "Unknown", 0);
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
    return Memory::C_MemoryManager::s_MemoryAlloc(size, pFileName, lineNumber);
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
    return ::operator new(size, pFileName, lineNumber);
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
    Memory::C_MemoryManager::s_MemoryFree(pDeletePointer);
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
    ::operator delete(pDeletePointer);
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
    Memory::C_MemoryManager::s_MemoryFree(pDeletePointer);
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
    ::operator delete(pDeletePointer);
}


#pragma endregion