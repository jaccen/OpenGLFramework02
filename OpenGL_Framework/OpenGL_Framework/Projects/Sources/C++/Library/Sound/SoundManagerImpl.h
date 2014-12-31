/* ヘッダファイル */
#include "SoundManager.h"
// #include "Common.h"
#include "../Debug/Helper/DebugHelper.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief サウンド
//! @brief サウンド関連の名前空間
//!
//-------------------------------------------------------------
namespace Sound
{
    namespace
    {
        const int32_t s_ALLOCATE_CHANNEL_ERROR_VALUE = -1;                                               ///< @brief チャネル割り当てのエラー値
        const int32_t s_PLAY_BGM_ERROR_VALUE = -1;                                                       ///< @brief BGM再生のエラー値
    }

    //-------------------------------------------------------------
    //!
    //! @brief サウンドマネージャーインプリメント
    //! @brief サウンドマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_SoundManager::C_SoundManagerImpl
    {
    public:
        C_SoundManagerImpl();                                                                           // コンストラクタ
        ~C_SoundManagerImpl();                                                                          // デストラクタ
        void Finalize();                                                                                // 終了処理
        bool LoadSoundEffect(const std::string& rFilePath);                                             // サウンドエフェクトのロード処理
        void ReleaseSoundEffect(const std::string& rFilePath);                                          // サウンドエフェクトの解放処理
        void AllReleaseSoundEffect();                                                                   // サウンドエフェクトを全て解放
        bool LoadBgm(const std::string& rFilePath);                                                     // BGMのロード処理
        void ReleaseBgm(const std::string& rFilePath);                                                  // BGMの解放処理
        void AllReleaseBgm();                                                                           // BGMを全て解放
        void AllRelease();                                                                              // サウンドエフェクトとBGMを全て解放
        void RepairAppositeVolume(int32_t* pVolume);                                                    // 適切なボリュームに修正
        void RepairAppositeDistance(uint8_t* pDistance);                                                // 適切な距離に修正
        boost::optional<const SoundEffectPtr&> GetSoundEffect(const std::string& rFilePath) const;      // サウンドエフェクトの取得
        boost::optional<const BgmPtr&> GetBgm(const std::string& rFilePath) const;                      // BGMの取得
        void SetFinalizeFlag(bool finalizeFlag);                                                        // 終了処理を行ったか判断するフラグを設定
    private:
        std::unordered_map<std::string, SoundEffectPtr> pSoundEffects_;                                 ///< @brief サウンドエフェクト
        std::unordered_map<std::string, BgmPtr> pBgms_;                                                 ///< @brief BGM
        bool finalizeFlag_ = false;                                                                     ///< @brief 終了処理を行ったか判断するフラグ
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SoundManager::C_SoundManagerImpl::C_SoundManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SoundManager::C_SoundManagerImpl::~C_SoundManagerImpl()
    {
        if (finalizeFlag_ == false) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトとBGMの終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::Finalize()
    {
        // サウンドエフェクトとBGMを全て解放
        AllRelease();

        // ミキサーAPIを閉じる
        ::Mix_CloseAudio();
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトのロードを行う
     *  @param  ファイルパス
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SoundManager::C_SoundManagerImpl::LoadSoundEffect(const std::string& rFilePath)
    {
        // 既に同じサウンドエフェクトをロードしている場合
        if (pSoundEffects_.find(rFilePath) != pSoundEffects_.end())
        {
            std::cout << "[ C_SoundManagerImpl::LoadSoundEffect ] : 既に同じサウンドエフェクトをロードしています。" << std::endl;
            std::cout << "                           ファイルパス : " << rFilePath << std::endl;

            return true;
        }

        // サウンドエフェクトをロード
        SoundEffectPtr pTemporarySoundEffect(Mix_LoadWAV(rFilePath.c_str()),
                                             [](SoundEffect* pSoundEffect){ ::Mix_FreeChunk(pSoundEffect); });

        if (!pTemporarySoundEffect)
        {
            std::cout << "[ C_SoundManagerImpl::LoadSoundEffect ] : サウンドエフェクトのロードに失敗しました。" << std::endl;
            std::cout << "                             エラー内容 : " << Mix_GetError() << std::endl;

            return false;
        }

        // サウンドエフェクトを保持する
        pSoundEffects_.emplace(rFilePath, pTemporarySoundEffect);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトの解放を行う
     *  @param  ファイルパス
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::ReleaseSoundEffect(const std::string& rFilePath)
    {
        // サウンドエフェクトはロードされていない場合
        if (pSoundEffects_.find(rFilePath) == pSoundEffects_.end())
        {
            std::cout << "[ C_SoundManagerImpl::ReleaseSoundEffect ] : サウンドエフェクトがロードされていません。" << std::endl;

            return;
        }

        // サウンドエフェクトの要素を削除
        pSoundEffects_.erase(rFilePath);
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトを全て解放する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::AllReleaseSoundEffect()
    {
        pSoundEffects_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  BGMのロードを行う
     *  @param  ファイルのパス
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SoundManager::C_SoundManagerImpl::LoadBgm(const std::string& rFilePath)
    {
        // 既に同じBGMをロードしている場合
        if (pBgms_.find(rFilePath) != pBgms_.end())
        {
            std::cout << "[ C_SoungManagerImpl::LoadBGM ] : 既に同じBGMをロードしています。" << std::endl;
            std::cout << "                   ファイルパス : " << rFilePath << std::endl;

            return true;
        }

        // BGMをロード
        BgmPtr pTemporaryBgm(::Mix_LoadMUS(rFilePath.c_str()),
            [](Bgm* pBgm){ ::Mix_FreeMusic(pBgm); });

        if (!pTemporaryBgm)
        {
            PrintLog("[ C_SoungManagerImpl::LoadBGM ] : BGMのロードに失敗しました。\n");
            PrintLog("                     エラー内容 : %s\n", Mix_GetError());

            return false;
        }

        // BGMを保持する
        pBgms_.emplace(rFilePath, pTemporaryBgm);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  BGMの解放を行う
     *  @param  ファイスパス
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::ReleaseBgm(const std::string& rFilePath)
    {
        // BGMがロードされていない場合
        if (pBgms_.find(rFilePath) == pBgms_.end())
        {
            std::cout << "[ C_SoundManagerImpl::ReleaseBGM ] : BGMがロードされていません。" << std::endl;

            return;
        }

        // BGMの要素を削除
        pBgms_.erase(rFilePath);
    }


    /*************************************************************//**
     *
     *  @brief  BGMを全て解放する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::AllReleaseBgm()
    {
        pBgms_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトとBGMを全て解放する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::AllRelease()
    {
        AllReleaseSoundEffect();
        AllReleaseBgm();
    }


    /*************************************************************//**
     *
     *  @brief  適切なボリュームに修正を行う
     *  @param  ボリューム
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::RepairAppositeVolume(int32_t* pVolume)
    {
        assert(pVolume);

        if ((*pVolume) < 0)
        {
            (*pVolume) = 0;
        }
        else if ((*pVolume) > Volume::s_MAXIMUM)
        {
            (*pVolume) = Volume::s_MAXIMUM;
        }
    }


    /*************************************************************//**
     *
     *  @brief  適切な距離に修正を行う
     *  @param  距離
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::RepairAppositeDistance(uint8_t* pDistance)
    {
        assert(pDistance);

        if ((*pDistance) < Distance::s_NEAREST)
        {
            (*pDistance) = Distance::s_NEAREST;
        }
        else if ((*pDistance) > Distance::s_FARTHEST)
        {
            (*pDistance) = Distance::s_FARTHEST;
        }
    }


    /*************************************************************//**
     *
     *  @brief  サウンドエフェクトを取得する
     *  @param  ファイルパス
     *  @return ロードされている場合  ：サウンドエフェクト
     *  @return ロードされていない場合：none
     *
     ****************************************************************/
    boost::optional<const SoundEffectPtr&> C_SoundManager::C_SoundManagerImpl::GetSoundEffect(const std::string& rFilePath) const
    {
        auto iterator = pSoundEffects_.find(rFilePath);
        if (iterator == pSoundEffects_.end()) return boost::none;

        return (*iterator).second;
    }


    /*************************************************************//**
     *
     *  @brief  BGMを取得する
     *  @param  ファイルパス
     *  @return BGM
     *
     ****************************************************************/
    boost::optional<const BgmPtr&> C_SoundManager::C_SoundManagerImpl::GetBgm(const std::string& rFilePath) const
    {
        auto iterator = pBgms_.find(rFilePath);
        if (iterator == pBgms_.end()) return boost::none;

        return (*iterator).second;
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行ったか判断するフラグを設定する
     *  @param  終了処理を行ったか判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_SoundManager::C_SoundManagerImpl::SetFinalizeFlag(bool finalizeFlag)
    {
        finalizeFlag_ = finalizeFlag;
    }
}