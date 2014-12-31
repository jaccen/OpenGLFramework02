/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../Singleton/Assert/AssertSingleton.h"
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <luabind/operator.hpp>


//-------------------------------------------------------------
//!
//! @brief Lua
//! @brief Lua関連の名前空間
//!
//-------------------------------------------------------------
namespace Lua
{
    /* 別名 */
    using LuaStatePtr = std::shared_ptr<lua_State>;                                                     // LuaStatePtr型


    namespace
    {
        /* ID */
        namespace ID
        {
            const char* s_pGLOBAL = "Global";                                                           ///< @brief 全体で使用可能
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief Luaステートマネージャー
    //! @brief Luaステートを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_LuaStateManager : public Singleton::C_AssertSingleton<C_LuaStateManager>
    {
    public:
        C_LuaStateManager();                                                                                // コンストラクタ
        ~C_LuaStateManager() override;                                                                      // デストラクタ
        void Create(const std::string& rId);                                                                // Luaステートを作成
        void Destroy(const std::string& rId);                                                               // Luaステートを破棄
        void AllDestroy();                                                                                  // Luaステートを全て破棄
        void PrintStack(const std::string& rId = ID::s_pGLOBAL);                                            // スタックの内容を出力
        boost::optional<const LuaStatePtr&> GetState(const std::string& rId = ID::s_pGLOBAL) const;         // Luaステートを取得
    private:
        /* 前方宣言 */
        class C_LuaManagerStateImpl;

        std::unique_ptr<C_LuaManagerStateImpl> upImpl_;                                                     /// < brief 実装情報
    };
}
