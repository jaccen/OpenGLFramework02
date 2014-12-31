/* ヘッダファイル */
#include "MouseManager.h"
#include <SDL_mouse.h>
#include <array>


//-------------------------------------------------------------
//!
//! @brief インプット
//! @brief 入力関連の名前空間
//!
//-------------------------------------------------------------
namespace Input
{
    //-------------------------------------------------------------
    //!
    //! @brief マウスマネージャーインプリメント
    //! @brief マウスマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_MouseManager::C_MouseManagerImpl
    {
    public:
        C_MouseManagerImpl();                                                       // コンストラクタ
        ~C_MouseManagerImpl();                                                      // デストラクタ

        void CursorAndButtonUpdate();                                               // カーソルとボタンの更新処理
        void WheelUpdate();                                                         // ホイールの更新処理
        int32_t GetCursorPositionX() const;                                         // カーソルのX座標を取得
        int32_t GetCursorPositionY() const;                                         // カーソルのY座標を取得
        int32_t GetButtonPressingCount(eButton button) const;                       // ボタンを押しているフレーム数を取得
        int32_t GetButtonReleasingCount(eButton button) const;                      // ボタンを離しているフレーム数を取得
        int32_t GetWheelScrollingCount(eWheelScroll wheelScroll) const;             // ホイールを回転しているフーレム数を取得
        int32_t GetWheelReleasingCount(eWheelScroll wheelScroll) const;             // ホイールを回転していないフレーム数を取得
        void SetWheelScrollVertical(int32_t wheelScrollVertical);                   // ホイールの垂直方向の回転を設定
    private:
        int32_t cursorPositionX_ = 0;                                               ///< @brief カーソルのX座標
        int32_t cursorPositionY_ = 0;                                               ///< @brief カーソルのY座標
        std::array<int32_t, BUTTON_TOTAL_NUMBER> buttonPressingCounts_;             ///< @brief ボタンの押しているフレーム数のカウンタ
        std::array<int32_t, BUTTON_TOTAL_NUMBER> buttonReleasingCounts_;            ///< @brief ボタンの離しているフレーム数のカウンタ
        std::array<int32_t, WHEEL_SCROLL_TOTAL_NUMBER> wheelScrollingCounts_;       ///< @brief ホイールの回転しているフレーム数のカウンタ
        std::array<int32_t, WHEEL_SCROLL_TOTAL_NUMBER> wheelReleasingCounts_;       ///< @brief ホイールの回転していないフレーム数のカウンタ
        int32_t wheelScrollVertical_ = 0;                                           ///< @brief ホイールの垂直方向の回転

        void WheelResetReleasingAndUpScrolling(eWheelScroll wheelScroll);           /* ホイールを回転していないフレーム数のリセットと
                                                                                       回転しているフレーム数の増加*/
        void WheelResetScrollingAndUpReleasing(eWheelScroll wheelScroll);           /* ホイールを回転しているフレーム数のリセットと
                                                                                       回転していないフレーム数の増加*/
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_MouseManager::C_MouseManagerImpl::C_MouseManagerImpl()
    {
        // ボタンのフレーム数のカウンタを初期化
        buttonPressingCounts_.fill(0);
        buttonReleasingCounts_.fill(0);

        // ホイールの回転のフレーム数のカウンタを初期化
        wheelScrollingCounts_.fill(0);
        wheelReleasingCounts_.fill(0);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_MouseManager::C_MouseManagerImpl::~C_MouseManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  カーソルとボタンの更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_MouseManager::C_MouseManagerImpl::CursorAndButtonUpdate()
    {
        // カーソルの座標とボタンの状態を取得
        Uint32 buttonState = ::SDL_GetMouseState(&cursorPositionX_, &cursorPositionY_);

        for (unsigned int i = 0; i < BUTTON_TOTAL_NUMBER; ++i)
        {
            // ボタンが入力されている場合
            if (buttonState & SDL_BUTTON((i + 1)))
            {
                // ボタンを離しているフレーム数をリセットし、
                // ボタンを押しているフレーム数を1増加
                if (buttonReleasingCounts_[i] > 0) buttonReleasingCounts_[i] = 0;

                ++buttonPressingCounts_[i];
            }
            else
            {
                // ボタンを押しているフレーム数をリセットし、
                // ボタンを離しているフレーム数を1増加
                if (buttonPressingCounts_[i] > 0) buttonPressingCounts_[i] = 0;

                ++buttonReleasingCounts_[i];
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  ホイールの更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_MouseManager::C_MouseManagerImpl::WheelUpdate()
    {
        // ホイールが上回転している場合
        if (wheelScrollVertical_ > 0)
        {
            // 上回転をしているフレーム数を上げる
            WheelResetReleasingAndUpScrolling(WHEEL_SCROLL_UP);
            WheelResetScrollingAndUpReleasing(WHEEL_SCROLL_DOWN);
        }
        // ホイールが下回転している場合
        else if (wheelScrollVertical_ < 0)
        {
            // 下回転をしているフレーム数を上げる
            WheelResetReleasingAndUpScrolling(WHEEL_SCROLL_DOWN);
            WheelResetScrollingAndUpReleasing(WHEEL_SCROLL_UP);
        }
        else
        {
            // 上下の離しているフレーム数を上げる
            WheelResetScrollingAndUpReleasing(WHEEL_SCROLL_UP);
            WheelResetScrollingAndUpReleasing(WHEEL_SCROLL_DOWN);
        }

        // ホイールの垂直方向の回転をリセット
        wheelScrollVertical_ = 0;
    }


    /*************************************************************//**
     *
     *  @brief  カーソルのX座標を取得する
     *  @param  なし
     *  @return カーソルのX座標
     *
     ****************************************************************/
    int32_t C_MouseManager::C_MouseManagerImpl::GetCursorPositionX() const
    {
        return cursorPositionX_;
    }


    /*************************************************************//**
     *
     *  @brief  カーソルのY座標を取得する
     *  @param  なし
     *  @return カーソルのY座標
     *
     ****************************************************************/
    int32_t C_MouseManager::C_MouseManagerImpl::GetCursorPositionY() const
    {
        return cursorPositionY_;
    }


    /*************************************************************//**
     *
     *  @brief  ボタンを押しているフレーム数を取得する
     *  @param  ボタン
     *  @return ボタンを押しているフレーム数
     *
     ****************************************************************/
    int32_t C_MouseManager::C_MouseManagerImpl::GetButtonPressingCount(eButton button) const
    {
        return buttonPressingCounts_.at(button);
    }


    /*************************************************************//**
     *
     *  @brief  ボタンを離しているフレーム数を取得する
     *  @param  ボタン
     *  @return ボタンを離しているフレーム数
     *
     ****************************************************************/
    int32_t C_MouseManager::C_MouseManagerImpl::GetButtonReleasingCount(eButton button) const
    {
        return buttonReleasingCounts_.at(button);
    }


    /*************************************************************//**
     *
     *  @brief  ホイールを回転しているフレーム数を取得する
     *  @param  ホイールの回転方向
     *  @return ホイールを回転しているフレーム数
     *
     ****************************************************************/
    int32_t C_MouseManager::C_MouseManagerImpl::GetWheelScrollingCount(eWheelScroll wheelScroll) const
    {
        return wheelScrollingCounts_.at(wheelScroll);
    }


    /*************************************************************//**
     *
     *  @brief  ホイールを回転していないフレーム数を取得する
     *  @param  ホイールの回転方向
     *  @return ホイールを回転していないフレーム数
     *
     ****************************************************************/
    int C_MouseManager::C_MouseManagerImpl::GetWheelReleasingCount(eWheelScroll wheelScroll) const
    {
        return wheelReleasingCounts_.at(wheelScroll);
    }


    /*************************************************************//**
     *
     *  @brief  ホイールを垂直方向の回転を設定する
     *  @param  ホイールの垂直方向の回転
     *  @return なし
     *
     ****************************************************************/
    void C_MouseManager::C_MouseManagerImpl::SetWheelScrollVertical(int32_t wheelScrollVertical)
    {
        wheelScrollVertical_ = wheelScrollVertical;
    }


    /*************************************************************//**
     *
     *  @brief  ホイールの回転していないフレーム数のリセットと
     *  @brief  回転しているフレーム数の増加を行う
     *  @param  ホイールの回転方向
     *  @return なし
     *
     ****************************************************************/
    void C_MouseManager::C_MouseManagerImpl::WheelResetReleasingAndUpScrolling(eWheelScroll wheelScroll)
    {
        if (wheelReleasingCounts_[wheelScroll] > 0)
        {
            wheelReleasingCounts_[wheelScroll] = 0;
        }

        ++wheelScrollingCounts_[wheelScroll];
    }


    /*************************************************************//**
     *
     *  @brief  ホイールの回転しているフレーム数のリセットと
     *  @brief  回転していないフレーム数の増加を行う
     *  @param  ホイールの回転方向
     *  @return なし
     *
     ****************************************************************/
    void C_MouseManager::C_MouseManagerImpl::WheelResetScrollingAndUpReleasing(eWheelScroll wheelScroll)
    {
        if (wheelScrollingCounts_[wheelScroll] > 0)
        {
            wheelScrollingCounts_[wheelScroll] = 0;
        }

        ++wheelReleasingCounts_[wheelScroll];
    }
}