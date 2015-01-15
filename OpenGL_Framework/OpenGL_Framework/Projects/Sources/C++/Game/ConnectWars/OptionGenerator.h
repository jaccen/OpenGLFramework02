/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectWarsDefine.h"
#include "../../Library/Singleton/Assert/AssertSingleton.h"
#include "../../Library/Physics/PhysicsDefine.h"
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
    class C_BaseOption;
    class C_RigidBodyMoveLogic;


    /* 別名 */
    using OptionPtr = std::shared_ptr<C_BaseOption>;                                                // OptionPtr型


    //-------------------------------------------------------------
    //!
    //! @brief オプションジェネレーター
    //! @brief オプションの生成を行うクラス
    //!
    //-------------------------------------------------------------
    class C_OptionGenerator : public Singleton::C_AssertSingleton<C_OptionGenerator>
    {
    public:
        /* 別名 */
        using CreateFunction = C_BaseOption*(*)();                                                  // CreateFunction型

        C_OptionGenerator();                                                                        // コンストラクタ
        ~C_OptionGenerator() override;                                                              // デストラクタ
        OptionPtr Create(const std::string& rId, const Physics::Vector3& rPosition);                // 生成処理
        void RegistFunction(const std::string& rId, CreateFunction pCreateFunction);                // 関数の登録
        void SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem);                                 // タスクシステムを設定
    private:
        std::unordered_map<std::string, CreateFunction> pCreateFunctions_;                          ///< @brief 生成関数
        Task::C_GeneralTaskSystem* pTaskSystem_ = nullptr;                                          ///< @brief タスクシステム
        int32_t number = 0;                                                                         ///< @brief 番号
    };
}