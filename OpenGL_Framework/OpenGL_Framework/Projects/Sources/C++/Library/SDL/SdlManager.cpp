/* ヘッダファイル */
#include "SdlManager.h"
#include "../Debug/Helper/DebugHelper.h"
#include <SDL.h>


//-------------------------------------------------------------
//!
//! @brief SDL
//! @brief SDL関連の名前空間
//!
//-------------------------------------------------------------
namespace SDL
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SdlManager::C_SdlManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SdlManager::~C_SdlManager()
    {
        if (finalizeFlag_ == false) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  なし
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SdlManager::Initialize()
    {
        const int32_t ERROR_VALUE = -1;

        // SDLの初期化処理
        if (::SDL_Init(SDL_INIT_EVERYTHING) == ERROR_VALUE)
        {
            PrintLog("[ C_SdlManager::Initialize ] : SDLの初期化に失敗しました。\n");
            PrintLog("                  エラー内容 : %s\n", ::SDL_GetError());

            return false;
        }
        
        finalizeFlag_ = false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SdlManager::Finalize()
    {
        ::SDL_Quit();
        finalizeFlag_ = true;
    }
}