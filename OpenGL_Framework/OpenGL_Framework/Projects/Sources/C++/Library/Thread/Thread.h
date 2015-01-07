/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include <SDL_thread.h>


//-------------------------------------------------------------
//!
//! @brief スレッド
//! @brief スレッド関連の名前空間
//!
//-------------------------------------------------------------
namespace Thread
{
    /* 別名 */
    using ThreadData = SDL_Thread;                                  // ThreadData型
    using ThreadFunction = SDL_ThreadFunction;                      // ThreadFunction型


    //-------------------------------------------------------------
    //!
    //! @brief スレッド
    //! @brief スレッドを表すクラス
    //!
    //-------------------------------------------------------------
    class C_Thread
    {
    public:
        C_Thread();                                                 // コンストラクタ
        ~C_Thread();                                                // デストラクタ
        void Create(ThreadFunction pThreadFunction,                 // スレッドの作成
                    const std::string& rName, 
                    void* pFunctionData = nullptr);
        int32_t Join();                                             // スレッドの終了の待機
        void Detach();                                              // スレッドの管理を放棄
    private:
        ThreadData* pThreadData_ = nullptr;                         ///< @brief スレッド情報
    };
}