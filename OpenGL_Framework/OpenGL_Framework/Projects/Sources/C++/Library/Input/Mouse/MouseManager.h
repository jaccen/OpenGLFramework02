/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Singleton/Singleton.h"


//-------------------------------------------------------------
//!
//! @brief インプット
//! @brief 入力関連の名前空間
//!
//-------------------------------------------------------------
namespace Input
{
    /** マウスボタン */
    enum eButton
    {
        BUTTON_LEFT,                                                            ///< @brief マウスの左ボタン
        BUTTON_MIDDLE,                                                          ///< @brief マウスのホイールボタン
        BUTTON_RIGHT,                                                           ///< @brief マウスの右ボタン
        BUTTON_EXTRA1,                                                          ///< @brief マウスの余分なボタン1
        BUTTON_EXTRA2,                                                          ///< @brief マウスの余分なボタン2

        BUTTON_TOTAL_NUMBER,                                                    ///< @brief マウスボタンの総数
    };

    /** マウスホイールの回転方向 */
    enum eWheelScroll
    {
        WHEEL_SCROLL_UP,                                                        ///< @brief マウスホイールの上回転
        WHEEL_SCROLL_DOWN,                                                      ///< @brief マウスホイールの下回転

        WHEEL_SCROLL_TOTAL_NUMBER,                                              ///< @brief マウスホイールの回転方向の総数
    };

    //-------------------------------------------------------------
    //!
    //! @brief マウスマネージャー
    //! @brief マウス入力を管理するクラス
    //!
    //-------------------------------------------------------------
    class C_MouseManager : public Singleton::C_Singleton<C_MouseManager>
    {
        friend C_Singleton<C_MouseManager>;                                     // シングルトンをフレンド化
    public:
        void Update();                                                          // 更新処理
        int32_t GetCursorPositionX() const;                                     // カーソルのX座標を取得
        int32_t GetCursorPositionY() const;                                     // カーソルのY座標を取得
        int32_t GetButtonPressingCount(eButton button) const;                   // ボタンを押しているフレーム数を取得
        int32_t GetButtonReleasingCount(eButton button) const;                  // ボタンを離しているフレーム数を取得
        int32_t GetWheelScrollingCount(eWheelScroll wheelScroll) const;         // ホイールを回転しているフーレム数を取得
        int32_t GetWheelReleasingCount(eWheelScroll wheelScroll) const;         // ホイールを回転していないフレーム数を取得
        void SetWheelScrollVertical(int32_t wheelScrollVertical);               // ホイールの垂直方向の回転を設定
    private:
        /* 前方宣言 */
        class C_MouseManagerImpl;

        std::unique_ptr<C_MouseManagerImpl> upImpl_;                            ///< @brief 実装情報

        C_MouseManager();                                                       // コンストラクタ
        ~C_MouseManager() override;                                             // デストラクタ
    };
}