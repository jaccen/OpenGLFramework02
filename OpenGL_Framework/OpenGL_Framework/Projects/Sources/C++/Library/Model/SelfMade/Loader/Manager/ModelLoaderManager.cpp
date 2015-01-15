/* ヘッダファイル */
#include "ModelLoaderManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief モデル
//! @brief モデル関連の名前空間
//!
//-------------------------------------------------------------
namespace Model
{
    //-------------------------------------------------------------
    //!
    //! @brief SelfMade
    //! @brief 自作関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace SelfMade
    {
        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_ModelLoaderManager::C_ModelLoaderManager() :

            // 実装情報
            upImpl_(std::make_unique<C_ModelLoaderManagerImpl>())

        {
        }


        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_ModelLoaderManager::~C_ModelLoaderManager()
        {
        }


        /*************************************************************//**
         *
         *  @brief  モデルローダーの登録を行う
         *  @param  モデルローダー
         *  @param  ID
         *  @return なし
         *
         ****************************************************************/
        void C_ModelLoaderManager::Entry(const ModelLoaderPtr& prMaterial, const std::string& rId)
        {
            upImpl_->Entry(prMaterial, rId);
        }


        /*************************************************************//**
         *
         *  @brief  モデルローダーの除去を行う
         *  @param  ID
         *  @return なし
         *
         ****************************************************************/
        void C_ModelLoaderManager::Remove(const std::string& rId)
        {
            upImpl_->Remove(rId);
        }


        /*************************************************************//**
         *
         *  @brief  全てのモデルローダーの除去を行う
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void C_ModelLoaderManager::AllRemove()
        {
            upImpl_->AllRemove();
        }


        /*************************************************************//**
         *
         *  @brief  モデルローダーを取得する
         *  @param  ID
         *  @return 取得できた場合      ：モデルローダー
         *  @return 取得できなかった場合：none
         *
         ****************************************************************/
        boost::optional<const ModelLoaderPtr&> C_ModelLoaderManager::GetModelLoader(const std::string& rId) const
        {
            return upImpl_->GetModelLoader(rId);
        }
    }
}