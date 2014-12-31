/* ヘッダファイル */
#include "WindowManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief ウィンドウ
//! @brief ウィンドウ関連の名前空間
//!
//-------------------------------------------------------------
namespace Window
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_WindowManager::C_WindowManager() :

        // 実装情報
        upImpl_(std::make_unique<C_WindowManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_WindowManager::~C_WindowManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  登録処理を行う
     *  @param  カメラ
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_WindowManager::Entry(const WindowPtr& pWindow,
                                const std::string& rId)
    {
        upImpl_->Entry(pWindow, rId);
    }


    /*************************************************************//**
     *
     *  @brief  カメラの除去処理を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_WindowManager::Remove(const std::string& rId)
    {
        upImpl_->Remove(rId);
    }


    /*************************************************************//**
     *
     *  @brief  全てのカメラの除去処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_WindowManager::AllRemove()
    {
        upImpl_->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  カメラを取得する
     *  @param  ID
     *  @return 取得できた場合      ：カメラ
     *  @return 取得できなかった場合：none
     *
     ****************************************************************/
    boost::optional<const WindowPtr&> C_WindowManager::GetWindow(const std::string& rId) const
    {
        return upImpl_->GetWindow(rId);
    }
}