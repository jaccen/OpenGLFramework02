/* ヘッダファイル */
#include "OpenGlManager.h"
#include "../../Debug/Helper/DebugHelper.h"
#include "../../JSON/JsonObject.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL関連の名前空間
//!
//-------------------------------------------------------------
namespace OpenGL
{
    /* 別名 */
    using Profile = SDL_GLprofile;                                                                      // Profile型

    //-------------------------------------------------------------
    //!
    //! @brief OpenGLマネージャーインプリメント
    //! @brief OpenGLマネージャーインプリメントのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_OpenGlManager::C_OpenGlManagerImpl
    {
    public:
        C_OpenGlManagerImpl(C_OpenGlManager* pOpenGlManager);                                           // コンストラクタ
        ~C_OpenGlManagerImpl();                                                                         // デストラクタ
        bool Initialize(const Window::C_BaseWindow& rMainWindow);                                       // 初期化処理
        bool InitializeWithJsonFile(const Window::C_BaseWindow& rMainWindow,                            // Jsonファイルで初期化処理
                                    const std::string& rFilePath);
        void Finalize();                                                                                // 終了処理
        bool CreateRenderingContext(const std::string& rId);                                            // レンダリングコンテキストを作成
        void DestroyRenderingContext(const std::string& rId);                                           // レンダリングコンテキストを破棄
        void AllDestroyRenderingContext();                                                              // 全てのレンダリングコンテキストを破棄
        bool SetCurrentRenderingContext(const std::string& rId);                                        // レンダリングコンテキストをカレントに設定
        void ResetCurrentRenderingContext();                                                            // カレントのレンダリングコンテキストをリセット
        void SwapBuffer();                                                                              // バッファの入れ替え
    private:
        std::unordered_map<std::string, RenderingContextPtr> pRenderingContexts_;                       ///< @brief レンダリングコンテキスト
        Window::WindowDataPtr pMainWindowData_;                                                         ///< @brief メインウィンドウデータ
        C_OpenGlManager* pOpenGlManager_ = nullptr;                                                     ///< @brief OpenGLマネージャー

        bool InitializeGlew();                                                                          // glewの初期化処理
        void EnableDoubleBuffer(bool validFlag);                                                        // ダブルバッファの有効化
        void EnableSwapInterval(bool validFlag);                                                        // 垂直同期を有効化
        void EnableShareRenderingContext(bool validFlag = true);                                        // レンダリングコンテキストの共有を有効化
        void ResetMainWindowData();                                                                     // メインウィンドウの情報をリセット
        void SetVersion(int32_t major, int32_t minor);                                                  // バージョンの設定
        void SetProfire(int32_t profire);                                                               // プロファイルを設定
        void SetColorBuffferSize(int32_t redBufferSize,                                                 // カラーバッファのサイズを設定
                                 int32_t greenBufferSize,
                                 int32_t blueBufferSize,
                                 int32_t alphaBufferSize);
        void SetFrameBufferSize(int32_t bufferSize);                                                    // フレームバッファのサイズを設定
        void SetDepthBufferSize(int32_t bufferSize);                                                    // 深度バッファのサイズを設定
        void SetStencilBufferSize(int32_t bufferSize);                                                  // ステンシルバッファのサイズを設定
        void SetMultiSample(int32_t sampleNumber);                                                      // マルチサンプルの設定
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_OpenGlManager::C_OpenGlManagerImpl::C_OpenGlManagerImpl(C_OpenGlManager* pOpenGlManager) :

        // OpenGLマネージャー
        pOpenGlManager_(pOpenGlManager)

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_OpenGlManager::C_OpenGlManagerImpl::~C_OpenGlManagerImpl()
    {
        if (pMainWindowData_) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  メインウィンドウ
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_OpenGlManager::C_OpenGlManagerImpl::Initialize(const Window::C_BaseWindow& rMainWindow)
    {
        // バージョンを設定
        const int32_t MAJOR_VERSION = 4;
        const int32_t MINOR_VERSION = 0;

        SetVersion(MAJOR_VERSION, MINOR_VERSION);

        // プロファイルの設定
        SetProfire(Profile::SDL_GL_CONTEXT_PROFILE_CORE);

        // カラーバッファの設定
        const int32_t RED_BUFFER_SIZE = 8;
        const int32_t GREEN_BUFFER_SIZE = 8;
        const int32_t BLUE_BUFFER_SIZE = 8;
        const int32_t ALPHA_BUFFER_SIZE = 8;

        SetColorBuffferSize(RED_BUFFER_SIZE,
                            GREEN_BUFFER_SIZE,
                            BLUE_BUFFER_SIZE,
                            ALPHA_BUFFER_SIZE);

        // バッファサイズの設定
        const int32_t FRAME_BUFFER_SIZE = 32;

        static_assert(FRAME_BUFFER_SIZE >= (RED_BUFFER_SIZE 
                                          + GREEN_BUFFER_SIZE
                                          + BLUE_BUFFER_SIZE 
                                          + ALPHA_BUFFER_SIZE), "フレームバッファのサイズが足りません。");

        SetFrameBufferSize(FRAME_BUFFER_SIZE);

        // 深度バッファの設定
        const int32_t DEPTH_BUFFER_SIZE = 32;

        SetDepthBufferSize(DEPTH_BUFFER_SIZE);

        // マルチサンプルの設定
        const int32_t MULTI_SAMPLE_SAMPLE_NUMBER = 4;

        SetMultiSample(MULTI_SAMPLE_SAMPLE_NUMBER);

        // ステンシルバッファの設定
        const int32_t STENCIL_BUFFER_SIZE = 8;

        SetStencilBufferSize(STENCIL_BUFFER_SIZE);

        // ダブルバッファを有効化
        EnableDoubleBuffer(true);

        // 垂直同期を有効化
        EnableSwapInterval(true);

        // レンダリングコンテキストの共有を有効化
        EnableShareRenderingContext(true);

        // メインウィンドウの情報を設定
        pMainWindowData_ = rMainWindow.GetWindowData();

        // レンダリングコンテキストを作成
        if (CreateRenderingContext(RenderingContextID::s_pMAIN) == false) return false;

        // GLEWの初期化処理
        if (InitializeGlew() == false) return false;

        // ビューポートの設定
        const int32_t VIEW_POSITION_X = 0, VIEW_POSITIOIN_Y = 0;
        const int32_t VIEW_WIDTH = rMainWindow.GetWidth();
        const int32_t VIEW_HEIGHT = rMainWindow.GetHeight();

        pOpenGlManager_->SetViewport(VIEW_POSITION_X, VIEW_POSITIOIN_Y, VIEW_WIDTH, VIEW_HEIGHT);

        // 深度テストを有効にする
        pOpenGlManager_->EnableDepthTest(true);

        // マルチサンプリングを有効にする
        pOpenGlManager_->EnableMultiSample(true);

        // バックバッファをクリア
        pOpenGlManager_->ClearBackBuffer();

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  JSONファイルで初期化処理を行う
     *  @param  メインウィンドウ
     *  @param  ファイルパス
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_OpenGlManager::C_OpenGlManagerImpl::InitializeWithJsonFile(const Window::C_BaseWindow& rMainWindow,
                                                                      const std::string& rFilePath)
    {
        // JSONオブジェクトを作成
        auto data = JSON::JsonObject::s_CreateFromFile(rFilePath);

        // バージョンを設定
        SetVersion(data["OpenGLData"]["Version"]["Major"].GetValue<JSON::Integer>(),
                   data["OpenGLData"]["Version"]["Minor"].GetValue<JSON::Integer>());

        // プロファイルの設定
        SetProfire(Profile::SDL_GL_CONTEXT_PROFILE_CORE);

        // カラーバッファの設定
        const int32_t RED_BUFFER_SIZE = data["OpenGLData"]["Buffer"]["Color"]["Red"].GetValue<JSON::Integer>();
        const int32_t GREEN_BUFFER_SIZE = data["OpenGLData"]["Buffer"]["Color"]["Green"].GetValue<JSON::Integer>();
        const int32_t BLUE_BUFFER_SIZE = data["OpenGLData"]["Buffer"]["Color"]["Blue"].GetValue<JSON::Integer>();
        const int32_t ALPHA_BUFFER_SIZE = data["OpenGLData"]["Buffer"]["Color"]["Alpha"].GetValue<JSON::Integer>();

        SetColorBuffferSize(RED_BUFFER_SIZE, GREEN_BUFFER_SIZE, BLUE_BUFFER_SIZE, ALPHA_BUFFER_SIZE);

        // フレームバッファの設定
        const int32_t FRAME_BUFFER_SIZE = 32;

        assert(FRAME_BUFFER_SIZE >= (RED_BUFFER_SIZE 
                                   + GREEN_BUFFER_SIZE
                                   + BLUE_BUFFER_SIZE
                                   + ALPHA_BUFFER_SIZE));

        SetFrameBufferSize(FRAME_BUFFER_SIZE);

        // 深度バッファの設定
        SetDepthBufferSize(data["OpenGLData"]["Buffer"]["Depth"].GetValue<JSON::Integer>());

        // ステンシルバッファの設定
        SetStencilBufferSize(data["OpenGLData"]["Buffer"]["Stencil"].GetValue<JSON::Integer>());

        // マルチサンプルの設定
        if (data["OpenGLData"]["MultiSample"]["UseFlag"].GetValue<JSON::Boolean>() == true)
        {
            SetMultiSample(data["OpenGLData"]["MultiSample"]["SampleNumber"].GetValue<JSON::Integer>());
        }

        // ダブルバッファを有効化
        EnableDoubleBuffer(true);

        // 垂直同期を有効化
        EnableSwapInterval(data["OpenGLData"]["UseSwapIntervalFlag"].GetValue<JSON::Boolean>());

        // レンダリングコンテキストの共有を有効化
        EnableShareRenderingContext(data["OpenGLData"]["UseShareRenderingContextFlag"].GetValue<JSON::Boolean>());

        // メインウィンドウの情報を設定
        pMainWindowData_ = rMainWindow.GetWindowData();

        // レンダリングコンテキストを作成
        if (CreateRenderingContext(RenderingContextID::s_pMAIN) == false) return false;

        // GLEWの初期化処理
        if (InitializeGlew() == false) return false;

        // ビューポートの設定
        const int32_t VIEW_POSITION_X = 0, VIEW_POSITIOIN_Y = 0;
        const int32_t VIEW_WIDTH = rMainWindow.GetWidth();
        const int32_t VIEW_HEIGHT = rMainWindow.GetHeight();

        pOpenGlManager_->SetViewport(VIEW_POSITION_X, VIEW_POSITIOIN_Y, VIEW_WIDTH, VIEW_HEIGHT);

        // 深度テストを有効にする
        pOpenGlManager_->EnableDepthTest(true);

        // マルチサンプリングを有効にする
        pOpenGlManager_->EnableMultiSample(true);

        // バックバッファをクリア
        pOpenGlManager_->ClearBackBuffer();

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  OpenGLの終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::Finalize()
    {
        // カレントのレンダリングコンテキストをリセットし、
        // すべてのレンダリングコンテキストを破棄
        ResetCurrentRenderingContext();
        AllDestroyRenderingContext();

        // メインウィンドウの情報の所有権を破棄
        pMainWindowData_.reset();
    }


    /*************************************************************//**
     *
     *  @brief  レンダリングコンテキストを作成する
     *  @param  ID
     *  @return 正常終了：true ・ 異常終了：false
     *
     ****************************************************************/
    bool C_OpenGlManager::C_OpenGlManagerImpl::CreateRenderingContext(const std::string& rId)
    {
        assert(pMainWindowData_);

        if (pRenderingContexts_.find(rId) != pRenderingContexts_.end())
        {
            PrintLog("[ C_OpenGlManagerImpl::CreateRenderingContext ] : 既にレンダリングコンテキストが作成されています。\n");
            PrintLog("                                             ID : %s\n", rId.c_str());

            return false;
        }

        // レンダリングコンテキストを作成
        RenderingContextPtr pRenderingContext(::SDL_GL_CreateContext(pMainWindowData_.get()),
                                              [](RenderingContext* pRenderingContext){ ::SDL_GL_DeleteContext(pRenderingContext); });

        if (!pRenderingContext)
        {
            PrintLog("[ C_OpenGlManagerImpl::CreateRenderingContext ] : レンダリングコンテキストの作成に失敗しました。\n");
            PrintLog("                                     エラー内容 : %s\n", ::SDL_GetError());

            return false;
        }

        pRenderingContexts_.emplace(rId, pRenderingContext);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  レンダリングコンテキストを破棄する
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::DestroyRenderingContext(const std::string& rId)
    {
        if (pRenderingContexts_.find(rId) == pRenderingContexts_.end())
        {
            std::cout << "[ C_OpenGlManagerImpl::DestroyRenderingContext ] : レンダリングコンテキストが際せくされていません。" << std::endl;
            std::cout << "                                              ID : " << rId << std::endl;

            return;
        }

        pRenderingContexts_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  全てのレンダリングコンテキストを破棄する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::AllDestroyRenderingContext()
    {
        pRenderingContexts_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  レンダリングコンテキストをカレントに設定する
     *  @param  ID
     *  @return 正常終了：true ・ 異常終了：false
     *
     ****************************************************************/
    bool C_OpenGlManager::C_OpenGlManagerImpl::SetCurrentRenderingContext(const std::string& rId)
    {
        assert(pMainWindowData_);

        auto iterator = pRenderingContexts_.find(rId);

        if (iterator == pRenderingContexts_.end())
        {
            PrintLog("[ C_OpenGlManagerImpl::SetCurrentRenderingContext ] : レンダリングコンテキストが作成されていません。\n");
            PrintLog("                         ID : %s\n", rId.c_str());

            return false;
        }

        if (::SDL_GL_MakeCurrent(pMainWindowData_.get(), (*iterator).second.get()) != 0)
        {
            PrintLog("[ C_OpenGlManagerImpl::SetCurrentRenderingContext ] : レンダリングコンテキストをカレントにするのに失敗しました。\n");
            PrintLog("                                         エラー内容 : %s\n", ::SDL_GetError());

            return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  カレントのレンダリングコンテキストをリセットする
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::ResetCurrentRenderingContext()
    {
        assert(pMainWindowData_);

        ::SDL_GL_MakeCurrent(pMainWindowData_.get(), nullptr);
    }


    /*************************************************************//**
     *
     *  @brief  バッファの入れ替えを行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::SwapBuffer()
    {
        ::SDL_GL_SwapWindow(pMainWindowData_.get());
    }

    /*************************************************************//**
     *
     *  @brief  glewの初期化処理を行う
     *  @param  なし
     *  @return 正常終了：true ・ 異常終了：false
     *
     ****************************************************************/
    bool C_OpenGlManager::C_OpenGlManagerImpl::InitializeGlew()
    {
        // glewInitを呼ぶ前にこれをGL_TRUEにする必要がある( 内部の処理の問題 )
        glewExperimental = GL_TRUE;

        // 拡張関数をロード
        GLenum errorResult = ::glewInit();

        if (errorResult != GLEW_OK)
        {
            PrintLog("[ C_OpenGlManagerImpl::Initialize ] : 拡張関数のロードに失敗しました。\n");
            PrintLog("                         エラー内容 : %s\n", ::glewGetErrorString(errorResult));

            return false;
        }

        // GLEW2.0をグラフィックカードがサポートしていない場合
        if (!GLEW_VERSION_2_0)
        {
            PrintLog("[ C_OpenGlManagerImpl::Initialize ] : GLEW2.0をグラフィックカードがサポートしていません。\n");

            return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  ダブルバッファを有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::EnableDoubleBuffer(bool validFlag)
    {
        (validFlag == true) ? ::SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) : ::SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
    }


    /*************************************************************//**
     *
     *  @brief  垂直同期を有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::EnableSwapInterval(bool validFlag)
    {
        (validFlag == true) ? ::SDL_GL_SetSwapInterval(1) : ::SDL_GL_SetSwapInterval(0);
    }


    /*************************************************************//**
     *
     *  @brief  レンダリングコンテキストの共有を有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::EnableShareRenderingContext(bool validFlag)
    {
        (validFlag == true) ? ::SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1) : ::SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 0);
    }


    /*************************************************************//**
     *
     *  @brief  バージョンを設定する
     *  @param  メジャーバージョン
     *  @param  マイナーバージョン
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::SetVersion(int32_t major, int32_t minor)
    {
        assert(major >= 1 && minor >= 0);

        ::SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
        ::SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
    }


    /*************************************************************//**
     *
     *  @brief  プロファイルを設定する
     *  @param  プロファイル
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::SetProfire(int32_t profile)
    {
        ::SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, profile);
    }


    /*************************************************************//**
     *
     *  @brief  カラーバッファのサイズを設定する
     *  @param  レッドバッファのサイズ
     *  @param  グリーンバッファのサイズ
     *  @param  ブルーバッファのサイズ
     *  @param  アルファバッファのサイズ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::SetColorBuffferSize(int32_t redBufferSize,
                                                                   int32_t greenBufferSize,
                                                                   int32_t blueBufferSize,
                                                                   int32_t alphaBufferSize)
    {
        assert(redBufferSize >= 0);
        assert(greenBufferSize >= 0);
        assert(blueBufferSize >= 0);
        assert(alphaBufferSize >= 0);

        ::SDL_GL_SetAttribute(SDL_GL_RED_SIZE, redBufferSize);
        ::SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, greenBufferSize);
        ::SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, blueBufferSize);
        ::SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, alphaBufferSize);
    }


    /*************************************************************//**
     *
     *  @brief  フレームバッファのサイズを設定する
     *  @param  フレームバッファのサイズ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::SetFrameBufferSize(int32_t bufferSize)
    {
        ::SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, bufferSize);
    }


    /*************************************************************//**
     *
     *  @brief  深度バッファのサイズを設定する
     *  @param  深度バッファのサイズ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::SetDepthBufferSize(int32_t bufferSize)
    {
        ::SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, bufferSize);
    }


    /*************************************************************//**
     *
     *  @brief  ステンシルバッファを設定する
     *  @param  ステンシルバッファのサイズ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::SetStencilBufferSize(int32_t bufferSize)
    {
        ::SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, bufferSize);
    }


    /*************************************************************//**
     *
     *  @brief  マルチサンプルアンチエイリアスを設定する
     *  @param  マルチサンプルで利用するサンプルの数
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::C_OpenGlManagerImpl::SetMultiSample(int32_t sampleNumber)
    {
        ::SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        ::SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, sampleNumber);
    }
}