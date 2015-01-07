/* 二重インクルード防止 */
#pragma once


/* マクロ定義 */
#define USE_GENERAL_MEMORY_POOL


/* ヘッダファイル */
#include "../List/MemoryList.h"


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
    //! @brief メモリマネージャー
    //! @brief メモリの管理を行うクラス
    //! @brief ※ このヘッダより前でUSE_GENERAL_MEMORY_POOLマクロを
    //! @brief    定義することにより汎用メモリプールにてメモリの確保を行うようになる
    //!
    //-------------------------------------------------------------
    class C_MemoryManager
    {
    public:
        /* メモリの割り当て */
        static void* s_MemoryAlloc(size_t size, const char* pFileName, int32_t lineNumber);

        /* メモリの解放を行う */
        static void s_MemoryFree(void* pFreePointer);

        /* 解放していないメモリを出力 */
        static void s_PrintNoDeleteMemory();
    };
}


#pragma region new・delete演算子のオーバーロード


/*************************************************************//**
 *
 *  @brief  new演算子のオーバーロード
 *  @param  メモリのサイズ
 *  @return 割り当てられたメモリのポインタ
 *
 ****************************************************************/
inline void* operator new(std::size_t size)
{
    return Memory::C_MemoryManager::s_MemoryAlloc(size, "Unknown", 0);
}


/*************************************************************//**
 *
 *  @brief  new演算子のオーバーロード
 *  @param  メモリのサイズ
 *  @param  ファイル名
 *  @param  行数
 *  @return 割り当てられたメモリのポインタ
 *
 ****************************************************************/
inline void* operator new(std::size_t size, const char* pFileName, int32_t lineNumber)
{
    return Memory::C_MemoryManager::s_MemoryAlloc(size, pFileName, lineNumber);
}


/*************************************************************//**
 *
 *  @brief  new[]演算子のオーバーロード
 *  @param  メモリのサイズ
 *  @param  ファイル名
 *  @param  行数
 *  @return 割り当てられたメモリのポインタ
 *
 ****************************************************************/
inline void* operator new[](std::size_t size, const char* pFileName, int32_t lineNumber)
{
    return ::operator new(size, pFileName, lineNumber);
}


/*************************************************************//**
 *
 *  @brief  delete演算子のオーバーロード
 *  @param  解放するメモリのポインタ
 *  @return なし
 *
 ****************************************************************/
inline void operator delete(void* pDeletePointer) 
{
    Memory::C_MemoryManager::s_MemoryFree(pDeletePointer);
}


/*************************************************************//**
 *
 *  @brief  delete[]演算子のオーバーロード
 *  @param  解放するメモリのポインタ
 *  @return なし
 *
 ****************************************************************/
inline void operator delete[](void* pDeletePointer)
{
    ::operator delete(pDeletePointer);
}


/*************************************************************//**
 *
 *  @brief  delete演算子のオーバーロード( 例外時用 )
 *  @param  解放するメモリのポインタ
 *  @param  ファイル名
 *  @param  行数
 *  @return なし
 *
 ****************************************************************/
inline void operator delete(void* pDeletePointer, const char* pFileName, int32_t lineNumber) 
{
    Memory::C_MemoryManager::s_MemoryFree(pDeletePointer);
}


/*************************************************************//**
 *
 *  @brief  delete[]演算子のオーバーロード( 例外時用 )
 *  @param  解放するメモリのポインタ
 *  @param  ファイル名
 *  @param  行数
 *  @return なし
 *
 ****************************************************************/
inline void operator delete[](void* pDeletePointer, const char* pFileName, int32_t lineNumber)
{
    ::operator delete(pDeletePointer);
}


#pragma endregion