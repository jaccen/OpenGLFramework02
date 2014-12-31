/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Singleton/Singleton.h"
#include <chrono>
#include <functional>


//-------------------------------------------------------------
//!
//! @brief タイマー
//! @brief タイマー関連の名前空間
//!
//-------------------------------------------------------------
namespace Timer
{
    namespace
    {
        /* デフォルト */
        namespace Default
        {
            const int16_t s_FPS = 60;
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief タイムマネージャー
    //! @brief タイマーを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_TimeManager : public Singleton::C_Singleton<C_TimeManager>
    {
        friend C_Singleton<C_TimeManager>;                                  //シングルトンクラスをフレンド化
    public:
        void Initialize();                                                  // 初期化処理
        void Update();                                                      // 更新処理
        float MeasureProcess(const std::function<void()>& rFunction);       // 処理速度を計測
        void EnableFrameSkip(bool validFlag = true);                        // フレームスキップを有効化
        int16_t GetFps() const;                                             // FPSを取得
        float GetNowFps() const;                                            // 現在のFPSを取得
        float GetTime() const;                                              // プログラムを開始してからの時間を取得
        float GetDeltaTime() const;                                         // 1フレームの差分( 経過 )時間を取得
        uint32_t GetFrameCount() const;                                     // ゲームが開始してから経過したフレーム数を取得
        bool IsDrawFlag() const;                                            // 描画フラグを取得
        float GetTimeScale() const;                                         // 時間のスケールを取得
        void SetFps(int16_t fps = Default::s_FPS);                          // FPSを設定
        void SetTimeScale(float timeScale = 1.0f);                          // 時間のスケールを設定
        void SetWaitFlag(bool waitFlag = true);                             // 待機処理をするか判断するフラグを設定
    private:
        /* 前方宣言 */
        class C_TimeManagerImpl;

        std::unique_ptr<C_TimeManagerImpl> upImpl_;                         ///< @brief 実装情報

        C_TimeManager();                                                    // コンストラクタ
        ~C_TimeManager() override;                                          // デストラクタ
    };
}