/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Pool/General/GeneralMemoryPool.h"


//-------------------------------------------------------------
//!
//! @brief メモリ
//! @brief メモリ関連の名前空間
//!
//-------------------------------------------------------------
namespace Memory
{
    /* 前方宣言 */
    class C_MemoryListInitializer;


    //-------------------------------------------------------------
    //!
    //! @brief メモリーリスト
    //! @brief メモリをリスト状に管理するクラス
    //!
    //-------------------------------------------------------------
    struct S_MemoryList
    {
        friend C_MemoryListInitializer;                         // メモリリストイニシャライザクラスをフレンド化
    public:
        size_t size_ = 0;                                       ///< @brief メモリサイズ
        const char* pFileName_ = nullptr;                       ///< @brief ファイル名
        int32_t lineNumber_ = 0;                                ///< @brief 行数
        bool usePoolFlag_ = false;                              ///< @brief プールを使用しているか判断するフラグ
        S_MemoryList* pNext_ = nullptr;                         ///< @brief 次のリスト

/* 汎用メモリプール使用時 */
#ifdef USE_GENERAL_MEMORY_POOL

        static C_GeneralMemoryPool* s_pGeneralMemoryPool;       ///< @brief 汎用メモリプール

#endif

        static S_MemoryList* s_pLast;                           ///< @brief 最後のリストのポインタ
    };



    /* 汎用メモリプール使用時 */
#ifdef USE_GENERAL_MEMORY_POOL


    //-------------------------------------------------------------
    //!
    //! @brief メモリーリストイニシャライザ
    //! @brief メモリリストの静的変数の寿命を保証するためのクラス
    //!
    //-------------------------------------------------------------
    class C_MemoryListInitializer
    {
    public:
        C_MemoryListInitializer();                              // コンストラクタ
        ~C_MemoryListInitializer();                             // デストラクタ
    };


    /* メモリーリストイニシャライザのインスタンス */
    static C_MemoryListInitializer s_memoryListInitializer;


#endif

}