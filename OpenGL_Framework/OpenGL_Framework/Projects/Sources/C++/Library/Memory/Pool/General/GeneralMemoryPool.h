/* 二重インクルード防止 */ 
#pragma once


/* ヘッダファイル */
#include "../MemoryPool.h"


//-------------------------------------------------------------
//!
//! @brief メモリ
//! @brief メモリ関連の名前空間
//!
//-------------------------------------------------------------
namespace Memory
{
    /** 各バイトを表す構造体 */
    struct S_Byte32 { char datas_[32]; };                           //!< @brief 32バイト
    struct S_Byte64 { char datas_[64]; };                           //!< @brief 64バイト
    struct S_Byte128{ char datas_[128]; };                          //!< @brief 128バイト
    struct S_Byte256{ char datas_[256]; };                          //!< @brief 256バイト


    //-------------------------------------------------------------
    //!
    //! @brief ジェネラルメモリプール
    //! @brief 汎用的なメモリプールを表すクラス
    //!
    //-------------------------------------------------------------
    class C_GeneralMemoryPool
    {
    public:
        C_GeneralMemoryPool() = default;                            //!< @brief デフォルトコンストラクタ
        ~C_GeneralMemoryPool() = default;                           //!< @brief デフォルトコンストラクタ

        /*************************************************************//**
         *
         *  @brief  プールからメモリの割り当てを行う
         *  @param  メモリのサイズ
         *  @return 割り当てられたメモリのポインタ
         *
         ****************************************************************/
        void* PoolAlloc(uint32_t size)
        {
            void* pAllocPointer = nullptr;

            if (size < 32)  pAllocPointer = poolByte32_.Alloc();
            else if (size < 64)  pAllocPointer = poolByte64_.Alloc();
            else if (size < 128) pAllocPointer = poolByte128_.Alloc();
            else if (size < 256) pAllocPointer = poolByte256_.Alloc();

            return pAllocPointer;
        }


        /*************************************************************//**
         *
         *  @brief  プールからメモリの解放を行う
         *  @param  解放するメモリのポインタ
         *  @param  メモリのサイズ
         *  @return なし
         *
         ****************************************************************/
        void PoolFree(void* pFreePointer, uint32_t size)
        {
            if (size < 32)  poolByte32_.Free(pFreePointer);
            else if (size < 64)  poolByte64_.Free(pFreePointer);
            else if (size < 128) poolByte128_.Free(pFreePointer);
            else if (size < 256) poolByte256_.Free(pFreePointer);
        }
    private:
        C_MemoryPool<S_Byte32> poolByte32_;                     ///< @brief 32バイトメモリプール
        C_MemoryPool<S_Byte64> poolByte64_;                     ///< @brief 64バイトメモリプール
        C_MemoryPool<S_Byte128> poolByte128_;                   ///< @brief 128バイトメモリプール
        C_MemoryPool<S_Byte256> poolByte256_;                   ///< @brief 256バイトメモリプール
    };
}