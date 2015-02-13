/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectWarsDefine.h"
#include "../../Library/Singleton/Assert/AssertSingleton.h"
#include "../../Library/Physics/PhysicsDefine.h"
#include "../../Library/JSON/Object/JsonObject.h"
#include <unordered_map>


/* 前方宣言 */
namespace Task
{
    class C_GeneralTaskSystem;
}


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* 前方宣言 */
    class C_BaseEnemy;


    /* 別名 */
    using EnemyPtr = std::shared_ptr<C_BaseEnemy>;                                                  // EnemyPtr型


    //-------------------------------------------------------------
    //!
    //! @brief エネミージェネレーター
    //! @brief 敵の生成を行うクラス
    //!
    //-------------------------------------------------------------
    class C_EnemyGenerator : public Singleton::C_AssertSingleton<C_EnemyGenerator>
    {
    public:
        /* 別名 */
        using CreateFunction = C_BaseEnemy*(*)();                                                   // CreateFunction型

        C_EnemyGenerator();                                                                         // コンストラクタ
        ~C_EnemyGenerator() override;                                                               // デストラクタ
        EnemyPtr Create(const std::string& rId);                                                    // 生成処理
        void AutoCreate(int32_t frame);                                                             // 自動生成処理
        void RegistFunction(const std::string& rId, CreateFunction pCreateFunction);                // 関数の登録
        void SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem);                                 // タスクシステムを設定
        void SetEnemyData(const JSON::JsonObjectPtr& prEnemyData);                                  // 敵データを設定
    private:
        std::unordered_map<std::string, CreateFunction> pCreateFunctions_;                          ///< @brief 生成関数
        Task::C_GeneralTaskSystem* pTaskSystem_ = nullptr;                                          ///< @brief タスクシステム
        int32_t number = 0;                                                                         ///< @brief 番号
        JSON::JsonObjectPtr pEnemyData_;                                                            ///< @brief 敵データ
    };
}