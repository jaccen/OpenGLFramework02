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
    class C_BaseBullet;
    class C_RigidBodyMoveLogic;


    /* 別名 */
    using BulletPtr = std::shared_ptr<C_BaseBullet>;                                                // BulletPtr型


    //-------------------------------------------------------------
    //!
    //! @brief バレットジェネレーター
    //! @brief バレットの生成を行うクラス
    //!
    //-------------------------------------------------------------
    class C_BulletGenerator : public Singleton::C_AssertSingleton<C_BulletGenerator>
    {
    public:
        /* 別名 */
        using CreateFunction = C_BaseBullet*(*)(int32_t shooterType);                               // CreateFunction型

        C_BulletGenerator();                                                                        // コンストラクタ
        ~C_BulletGenerator() override;                                                              // デストラクタ
        BulletPtr Create(const std::string& rId,                                                    // 生成処理
                         const Physics::Vector3& rPosition,
                         int32_t power,
                         C_RigidBodyMoveLogic* pMoveLogic,
                         int32_t shooterType);
        void RegistFunction(const std::string& rId, CreateFunction pCreateFunction);                // 関数の登録
        void SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem);                                 // タスクシステムを設定
    private:
        std::unordered_map<std::string, CreateFunction> pCreateFunctions_;                          ///< @brief 生成関数
        Task::C_GeneralTaskSystem* pTaskSystem_ = nullptr;                                          ///< @brief タスクシステム
        int32_t number = 0;                                                                         ///< @brief 番号
    };
}