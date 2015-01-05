/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Singleton/Assert/AssertSingleton.h"
#include "../PhysicsDefine.h"


//-------------------------------------------------------------
///
/// @brief フィジックス
/// @brief 物理関連の名前空間
///
//-------------------------------------------------------------
namespace Physics
{
    /* 前方宣言 */
    class C_RigidBody;
    class C_SoftBody;
    

    namespace
    {
        /* デフォルト */
        namespace Default
        {
            const Vector3 s_GRAVITY = Vector3(0.0f, 9.8f, 0.0f);                                                                ///< @brief 重力
            const float s_AIR_DENSITY = 1.2f;                                                                                   ///< @brief 空気密度
        }
    }

    //-------------------------------------------------------------
    //!
    //! @brief フィジックスエンジン
    //! @brief 物理エンジンを表すクラス
    //!
    //-------------------------------------------------------------
    class C_PhysicsEngine : public Singleton::C_AssertSingleton<C_PhysicsEngine>
    {
    public:
        /* 別名 */
        using BroadphaseFilterType = btBroadphaseProxy;                                                                         // BroadphaseFilterType型

        C_PhysicsEngine(const Vector3& rWorldMin = Vector3(-10000.0f, -10000.0f, -10000.0f),                                    // コンストラクタ
                        const Vector3& rWorldMax = Vector3( 10000.0f,  10000.0f,  10000.0f),
                        uint16_t maxObjectCount = 10000);
        ~C_PhysicsEngine() override;                                                                                            // デストラクタ
        void Initialize(const Vector3& rGravity = Default::s_GRAVITY,                                                           // 初期化処理
                        float airDensity = Default::s_AIR_DENSITY);
        void Update(float deltaTime);                                                                                           // 更新処理
        void Finalize();                                                                                                        // 終了処理
        void AddRigidBody(C_RigidBody* pRigidBody,                                                                              // 剛体を追加
                          int16_t collisionType = BroadphaseFilterType::AllFilter, 
                          int16_t collisionMask = BroadphaseFilterType::AllFilter);
        void AddSoftBody(C_SoftBody* pSoftBody,                                                                                 // 軟体を追加
                         int16_t collisionType = BroadphaseFilterType::DefaultFilter,
                         int16_t collisionMask = BroadphaseFilterType::AllFilter);
        void RemoveRigidBody(C_RigidBody* pRigidBody);                                                                          // 剛体を除去
        void RemoveSoftBody(C_SoftBody* pSoftBody);                                                                             // 軟体を除去
        const Vector3& GetGravity() const;                                                                                      // 重力を取得
        SoftBodyInfo* GetSoftBodyInfo() const;                                                                                  // ソフトボディ情報を取得
        void SetGravity(const Vector3& rGravity = Default::s_GRAVITY);                                                          // 重力を設定
        void SetCollisionCallbackFunction(CollisionCallbackFunction pCollisionCallbackFunction);                                // 衝突コールバック関数を設定
        void SetSimulationSubstepCallbackFunction(SimulationSubstepCallbackFunction pSimulationSubstepCallbackFunction,         // シミュレーションのサブステップコールバック関数を設定
                                                  void* pWorldUserInfo = nullptr,
                                                  bool previousSubstepCallbackFlag = false);
    private:
        /* 前方宣言 */
        class C_PhysicsEngineImpl;

        std::unique_ptr<C_PhysicsEngineImpl> upImpl_;                                                                           ///< @brief 実装情報
    };
}