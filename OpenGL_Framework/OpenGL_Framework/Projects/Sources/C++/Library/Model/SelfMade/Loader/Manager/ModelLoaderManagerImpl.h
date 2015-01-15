/* ヘッダファイル */
#include "ModelLoaderManager.h"
#include <unordered_map>


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
        //-------------------------------------------------------------
        //!
        //! @brief モデルローダーマネージャーインプリメント
        //! @brief モデルローダーマネージャーのプライベート情報の実装
        //!
        //-------------------------------------------------------------
        class C_ModelLoaderManager::C_ModelLoaderManagerImpl
        {
        public:
            C_ModelLoaderManagerImpl();                                                                 // コンストラクタ
            ~C_ModelLoaderManagerImpl();                                                                // デストラクタ
            void Entry(const ModelLoaderPtr& prModelLoader, const std::string& rId);                    // 登録処理
            void Remove(const std::string& rId);                                                        // 除去処理
            void AllRemove();                                                                           // 全てのモデルローダーを除去
            boost::optional<const ModelLoaderPtr&> GetModelLoader(const std::string& rId) const;        // モデルローダーを取得
        private:
            std::unordered_map<std::string, ModelLoaderPtr> pModelLoaders_;                             ///< @brief モデルローダー
        };


        /*************************************************************//**
         *
         *  @brief  コンストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_ModelLoaderManager::C_ModelLoaderManagerImpl::C_ModelLoaderManagerImpl()
        {
        }


        /*************************************************************//**
         *
         *  @brief  デストラクタ
         *  @param  なし
         *
         ****************************************************************/
        C_ModelLoaderManager::C_ModelLoaderManagerImpl::~C_ModelLoaderManagerImpl()
        {
            if (pModelLoaders_.empty() == false) AllRemove();
        }


        /*************************************************************//**
         *
         *  @brief  モデルローダーの登録を行う
         *  @param  モデルローダー
         *  @param  ID
         *  @return なし
         *
         ****************************************************************/
        void C_ModelLoaderManager::C_ModelLoaderManagerImpl::Entry(const ModelLoaderPtr& prModelLoader, const std::string& rId)
        {
            // モデルローダーが既に登録されている場合
            if (pModelLoaders_.find(rId) != pModelLoaders_.end())
            {
                std::cout << "[ C_ModelLoaderManagerImpl::Entry ] : モデルローダーが既に登録されています。" << std::endl;
                std::cout << "                                 ID : " << rId << std::endl;

                return;
            }

            pModelLoaders_.emplace(rId, prModelLoader);
        }


        /*************************************************************//**
         *
         *  @brief  モデルローダーの除去を行う
         *  @param  ID
         *  @return なし
         *
         ****************************************************************/
        void C_ModelLoaderManager::C_ModelLoaderManagerImpl::Remove(const std::string& rId)
        {
            // モデルローダーが登録されていない場合
            if (pModelLoaders_.find(rId) == pModelLoaders_.end())
            {
                std::cout << "[ C_ModelLoaderManagerImpl::Remove ] : モデルローダーを登録していません。" << std::endl;
                std::cout << "                                  ID : " << rId << std::endl;

                return;
            }

            pModelLoaders_.erase(rId);
        }


        /*************************************************************//**
         *
         *  @brief  全てのモデルローダーの除去を行う
         *  @param  なし
         *  @return なし
         *
         ****************************************************************/
        void C_ModelLoaderManager::C_ModelLoaderManagerImpl::AllRemove()
        {
            pModelLoaders_.clear();
        }


        /*************************************************************//**
         *
         *  @brief  モデルローダーを取得する
         *  @param  ID
         *  @return 登録されていた場合    ：モデルローダー
         *  @return 登録されてなかった場合：none
         *
         ****************************************************************/
        boost::optional<const ModelLoaderPtr&> C_ModelLoaderManager::C_ModelLoaderManagerImpl::GetModelLoader(const std::string& rId) const
        {
            auto iterator = pModelLoaders_.find(rId);
            if (iterator == pModelLoaders_.end()) return boost::none;

            return (*iterator).second;
        }
    }
}