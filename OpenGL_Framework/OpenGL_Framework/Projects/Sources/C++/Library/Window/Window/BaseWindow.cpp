/* ヘッダファイル */
#include "BaseWindow.h"
#include "../../Debug/Helper/DebugHelper.h"


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
    C_BaseWindow::C_BaseWindow()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BaseWindow::~C_BaseWindow()
    {
        if (!pWindowData_) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  ウィンドウの初期化処理を行う
     *  @param  タイトル
     *  @param  幅
     *  @param  高さ
     *  @param  生成時に利用するフラグ
     *  @param  生成するときのX座標
     *  @param  生成するときのY座標
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_BaseWindow::Initialize(const std::string& rTitle,
                                  int32_t width,
                                  int32_t height,
                                  int32_t createFlags,
                                  int32_t createPositionX,
                                  int32_t createPositionY)
    {
        assert(createFlags & CreateFlag::SDL_WINDOW_OPENGL);
        
#ifndef _DEBUG

        /*
        // ウィンドウモードとフルスクリーンの切り替えを行うメッセージボックスを表示
        if (MessageBox(nullptr, "フルスクリーンモードで表示しますか？", "スクリーンモード設定", MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
        // 通常のフルスクリーン化( 裏でソフトを動かしてるとうまくいかないことがあるので注意 )
        createFlags |= CreateFlag::SDL_WINDOW_FULLSCREEN;

        // createFlags |= CreateFlag::SDL_WINDOW_FULLSCREEN_DESKTOP;
        }*/

#endif

        // ウィンドウの生成
        pWindowData_.reset(::SDL_CreateWindow(rTitle.c_str(),
                           createPositionX,
                           createPositionY,
                           width,
                           height,
                           createFlags),
                           [](WindowData* pWindowData){ ::SDL_DestroyWindow(pWindowData); });

        // ウィンドウの生成に失敗した場合
        if (!pWindowData_)
        {
            PrintLog("[ C_BaseWindow::Initialize ] : ウィンドウの生成に失敗しました。\n");
            PrintLog("                  エラー内容 : %s\n", ::SDL_GetError());

            return false;
        }

        // IDの取得
        id_ = ::SDL_GetWindowID(pWindowData_.get());

        // サイズの設定
        width_ = width;
        height_ = height;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  ウィンドウの終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseWindow::Finalize()
    {
        // ウィンドウデータの所有権を破棄し、IDをリセット
        pWindowData_.reset();
        id_ = 0;
    }


    /*************************************************************//**
     *
     *  @brief  ウィンドウの情報を取得する
     *  @param  なし
     *  @return ウィンドウ
     *
     ****************************************************************/
    const WindowDataPtr& C_BaseWindow::GetWindowData() const
    {
        return pWindowData_;
    }


    /*************************************************************//**
     *
     *  @brief  IDを取得する
     *  @param  なし
     *  @return ID
     *
     ****************************************************************/
    uint32_t C_BaseWindow::GetId() const
    {
        return id_;
    }


    /*************************************************************//**
     *
     *  @brief  幅を取得する
     *  @param  なし
     *  @return 幅
     *
     ****************************************************************/
    int32_t C_BaseWindow::GetWidth() const
    {
        return width_;
    }


    /*************************************************************//**
     *
     *  @brief  高さを取得する
     *  @param  なし
     *  @return 高さ
     *
     ****************************************************************/
    int32_t C_BaseWindow::GetHeight() const
    {
        return height_;
    }


    /*************************************************************//**
     *
     *  @brief  幅を設定する
     *  @param  幅
     *  @return なし
     *
     ****************************************************************/
    void C_BaseWindow::SetWidth(int32_t width)
    {
        width_ = width;
    }


    /*************************************************************//**
     *
     *  @brief  高さを設定する
     *  @param  高さ
     *  @return なし
     *
     ****************************************************************/
    void C_BaseWindow::SetHeight(int32_t height)
    {
        height_ = height;
    }


    /*************************************************************//**
     *
     *  @brief  アスペクト比を取得する
     *  @param  なし
     *  @return アスペクト比
     *
     ****************************************************************/
    template<typename T>
    T C_BaseWindow::GetAspectRatio()
    {
        return static_cast<T>(width_) / static_cast<T>(height_);
    }


#pragma region 明示的インスタンス化


    /* アスペクト比を取得 */
    template float C_BaseWindow::GetAspectRatio();
    template double C_BaseWindow::GetAspectRatio();


#pragma endregion

}