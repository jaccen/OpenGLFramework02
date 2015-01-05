/* ヘッダファイル */
#include "MaterialManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief マテリアル
//! @brief マテリアル関連の名前空間
//!
//-------------------------------------------------------------
namespace Material
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_MaterialManager::C_MaterialManager() :

        // 実装情報
        upImpl_(std::make_unique<C_MaterialManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_MaterialManager::~C_MaterialManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  マテリアルの登録を行う
     *  @param  マテリアル
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_MaterialManager::Entry(const MaterialPtr& prMaterial, const std::string& rId)
    {
        upImpl_->Entry(prMaterial, rId);
    }


    /*************************************************************//**
     *
     *  @brief  マテリアルの除去を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_MaterialManager::Remove(const std::string& rId)
    {
        upImpl_->Remove(rId);
    }


    /*************************************************************//**
     *
     *  @brief  全てのマテリアルの除去を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_MaterialManager::AllRemove()
    {
        upImpl_->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  マテリアルを取得する
     *  @param  ID
     *  @return 取得できた場合      ：マテリアル
     *  @return 取得できなかった場合：none
     *
     ****************************************************************/
    boost::optional<const MaterialPtr&> C_MaterialManager::GetMaterial(const std::string& rId) const
    {
        return upImpl_->GetMaterial(rId);
    }
}