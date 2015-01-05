/* ヘッダファイル */
#include "LightManager.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief ライト
//! @brief ライト関連の名前空間
//!
//-------------------------------------------------------------
namespace Light
{
    //-------------------------------------------------------------
    //!
    //! @brief ライトマネージャーインプリメント
    //! @brief ライトマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_LightManager::C_LightManagerImpl
    {
    public:
        C_LightManagerImpl();                                                           // コンストラクタ
        ~C_LightManagerImpl();                                                          // デストラクタ
        void Entry(const LightPtr& prLight, const std::string& rId);                    // 登録処理
        void Remove(const std::string& rId);                                            // 除去処理
        void AllRemove();                                                               // 全てのライトを除去
        boost::optional<const LightPtr&> GetLight(const std::string& rId) const;        // ライトを取得
    private:
        std::unordered_map<std::string, LightPtr> pLights_;                             ///< @brief ライト
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_LightManager::C_LightManagerImpl::C_LightManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_LightManager::C_LightManagerImpl::~C_LightManagerImpl()
    {
        if (pLights_.empty() == false) AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  ライトの登録を行う
     *  @param  ライト
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_LightManager::C_LightManagerImpl::Entry(const LightPtr& prLight, const std::string& rId)
    {
        // ライトが既に登録されている場合
        if (pLights_.find(rId) != pLights_.end())
        {
            std::cout << "[ C_LightManagerImpl::Entry ] : ライトが既に登録されています。" << std::endl;
            std::cout << "                           ID : " << rId << std::endl;

            return;
        }

        pLights_.emplace(rId, prLight);
    }


    /*************************************************************//**
     *
     *  @brief  ライトの除去を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_LightManager::C_LightManagerImpl::Remove(const std::string& rId)
    {
        // ライトが登録されていない場合
        if (pLights_.find(rId) == pLights_.end())
        {
            std::cout << "[ C_LightManagerImpl::Remove ] : ライトを登録していません。" << std::endl;
            std::cout << "                               ID : " << rId << std::endl;

            return;
        }

        pLights_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  全てのライトの除去を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_LightManager::C_LightManagerImpl::AllRemove()
    {
        pLights_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  ライトを取得する
     *  @param  ID
     *  @return 登録されていた場合    ：ライト
     *  @return 登録されてなかった場合：none
     *
     ****************************************************************/
    boost::optional<const LightPtr&> C_LightManager::C_LightManagerImpl::GetLight(const std::string& rId) const
    {
        auto iterator = pLights_.find(rId);
        if (iterator == pLights_.end()) return boost::none;

        return (*iterator).second;
    }
}