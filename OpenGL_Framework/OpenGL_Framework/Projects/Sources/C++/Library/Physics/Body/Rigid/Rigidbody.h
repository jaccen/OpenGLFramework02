/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../CollisionShape/CollisionShape.h"
#include "../../PhysicsDefine.h"
#include <tuple>


//-------------------------------------------------------------
///
/// @brief フィジックス
/// @brief 物理関連の名前空間
///
//-------------------------------------------------------------
namespace Physics
{
    //-------------------------------------------------------------
    //!
    //! @brief リジッドボディ
    //! @brief 剛体を表すクラス
    //!
    //-------------------------------------------------------------
    class C_RigidBody
    {
    public:
        C_RigidBody(C_CollisionShape* pCollisionShape,                                                  // コンストラクタ
                    const Transform& rTransform,
                    float mass = 0.0f,
                    const Vector3& rInertia = Vector3(0.0f, 0.0f, 0.0f));
        virtual ~C_RigidBody();                                                                         // デストラクタ
        void EnableActive(bool validFlag = true);                                                       // アクティブ状態を有効化
        void EnableCollisionResponse(bool validFlag = true);                                            // 衝突応答を有効化
        void EnableCollisionCallback(bool validFlag = true);                                            // 衝突コールバックを有効化
        void EnableFreezePosition(bool x = false, bool y = false, bool z = false);                      // 座標の固定を有効化
        void EnableFreezeRotation(bool x = false, bool y = false, bool z = false);                      // 回転の固定を有効化
        void ApplyForce(const Vector3& rForce,                                                          // 力を加える
                        const Vector3& rOffsetFromCenter = Vector3(0.0f, 0.0f, 0.0f));
        void ApplyImpulse(const Vector3& rImpulse,                                                      // 撃力を加える
                          const Vector3& rOffsetFromCenter = Vector3(0.0f, 0.0f, 0.0f));
        void AddPosition(const Vector3& rPosition);                                                     // 座標を加える
        void ResetVelocity();                                                                           // 速度をリセット
        btRigidBody* GetRigidBody() const;                                                              // 剛体を取得
        C_CollisionShape* GetCollisionShape() const;                                                    // 衝突形状を取得
        const Transform& GetTransform() const;                                                          // トランスフォームを取得
        const Transform& GetCenterOfGravityTransform() const;                                           // 重心のトランスフォームを取得
        const Vector3& GetLinearVelocity() const;                                                       // 線速度を取得
        const Vector3& GetAngularVelocity() const;                                                      // 角速度を取得
        float GetFriction() const;                                                                      // 摩擦係数を取得
        float GetRollingFriction() const;                                                               // 転がり摩擦係数を取得
        float GetRestitution() const;                                                                   // 反発係数を取得
        float GetLinearDamping() const;                                                                 // 移動減衰を取得
        float GetAngularDamping() const;                                                                // 回転減衰を取得
        std::tuple<Vector3, Vector3> GetAabb() const;                                                   // AABBを取得
        int32_t GetActivationState() const;                                                             // アクティベーションステートを取得
        int32_t GetUserIndex() const;                                                                   // 独自のインデックスを取得
        void* GetUserPointer() const;                                                                   // 独自のポインタを取得
        void SetTransform(const Transform& rTransform);                                                 // トランスフォームを設定
        void SetCenterOfGravityTransform(const Transform& rTransform);                                  // 重心のトランスフォームを設定
        void SetLinearVelocity(const Vector3& rLinearVelocity = Vector3(0.0f, 0.0f, 0.0f));             // 線速度を設定
        void SetAngularVelocity(const Vector3& rAngularVelocity = Vector3(0.0f, 0.0f, 0.0f));           // 角速度を設定
        void SetFriction(float friction = 1.0f);                                                        // 摩擦係数を設定
        void SetRollingFriction(float rollingFriction = 1.0f);                                          // 転がり摩擦係数を設定
        void SetRestitution(float restitution = 0.0f);                                                  // 反発係数を設定
        void SetLinearDamping(float linearDamping);                                                     // 移動減衰を設定
        void SetAngularDamping(float angularDamping);                                                   // 回転減衰を設定
        void SetActivationState(int32_t state);                                                         // アクティベーションステートを設定
        void SetUserIndex(int32_t index);                                                               // 独自のインデックスを設定
        void SetUserPointer(void* pPointer);                                                            // 独自のポインタを設定
    private:
        std::unique_ptr<btRigidBody> upRigidBody_;                                                      ///< @brief 剛体
        std::unique_ptr<C_CollisionShape> upCollisionShape_;                                            ///< @brief 衝突形状
        std::unique_ptr<btDefaultMotionState> upMotionState_;                                           ///< @brief モーションステート
    };
}