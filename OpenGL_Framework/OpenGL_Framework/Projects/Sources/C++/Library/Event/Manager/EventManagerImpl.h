/* ヘッダファイル */
#include "EventManager.h"
#include "../Window/Main/MainWindowEvent.h"
#include "../../Input/Keyboard/KeyboardManager.h"
#include "../../Input/Mouse/MouseManager.h"
#include <forward_list>


//-------------------------------------------------------------
//!
//! @brief イベント
//! @brief イベント関連の名前空間
//!
//-------------------------------------------------------------
namespace Event
{
    //-------------------------------------------------------------
    //!
    //! @brief イベントマネージャーインプリメント
    //! @brief イベントマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_EventManager::C_EventManagerImpl
    {
    public:
        C_EventManagerImpl();                                                       // コンストラクタ
        ~C_EventManagerImpl();                                                      // デストラクタ
        void Update();                                                              // 更新処理
        void EntryWindowEvent(C_BaseWindowEvent* pWindowEvent);                     // ウィンドウのイベントを登録
        bool IsFinishFlag() const;                                                  // 終了フラグを取得
    private:
        EventData event_;                                                           ///< @brief イベントの情報
        std::forward_list<std::unique_ptr<C_BaseWindowEvent>> upWindowEvents_;      ///< @brief ウィンドウのイベント

        static bool s_finishFlag;                                                   // 終了を判断するフラグ   

        void WindowEvent();                                                         // ウィンドウのイベント処理
        void QuitEvent();                                                           // 終了のイベント処理
    };


#pragma region 静的メンバ変数の初期化


    /* 終了を判断するフラグ */
    bool C_EventManager::C_EventManagerImpl::s_finishFlag = false;


#pragma endregion


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_EventManager::C_EventManagerImpl::C_EventManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_EventManager::C_EventManagerImpl::~C_EventManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_EventManager::C_EventManagerImpl::Update()
    {
        // イベントの更新
        while (::SDL_PollEvent(&event_))
        {
            switch (event_.type)
            {
            /* ウィンドウのイベント */
            case SDL_WINDOWEVENT:

                WindowEvent();

                break;
            /* マウスホイールのイベント */
            case SDL_MOUSEWHEEL:

                // マウスホイールの垂直方向の回転を設定
                Input::C_MouseManager::s_GetInstance()->SetWheelScrollVertical(event_.wheel.y);

                break;
            /* テキスト入力のイベント */
            case SDL_TEXTINPUT:

                Input::C_KeyboardManager::s_GetInstance()->SetInputCharacter(event_.text.text);

                break;
            /* 終了のイベント */
            case SDL_QUIT:

                QuitEvent();

                break;
            /* その他のイベント */
            default:
                break;
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  ウィンドウのイベントを登録する
     *  @param  ウィンドウのイベント
     *  @return なし
     *
     ****************************************************************/
    void C_EventManager::C_EventManagerImpl::EntryWindowEvent(C_BaseWindowEvent* pWindowEvent)
    {
        upWindowEvents_.emplace_front(pWindowEvent);
    }


    /*************************************************************//**
     *
     *  @brief  終了フラグを取得
     *  @param  なし
     *  @return 終了フラグ
     *
     ****************************************************************/
    bool C_EventManager::C_EventManagerImpl::IsFinishFlag() const
    {
        return s_finishFlag;
    }


    /*************************************************************//**
     *
     *  @brief  ウィンドウのイベント処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_EventManager::C_EventManagerImpl::WindowEvent()
    {
        // ループカウンタ
        int32_t loopCount = 0;

        // イテレータ
        auto iterator = upWindowEvents_.begin();

        // ウィンドウイベントを処理
        while (iterator != upWindowEvents_.end())
        {
            if (event_.window.windowID == (*iterator)->GetWindowId())
            {
                if ((*iterator)->Process(event_) == false)
                {
                    iterator = upWindowEvents_.erase_after(std::next(upWindowEvents_.before_begin(), loopCount));
                    continue;
                }

                ++iterator;
                ++loopCount;
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  終了のイベント処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_EventManager::C_EventManagerImpl::QuitEvent()
    {
        s_finishFlag = true;
    }
}