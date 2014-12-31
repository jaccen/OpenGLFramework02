/* ヘッダファイル */
#include "WindowManager.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief ウィンドウ
//! @brief ウィンドウ関連の名前空間
//!
//-------------------------------------------------------------
namespace Window
{
    //-------------------------------------------------------------
    //!
    //! @brief カメラマネージャーインプリメント
    //! @brief カメラマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_WindowManager::C_WindowManagerImpl
    {
    public:
        C_WindowManagerImpl();                                                              // コンストラクタ
        ~C_WindowManagerImpl();                                                             // デストラクタ
        void Update();                                                                      // 更新処理
        void Entry(const WindowPtr& prWindow,                                               // 登録処理
                   const std::string& rId);
        void Remove(const std::string& rId);                                                // 除去処理
        void AllRemove();                                                                   // 全てのウィンドウを除去

        /* ゲッター */
        boost::optional<const WindowPtr&> GetWindow(const std::string& rId) const;          // ウィンドウを取得
    private:
        std::unordered_map<std::string, WindowPtr> pWindows;                                ///< @brief ウィンドウ
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_WindowManager::C_WindowManagerImpl::C_WindowManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_WindowManager::C_WindowManagerImpl::~C_WindowManagerImpl()
    {
        if (pWindows.empty() == false) AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  登録処理を行う
     *  @param  ウィンドウ
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_WindowManager::C_WindowManagerImpl::Entry(const WindowPtr& prWindow,
                                                     const std::string& rId)
    {
        if (pWindows.find(rId) != pWindows.end())
        {
            std::cout << "[ C_WindowManagerImpl::Entry ] : ウィンドウが既に登録されています。" << std::endl;
            std::cout << "                            ID : " << rId << std::endl;

            return;
        }

        pWindows.emplace(rId, prWindow);
    }


    /*************************************************************//**
     *
     *  @brief  除去処理を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_WindowManager::C_WindowManagerImpl::Remove(const std::string& rId)
    {
        if (pWindows.find(rId) == pWindows.end())
        {
            std::cout << "[ C_WindowManagerImpl::Remove ] : ウィンドウを登録していません。" << std::endl;
            std::cout << "                             ID : " << rId << std::endl;

            return;
        }

        pWindows.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  全ての除去処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_WindowManager::C_WindowManagerImpl::AllRemove()
    {
        pWindows.clear();
    }


    /*************************************************************//**
     *
     *  @brief  ウィンドウを取得する
     *  @param  ID
     *  @return 取得できた場合      ：ウィンドウ
     *  @return 取得できなかった場合：none
     *
     ****************************************************************/
    boost::optional<const WindowPtr&> C_WindowManager::C_WindowManagerImpl::GetWindow(const std::string& rId) const
    {
        auto iterator = pWindows.find(rId);
        if (iterator == pWindows.end()) return boost::none;

        return (*iterator).second;
    }
}