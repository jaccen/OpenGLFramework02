/* 二重インクルード防止 */
#pragma once


//-------------------------------------------------------------
//!
//! @brief メモリ
//! @brief メモリ関連の名前空間
//!
//-------------------------------------------------------------
namespace Memory
{
    //-------------------------------------------------------------
    //!
    //! @brief メモリプール
    //! @brief 基本的なメモリプールを表すクラス
    //!
    //-------------------------------------------------------------
    template<typename T, size_t DefaultExpandNumber = 1000>
    class C_MemoryPool
    {
    public:
        /* 別名 */
        using MemoryPtr = C_MemoryPool<T, DefaultExpandNumber>*;        // MemoryPtr型


        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_MemoryPool()
        {
            // メモリを拡張
            ExpandFreeList(DefaultExpandNumber);
        }

        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        ~C_MemoryPool()
        {
            // 全てのメモリを解放
            for (MemoryPtr pNext = this->pNext_; pNext != nullptr; pNext = this->pNext_)
            {
                pNext_ = pNext_->pNext_;
                std::free(pNext);
            }
        }

        /*************************************************************//**
         *
         *  @brief  メモリの割り当てを行う
         *  @param  なし
         *  @return 割り当てたメモリのポインタ
         *
         ****************************************************************/
        void* Alloc()
        {
            // メモリが足りない場合はさらにメモリを拡張
            if (pNext_ == nullptr)
            {
                ExpandFreeList(DefaultExpandNumber);
            }

            // 次のポインタを設定
            MemoryPtr pHead = pNext_;
            pNext_ = pHead->pNext_;

            return pHead;
        }

        /*************************************************************//**
         *
         *  @brief  メモリの解放を行う
         *  @param  解放するメモリのポインタ
         *  @return なし
         *
         ****************************************************************/
        void Free(void* pFreePointer)
        {
            assert(pFreePointer);

            // 解放するポインタを次のポインタとして設定
            MemoryPtr pHead = static_cast<MemoryPtr>(pFreePointer);
            pHead->pNext_ = pNext_;
            pNext_ = pHead;
        }

    private:
        MemoryPtr pNext_ = nullptr;                                 ///< @brief 次のメモリのポインタ

        /*************************************************************//**
         *
         *  @brief  メモリの拡張を行う
         *  @param  メモリ拡張数
         *  @return なし
         *
         ****************************************************************/
        void ExpandFreeList(size_t expandNumber)
        {
            assert(expandNumber > 0);

            // サイズを計算
            size_t size = (sizeof(T) > sizeof(MemoryPtr) ? sizeof(T) : sizeof(MemoryPtr));

            // メモリを割り当て、次のポインタに設定
            MemoryPtr pRunner = reinterpret_cast<MemoryPtr>(std::malloc(size));
            pNext_ = pRunner;

            // 残りの拡張数分だけメモリを拡張
            for (size_t i = 0; i < expandNumber; ++i)
            {
                pRunner->pNext_ = reinterpret_cast<MemoryPtr>(std::malloc(size));
                pRunner = pRunner->pNext_;
            }

            // 一番最後のメモリにnullptrを設定
            pRunner->pNext_ = nullptr;
        }
    };
}