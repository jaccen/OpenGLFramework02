/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include <SDL_video.h>


//-------------------------------------------------------------
//!
//! @brief ウィンドウ
//! @brief ウィンドウ関連の名前空間
//!
//-------------------------------------------------------------
namespace Window
{
    /* 別名 */
    using WindowData = SDL_Window;                                                          // WindowData型
    using WindowDataPtr = std::shared_ptr<WindowData>;                                      // WindowDataPtr型
    using CreateFlag = SDL_WindowFlags;                                                     // CreateFlag型


    namespace
    {
        /* デフォルト */
        namespace Default
        {
            const int32_t s_WIDTH = 640;                                                    ///< @brief 幅
            const int32_t s_HEIGHT = 480;                                                   ///< @brief 高さ
        }

        /* 生成位置 */
        namespace CreatePosition
        {
            const int32_t s_CENTER = SDL_WINDOWPOS_CENTERED;                                ///< @brief 真ん中
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief ベースウィンドウ
    //! @brief ウィンドウの基底クラス
    //!
    //-------------------------------------------------------------
    class C_BaseWindow
    {
    public:
        C_BaseWindow();                                                                     // コンストラクタ
        virtual ~C_BaseWindow();                                                            // デストラクタ
        virtual bool Initialize(const ::std::string& rTitle = "OpenGL_Framework",           // 初期化処理
                                int32_t width = Default::s_WIDTH,
                                int32_t height = Default::s_HEIGHT,
                                int32_t createFlags = CreateFlag::SDL_WINDOW_OPENGL,
                                int32_t createPositionX = CreatePosition::s_CENTER,
                                int32_t createPositionY = CreatePosition::s_CENTER);
        virtual void Finalize();                                                            // 終了処理
        const WindowDataPtr& GetWindowData() const;                                         // ウィンドウの情報を取得
        uint32_t GetId() const;                                                             // IDを取得
        int32_t GetWidth() const;                                                           // 幅を取得
        int32_t GetHeight() const;                                                          // 高さを取得
        void SetWidth(int32_t width);                                                       // 幅を設定
        void SetHeight(int32_t height);                                                     // 高さを設定

        template<typename T = float>
        T GetAspectRatio();                                                                 // アスペクト比を取得
    protected:
        WindowDataPtr pWindowData_;                                                         ///< @brief ウィンドウ情報
        uint32_t id_ = 0;                                                                   ///< @brief ID
        int32_t width_ = 0;                                                                 ///< @brief 幅
        int32_t height_ = 0;                                                                ///< @brief 高さ
    };
}