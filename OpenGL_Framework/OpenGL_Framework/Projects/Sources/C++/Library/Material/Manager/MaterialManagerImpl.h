/* ヘッダファイル */
#include "MaterialManager.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief マテリアル
//! @brief マテリアル関連の名前空間
//!
//-------------------------------------------------------------
namespace Material
{
    //-------------------------------------------------------------
    //!
    //! @brief マテリアルマネージャーインプリメント
    //! @brief マテリアルマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_MaterialManager::C_MaterialManagerImpl
    {
    public:
        C_MaterialManagerImpl();                                                            // コンストラクタ
        ~C_MaterialManagerImpl();                                                           // デストラクタ
        void Entry(const MaterialPtr& prMaterial, const std::string& rId);                  // 登録処理
        void Remove(const std::string& rId);                                                // 除去処理
        void AllRemove();                                                                   // 全てのマテリアルを除去
        boost::optional<const MaterialPtr&> GetMaterial(const std::string& rId) const;      // マテリアルを取得
    private:
        std::unordered_map<std::string, MaterialPtr> pMaterials_;                           ///< @brief マテリアル
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_MaterialManager::C_MaterialManagerImpl::C_MaterialManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_MaterialManager::C_MaterialManagerImpl::~C_MaterialManagerImpl()
    {
        if (pMaterials_.empty() == false) AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  マテリアルの登録を行う
     *  @param  マテリアル
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_MaterialManager::C_MaterialManagerImpl::Entry(const MaterialPtr& prMaterial, const std::string& rId)
    {
        // マテリアルが既に登録されている場合
        if (pMaterials_.find(rId) != pMaterials_.end())
        {
            std::cout << "[ C_MaterialManagerImpl::Entry ] : マテリアルが既に登録されています。" << std::endl;
            std::cout << "                              ID : " << rId << std::endl;

            return;
        }

        pMaterials_.emplace(rId, prMaterial);
    }


    /*************************************************************//**
     *
     *  @brief  マテリアルの除去を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_MaterialManager::C_MaterialManagerImpl::Remove(const std::string& rId)
    {
        // マテリアルが登録されていない場合
        if (pMaterials_.find(rId) == pMaterials_.end())
        {
            std::cout << "[ C_MaterialManagerImpl::Remove ] : マテリアルを登録していません。" << std::endl;
            std::cout << "                               ID : " << rId << std::endl;

            return;
        }

        pMaterials_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  全てのマテリアルの除去を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_MaterialManager::C_MaterialManagerImpl::AllRemove()
    {
        pMaterials_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  マテリアルを取得する
     *  @param  ID
     *  @return 登録されていた場合    ：マテリアル
     *  @return 登録されてなかった場合：none
     *
     ****************************************************************/
    boost::optional<const MaterialPtr&> C_MaterialManager::C_MaterialManagerImpl::GetMaterial(const std::string& rId) const
    {
        auto iterator = pMaterials_.find(rId);
        if (iterator == pMaterials_.end()) return boost::none;

        return (*iterator).second;
    }
}