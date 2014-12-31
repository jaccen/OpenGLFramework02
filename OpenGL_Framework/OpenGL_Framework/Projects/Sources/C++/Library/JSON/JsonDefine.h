/* 二重インクルード防止 */
#pragma once


#include <memory>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <cstdio>
#include <deque>
#include <unordered_map>
#include <fstream>
#include <cstdint>
#include <cassert>
#include <tuple>
#include <memory>
#include <ostream>
#include <iomanip>


//-------------------------------------------------------------
///
/// @brief JSON
/// @brief JSON関連のクラスや関数などに付ける名前空間
///
//-------------------------------------------------------------
namespace JSON
{
    /** データの種類 */
    enum class ecDataType
    {
		TYPE_INTEGER,                   ///< @brief 整数
		TYPE_REAL,                      ///< @brief 実数
		TYPE_BOOLEAN,                   ///< @brief bool値
		TYPE_STRING,                    ///< @brief 文字列
		TYPE_ARRAY,                     ///< @brief 配列
		TYPE_OBJECT,                    ///< @brief オブジェクト( 連想配列 )
		TYPE_NULL,                      ///< @brief null値
	};

    //-------------------------------------------------------------
    //!
    //! @brief デフォルトアロック
    //! @brief デフォルトのメモリ割り当て構造体
    //!
    //-------------------------------------------------------------
    struct S_DefaultAlloc
    {
        /*************************************************************//**
         *
         *  @brief  関数呼び出し演算子のオーバーロード
         *  @param  メモリのサイズ
         *
         ****************************************************************/
        void* operator()(std::size_t size)
        {
            return Memory::C_MemoryManager::s_MemoryAlloc(size, "Unknown", 0);
        }
    };

    //-------------------------------------------------------------
    //!
    //! @brief デフォルトフリー
    //! @brief デフォルトのメモリ解放構造体
    //!
    //-------------------------------------------------------------
    struct S_DefaultFree
    {
        /*************************************************************//**
         *
         *  @brief  関数呼び出し演算子のオーバーロード
         *  @param  解放するメモリのポインタ
         *
         ****************************************************************/
        void operator()(void* pDeletePointer)
        {
            Memory::C_MemoryManager::s_MemoryFree(pDeletePointer);
        }
    };
}