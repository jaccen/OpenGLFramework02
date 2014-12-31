/* ヘッダファイル */
#include "Framework.h"
#include "../Window/Window/BaseWindow.h"


//-------------------------------------------------------------
//!
//! @brief フレームワーク
//! @brief フレームワーク関連の名前空間
//!
//-------------------------------------------------------------
namespace Framework
{
    //-------------------------------------------------------------
    //!
    //! @brief フレームワークインプリメント
    //! @brief フレームワークのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_Framework::C_FrameworkImpl
    {
    public:
        explicit C_FrameworkImpl(C_Framework* pGame);                       // コンストラクタ
        ~C_FrameworkImpl();                                                 // デストラクタ

        C_Framework* GetGame() const;                                       // ゲームを取得
    private:
        C_Framework* pGame_ = nullptr;                                      ///< @brief ゲーム
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_Framework::C_FrameworkImpl::C_FrameworkImpl(C_Framework* pGame) :

        // ゲーム
        pGame_(pGame)

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_Framework::C_FrameworkImpl::~C_FrameworkImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ゲームを取得
     *  @param  なし
     *  @return ゲーム
     *
     ****************************************************************/
    C_Framework* C_Framework::C_FrameworkImpl::GetGame() const
    {
        return pGame_;
    }
}