/* ヘッダファイル */
#include "SoundManagerImpl.h"
#include "../Debug/Helper/DebugHelper.h"
#include <SDL.h>


//-------------------------------------------------------------
//!
//! @brief サウンド
//! @brief サウンド関連の名前空間
//!
//-------------------------------------------------------------
namespace Sound
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SoundManager::C_SoundManager() :

        // 実装情報
        upImpl_(std::make_unique<C_SoundManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SoundManager::~C_SoundManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ミキサーAPIを開く処理を行う
     *  @param  なし
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SoundManager::Initialize()
    {
        // 初期化されていない場合、初期化する
        if (::SDL_WasInit(SDL_INIT_AUDIO) == 0) ::SDL_InitSubSystem(SDL_INIT_AUDIO);

        // ミキサーAPIを開く
        const int32_t CHUNK_SIZE = 4096;

        if (::Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, CHUNK_SIZE) < 0)
        {
            PrintLog("[ C_SoundManager::Initialize ] : ミックスオーディオを開くのに失敗しました。\n");
            PrintLog("                    エラー内容 : %s\n", Mix_GetError());

            return false;
        }

        // 同時再生音数を設定
        ::Mix_AllocateChannels(Channel::s_MAX_COUNT);

        // 終了処理のフラグを下げる
        upImpl_->SetFinalizeFlag(false);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトとBGMの終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::Finalize()
    {
        upImpl_->Finalize();
        upImpl_->SetFinalizeFlag(true);
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトのロードを行う
     *  @param  ファイルパス
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SoundManager::LoadSoundEffect(const std::string& rFilePath)
    {
        if (upImpl_->LoadSoundEffect(rFilePath) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトの解放を行う
     *  @param  ファイルパス
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::ReleaseSoundEffect(const std::string& rFilePath)
    {
        upImpl_->ReleaseSoundEffect(rFilePath);
    }


    /*************************************************************//**
     *
     *  @brief  全てのサウンドエフェクトの解放を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::AllReleaseSoundEffect()
    {
        upImpl_->AllReleaseSoundEffect();
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトの再生を行う
     *  @param  サウンドエフェクト
     *  @param  割り当てるチャネル( -1の場合は自動割り当て )
     *  @param  再生回数( -1の場合はループ再生 )
     *  @param  割り当てられたチャネルを取得するポインタ
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SoundManager::PlaySoundEffect(const SoundEffectPtr& prSoundEffect,
        int32_t allocateChannel,
        int32_t playCount,
        int32_t* pGetAllocateChannel)
    {
        assert(prSoundEffect);

        // サウンドエフェクトを再生し、割り当てられたチャネルを取得
        int32_t allocatedChannel = Mix_PlayChannel(allocateChannel, prSoundEffect.get(), playCount);

        if (allocatedChannel == s_ALLOCATE_CHANNEL_ERROR_VALUE)
        {
            PrintLog("[ C_SoundManager::PlaySoundEffect ] : チャネルの割り当てに失敗しました。\n");
            PrintLog("                         エラー内容 : %s\n", Mix_GetError());

            return false;
        }

        // ポインタが設定されている場合は割り当てられたチャネルを取得する
        if (pGetAllocateChannel != nullptr) *pGetAllocateChannel = allocatedChannel;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトのフェードインでの再生を行う
     *  @param  サウンドエフェクト
     *  @param  割り当てるチャネル( -1の場合は自動割り当て )
     *  @param  再生回数( -1の場合はループ再生 )
     *  @param  フェードインの時間
     *  @param  割り当てられたチャネルを取得するポインタ
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SoundManager::FadeInPlaySoundEffect(const SoundEffectPtr& prSoundEffect,
        int32_t allocateChannel,
        int32_t playCount,
        int32_t fadeInTime,
        int32_t* pGetAllocateChannel)
    {
        assert(prSoundEffect);

        // サウンドエフェクトをフェードインで再生し、割り当てられたチャネルを取得
        int32_t allocatedChannel = Mix_FadeInChannel(allocateChannel, prSoundEffect.get(), playCount, fadeInTime);

        if (allocatedChannel == s_ALLOCATE_CHANNEL_ERROR_VALUE)
        {
            PrintLog("[ C_SoundManager::FadeInPlaySoundEffect ] : チャネルの割り当てに失敗しました。\n");
            PrintLog("                               エラー内容 : %s\n", Mix_GetError());

            return false;
        }

        // ポインタが設定されている場合は割り当てられたチャネルを取得する
        if (pGetAllocateChannel != nullptr) *pGetAllocateChannel = allocatedChannel;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトの一時停止を行う
     *  @param  チャネル( -1の場合はすべて一時停止 )
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::PauseSoundEffect(int32_t channel)
    {
        assert(channel < Channel::s_MAX_COUNT);

        ::Mix_Pause(channel);
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトの再び再生を行う
     *  @param  チャネル( -1の場合はすべて一時停止 )
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::ResumeSoundEffect(int32_t channel)
    {
        assert(channel < Channel::s_MAX_COUNT);

        ::Mix_Resume(channel);
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトの停止を行う
     *  @param  チャネル( -1の場合はすべて一時停止 )
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::StopSoundEffect(int32_t channel)
    {
        assert(channel < Channel::s_MAX_COUNT);

        ::Mix_HaltChannel(channel);
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトのフェードアウトでの停止を行う
     *  @param  チャネル( -1の場合はすべて一時停止 )
     *  @param  フェードアウトの時間
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::FadeOutStopSoundEffect(int32_t channel, int32_t fadeOutTime)
    {
        assert(channel < Channel::s_MAX_COUNT);
        assert(fadeOutTime >= 0);

        ::Mix_FadeOutChannel(channel, fadeOutTime);
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトが再生中か確認を行う
     *  @param  チャネル( -1の場合はすべて一時停止 )
     *  @return 再生中：true
     *  @return 停止中：false
     *
     ****************************************************************/
    bool C_SoundManager::CheckPlayingSoundEffect(int32_t channel)
    {
        if (::Mix_Playing(channel) == 0) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  チャネルのボリューム設定を行う
     *  @param  チャネル( -1の場合はすべて設定 )
     *  @param  ボリューム
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::SetChannelVolume(int32_t channel, int32_t volume)
    {
        assert(channel < Channel::s_MAX_COUNT);

        // 適切なボリュームに修正する
        upImpl_->RepairAppositeVolume(&volume);

        // チャネルのボリュームを設定
        ::Mix_Volume(channel, volume);
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトのボリューム設定を行う
     *  @param  サウンドエフェクト
     *  @param  ボリューム
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::SetSoundEffectVolume(const SoundEffectPtr& prSoundEffect, int32_t volume)
    {
        assert(prSoundEffect);

        // 適切なボリュームに修正する
        upImpl_->RepairAppositeVolume(&volume);

        // サウンドエフェクトのボリュームを設定
        ::Mix_VolumeChunk(prSoundEffect.get(), volume);
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトの距離の設定を行う
     *  @param  チャネル
     *  @param  距離( 0が最も近く、255が最も遠い )
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SoundManager::SetSoundEffectDistance(int32_t channel, uint8_t distance)
    {
        assert(channel < Channel::s_MAX_COUNT);

        // 適切な距離に修正
        upImpl_->RepairAppositeDistance(&distance);

        // サウンドエフェクトの距離を設定
        if (::Mix_SetDistance(channel, distance) == 0)
        {
            PrintLog("[ C_SoundManager::SetSoundEffectDistance ] : 距離の設定に失敗しました。\n");
            PrintLog("                                エラー内容 : %s\n", Mix_GetError());

            return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトの方向と距離の設定を行う
     *  @param  チャネル
     *  @param  方向( 0が前、90が右、180が後ろ、270が左 )
     *  @param  距離( 0が最も近く、255が最も遠い )
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SoundManager::SetSoundEffectPosition(int32_t channel, int16_t direction, uint8_t distance)
    {
        assert(channel < Channel::s_MAX_COUNT);
        assert(direction >= 0 || direction <= 360);

        // 適切な距離に修正
        upImpl_->RepairAppositeDistance(&distance);

        // サウンドエフェクトの方向と距離を設定
        if (::Mix_SetPosition(channel, direction, distance) == 0)
        {
            PrintLog("[ C_SoundManager::SetSoundEffectPosition ] : 方向と距離の設定に失敗しました。\n");
            PrintLog("                                エラー内容 : %s\n", Mix_GetError());

            return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  BGMのロードを行う
     *  @param  ファイルパス
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SoundManager::LoadBgm(const std::string& rFilePath)
    {
        if (upImpl_->LoadBgm(rFilePath) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  BGMの解放を行う
     *  @param  ファイスパス
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::ReleaseBgm(const std::string& rFilePath)
    {
        upImpl_->ReleaseBgm(rFilePath);
    }


    /*************************************************************//**
     *
     *  @brief  BGMを全て解放する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::AllReleaseBgm()
    {
        upImpl_->AllReleaseBgm();
    }


    /*************************************************************//**
     *
     *  @brief  BGMの再生を行う
     *  @param  BGM
     *  @param  再生回数( -1の場合はループ再生 )
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SoundManager::PlayBgm(const BgmPtr& prBgm, int32_t playCount)
    {
        assert(prBgm);

        // BGMを再生
        if (::Mix_PlayMusic(prBgm.get(), playCount) == s_PLAY_BGM_ERROR_VALUE)
        {
            PrintLog("[ C_SoundManager::PlayBGM ] : BGMの再生に失敗しました。\n");
            PrintLog("                 エラー内容 : %s\n", Mix_GetError());

            return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  BGMのフェードインでの再生を行う
     *  @param  BGM
     *  @param  再生回数( -1の場合はループ再生 )
     *  @param  フェードインの時間
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SoundManager::FadeInPlayBgm(const BgmPtr& prBgm,
        int32_t playCount,
        int32_t fadeInTime)
    {
        assert(prBgm);

        // BGMを再生
        if (::Mix_FadeInMusic(prBgm.get(), playCount, fadeInTime) == s_PLAY_BGM_ERROR_VALUE)
        {
            PrintLog("[ C_SoundManager::FadeInPlayBGM ] : フェードインでの再生に失敗しました。\n");
            PrintLog("                       エラー内容 : %s\n", Mix_GetError());

            return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  BGMの一時停止を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::PauseBgm()
    {
        // BGMを一時停止
        ::Mix_PauseMusic();
    }


    /*************************************************************//**
     *
     *  @brief  BGMの再び再生を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::ResumeBgm()
    {
        // BGMを再び再生
        ::Mix_ResumeMusic();
    }


    /*************************************************************//**
     *
     *  @brief  BGMの停止を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::StopBgm()
    {
        // BGMを停止
        ::Mix_HaltMusic();
    }


    /*************************************************************//**
     *
     *  @brief  BGMのフェードアウトでの停止を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::FadeOutStopBgm(int32_t fadeOutTime)
    {
        assert(fadeOutTime >= 0);

        // BGMをフェードアウトで停止
        ::Mix_FadeOutMusic(fadeOutTime);
    }


    /*************************************************************//**
     *
     *  @brief  BGMの巻き戻し再生を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::RewindBgm()
    {
        // BGMを巻き戻して再生
        ::Mix_RewindMusic();
    }


    /*************************************************************//**
     *
     *  @brief  BGMが再生中か確認を行う
     *  @param  なし
     *  @return 再生中：true
     *  @return 停止中：false
     *
     ****************************************************************/
    bool C_SoundManager::CheckPlayingBgm()
    {
        if (::Mix_PlayingMusic() == 0) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  BGMのボリューム設定を行う
     *  @param  ボリューム
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::SetBgmVolume(int32_t volume)
    {
        // 適切なボリュームに修正する
        upImpl_->RepairAppositeVolume(&volume);

        // BGMのボリュームを設定
        ::Mix_VolumeMusic(volume);
    }


    /*************************************************************//**
     *
     *  @brief  BGMの開始時間の設定を行う
     *  @param  開始時間( 秒単位 )
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SoundManager::SetBgmStartTime(double startTime)
    {
        const int32_t SET_POSITION_ERROR_VALUE = -1;

        if (::Mix_SetMusicPosition(startTime) == SET_POSITION_ERROR_VALUE)
        {
            PrintLog("[ C_SoundManager::SetBgmStartTime ] : 開始時間の設定に失敗しました。\n");
            PrintLog("                         エラー内容 : %s\n", Mix_GetError());

            return false;
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトとBGMを全て解放する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::AllRelease()
    {
        upImpl_->AllRelease();
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトの取得を行う
     *  @param  ファイルパス
     *  @return サウンドエフェクト
     *
     ****************************************************************/
    boost::optional<const SoundEffectPtr&> C_SoundManager::GetSoundEffect(const std::string& rFilePath) const
    {
        return upImpl_->GetSoundEffect(rFilePath);
    }


    /*************************************************************//**
     *
     *  @brief  BGMの取得を行う
     *  @param  ファイルパス
     *  @return BGM
     *
     ****************************************************************/
    boost::optional<const BgmPtr&> C_SoundManager::GetBgm(const std::string& rFilePath) const
    {
        return upImpl_->GetBgm(rFilePath);
    }
}