/* ヘッダファイル */
#include "FrameworkImpl.h"
#include "../SDL/SdlManager.h"
#include "../Window/Manager/WindowManager.h"
#include "../Event/Manager/EventManager.h"
#include "../Timer/TimeManager.h"
#include "../JSON/JsonObject.h"
#include "../OpenGL/Manager/OpenGlManager.h"
#include "../Input/Keyboard/KeyboardManager.h"
#include "../Input/Mouse/MouseManager.h"
#include "../Input/Gamepad/Manager/GamepadManager.h"
#include "../Sound/SoundManager.h"
#include "../Texture/Manager/TextureManager.h"
#include "../Debug/String/DebugString.h"
#include "../Camera/Manager/CameraManager.h"


/* マクロ定義 */
#define _CRTDBG_MAP_ALLOC           // <crtdbg.h>内の関数のメモリの割り当てを追跡するようにするマクロ


/* VisualStudio関連のヘッダファイル */
#include <crtdbg.h>


//-------------------------------------------------------------
//!
//! @brief フレームワーク
//! @brief フレームワーク関連の名前空間
//!
//-------------------------------------------------------------
namespace Framework
{
    /* プロトタイプ宣言 */
    static bool s_InitializeMainWindowWithJsonFile(Window::C_BaseWindow* pMainWindow,
                                                   const std::string& rFilePath);


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_Framework::C_Framework(C_Framework* pGame) :

        // 実装情報
        upImpl_(std::make_unique<C_FrameworkImpl>(pGame))

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_Framework::~C_Framework()
    {
    }


    /*************************************************************//**
     *
     *  @brief  実行処理を行う
     *  @param  なし
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_Framework::Run()
    {
        // 最初の処理
        FirstProcess();

        // 初期化処理
        if (upImpl_->GetGame()->Initialize() == false) return false;

        /* メインループ */
        while (Event::C_EventManager::s_GetInstance()->IsFinishFlag() == false)
        {
            // 更新処理
            if (upImpl_->GetGame()->Update() == false) break;

            // 描画フラグが立っている場合は描画処理と画面の更新を行う
            if (Timer::C_TimeManager::s_GetInstance()->IsDrawFlag() == true)
            {
                upImpl_->GetGame()->Draw();
                upImpl_->GetGame()->UpdateScreen();
            }
        }

