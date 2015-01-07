/* ヘッダファイル */
#include "MemoryManager.h"


//-------------------------------------------------------------
//!
//! @brief メモリ
//! @brief メモリ関連の名前空間
//!
//-------------------------------------------------------------
namespace Memory
{
    /*************************************************************//**
     *
     *  @brief  メモリの割り当てを行う
     *  @param  メモリサイズ
     *  @param  ファイル名
     *  @param  行数
     *  @return 割り当てたメモリのポインタ
     *
     ****************************************************************/
    void* C_MemoryManager::s_MemoryAlloc(size_t size, const char* pFileName, int32_t lineNumber)
    {
        // 割り当てるポインタ
        void* pAllocPointer = nullptr;

        // メモリリストのサイズ
        size_t memoryListSize = sizeof(S_MemoryList);

/* 汎用メモリープールを使用時 */
#ifdef USE_GENERAL_MEMORY_POOL

        if (S_MemoryList::s_pGeneralMemoryPool)
        {
            // メモリプールから割り当てを行い、
            // できた場合は各データをリストに設定してリストの分だけポインタをずらして返す
            pAllocPointer = S_MemoryList::s_pGeneralMemoryPool->PoolAlloc(size + memoryListSize);

            if (pAllocPointer)
            {
                S_MemoryList* pCurrent = static_cast<S_MemoryList*>(pAllocPointer);

                pCurrent->size_ = size;
                pCurrent->pFileName_ = pFileName;
                pCurrent->lineNumber_ = lineNumber;
                pCurrent->usePoolFlag_ = true;

                return static_cast<void*>(static_cast<char*>(pAllocPointer) + memoryListSize);
            }
        }

#endif

        // 通常のメモリ割り当てを行う
        pAllocPointer = std::malloc(size + memoryListSize);
        assert(pAllocPointer);

        // メモリリストとしてキャストし、次のポインタをnullptrに設定
        S_MemoryList* pCurrent = static_cast<S_MemoryList*>(pAllocPointer);
        pCurrent->pNext_ = nullptr;

        // 最後のリストがnullptrの場合はリストをそのまま設定
        // 違う場合は最後のポインタからたどり、先頭のポインタにリストを設定
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

        // 各データをリストに設定してリストの分だけポインタをずらして返す
        pCurrent->size_ = size;
        pCurrent->pFileName_ = pFileName;
        pCurrent->lineNumber_ = lineNumber;
        pCurrent->usePoolFlag_ = false;

        return static_cast<void*>(static_cast<char*>(pAllocPointer)+memoryListSize);
    }


    /*************************************************************//**
     *
     *  @brief  メモリの解放を行う
     *  @param  解放するメモリのポインタ
     *  @return なし
     *
     ****************************************************************/
    void C_MemoryManager::s_MemoryFree(void* pFreePointer)
    {
        if (pFreePointer == nullptr) return;

        // メモリリストのサイズ
        size_t memoryListSize = sizeof(S_MemoryList);

        // メモリリストとしてキャスト
        S_MemoryList* pCurrent = reinterpret_cast<S_MemoryList*>(static_cast<char*>(pFreePointer) - memoryListSize);

/* 汎用メモリプール使用時 */
#ifdef USE_GENERAL_MEMORY_POOL

        // プールをしている場合、プールからメモリを解放
        if (pCurrent->usePoolFlag_ == true)
        {
            if (S_MemoryList::s_pGeneralMemoryPool == nullptr) return;

            S_MemoryList::s_pGeneralMemoryPool->PoolFree(pCurrent, pCurrent->size_ + memoryListSize);
            return;
        }

#endif  

        // 最後のリストと同じポインタの場合、その次のポインタを設定
        // 違う場合は最後のポインタから一致するリストを検索し、そのリストにその次のポインタを設定
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

        // メモリを解放
        std::free(pCurrent);
    }


    /*************************************************************//**
     *
     *  @brief  解放していないメモリを出力する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_MemoryManager::s_PrintNoDeleteMemory()
    {
        for (S_MemoryList* pLast = S_MemoryList::s_pLast; pLast; pLast = pLast->pNext_)
        {
            std::cout << "[ Memory::LeakReport ] : FileName : " << pLast->pFileName_ << ", LineNo(" << pLast->lineNumber_ << ")" << ", Size(" << pLast->size_ << ")" << std::endl;
        }
    }
}