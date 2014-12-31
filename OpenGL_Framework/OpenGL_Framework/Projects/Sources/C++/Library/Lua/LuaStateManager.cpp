/* ヘッダファイル */
#include "LuaStateManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief Lua
//! @brief Lua関連の名前空間
//!
//-------------------------------------------------------------
namespace Lua
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_LuaStateManager::C_LuaStateManager() :

        // 実装情報
        upImpl_(std::make_unique<C_LuaManagerStateImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_LuaStateManager::~C_LuaStateManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  Luaステートを作成する
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_LuaStateManager::Create(const std::string& rId)
    {
        upImpl_->Create(rId);
    }


    /*************************************************************//**
     *
     *  @brief  Luaステートを破棄する
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_LuaStateManager::Destroy(const std::string& rId)
    {
        upImpl_->Destroy(rId);
    }


    /*************************************************************//**
     *
     *  @brief  Luaステートを全て破棄する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_LuaStateManager::AllDestroy()
    {
        upImpl_->AllDestroy();
    }


    /*************************************************************//**
     *
     *  @brief  スタックの内容を出力する
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_LuaStateManager::PrintStack(const std::string& rId)
    {
        upImpl_->PrintStack(rId);
    }


    /*************************************************************//**
     *
     *  @brief  Luaステートを取得する
     *  @param  なし
     *  @return Luaステート
     *
     ****************************************************************/
    boost::optional<const LuaStatePtr&> C_LuaStateManager::GetState(const std::string& rId) const
    {
        return upImpl_->GetState(rId);
    }
}