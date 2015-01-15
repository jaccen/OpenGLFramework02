/* ヘッダファイル */
#include "SpriteCreaterManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief スプライト
//! @brief スプライト関連の名前空間
//!
//-------------------------------------------------------------
namespace Sprite
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SpriteCreaterManager::C_SpriteCreaterManager() :

        // 実装情報
        upImpl_(std::make_unique<C_SpriteCreaterManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SpriteCreaterManager::~C_SpriteCreaterManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreaterManager::Draw()
    {
        upImpl_->Draw();
    }


    /*************************************************************//**
     *
     *  @brief  ソート処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreaterManager::Sort()
    {
        upImpl_->Sort();
    }


    /*************************************************************//**
     *
     *  @brief  スプライトシステムの作成する
     *  @param  ID
     *  @param  カメラ
     *  @parama テクスチャ情報
     *  @param  スプライトの最大数
     *  @param  優先度
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SpriteCreaterManager::Create(const std::string& rId,
                                        const Camera::CameraPtr& prCamera,
                                        const Texture::TextureDataPtr pTextureData,
                                        uint32_t maxSpriteCount,
                                        float priority)
    {
        if (upImpl_->Create(rId, prCamera, pTextureData, maxSpriteCount, priority) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  スプライトシステムを破棄する
     *  @parama ID
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreaterManager::Destroy(const std::string& rId)
    {
        upImpl_->Destroy(rId);
    }


    /*************************************************************//**
     *
     *  @brief  スプライトシステムを全て破棄する
     *  @parama なし
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreaterManager::AllDestroy()
    {
        upImpl_->AllDestroy();
    }


    /*************************************************************//**
     *
     *  @brief  スプライトシステムを取得する
     *  @parama ID
     *  @return 作成されている場合  ：スプライトシステム
     *  @return 作成されていない場合：none
     *
     ****************************************************************/
    boost::optional<SpriteCreaterWeakPtr> C_SpriteCreaterManager::GetSpriteCreater(const std::string& rId)
    {
        return upImpl_->GetSpriteCreater(rId);
    }
}