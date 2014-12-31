/* ヘッダファイル */
#include "GameObjectManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief ゲームオブジェクト
//! @brief ゲームに存在するオブジェクト関連の名前空間
//!
//-------------------------------------------------------------
namespace GameObject
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_GameObjectManager::C_GameObjectManager() :

        // 実装情報
        upImpl_(std::make_unique<C_GameObjectManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_GameObjectManager::~C_GameObjectManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ゲームオブジェクトの登録処理を行う
     *  @param  ゲームオブジェクト
     *  @return なし
     *
     ****************************************************************/
    void C_GameObjectManager::Entry(const GameObjectPtr& prGameObject)
    {
        upImpl_->Entry(prGameObject);
    }


    /*************************************************************//**
     *
     *  @brief  ゲームオブジェクトの除去を行う
     *  @param  ゲームオブジェクト
     *  @return なし
     *
     ****************************************************************/
    void C_GameObjectManager::Remove(const GameObjectPtr& prGameObject)
    {
        upImpl_->Remove(prGameObject);
    }


    /*************************************************************//**
     *
     *  @brief  ゲームオブジェクトの除去を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_GameObjectManager::Remove(const std::string& rId)
    {
        upImpl_->Remove(rId);
    }


    /*************************************************************//**
     *
     *  @brief  ゲームオブジェクトの除去を行う
     *  @param  種類
     *  @return なし
     *
     ****************************************************************/
    void C_GameObjectManager::Remove(int32_t type)
    {
        upImpl_->Remove(type);
    }


    /*************************************************************//**
     *
     *  @brief  全てゲームオブジェクトの除去を行う
     *  @param  ゲームオブジェクト
     *  @return なし
     *
     ****************************************************************/
    void C_GameObjectManager::AllRemove()
    {
        upImpl_->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  IDからゲームオブジェクトを取得する
     *  @param  ID
     *  @return ゲームオブジェクト
     *
     ****************************************************************/
    boost::optional<const GameObjectPtr&> C_GameObjectManager::GetGameObjectWithId(const std::string& rId)
    {
        return upImpl_->FindGameObjectWithId(rId);
    }


    /*************************************************************//**
     *
     *  @brief  種類からゲームオブジェクトを取得する
     *  @param  種類
     *  @return ゲームオブジェクト
     *
     ****************************************************************/
    GameObjectList C_GameObjectManager::GetGameObjectsWithType(int32_t type)
    {
        return upImpl_->FindGameObjectsWithType(type);
    }
}