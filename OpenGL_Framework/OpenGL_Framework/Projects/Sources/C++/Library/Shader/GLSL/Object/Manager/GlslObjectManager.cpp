/* ヘッダファイル */
#include "GlslObjectManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief シェーダー
//! @brief シェーダー関連の名前空間
//!
//-------------------------------------------------------------
namespace Shader
{
    //-------------------------------------------------------------
    //!
    //! @brief GLSL
    //! @brief GLSL関連の名前空間
    //!
    //-------------------------------------------------------------
    namespace GLSL
    {
        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_GlslObjectManager::C_GlslObjectManager() :

            // 実装情報
            upImpl_(std::make_unique<C_GlslObjectManagerImpl>())

        {
        }


        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_GlslObjectManager::~C_GlslObjectManager()
        {
        }


        /*************************************************************//**
         *
         *  @brief  GLSLオブジェクトの登録を行う
         *  @param  GLSLオブジェクト
         *  @param  ID
         *  @return なし
         *
         ****************************************************************/
        void C_GlslObjectManager::Entry(const GlslObjectPtr& prGlslObject, const std::string& rId)
        {
            upImpl_->Entry(prGlslObject, rId);
        }


        /*************************************************************//**
         *
         *  @brief  GLSLオブジェクトの除去を行う
         *  @param  ID
         *  @return なし
         *
         ****************************************************************/
        void C_GlslObjectManager::Remove(const std::string& rId)
        {
            upImpl_->Remove(rId);
        }


        /*************************************************************//**
         *
         *  @brief  全てのGLSLオブジェクトの除去を行う
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void C_GlslObjectManager::AllRemove()
        {
            upImpl_->AllRemove();
        }


        /*************************************************************//**
         *
         *  @brief  GLSLオブジェクトを取得する
         *  @param  ID
         *  @return 取得できた場合      ：GLSLオブジェクト
         *  @return 取得できなかった場合：none
         *
         ****************************************************************/
        boost::optional<const GlslObjectPtr&> C_GlslObjectManager::GetGlslObject(const std::string& rId) const
        {
            return upImpl_->GetGlslObject(rId);
        }
    }
}