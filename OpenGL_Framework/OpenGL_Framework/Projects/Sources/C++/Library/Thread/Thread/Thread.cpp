#include "Thread.h"


//-------------------------------------------------------------
//!
//! @brief スレッド
//! @brief スレッド関連の名前空間
//!
//-------------------------------------------------------------
namespace Thread
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_Thread::C_Thread()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_Thread::~C_Thread()
    {
        if (pThreadData_) Join();
    }


    /*************************************************************//**
     *
     *  @brief  スレッドを作成する
     *  @param  実行する関数
     *  @param  名前
     *  @param  関数に渡すデータ
     *  @return なし
     *
     ****************************************************************/
    void C_Thread::Create(ThreadFunction pThreadFunction,
                          const std::string& rName,
                          void* pFunctionData)
    {
        assert(pThreadData_ == nullptr);

        pThreadData_ = SDL_CreateThread(pThreadFunction, rName.c_str(), pFunctionData);
    }


    /*************************************************************//**
     *
     *  @brief  スレッドの終了の待機を行う
     *  @param  なし
     *  @return 実行した関数の戻り値
     *
     ****************************************************************/
    int32_t C_Thread::Join()
    {
        assert(pThreadData_);

        int32_t functionReturnValue = 0;
        ::SDL_WaitThread(pThreadData_, &functionReturnValue);
        pThreadData_ = nullptr;

        return functionReturnValue;
    }


    /*************************************************************//**
     *
     *  @brief  スレッドの管理の放棄を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_Thread::Detach()
    {
        assert(pThreadData_);

        ::SDL_DetachThread(pThreadData_);
        pThreadData_ = nullptr;
    }
}