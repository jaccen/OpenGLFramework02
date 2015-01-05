/* ヘッダファイル */
#include "TimeManager.h"
#include <thread>
#include <chrono>


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
        const int16_t s_AVERAGE_SAMPLE_NUMBER = 30;                                         ///< @brief 平均を計算するサンプル数
        const int32_t s_ONE_TOUSAND_MILLISECONDS = 1000;                                    ///< @brief 1000ミリ秒( 1秒 )
        const float s_RECIPROCAL_ONE_TOUSAND_MILLISECONDS = 0.001f;                         ///< @brief 1000ミリ秒の逆数
    }


    //-------------------------------------------------------------
    //!
    //! @brief タイムマネージャーインプリメント
    //! @brief タイマーマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_TimeManager::C_TimeManagerImpl
    {
    public:
        C_TimeManagerImpl();                                                                // コンストラクタ
        ~C_TimeManagerImpl();                                                               // デストラクタ
        void Initialize();                                                                  // 初期化処理
        void Update();                                                                      // 更新処理
        void EnableFrameSkip(bool validFlag);                                               // フレームスキップを有効化
        int16_t GetFps() const;                                                             // FPSを取得
        float GetNowFps() const;                                                            // 現在のFPSを取得
        uint64_t GetTime() const;                                                           // プログラムを開始してからの時間を取得
        uint64_t GetDeltaTime() const;                                                      // 1フレームの差分( 経過 )時間を取得
        uint32_t GetFrameCount() const;                                                     // フレーム数のカウンタを取得
        bool IsDrawFlag() const;                                                            // 描画フラグを取得
        float GetTimeScale() const;                                                         // 時間のスケールを取得
        void SetFps(int16_t fps);                                                           // FPSを設定
        void SetTimeScale(float timeScale);                                                 // 時間のスケールを設定
        void SetWaitFlag(bool waitFlag);                                                    // 待機処理をするか判断するフラグ
    private:
        /* 型変換 */
        using Milliseconds = std::chrono::milliseconds;                                     // Milliseconds型を宣言

        std::chrono::time_point<std::chrono::system_clock> startTimePoint_;                 ///< @brief 開始時のタイムポイント
        uint64_t startTime_ = 0;                                                            ///< @brief 測定開始時間
        uint64_t endTime_ = 0;                                                              ///< @brief 測定終了時間
        uint64_t deltaTime_ = 0;                                                            ///< @brief 差分時間
        int32_t loopCount_ = 1;                                                             ///< @brief ループの回数を数えるカウンタ
        uint32_t frameCount_ = 1;                                                           ///< @brief フレーム数のカウンタ
        int16_t fps_ = Default::s_FPS;                                                      ///< @brief FPS
        float nowFps_ = 0.0;                                                                ///< @brief 現在のFPS
        bool drawFlag_ = true;                                                              ///< @brief 描画を判断するフラグ
        bool frameSkipFlag_ = true;                                                         ///< @brief フレームスキップを行うか判断するフラグ
        float timeScale_ = 1.0;                                                             ///< @brief 時間のスケール
        bool waitFlag_ = true;                                                              ///< @brief 待機処理をするか判断するフラグ

        void Wait();                                                                        // 待機処理
        void Calculate();                                                                   // 計算処理
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_TimeManager::C_TimeManagerImpl::C_TimeManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_TimeManager::C_TimeManagerImpl::~C_TimeManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TimeManager::C_TimeManagerImpl::Initialize()
    {
        // 開始時のタイムポイントを取得
        startTimePoint_ = std::chrono::high_resolution_clock::now();

        // 測定開始時間を取得
        startTime_ = GetTime();
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TimeManager::C_TimeManagerImpl::Update()
    {
        // 待機処理
        Wait();

        // 計算処理
        Calculate();
    }


    /*************************************************************//**
     *
     *  @brief  フレームスキップを有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_TimeManager::C_TimeManagerImpl::EnableFrameSkip(bool validFlag)
    {
        frameSkipFlag_ = validFlag;
        if (frameSkipFlag_ == false) drawFlag_ = true;
    }


    /*************************************************************//**
     *
     *  @brief  FPSを取得する
     *  @param  なし
     *  @return FPS
     *
     ****************************************************************/
    int16_t C_TimeManager::C_TimeManagerImpl::GetFps() const
    {
        return fps_;
    }


    /*************************************************************//**
     *
     *  @brief  現在のFPSを取得する
     *  @param  なし
     *  @return 現在のFPS
     *
     ****************************************************************/
    float C_TimeManager::C_TimeManagerImpl::GetNowFps() const
    {
        return nowFps_;
    }


    /*************************************************************//**
     *
     *  @brief  プログラムを開始してからの時間を取得する
     *  @param  なし
     *  @return プログラムを開始してからの時間
     *
     ****************************************************************/
    uint64_t C_TimeManager::C_TimeManagerImpl::GetTime() const
    {
        return std::chrono::duration_cast<Milliseconds>(std::chrono::high_resolution_clock::now() - startTimePoint_).count();
    }


    /*************************************************************//**
     *
     *  @brief  1フレームの差分( 経過 )時間を取得する
     *  @param  なし
     *  @return 差分時間( 秒単位 )
     *
     ****************************************************************/
    uint64_t C_TimeManager::C_TimeManagerImpl::GetDeltaTime() const
    {
        return deltaTime_;
    }


    /*************************************************************//**
     *
     *  @brief  フレーム数のカウンタを取得する
     *  @param  なし
     *  @return フレーム数のカウンタ
     *
     ****************************************************************/
    uint32_t C_TimeManager::C_TimeManagerImpl::GetFrameCount() const
    {
        return frameCount_;
    }


    /*************************************************************//**
     *
     *  @brief  描画フラグを取得する
     *  @param  なし
     *  @return 描画フラグ
     *
     ****************************************************************/
    bool C_TimeManager::C_TimeManagerImpl::IsDrawFlag() const
    {
        return drawFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  時間のスケールを取得する
     *  @param  なし
     *  @return 時間のスケール
     *
     ****************************************************************/
    float C_TimeManager::C_TimeManagerImpl::GetTimeScale() const
    {
        return timeScale_;
    }


    /*************************************************************//**
     *
     *  @brief  FPSを設定する
     *  @param  FPS
     *  @return なし
     *
     ****************************************************************/
    void C_TimeManager::C_TimeManagerImpl::SetFps(int16_t fps)
    {
        assert(fps > 0);

        fps_ = fps;
    }


    /*************************************************************//**
     *
     *  @brief  時間のスケールを設定する
     *  @param  時間のスケール
     *  @return なし
     *
     ****************************************************************/
    void C_TimeManager::C_TimeManagerImpl::SetTimeScale(float timeScale)
    {
        timeScale_ = timeScale;
    }


    /*************************************************************//**
     *
     *  @brief  待機処理をするか判断するフラグを設定する
     *  @param  待機処理をするか判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_TimeManager::C_TimeManagerImpl::SetWaitFlag(bool waitFlag)
    {
        waitFlag_ = waitFlag;
    }


    /*************************************************************//**
     *
     *  @brief  待機処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TimeManager::C_TimeManagerImpl::Wait()
    {
        // 以前の終了時間を保持し、終了時間を取得
        uint64_t beforeEndTime = endTime_;
        endTime_ = GetTime();

        // 1フレームの差分( 経過 )時間を求める
        deltaTime_ = endTime_ - beforeEndTime;

        if (waitFlag_ == true)
        {
            // 測定開始時間からの経過時間を求める
            uint64_t elapsedTime = endTime_ - startTime_;

            // 待機時間を求める
            int32_t waitTime = loopCount_ * s_ONE_TOUSAND_MILLISECONDS / fps_ - static_cast<int32_t>(elapsedTime);

            // 待機時間がある場合
            if (waitTime > 0)
            {
                // 描画フラグを上げる
                drawFlag_ = true;

                // 待機時間分だけ待つ
                std::this_thread::sleep_for(Milliseconds(waitTime));
            }
            else
            {
                // フレームスキップ有効時は描画フラグを下げる
                if (frameSkipFlag_ == true) drawFlag_ = false;
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  経過時間などの計算を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TimeManager::C_TimeManagerImpl::Calculate()
    {
        // 平均時間を求めるサンプル数の回数分、ループを回した場合
        if (loopCount_ >= s_AVERAGE_SAMPLE_NUMBER)
        {
            // 現在の時間を取得
            uint64_t nowTime = GetTime();

            // 経過時間を求める
            float elapsedTime = static_cast<float>(nowTime - startTime_);

            // 現在のFPSを求める
            nowFps_ = static_cast<float>(s_ONE_TOUSAND_MILLISECONDS) / (elapsedTime / static_cast<float>(s_AVERAGE_SAMPLE_NUMBER));

            // ループを数えるカウンタをリセット
            loopCount_ = 1;

            // 測定開始時間を更新
            startTime_ = nowTime;
        }
        else
        {
            // ループの回数を1増加
            ++loopCount_;
        }

        // フレーム数のカウンタを1増加
        ++frameCount_;
    }
}