/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Singleton/Singleton.h"
#include <SDL_keyboard.h>


//-------------------------------------------------------------
//!
//! @brief インプット
//! @brief 入力関連の名前空間
//!
//-------------------------------------------------------------
namespace Input
{
    /* 別名 */
    using KeyCode = SDL_Scancode;                                   // KeyCode型


    //-------------------------------------------------------------
    //!
    //! @brief キーボードマネージャー
    //! @brief キー入力の管理をするクラス
    //!
    //-------------------------------------------------------------
    class C_KeyboardManager : public Singleton::C_Singleton<C_KeyboardManager>
    {

        friend C_Singleton<C_KeyboardManager>;                              // シングルトンクラスをフレンド化
    public:
        void Initialize();                                                  // 初期化処理
        void Update();                                                      // 更新処理
        int32_t GetPressingCount(KeyCode keycode) const;                    // 押しているフレーム数を取得
        int32_t GetReleasingCount(KeyCode keycode) const;                   // 離しているフレーム数を取得
        const std::string& GetInputCharacter() const;                       // 入力した文字を取得
        void SetInputCharacter(const std::string& rInputCharacter);         // 入力した文字を設定
    private:
        /* 前方宣言 */
        class C_KeyboardManagerImpl;

        std::unique_ptr<C_KeyboardManagerImpl> upImpl_;                     ///< @brief 実装情報

        C_KeyboardManager();                                                // コンストラクタ
        ~C_KeyboardManager() override;                                      // デストラクタ
    };
}
