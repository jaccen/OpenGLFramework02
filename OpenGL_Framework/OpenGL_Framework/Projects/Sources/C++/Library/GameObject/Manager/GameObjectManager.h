/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Singleton/Assert/AssertSingleton.h"
#include <deque>


//-------------------------------------------------------------
//!
//! @brief ゲームオブジェクト
//! @brief ゲームに存在するオブジェクト関連の名前空間
//!
//-------------------------------------------------------------
namespace GameObject
{
    /* 前方宣言 */
    class C_GameObject;


    /* 型変換 */
    using GameObjectPtr = std::shared_ptr<C_GameObject>;                                        // GameObjectPtr型を宣言
    using GameObjectList = std::deque<GameObjectPtr>;                                           // GameObjectList型を宣言


    //-------------------------------------------------------------
    //!
    //! @brief ゲームオブジェクトマネージャー
    //! @brief ゲームオブジェクトを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_GameObjectManager : public Singleton::C_AssertSingleton<C_GameObjectManager>
    {
    public:
        C_GameObjectManager();                                                                  // コンストラクタ
        ~C_GameObjectManager() override;                                                        // デストラクタ
        void Entry(const GameObjectPtr& prGameObject);                                          // 登録処理
        void Remove(const GameObjectPtr& prGameObject);                                         // 除去処理
        void Remove(const std::string& rId);                                                    // 除去処理
        void Remove(int32_t type);                                                              // 除去処理
        void AllRemove();                                                                       // 全てのゲームオブジェクトを除去
        boost::optional<const GameObjectPtr&> GetGameObjectWithId(const std::string& rId);      // IDからゲームオブジェクトを取得
        GameObjectList GetGameObjectsWithType(int32_t type);                                    // 種類からゲームオブジェクトを取得
    private:
        /* 前方宣言 */
        class C_GameObjectManagerImpl;

        std::unique_ptr<C_GameObjectManagerImpl> upImpl_;                                       ///< @brief 実装情報
    };
}