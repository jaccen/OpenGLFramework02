/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Singleton/Singleton.h"


//-------------------------------------------------------------
//!
//! @brief SDL
//! @brief SDL関連の名前空間
//!
//-------------------------------------------------------------
namespace SDL
{
    //-------------------------------------------------------------
    //!
    //! @brief SDLマネージャー
    //! @brief SDLを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_SdlManager : public Singleton::C_Singleton<C_SdlManager>
    {
        friend C_Singleton<C_SdlManager>;           // シングルトンクラスをフレンド化
    public:
        bool Initialize();                          // 初期化処理
        void Finalize();                            // 終了処理
    private:
        bool finalizeFlag_ = false;                 ///< @brief 終了処理を行ったか判断するフラグ 

        C_SdlManager();                             // コンストラクタ
        ~C_SdlManager() override;                   // デストラクタ
    };
}