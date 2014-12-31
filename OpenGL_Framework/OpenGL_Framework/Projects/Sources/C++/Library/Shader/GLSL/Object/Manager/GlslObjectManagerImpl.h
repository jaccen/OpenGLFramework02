/* ヘッダファイル */
#include "GlslObjectManager.h"
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
        //! @brief GLSLオブジェクトマネージャーインプリメント
        //! @brief GLSLオブジェクトマネージャーのプライベート情報の実装
        //!
        //-------------------------------------------------------------
        class C_GlslObjectManager::C_GlslObjectManagerImpl
        {
        public:
            C_GlslObjectManagerImpl();                                                              // コンストラクタ
            ~C_GlslObjectManagerImpl();                                                             // デストラクタ
            void Entry(const GlslObjectPtr& prGlslObject, const std::string& rId);                  // 登録処理
            void Remove(const std::string& rId);                                                    // 除去処理
            void AllRemove();                                                                       // 全てのGLSLオブジェクトを除去
            boost::optional<const GlslObjectPtr&> GetGlslObject(const std::string& rId) const;      // GLSLオブジェクトを取得
        private:
            std::unordered_map<std::string, GlslObjectPtr> prGlslObjects_;                          ///< @brief GLSLオブジェクト
        };


        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_GlslObjectManager::C_GlslObjectManagerImpl::C_GlslObjectManagerImpl()
        {
        }


        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_GlslObjectManager::C_GlslObjectManagerImpl::~C_GlslObjectManagerImpl()
        {
            if (prGlslObjects_.empty() == false) AllRemove();
        }


        /*************************************************************//**
         *
         *  @brief  GLSLオブジェクトの登録を行う
         *  @param  GLSLオブジェクト
         *  @param  ID
         *  @return なし
         *
         ****************************************************************/
        void C_GlslObjectManager::C_GlslObjectManagerImpl::Entry(const GlslObjectPtr& prGlslObject, const std::string& rId)
        {
            // GLSLオブジェクトが既に登録されている場合
            if (prGlslObjects_.find(rId) != prGlslObjects_.end())
            {
                std::cout << "[ C_GlslObjectManagerImpl::Entry ] : GLSLオブジェクトが既に登録されています。" << std::endl;
                std::cout << "                                ID : " << rId << std::endl;

                return;
            }

            prGlslObjects_.emplace(rId, prGlslObject);
        }


        /*************************************************************//**
         *
         *  @brief  GLSLオブジェクトの除去を行う
         *  @param  ID
         *  @return なし
         *
         ****************************************************************/
        void C_GlslObjectManager::C_GlslObjectManagerImpl::Remove(const std::string& rId)
        {
            // GLSLオブジェクトが登録されていない場合
            if (prGlslObjects_.find(rId) == prGlslObjects_.end())
            {
                std::cout << "[ C_GlslObjectManagerImpl::Remove ] : GLSLオブジェクトを登録していません。" << std::endl;
                std::cout << "                                 ID : " << rId << std::endl;

                return;
            }

            prGlslObjects_.erase(rId);
        }


        /*************************************************************//**
         *
         *  @brief  全てのシェーダーの除去を行う
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void C_GlslObjectManager::C_GlslObjectManagerImpl::AllRemove()
        {
            prGlslObjects_.clear();
        }


        /*************************************************************//**
         *
         *  @brief  GLSLオブジェクトを取得する
         *  @param  ID
         *  @return 登録されていた場合    ：GLSLオブジェクト
         *  @return 登録されてなかった場合：none
         *
         ****************************************************************/
        boost::optional<const GlslObjectPtr&> C_GlslObjectManager::C_GlslObjectManagerImpl::GetGlslObject(const std::string& rId) const
        {
            auto iterator = prGlslObjects_.find(rId);
            if (iterator == prGlslObjects_.end()) return boost::none;

            return (*iterator).second;
        }
    }
}