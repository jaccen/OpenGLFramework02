/* ヘッダファイル */
#include "JsonObjectManager.h"
#include <unordered_map>


//-------------------------------------------------------------
///
/// @brief JSON
/// @brief JSON関連のクラスや関数などに付ける名前空間
///
//-------------------------------------------------------------
namespace JSON
{
    //-------------------------------------------------------------
    //!
    //! @brief JSONオブジェクトマネージャーインプリメント
    //! @brief JSONオブジェクトマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_JsonObjectManager::C_JsonObjectManagerImpl
    {
    public:
        C_JsonObjectManagerImpl();                                                                  // コンストラクタ
        ~C_JsonObjectManagerImpl();                                                                 // デストラクタ
        void Entry(const JsonObjectPtr& prJsonObject, const std::string& rId);                      // 登録処理
        void Remove(const std::string& rId);                                                        // 除去処理
        void AllRemove();                                                                           // 全てのJSONオブジェクトを除去
        boost::optional<const JsonObjectPtr&> GetJsonObject(const std::string& rId) const;          // JSONオブジェクトを取得
    private:
        std::unordered_map<std::string, JsonObjectPtr> pJsonObjects_;                                ///< @brief JSONオブジェクト
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_JsonObjectManager::C_JsonObjectManagerImpl::C_JsonObjectManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_JsonObjectManager::C_JsonObjectManagerImpl::~C_JsonObjectManagerImpl()
    {
        if (pJsonObjects_.empty() == false) AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  JSONオブジェクトの登録を行う
     *  @param  JSONオブジェクト
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_JsonObjectManager::C_JsonObjectManagerImpl::Entry(const JsonObjectPtr& prJsonObject, const std::string& rId)
    {
        // JSONオブジェクトが既に登録されている場合
        if (pJsonObjects_.find(rId) != pJsonObjects_.end())
        {
            std::cout << "[ C_JsonObjectManagerImpl::Entry ] : JSONオブジェクトが既に登録されています。" << std::endl;
            std::cout << "                                ID : " << rId << std::endl;

            return;
        }

        pJsonObjects_.emplace(rId, prJsonObject);
    }


    /*************************************************************//**
     *
     *  @brief  JSONオブジェクトの除去を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_JsonObjectManager::C_JsonObjectManagerImpl::Remove(const std::string& rId)
    {
        // JSONオブジェクトが登録されていない場合
        if (pJsonObjects_.find(rId) == pJsonObjects_.end())
        {
            std::cout << "[ C_JsonObjectManagerImpl::Remove ] : JSONオブジェクトを登録していません。" << std::endl;
            std::cout << "                                 ID : " << rId << std::endl;

            return;
        }

        pJsonObjects_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  全てのJSONオブジェクトの除去を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_JsonObjectManager::C_JsonObjectManagerImpl::AllRemove()
    {
        pJsonObjects_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  JSONオブジェクトを取得する
     *  @param  ID
     *  @return 登録されていた場合    ：JSONオブジェクト
     *  @return 登録されてなかった場合：none
     *
     ****************************************************************/
    boost::optional<const JsonObjectPtr&> C_JsonObjectManager::C_JsonObjectManagerImpl::GetJsonObject(const std::string& rId) const
    {
        auto iterator = pJsonObjects_.find(rId);
        if (iterator == pJsonObjects_.end()) return boost::none;

        return (*iterator).second;
    }
}