        // 終了処理
        upImpl_->GetGame()->Finalize();

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  なし
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_Framework::Initialize()
    {
        // SDLマネージャーの初期化処理 
        if (SDL::C_SdlManager::s_GetInstance()->Initialize() == false) return false;

        // メインウィンドウの初期化処理
        auto pMainWindow = std::make_shared<Window::C_BaseWindow>();
        Window::C_WindowManager::s_GetInstance()->Entry(pMainWindow);

        if (pMainWindow->Initialize() == false) return false;

        // OpenGLマネージャーの初期化処理
        if (OpenGL::C_OpenGlManager::s_GetInstance()->Initialize(*pMainWindow) == false) return false;

        // イベントマネージャーの初期化処理
        Event::C_EventManager::s_GetInstance()->Initialize(*pMainWindow);

        // タイムネージャーの初期化処理
        Timer::C_TimeManager::s_GetInstance()->Initialize();

        // キーボードマネージャーの初期化処理
        Input::C_KeyboardManager::s_GetInstance()->Initialize();

        // ゲームパッドマネージャーの初期化処理
        Input::C_GamepadManager::s_GetInstance()->Initialize();

        // サウンドマネージャーの初期化処理
        if (Sound::C_SoundManager::s_GetInstance()->Initialize() == false) return false;

        // フォントマネージャーの初期化処理
        if (Font::C_FontManager::s_GetInstance()->Initialize() == false) return false;

        // デバッグ文字列の初期化処理
        if (Debug::C_DebugString::s_GetInstance()->Initialize() == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  JSONファイルで初期化処理を行う
     *  @param  メインウィンドウデータのファイルパス
     *  @param  OpenGLデータのファイルパス
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_Framework::InitializeWithJsonFile(const std::string& rMainWindowDataFilePath,
                                             const std::string& rOpenGlDataFilePath)
    {
        // SDLマネージャーの初期化処理 
        if (SDL::C_SdlManager::s_GetInstance()->Initialize() == false) return false;

        // メインウィンドウの初期化処理
        auto pMainWindow = std::make_shared<Window::C_BaseWindow>();
        Window::C_WindowManager::s_GetInstance()->Entry(pMainWindow);

        if (s_InitializeMainWindowWithJsonFile(pMainWindow.get(), rMainWindowDataFilePath) == false)
        {
            return false;
        }

        // OpenGLマネージャーの初期化処理
        if (OpenGL::C_OpenGlManager::s_GetInstance()->InitializeWithJsonFile(*pMainWindow, rOpenGlDataFilePath) == false)
        {
            return false;
        }

        // イベントマネージャーの初期化処理
        Event::C_EventManager::s_GetInstance()->Initialize(*pMainWindow);

        // タイムネージャーの初期化処理
        Timer::C_TimeManager::s_GetInstance()->Initialize();

        // キーボードマネージャーの初期化処理
        Input::C_KeyboardManager::s_GetInstance()->Initialize();

        // ゲームパッドマネージャーの初期化処理
        Input::C_GamepadManager::s_GetInstance()->Initialize();

        // サウンドマネージャーの初期化処理
        if (Sound::C_SoundManager::s_GetInstance()->Initialize() == false) return false;
        
        // フォントマネージャーの初期化処理
        if (Font::C_FontManager::s_GetInstance()->Initialize() == false) return false;

        // デバッグ文字列の初期化処理
        if (Debug::C_DebugString::s_GetInstance()->Initialize() == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_Framework::Update()
    {
        // タイムマネージャーの更新処理
        Timer::C_TimeManager::s_GetInstance()->Update();

        // イベントマネージャーの更新処理
        Event::C_EventManager::s_GetInstance()->Update();

        // キーボードマネージャーの更新処理
        Input::C_KeyboardManager::s_GetInstance()->Update();

        // マウスマネージャーの更新処理
        Input::C_MouseManager::s_GetInstance()->Update();

        // ゲームパッドマネージャーの更新処理
        Input::C_GamepadManager::s_GetInstance()->Update();

        // カメラマネージャーの更新処理
        Camera::C_CameraManager::s_GetInstance()->Update();

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_Framework::Draw()
    {
        Debug::C_DebugString::s_GetInstance()->Draw("[ FPS : " + std::to_string(Timer::C_TimeManager::s_GetInstance()->GetNowFps()) + " ]", Debug::Vector3(0.0f, 0.0f, 0.0f), 0.7f, 255, 255, 255);
    }


    /*************************************************************//**
     *
     *  @brief  画面の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_Framework::UpdateScreen()
    {
        OpenGL::C_OpenGlManager::s_GetInstance()->SwapBuffer();
        OpenGL::C_OpenGlManager::s_GetInstance()->ClearBackBuffer();
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_Framework::Finalize()
    {
        // デバッグ文字列の終了処理
        Debug::C_DebugString::s_GetInstance()->Finalize();

        // テクスチャを全て破棄
        Texture::C_TextureManager::s_GetInstance()->AllDestroy();

        // フォントマネージャーの終了処理
        Font::C_FontManager::s_GetInstance()->Finalize();

        // サウンドマネージャーの終了処理
        Sound::C_SoundManager::s_GetInstance()->Finalize();

        // ゲームパッドマネージャーの終了処理
        Input::C_GamepadManager::s_GetInstance()->Finalize();

        // OpenGLマネージャーの終了処理
        OpenGL::C_OpenGlManager::s_GetInstance()->Finalize();

        // メインウィンドウを除去
        Window::C_WindowManager::s_GetInstance()->Remove();

        // SDLマネージャーの終了処理
        SDL::C_SdlManager::s_GetInstance()->Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  一番最初に行うべき処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_Framework::FirstProcess()
    {
        // プログラム終了時にメモリリーク情報をダンプする設定
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

        // 出力先をデバッグウィンドウに設定
        _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

        // メモリーリークが発生した位置を検知してくれる関数( 引数にメモリーリークした番号を入れる )
        //_CrtSetBreakAlloc(152);
    }


    /*************************************************************//**
     *
     *  @brief  JSONファイルでメインウィンドウの初期化処理を行う
     *  @param  メインウィンドウ
     *  @param  ファイルパス
     *  @return 正常終了：true
     *  @return 以上終了：false
     *
     ****************************************************************/
    bool s_InitializeMainWindowWithJsonFile(Window::C_BaseWindow* pMainWindow,
                                            const std::string& rFilePath)
    {
        // JSONオブジェクトを生成
        auto data = JSON::JsonObject::s_CreateFromFile(rFilePath);

        // メインウィンドウのタイトル・サイズ・生成フラグを取得
        std::string title = data["MainWindowData"]["Title"].GetValue<JSON::String>();
        int32_t width = data["MainWindowData"]["Size"]["Width"].GetValue<JSON::Integer>();
        int32_t height = data["MainWindowData"]["Size"]["Height"].GetValue<JSON::Integer>();
        int32_t createFlags = Window::CreateFlag::SDL_WINDOW_OPENGL;

        if (data["MainWindowData"]["CreateFlag"]["Resizeable"].GetValue<JSON::Boolean>() == true)
        {
            createFlags |= Window::CreateFlag::SDL_WINDOW_RESIZABLE;
        }

        if (data["MainWindowData"]["CreateFlag"]["FullScreen"].GetValue<JSON::Boolean>() == true)
        {
            createFlags |= Window::CreateFlag::SDL_WINDOW_FULLSCREEN;
        }

        // メインウィンドウの初期化処理
        if (pMainWindow->Initialize(title, width, height, createFlags) == false) return false;

        // タイムネージャーの初期化処理
        Timer::C_TimeManager::s_GetInstance()->Initialize();

        return true;
    }
}