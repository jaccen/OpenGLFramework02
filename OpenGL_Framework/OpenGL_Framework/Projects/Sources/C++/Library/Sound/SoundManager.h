/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Singleton/Singleton.h"
#include <SDL_mixer.h>


//-------------------------------------------------------------
//!
//! @brief サウンド
//! @brief サウンド関連の名前空間
//!
//-------------------------------------------------------------
namespace Sound
{
    /* 別名 */
    using SoundEffect = Mix_Chunk;                                                                                          // SoundEffect型
    using SoundEffectPtr = std::shared_ptr<SoundEffect>;                                                                    // SoundEffecPtr型
    using Bgm = Mix_Music;                                                                                                  // Bgm型
    using BgmPtr = std::shared_ptr<Bgm>;                                                                                    // BgmPtr型


    namespace
    {
        /* 再生の種類 */
        namespace PlayType
        {
            const int32_t s_ONCE = 0;
            const int32_t s_LOOP = -1;
        }

        /* チャネル関連 */
        namespace Channel
        {
            const int32_t s_MAX_COUNT = 16;
            const int32_t s_AUTO_ALLOCATE = -1;
            const int32_t s_ALL = -1;
        }

        /* ボリューム関連 */
        namespace Volume
        {
            const int32_t s_MINIMUM = 0;
            const int32_t s_MAXIMUM = MIX_MAX_VOLUME;
        }

        /* 距離 */
        namespace Distance
        {
            const uint8_t s_NEAREST = 0;
            const uint8_t s_FARTHEST = 255;
        }

        /* 向き */
        namespace Direction
        {
            const int16_t s_FRONT = 0;
            const int16_t s_RIGHT = 90;
            const int16_t s_BACK = 180;
            const int16_t s_LEFT = 270;
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief サウンドマネージャー
    //! @brief サウンドを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_SoundManager : public Singleton::C_Singleton<C_SoundManager>
    {
        friend C_Singleton<C_SoundManager>;                                                                                 // シングルトンクラスをフレンド化
    public:
        bool Initialize();                                                                                                  // 初期化処理
        void Finalize();                                                                                                    // 終了処理
        bool LoadSoundEffect(const std::string& rFilePath);                                                                 // サウンドエフェクトのロード処理
        void ReleaseSoundEffect(const std::string& rFilePath);                                                              // サウンドエフェクトの解放処理
        void AllReleaseSoundEffect();                                                                                       // 全てのサウンドエフェクトを解放
        bool PlaySoundEffect(const SoundEffectPtr& prSoundEffect,                                                           // サウンドエフェクトを再生
                             int32_t allocateChannel = Channel::s_AUTO_ALLOCATE,
                             int32_t playCount = PlayType::s_ONCE,
                             int32_t* pGetAllocateChannel = nullptr);
        bool FadeInPlaySoundEffect(const SoundEffectPtr& prSoundEffect,                                                     // サウンドエフェクトをフェードインで再生
                                   int32_t allocateChannel = Channel::s_AUTO_ALLOCATE,
                                   int32_t playCount = PlayType::s_ONCE,
                                   int32_t fadeInTime = 1000,
                                   int32_t* pGetAllocateChannel = nullptr);
        void PauseSoundEffect(int32_t channel = Channel::s_ALL);                                                            // サウンドエフェクトを一時停止
        void ResumeSoundEffect(int32_t channel = Channel::s_ALL);                                                           // サウンドエフェクトを再び再生
        void StopSoundEffect(int32_t channel = Channel::s_ALL);                                                             // サウンドエフェクトを停止
        void FadeOutStopSoundEffect(int32_t channel = Channel::s_ALL, int32_t fadeOutTime = 1000);                          // サウンドエフェクトをフェードアウトで停止
        bool CheckPlayingSoundEffect(int32_t channel = Channel::s_ALL);                                                     // サウンドエフェクトが再生中か確認
        void SetChannelVolume(int32_t channel = Channel::s_ALL, int32_t volume = Volume::s_MAXIMUM);                        // チャネルのボリュームを設定
        void SetSoundEffectVolume(const SoundEffectPtr& prSoundEffect, int32_t volume = Volume::s_MAXIMUM);                 // サウンドエフェクトのボリュームを設定
        bool SetSoundEffectDistance(int32_t channel, uint8_t distance = Distance::s_NEAREST);                               // サウンドエフェクトの距離を設定
        bool SetSoundEffectPosition(int32_t channel,                                                                        // サウンドエフェクトの方向と距離を設定
                                    int16_t direction = Direction::s_FRONT,
                                    uint8_t distance = Distance::s_NEAREST);
        bool LoadBgm(const std::string& rFileName);                                                                         // BGMのロード処理
        void ReleaseBgm(const std::string& rId);                                                                            // BGMの解放処理
        void AllReleaseBgm();                                                                                               // 全てのBGMを解放
        bool PlayBgm(const BgmPtr& prBgm, int32_t playCount = PlayType::s_ONCE);                                            // BGMを再生
        bool FadeInPlayBgm(const BgmPtr& prBgm,                                                                             // BGMをフェードインで再生
                           int32_t playCount = PlayType::s_ONCE,
                           int32_t fadeInTime = 1000);
        void PauseBgm();                                                                                                    // BGMを一時停止
        void ResumeBgm();                                                                                                   // BGMを再び再生
        void StopBgm();                                                                                                     // BGMを停止
        void FadeOutStopBgm(int32_t fadeOutTime = 1000);                                                                    // BGMをフェードアウトで停止
        void RewindBgm();                                                                                                   // BGMを巻き戻して再生
        bool CheckPlayingBgm();                                                                                             // BGMが再生中か確認
        void SetBgmVolume(int32_t volume = Volume::s_MAXIMUM);                                                              // BGMのボリュームを設定
        bool SetBgmStartTime(double startTime);                                                                             // BGMの開始時間を設定
        void AllRelease();                                                                                                  // サウンドエフェクトとBGMを全て解放
        boost::optional<const SoundEffectPtr&> GetSoundEffect(const std::string& rFilePath) const;                          // サウンドエフェクトを取得
        boost::optional<const BgmPtr&> GetBgm(const std::string& rFilePath) const;                                          // BGMを取得
    private:
        /* 前方宣言 */
        class C_SoundManagerImpl;

        std::unique_ptr<C_SoundManagerImpl> upImpl_;                                                                        ///< @brief 実装情報

        C_SoundManager();                                                                                                   // コンストラクタ
        ~C_SoundManager() override;                                                                                         // デストラクタ
    };
}