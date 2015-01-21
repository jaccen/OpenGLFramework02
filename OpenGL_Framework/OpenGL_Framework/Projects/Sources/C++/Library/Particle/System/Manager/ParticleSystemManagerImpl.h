/* ヘッダファイル */
#include "ParticleSystemManager.h"
#include "../../../Debug/Helper/DebugHelper.h"
#include <deque>


//-------------------------------------------------------------
//!
//! @brief パーティクル
//! @brief パーティクル関連の名前空間
//!
//-------------------------------------------------------------
namespace Particle
{
    /* 別名 */
    using ParticleSystemPtr = std::shared_ptr<C_ParticleSystem>;                                                    // ParticleSystemPtr型


    //-------------------------------------------------------------
    //!
    //! @brief パーティクルマネージャーインプリメント
    //! @brief パーティクルシステムのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_ParticleSystemManager::C_ParticleSystemManagerImpl
    {
    public:
        C_ParticleSystemManagerImpl();                                                                              // コンストラクタ
        ~C_ParticleSystemManagerImpl();                                                                             // デストラクタ
        void Update();                                                                                              // 更新処理
        void Draw();                                                                                                // 描画処理
        bool Create(const std::string& rId,                                                                         // パーティクルシステムを作成
                    const Camera::CameraPtr& prCamera,
                    Texture::TextureHandle textureHandle,
                    uint32_t maxParticleCount);
        void Destroy(const std::string& rId);                                                                       // パーティクルシステムを破棄
        void AllDestroy();                                                                                          // パーティクルシステムを全て破棄
        boost::optional<ParticleSystemWeakPtr> GetParticleSystem(const std::string& rId);                           // パーティクルシステムを取得
    private:
        std::deque<std::pair<std::string, ParticleSystemPtr>> pParticleSystems_;                                    ///< @brief パーティクルシステム
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_ParticleSystemManager::C_ParticleSystemManagerImpl::C_ParticleSystemManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_ParticleSystemManager::C_ParticleSystemManagerImpl::~C_ParticleSystemManagerImpl()
    {
        if (pParticleSystems_.empty() == false) AllDestroy();
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystemManager::C_ParticleSystemManagerImpl::Update()
    {
        for (auto& rParticleSystem : pParticleSystems_)
        {
            if (rParticleSystem.second->GetEnableFlag() == true) rParticleSystem.second->Update();
        }
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystemManager::C_ParticleSystemManagerImpl::Draw()
    {
        for (auto &rParticleSystem : pParticleSystems_)
        {
            if (rParticleSystem.second->GetEnableFlag() == true) rParticleSystem.second->Draw();
        }
    }


    /*************************************************************//**
     *
     *  @brief  パーティクルシステムの作成する
     *  @param  ID
     *  @param  カメラ
     *  @parama テクスチャハンドル
     *  @param  パーティクルの最大数
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_ParticleSystemManager::C_ParticleSystemManagerImpl::Create(const std::string& rId,
                                                                      const Camera::CameraPtr& prCamera,
                                                                      Texture::TextureHandle textureHandle,
                                                                      uint32_t maxParticleCount)
    {
        // 既に作成している場合
        auto iterator = std::find_if(pParticleSystems_.begin(),
                                     pParticleSystems_.end(),
                                     [&](const std::pair<std::string, ParticleSystemPtr>& rpPatricleSystem){ return rpPatricleSystem.first == rId; });


        if (iterator != pParticleSystems_.end())
        {
            std::cout << "[ C_ParticleSystemManagerImpl::Create ] : 既に同じをパーティクルシステムを作成しています。" << std::endl;
            std::cout << "                               ID : " << rId << std::endl;

            return true;
        }

        // パーティクルシステムを生成し、初期化
        auto pParticleSystem = std::make_shared<C_ParticleSystem>();

        if (pParticleSystem->Initialize(prCamera, textureHandle, maxParticleCount) == false)
        {
            PrintLog("[ C_ParticleSystemManagerImpl::Initialize ] : パーティクルシステムの初期化処理に失敗しました。");

            return false;
        }

        // パーティクルシステムを保持する
        pParticleSystems_.emplace_back(rId, pParticleSystem);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  パーティクルシステムを破棄する
     *  @parama ID
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystemManager::C_ParticleSystemManagerImpl::Destroy(const std::string& rId)
    {
        // パーティクルシステムが作成されていない場合
        auto iterator = std::find_if(pParticleSystems_.begin(),
                                     pParticleSystems_.end(),
                                     [&](const std::pair<std::string, ParticleSystemPtr>& rpPatricleSystem){ return rpPatricleSystem.first == rId; });


        if (iterator == pParticleSystems_.end())
        {
            std::cout << "[ C_ParticleSystemManagerImpl::Destroy ] : パーティクルシステムが作成されていません。" << std::endl;

            return;
        }

        (*iterator).second->Finalize();
        pParticleSystems_.erase(iterator);
    }


    /*************************************************************//**
     *
     *  @brief  パーティクルシステムを全て破棄する
     *  @parama なし
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystemManager::C_ParticleSystemManagerImpl::AllDestroy()
    {
        for (auto& rParticleSystem : pParticleSystems_) rParticleSystem.second->Finalize();
        pParticleSystems_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  パーティクルシステムを取得する
     *  @parama ID
     *  @return 作成されている場合  ：パーティクルシステム
     *  @return 作成されていない場合：none
     *
     ****************************************************************/
    boost::optional<ParticleSystemWeakPtr> C_ParticleSystemManager::C_ParticleSystemManagerImpl::GetParticleSystem(const std::string& rId)
    {
        auto iterator = std::find_if(pParticleSystems_.begin(),
                                     pParticleSystems_.end(),
                                     [&](const std::pair<std::string, ParticleSystemPtr>& rpPatricleSystem){ return rpPatricleSystem.first == rId; });
        
        if (iterator == pParticleSystems_.end()) return boost::none;
        return (*iterator).second;
    }
}