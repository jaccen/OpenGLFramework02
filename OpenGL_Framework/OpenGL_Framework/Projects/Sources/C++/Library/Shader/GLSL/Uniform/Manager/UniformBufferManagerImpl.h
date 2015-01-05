/* ヘッダファイル */
#include "UniformBufferManager.h"
#include <unordered_map>


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
        //-------------------------------------------------------------
        //!
        //! @brief ユニフォームバッファインプリメント
        //! @brief ユニフォームバッファのプライベート情報の実装
        //!
        //-------------------------------------------------------------
        class C_UniformBufferManager::C_UniformBufferManagerImpl
        {
        public:
            C_UniformBufferManagerImpl();                                                                   // コンストラクタ
            ~C_UniformBufferManagerImpl();                                                                  // デストラクタ
            void Entry(const UniformBufferPtr& prUniformBuffer, const std::string& rId);                    // 登録処理
            void Remove(const std::string& rId);                                                            // 除去処理
            void AllRemove();                                                                               // 全てのユニフォームバッファを除去
            boost::optional<const UniformBufferPtr&> GetUniformBuffer(const std::string& rId) const;        // ユニフォームバッファを取得
        private:
            std::unordered_map<std::string, UniformBufferPtr> pUniformBuffers_;                             ///< @brief ユニフォームバッファ
        };


        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_UniformBufferManager::C_UniformBufferManagerImpl::C_UniformBufferManagerImpl()
        {
        }


        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_UniformBufferManager::C_UniformBufferManagerImpl::~C_UniformBufferManagerImpl()
        {
            if (pUniformBuffers_.empty() == false) AllRemove();
        }


        /*************************************************************//**
         *
         *  @brief  ユニフォームバッファの登録を行う
         *  @param  ユニフォームバッファ
         *  @param  ID
         *  @return なし
         *
         ****************************************************************/
        void C_UniformBufferManager::C_UniformBufferManagerImpl::Entry(const UniformBufferPtr& prUniformBuffer, const std::string& rId)
        {
            // ユニフォームバッファが既に登録されている場合
            if (pUniformBuffers_.find(rId) != pUniformBuffers_.end())
            {
                std::cout << "[ C_UniformBufferManagerImpl::Entry ] : ユニフォームバッファが既に登録されています。" << std::endl;
                std::cout << "                                   ID : " << rId << std::endl;

                return;
            }

            pUniformBuffers_.emplace(rId, prUniformBuffer);
        }


        /*************************************************************//**
         *
         *  @brief  ユニフォームバッファの除去を行う
         *  @param  ID
         *  @return なし
         *
         ****************************************************************/
        void C_UniformBufferManager::C_UniformBufferManagerImpl::Remove(const std::string& rId)
        {
            // ユニフォームバッファが登録されていない場合
            if (pUniformBuffers_.find(rId) == pUniformBuffers_.end())
            {
                std::cout << "[ C_UniformBufferManagerImpl::Remove ] : ユニフォームバッファを登録していません。" << std::endl;
                std::cout << "                                    ID : " << rId << std::endl;

                return;
            }

            pUniformBuffers_.erase(rId);
        }


        /*************************************************************//**
         *
         *  @brief  全てのユニフォームバッファの除去を行う
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void C_UniformBufferManager::C_UniformBufferManagerImpl::AllRemove()
        {
            pUniformBuffers_.clear();
        }


        /*************************************************************//**
         *
         *  @brief  ユニフォームバッファを取得する
         *  @param  ID
         *  @return 登録されていた場合    ：ユニフォームバッファ
         *  @return 登録されてなかった場合：none
         *
         ****************************************************************/
        boost::optional<const UniformBufferPtr&> C_UniformBufferManager::C_UniformBufferManagerImpl::GetUniformBuffer(const std::string& rId) const
        {
            auto iterator = pUniformBuffers_.find(rId);
            if (iterator == pUniformBuffers_.end()) return boost::none;

            return (*iterator).second;
        }
    }
}