/* ヘッダファイル */
#include "TimeManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief タイマー
//! @brief タイマー関連の名前空間
//!
//-------------------------------------------------------------
namespace Timer
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_TimeManager::C_TimeManager() :

        // 実装情報
        upImpl_(std::make_unique<C_TimeManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_TimeManager::~C_TimeManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TimeManager::Initialize()
    {
        upImpl_->Initialize();
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_TimeManager::Update()
    {
        upImpl_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  処理速度の計測を行う
     *  @param  計測したい関数
     *  @return 計測時間( 秒単位 )
     *
     ****************************************************************/
    float C_TimeManager::MeasureProcess(const std::function<void()>& rFunction)
    {
        float startTime = GetTime();

        rFunction();

        float endTime = GetTime();

        return (endTime - startTime);
    }


    /*************************************************************//**
     *
     *  @brief  フレームスキップを有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_TimeManager::EnableFrameSkip(bool validFlag)
    {
        upImpl_->EnableFrameSkip(validFlag);
    }


    /*************************************************************//**
     *
     *  @brief  FPSを取得する
     *  @param  なし
     *  @return FPS
     *
     ****************************************************************/
    int16_t C_TimeManager::GetFps() const
    {
        return upImpl_->GetFps();
    }


    /*************************************************************//**
     *
     *  @brief  現在のFPSを取得する
     *  @param  なし
     *  @return 現在のFPS
     *
     ****************************************************************/
    float C_TimeManager::GetNowFps() const
    {
        return upImpl_->GetNowFps();
    }


    /*************************************************************//**
     *
     *  @brief  プログラムを開始してからの時間
     *  @brief  ( 厳密にはSDLの初期化後の時間 )を取得する
     *  @param  なし
     *  @return プログラムを開始してからの時間( 秒単位 )
     *
     ****************************************************************/
    float C_TimeManager::GetTime() const
    {
        return static_cast<float>(upImpl_->GetTime()) * s_RECIPROCAL_ONE_TOUSAND_MILLISECONDS * upImpl_->GetTimeScale();
    }


    /*************************************************************//**
     *
     *  @brief  差分( 経過 )時間を取得する
     *  @param  なし
     *  @return 差分時間( 秒単位 )
     *
     ****************************************************************/
    float C_TimeManager::GetDeltaTime() const
    {
        return static_cast<float>(upImpl_->GetDeltaTime()) * s_RECIPROCAL_ONE_TOUSAND_MILLISECONDS * upImpl_->GetTimeScale();
    }


    /*************************************************************//**
     *
     *  @brief  ゲームが開始してから経過したフレーム数を取得する
     *  @param  なし
     *  @return ゲームが開始してから経過したフレーム数
     *
     ****************************************************************/
    uint32_t C_TimeManager::GetFrameCount() const
    {
        return upImpl_->GetFrameCount();
    }


    /*************************************************************//**
     *
     *  @brief  描画フラグを取得する
     *  @param  なし
     *  @return 描画フラグ
     *
     ****************************************************************/
    bool C_TimeManager::IsDrawFlag() const
    {
        return upImpl_->IsDrawFlag();
    }


    /*************************************************************//**
     *
     *  @brief  時間のスケールを取得する
     *  @param  なし
     *  @return 時間のスケール
     *
     ****************************************************************/
    float C_TimeManager::GetTimeScale() const
    {
        return upImpl_->GetTimeScale();
    }


    /*************************************************************//**
     *
     *  @brief  FPSを設定する
     *  @param  FPS
     *  @return なし
     *
     ****************************************************************/
    void C_TimeManager::SetFps(int16_t fps)
    {
        upImpl_->SetFps(fps);
    }


    /*************************************************************//**
     *
     *  @brief  時間のスケールを設定する
     *  @param  時間のスケール
     *  @return なし
     *
     ****************************************************************/
    void C_TimeManager::SetTimeScale(float timeScale)
    {
        upImpl_->SetTimeScale(timeScale);
    }


    /*************************************************************//**
     *
     *  @brief  待機処理をするか判断するフラグを設定する
     *  @param  待機処理をするか判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_TimeManager::SetWaitFlag(bool waitFlag)
    {
        upImpl_->SetWaitFlag(waitFlag);
    }
}