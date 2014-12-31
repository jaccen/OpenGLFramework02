/* ヘッダファイル */
#include "UniformBufferManagerImpl.h"


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
        C_UniformBufferManager::C_UniformBufferManager() :

            // 実装情報
            upImpl_(std::make_unique<C_UniformBufferManagerImpl>())

        {
        }


        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_UniformBufferManager::~C_UniformBufferManager()
        {
        }


        /*************************************************************//**
         *
         *  @brief  ユニフォームバッファの登録を行う
         *  @param  ユニフォームバッファ
         *  @param  ID
         *  @return なし
         *
         ****************************************************************/
        void C_UniformBufferManager::Entry(const UniformBufferPtr& prUniformBuffer, const std::string& rId)
        {
            upImpl_->Entry(prUniformBuffer, rId);
        }


        /*************************************************************//**
         *
         *  @brief  ユニフォームバッファの除去を行う
         *  @param  ID
         *  @return なし
         *
         ****************************************************************/
        void C_UniformBufferManager::Remove(const std::string& rId)
        {
            upImpl_->Remove(rId);
        }


        /*************************************************************//**
         *
         *  @brief  全てのユニフォームバッファの除去を行う
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void C_UniformBufferManager::AllRemove()
        {
            upImpl_->AllRemove();
        }


        /*************************************************************//**
         *
         *  @brief  ユニフォームバッファを取得する
         *  @param  ID
         *  @return 取得できた場合      ：ユニフォームバッファ
         *  @return 取得できなかった場合：none
         *
         ****************************************************************/
        boost::optional<const UniformBufferPtr&> C_UniformBufferManager::GetUniformBuffer(const std::string& rId) const
        {
            return upImpl_->GetUniformBuffer(rId);
        }
    }
}