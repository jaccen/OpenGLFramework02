/* ヘッダファイル */
#include "GameObjectManager.h"
#include "../GameObject.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief ゲームオブジェクト
//! @brief ゲームに存在するオブジェクト関連の名前空間
//!
//-------------------------------------------------------------
namespace GameObject
{
    //-------------------------------------------------------------
    //!
    //! @brief ゲームオブジェクトマネージャーインプリメント
    //! @brief ゲームオブジェクトマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_GameObjectManager::C_GameObjectManagerImpl
    {
    public:
        C_GameObjectManagerImpl();                                                                  // コンストラクタ
        ~C_GameObjectManagerImpl();                                                                 // デストラクタ
        void Entry(const GameObjectPtr& prGameObject);                                              // 登録処理
        void Remove(const GameObjectPtr& prGameObject);                                             // 除去処理
        void Remove(const std::string& rId);                                                        // 除去処理
        void Remove(int32_t type);                                                                  // 除去処理
        void AllRemove();                                                                           // 全てのゲームオブジェクトを除去
        boost::optional<const GameObjectPtr&> FindGameObjectWithId(const std::string& rId);         // IDからゲームオブジェクトを検索
        GameObjectList FindGameObjectsWithType(int32_t type);                                       // 種類からゲームオブジェクトを検索
    private:
        std::unordered_map<std::string, GameObjectPtr> pGameObjects_;                               // ゲームオブジェクト
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_GameObjectManager::C_GameObjectManagerImpl::C_GameObjectManagerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_GameObjectManager::C_GameObjectManagerImpl::~C_GameObjectManagerImpl()
    {
        if (pGameObjects_.empty() == false) AllRemove();
    }



    /*************************************************************//**
     *
     *  @brief  ゲームオブジェクトの登録処理を行う
     *  @param  ゲームオブジェクト
     *  @return なし
     *
     ****************************************************************/
    void C_GameObjectManager::C_GameObjectManagerImpl::Entry(const GameObjectPtr& prGameObject)
    {
        // IDを取得
        const std::string& rID = prGameObject->GetId();

        // ゲームオブジェクトが既に登録されている場合
        if (pGameObjects_.find(rID) != pGameObjects_.end())
        {
            std::cout << "[ C_GameObjectManagerImpl::Entry ] : ゲームオブジェクトが既に登録されています。" << std::endl;
            std::cout << "                                ID : " << rID << std::endl;

            return;
        }

        // ゲームオブジェクトを追加
        pGameObjects_.emplace(rID, prGameObject);
    }


    /*************************************************************//**
     *
     *  @brief  ゲームオブジェクトの除去を行う
     *  @param  ゲームオブジェクト
     *  @return なし
     *
     ****************************************************************/
    void C_GameObjectManager::C_GameObjectManagerImpl::Remove(const GameObjectPtr& prGameObject)
    {
        Remove(prGameObject->GetId());
    }


    /*************************************************************//**
     *
     *  @brief  ゲームオブジェクトの除去を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_GameObjectManager::C_GameObjectManagerImpl::Remove(const std::string& rId)
    {
        // ゲームオブジェクトが登録されていない場合
        if (pGameObjects_.find(rId) == pGameObjects_.end())
        {
            std::cout << "[ C_GameObjectManagerImpl::Remove ] : ゲームオブジェクトを登録していません。" << std::endl;
            std::cout << "                                 ID : " << rId << std::endl;

            return;
        }

        // 要素を削除
        pGameObjects_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  ゲームオブジェクトの除去を行う
     *  @param  種類
     *  @return なし
     *
     ****************************************************************/
    void C_GameObjectManager::C_GameObjectManagerImpl::Remove(int32_t type)
    {
        // イテレータで走査し、種類と同じものを削除
        auto iterator = pGameObjects_.begin();

        while (iterator != pGameObjects_.end())
        {
            if ((*iterator).second->GetType() == type) pGameObjects_.erase(iterator);

            ++iterator;
        }
    }


    /*************************************************************//**
     *
     *  @brief  全てゲームオブジェクトの除去を行う
     *  @param  ゲームオブジェクト
     *  @return なし
     *
     ****************************************************************/
    void C_GameObjectManager::C_GameObjectManagerImpl::AllRemove()
    {
        pGameObjects_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  IDからゲームオブジェクトを検索する
     *  @param  ID
     *  @return ゲームオブジェクト
     *
     ****************************************************************/
    boost::optional<const GameObjectPtr&> C_GameObjectManager::C_GameObjectManagerImpl::FindGameObjectWithId(const std::string& rId)
    {
        auto iterator = pGameObjects_.find(rId);
        if (iterator == pGameObjects_.end()) return boost::none;

        return (*iterator).second;
    }


    /*************************************************************//**
     *
     *  @brief  種類からゲームオブジェクトを検索する
     *  @param  種類
     *  @return ゲームオブジェクト
     *
     ****************************************************************/
    GameObjectList C_GameObjectManager::C_GameObjectManagerImpl::FindGameObjectsWithType(int32_t type)
    {
        std::deque<GameObjectPtr> pGameObjectList;

        for (auto& rGameObject : pGameObjects_)
        {
            if (rGameObject.second->GetType() == type) pGameObjectList.push_back(rGameObject.second);
        }

        return pGameObjectList;
    }
}