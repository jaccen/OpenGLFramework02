/* ヘッダファイル */
#include "ParticleSystemManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief パーティクル
//! @brief パーティクル関連の名前空間
//!
//-------------------------------------------------------------
namespace Particle
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_ParticleSystemManager::C_ParticleSystemManager() :

        // 実装情報
        upImpl_(std::make_unique<C_ParticleSystemManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_ParticleSystemManager::~C_ParticleSystemManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystemManager::Update()
    {
        upImpl_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystemManager::Draw()
    {
        upImpl_->Draw();
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
    bool C_ParticleSystemManager::Create(const std::string& rId,
                                         const std::shared_ptr<Camera::C_PerspectiveCamera>& sprCamera,
                                         Texture::TextureHandle textureHandle,
                                         uint32_t maxParticleNumber)
    {
        if (upImpl_->Create(rId, sprCamera, textureHandle, maxParticleNumber) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  パーティクルシステムを破棄する
     *  @parama ID
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystemManager::Destroy(const std::string& rId)
    {
        upImpl_->Destroy(rId);
    }


    /*************************************************************//**
     *
     *  @brief  パーティクルシステムを全て破棄する
     *  @parama なし
     *  @return なし
     *
     ****************************************************************/
    void C_ParticleSystemManager::AllDestroy()
    {
        upImpl_->AllDestroy();
    }


    /*************************************************************//**
     *
     *  @brief  パーティクルシステムを取得する
     *  @parama ID
     *  @return 作成されている場合  ：パーティクルシステム
     *  @return 作成されていない場合：none
     *
     ****************************************************************/
    boost::optional<ParticleSystemWeakPtr> C_ParticleSystemManager::GetParticleSystem(const std::string& rId)
    {
        return upImpl_->GetParticleSystem(rId);
    }
}