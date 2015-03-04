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
    class C_BaseBackground;


    /* 別名 */
    using BackgroundPtr = std::shared_ptr<C_BaseBackground>;                                            // BackgroundPtr型


    //-------------------------------------------------------------
    //!
    //! @brief バックグラウンドジェネレーター
    //! @brief バックグラウンドの生成を行うクラス
    //!
    //-------------------------------------------------------------
    class C_BackgroundGenerator : public Singleton::C_AssertSingleton<C_BackgroundGenerator>
    {
    public:
        /* 別名 */
        using CreateFunction = C_BaseBackground*(*)();                                          // CreateFunction型

        C_BackgroundGenerator();                                                                // コンストラクタ
        ~C_BackgroundGenerator() override;                                                      // デストラクタ
        BackgroundPtr Create(const std::string& rId,                                            // 生成処理
                             const Vector3& rPosition,
                             const Vector3& rRotation = Vector3::s_ZERO,
                             const Vector3& rScale = Vector3::s_ONE,
                             const Vector3& rVelocity = Vector3::s_ZERO,
                             const Vector3& rAccelaration = Vector3::s_ZERO,
                             const Vector3& rRotationVelocity = Vector3::s_ZERO,
                             const Vector3& rRotationAccelaration = Vector3::s_ZERO,
                             int32_t lifeFrame = -1);
        void AutoCreate(int32_t frame);                                                         // 自動生成処理
        void RegistFunction(const std::string& rId, CreateFunction pCreateFunction);            // 関数の登録
        void SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem);                             // タスクシステムを設定
        void SetBackgroundData(JSON::JsonObject* pBackgroundData);                              // 背景データを設定
        void SetAutoCreateMaxCount(int32_t autoCreateMaxCount);                                 // 自動生成の最大数を設定
    private:
        std::unordered_map<std::string, CreateFunction> pCreateFunctions_;                      ///< @brief 生成関数
        Task::C_GeneralTaskSystem* pTaskSystem_ = nullptr;                                      ///< @brief タスクシステム
        int32_t number = 0;                                                                     ///< @brief 番号
        JSON::JsonObject* pBackgroundData_;                                                     ///< @brief 背景データ
        int32_t autoCreateIndex_ = 0;                                                           ///< @brief 自動生成のインデックス
        int32_t autoCreateMaxCount_ = 0;                                                        ///< @brief 自動生成の最大数
    };
}