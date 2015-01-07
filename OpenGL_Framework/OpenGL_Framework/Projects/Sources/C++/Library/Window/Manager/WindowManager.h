/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Singleton/Singleton.h"
#include "../Window//BaseWindow.h"


//-------------------------------------------------------------
//!
//! @brief ウィンドウ
//! @brief ウィンドウ関連の名前空間
//!
//-------------------------------------------------------------
namespace Window
{
    /* 別名 */
    using WindowPtr = std::shared_ptr<C_BaseWindow>;                                                            // WindowPtr型


    namespace
    {
        /* ID */
        namespace ID
        {
            const char* s_pMAIN_WINDOW = "MainWindow";                                                          ///< @brief メインウィンドウ
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief ウィンドウマネージャー
    //! @brief ウィンドウを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_WindowManager : public Singleton::C_Singleton<C_WindowManager>
    {
        friend C_Singleton<C_WindowManager>;                                                                    // シングルトンクラスをフレンド化
    public:
        C_WindowManager();                                                                                      // コンストラクタ
        ~C_WindowManager() override;                                                                            // デストラクタ
        void Entry(const WindowPtr& prWindow,                                                                   // 登録処理
                   const std::string& rId = ID::s_pMAIN_WINDOW);
        void Remove(const std::string& rId = ID::s_pMAIN_WINDOW);                                               // 除去処理
        void AllRemove();                                                                                       // 全てのウィンドウを除去
        boost::optional<const WindowPtr&> GetWindow(const std::string& rId = ID::s_pMAIN_WINDOW) const;         // ウィンドウを取得
    private:
        /* 前方宣言 */
        class C_WindowManagerImpl;

        std::unique_ptr<C_WindowManagerImpl> upImpl_;                                                           ///< @brief 実装情報
    };
}