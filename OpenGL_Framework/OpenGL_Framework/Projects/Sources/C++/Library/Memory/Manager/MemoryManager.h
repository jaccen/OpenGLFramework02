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
        /*************************************************************//**
         *
         *  @brief  �������̊��蓖�Ă��s��
         *  @param  �������T�C�Y
         *  @param  �t�@�C����
         *  @param  �s��
         *  @return ���蓖�Ă��������̃|�C���^
         *
         ****************************************************************/
        static void* s_MemoryAlloc(size_t size, const char* pFileName, int32_t lineNumber)
        {
            // ���蓖�Ă�|�C���^
            void* pAllocPointer = nullptr;

            // ���������X�g�̃T�C�Y
            size_t memoryListSize = sizeof(S_MemoryList);

/* �ėp�������[�v�[�����g�p�� */
#ifdef USE_GENERAL_MEMORY_POOL

            if (S_MemoryList::s_pGeneralMemoryPool)
            {
                // �������v�[�����犄�蓖�Ă��s���A
                // �ł����ꍇ�͊e�f�[�^�����X�g�ɐݒ肵�ă��X�g�̕������|�C���^�����炵�ĕԂ�
                pAllocPointer = S_MemoryList::s_pGeneralMemoryPool->PoolAlloc(size + memoryListSize);

                if (pAllocPointer)
                {
                    S_MemoryList* pCurrent = static_cast<S_MemoryList*>(pAllocPointer);

                    pCurrent->size_ = size;
                    pCurrent->pFileName_ = pFileName;
                    pCurrent->lineNumber_ = lineNumber;
                    pCurrent->usePoolFlag_ = true;

                    return static_cast<void*>(static_cast<char*>(pAllocPointer)+memoryListSize);
                }
            }

#endif

            // �ʏ�̃��������蓖�Ă��s��
            pAllocPointer = std::malloc(size + memoryListSize);
            assert(pAllocPointer);

            // ���������X�g�Ƃ��ăL���X�g���A���̃|�C���^��nullptr�ɐݒ�
            S_MemoryList* pCurrent = static_cast<S_MemoryList*>(pAllocPointer);
            pCurrent->pNext_ = nullptr;

            // �Ō�̃��X�g��nullptr�̏ꍇ�̓��X�g�����̂܂ܐݒ�
            // �Ⴄ�ꍇ�͍Ō�̃|�C���^���炽�ǂ�A�擪�̃|�C���^�Ƀ��X�g��ݒ�
            if (S_MemoryList::s_pLast == nullptr)
            {
                S_MemoryList::s_pLast = pCurrent;
            }
            else
            {
                S_MemoryList* pLast = S_MemoryList::s_pLast;

                while (pLast->pNext_) pLast = pLast->pNext_;
                pLast->pNext_ = pCurrent;
            }

            // �e�f�[�^�����X�g�ɐݒ肵�ă��X�g�̕������|�C���^�����炵�ĕԂ�
            pCurrent->size_ = size;
            pCurrent->pFileName_ = pFileName;
            pCurrent->lineNumber_ = lineNumber;
            pCurrent->usePoolFlag_ = false;

            return static_cast<void*>(static_cast<char*>(pAllocPointer)+memoryListSize);
        }


        /*************************************************************//**
         *
         *  @brief  �������̉�����s��
         *  @param  ������郁�����̃|�C���^
         *  @return �Ȃ�
         *
         ****************************************************************/
        static void s_MemoryFree(void* pFreePointer)
        {
            // ���������X�g�̃T�C�Y
            size_t memoryListSize = sizeof(S_MemoryList);

            // ���������X�g�Ƃ��ăL���X�g
            S_MemoryList* pCurrent = reinterpret_cast<S_MemoryList*>(static_cast<char*>(pFreePointer)-memoryListSize);

/* �ėp�������v�[���g�p�� */
#ifdef USE_GENERAL_MEMORY_POOL

            // �v�[�������Ă���ꍇ�A�v�[�����烁���������
            if (pCurrent->usePoolFlag_ == true)
            {
                if (S_MemoryList::s_pGeneralMemoryPool == nullptr) return;

                S_MemoryList::s_pGeneralMemoryPool->PoolFree(pCurrent, pCurrent->size_ + memoryListSize);
                return;
            }

#endif

            // �Ō�̃��X�g�Ɠ����|�C���^�̏ꍇ�A���̎��̃|�C���^��ݒ�
            // �Ⴄ�ꍇ�͍Ō�̃|�C���^�����v���郊�X�g���������A���̃��X�g�ɂ��̎��̃|�C���^��ݒ�
            if (S_MemoryList::s_pLast == pCurrent)
            {
                S_MemoryList::s_pLast = pCurrent->pNext_;
            }
            else
            {
                for (S_MemoryList* pLast = S_MemoryList::s_pLast; pLast; pLast = pLast->pNext_)
                {
                    if (pLast->pNext_ == pCurrent) pLast->pNext_ = pCurrent->pNext_;
                }
            }

            // �����������
            std::free(pCurrent);
        }


        /*************************************************************//**
         *
         *  @brief  ���������[�N���Ȃ����m�F���A����ꍇ�̓��O�ɕ\��
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        static void s_LeakReport()
        {
            for (S_MemoryList* pLast = S_MemoryList::s_pLast; pLast; pLast = pLast->pNext_)
            {
                std::cout << "[ Memory::LeakReport ] : FileName : " << pLast->pFileName_ << ", LineNo(" << pLast->lineNumber_ << ")" << ", Size(" << pLast->size_ << ")" << std::endl;
            }
        }
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