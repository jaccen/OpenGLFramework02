/* ヘッダファイル */
#include "JsonObjectManagerImpl.h"


//-------------------------------------------------------------
///
/// @brief JSON
/// @brief JSON関連のクラスや関数などに付ける名前空間
///
//-------------------------------------------------------------
namespace JSON
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_JsonObjectManager::C_JsonObjectManager() :

        // 実装情報
        upImpl_(std::make_unique<C_JsonObjectManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_JsonObjectManager::~C_JsonObjectManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  JSONオブジェクトの登録を行う
     *  @param  JSONオブジェクト
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_JsonObjectManager::Entry(const JsonObjectPtr& prLight, const std::string& rId)
    {
        upImpl_->Entry(prLight, rId);
    }


    /*************************************************************//**
     *
     *  @brief  JSONオブジェクトの除去を行う
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_JsonObjectManager::Remove(const std::string& rId)
    {
        upImpl_->Remove(rId);
    }


    /*************************************************************//**
     *
     *  @brief  全てのJSONオブジェクトの除去を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_JsonObjectManager::AllRemove()
    {
        upImpl_->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  JSONオブジェクトを取得する
     *  @param  ID
     *  @return 取得できた場合      ：JSONオブジェクト
     *  @return 取得できなかった場合：none
     *
     ****************************************************************/
    boost::optional<const JsonObjectPtr&> C_JsonObjectManager::GetJsonObject(const std::string& rId) const
    {
        return upImpl_->GetJsonObject(rId);
    }
}