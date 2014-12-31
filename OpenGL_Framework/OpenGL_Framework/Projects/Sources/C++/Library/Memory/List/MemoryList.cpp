/* ヘッダファイル */
#include "MemoryList.h"


//-------------------------------------------------------------
//!
//! @brief メモリ
//! @brief メモリ関連の名前空間
//!
//-------------------------------------------------------------
namespace Memory
{

#pragma region 静的メンバ変数の初期化


/* 汎用メモリプール使用時 */
#ifdef USE_GENERAL_MEMORY_POOL


    /* 汎用メモリプール */
    C_GeneralMemoryPool* S_MemoryList::s_pGeneralMemoryPool = nullptr;


#endif


    /* 最後のリストのポインタ */
    S_MemoryList* S_MemoryList::s_pLast = nullptr;


#pragma endregion


/* 汎用メモリプール使用時 */
#ifdef USE_GENERAL_MEMORY_POOL


    /* メモリリストイニシャライザの参照カウンタ */
    static uint32_t s_niftyCount = 0;


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_MemoryListInitializer::C_MemoryListInitializer()
    {
        if (s_niftyCount == 0)
        {
            S_MemoryList::s_pGeneralMemoryPool = new C_GeneralMemoryPool;
        }

        ++s_niftyCount;
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_MemoryListInitializer::~C_MemoryListInitializer()
    {
        --s_niftyCount;

        if (s_niftyCount == 0)
        {
            if (S_MemoryList::s_pGeneralMemoryPool)
            {
                delete S_MemoryList::s_pGeneralMemoryPool;
                S_MemoryList::s_pGeneralMemoryPool = nullptr;
            }
        }
    }


#endif

}