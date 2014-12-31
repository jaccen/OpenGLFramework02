/* ヘッダファイル */
#include "LuaStateManager.h"
#include <unordered_map>


//-------------------------------------------------------------
//!
//! @brief Lua
//! @brief Lua関連の名前空間
//!
//-------------------------------------------------------------
namespace Lua
{
    //-------------------------------------------------------------
    //!
    //! @brief Luaマネージャーインプリメント
    //! @brief Luaマネージャーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_LuaStateManager::C_LuaManagerStateImpl
    {
    public:
        C_LuaManagerStateImpl();                                                                 // コンストラクタ
        ~C_LuaManagerStateImpl();                                                                // デストラクタ
        void Create(const std::string& rId);                                                // Luaステートを作成
        void Destroy(const std::string& rId);                                               // Luaステートを破棄
        void AllDestroy();                                                                  // Luaステートを全て破棄
        void PrintStack(const std::string& rId);                                            // スタックを出力
        boost::optional<const LuaStatePtr&> GetState(const std::string& rId) const;         // Luaステートを取得
    private:
        std::unordered_map<std::string, LuaStatePtr> pStates_;                              ///< @brief Luaステート
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_LuaStateManager::C_LuaManagerStateImpl::C_LuaManagerStateImpl()
    {
        // 全体で使用するLuaステートを作成
        Create(ID::s_pGLOBAL);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_LuaStateManager::C_LuaManagerStateImpl::~C_LuaManagerStateImpl()
    {
        if (pStates_.empty() == false) AllDestroy();
    }


    /*************************************************************//**
     *
     *  @brief  Luaステートを作成する
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_LuaStateManager::C_LuaManagerStateImpl::Create(const std::string& rId)
    {
        // 既に同じIDで作成している場合
        if (pStates_.find(rId) != pStates_.end())
        {
            std::cout << "[ C_LuaManagerStateImpl::Create ] : 既に同じIDでLuaステートを作成しています。" << std::endl;
            std::cout << "                          ID : " << rId << std::endl;

            return;
        }

        // Luaステートを作成
        pStates_[rId].reset(::luaL_newstate(), [](lua_State* pState){ ::lua_close(pState); });

        // 標準ライブラリを使用可能にする
        ::luaL_openlibs(pStates_[rId].get());

        // Luabindを開く
        ::luabind::open(pStates_[rId].get());
    }


    /*************************************************************//**
     *
     *  @brief  Luaステートを破棄する
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_LuaStateManager::C_LuaManagerStateImpl::Destroy(const std::string& rId)
    {
        // Luaステートが作成されていない場合
        if (pStates_.find(rId) == pStates_.end())
        {
            std::cout << "[ C_LuaManagerStateImpl::PrintStack ] : Luaステートが作成されていません。" << std::endl;

            return;
        }

        // 要素を削除
        pStates_.erase(rId);
    }


    /*************************************************************//**
     *
     *  @brief  Luaステートを全て破棄する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_LuaStateManager::C_LuaManagerStateImpl::AllDestroy()
    {
        pStates_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  スタックを出力する
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_LuaStateManager::C_LuaManagerStateImpl::PrintStack(const std::string& rId)
    {
        // Luaステートが作成されていない場合
        if (pStates_.find(rId) == pStates_.end())
        {
            std::cout << "[ C_LuaManagerStateImpl::PrintStack ] : Luaステートが作成されていません。" << std::endl;

            return;
        }

        // スタック数を取得
        const int32_t STACK_NUMBER = ::lua_gettop(pStates_[rId].get());

        if (STACK_NUMBER == 0)
        {
            std::cout << "[ C_LuaManagerStateImpl::PrintStack ] : スタックに何も積まれていません。" << std::endl;

            return;
        }

        for (int32_t i = STACK_NUMBER; i >= 1; i--)
        {
            std::printf("%03d(%04d): ", i, -STACK_NUMBER + i - 1);

            // タイプを取得
            int32_t type = ::lua_type(pStates_[rId].get(), i);

            // タイプからどのデータが積まれているのか判断する
            switch (type)
            {
            /* nil */
            case LUA_TNIL:

                std::printf("NIL\n");

                break;
            /* ブーリアン */
            case LUA_TBOOLEAN:

                std::printf("BOOLEAN %s\n", ::lua_toboolean(pStates_[rId].get(), i) ? "true" : "false");

                break;
            /* 軽量ユーザーデータ */
            case LUA_TLIGHTUSERDATA:

                std::printf("LIGHTUSERDATA\n");

                break;
            /* 数字 */
            case LUA_TNUMBER:

                std::printf("NUMBER %f\n", ::lua_tonumber(pStates_[rId].get(), i));

                break;
            /* 文字列 */
            case LUA_TSTRING:

                std::printf("STRING %s\n", lua_tostring(pStates_[rId].get(), i));

                break;
            /* テーブル */
            case LUA_TTABLE:

                std::printf("TABLE\n");

                break;
            /* 関数 */
            case LUA_TFUNCTION:

                std::printf("FUNCTION\n");

                break;
            /* ユーザーデータ */
            case LUA_TUSERDATA:

                std::printf("USERDATA\n");

                break;
            /* スレッド */
            case LUA_TTHREAD:

                std::printf("THREAD\n");

                break;
            }
        }

        std::printf("-----------------------------\n\n");
    }


    /*************************************************************//**
     *
     *  @brief  Luaステートを取得する
     *  @param  なし
     *  @return Luaステート
     *
     ****************************************************************/
    boost::optional<const LuaStatePtr&> C_LuaStateManager::C_LuaManagerStateImpl::GetState(const std::string& rId) const
    {
        auto iterator = pStates_.find(rId);
        if (iterator == pStates_.end()) return boost::none;

        return (*iterator).second;
    }
}