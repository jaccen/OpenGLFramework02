/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
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
    /* 前方宣言 */
    class C_RigidBody;
    class C_LinearJoint;
    class C_AngularJoint;


    //-------------------------------------------------------------
    //!
    //! @brief コンフィグ
    //! @brief ソフトボディの性質を表す構造体
    //!
    //-------------------------------------------------------------
    struct S_Config
    {
        float damping_ = 0.0f;                                                                          ///< @brief 減衰係数
        float dynamicFriction_ = 0.0f;                                                                  ///< @brief 動摩擦係数
        float poseMatching_ = 0.0f;                                                                     ///< @brief 形状維持力
        float rigidContactHardness_ = 1.0f;                                                             ///< @brief 剛性接触係数( 跳ね具合 )
        float softContactHardness_ = 1.0f;                                                              ///< @brief 軟性接触係数
        float kineticContactHardness_ = 0.1f;                                                           ///< @brief 運動接触係数
        float anchorsHardness_ = 1.0f;                                                                  ///< @brief アンカー硬度
        float pressure_ = 1000.0f;                                                                      ///< @brief 圧力
        float volumeConversation_ = 10.0f;                                                              ///< @brief 体積保存係数
        int32_t positionSolverIterationCount_ = 1;                                                      ///< @brief 座標の修正回数
        int32_t velocitySolverIterationCount_ = 0;                                                      ///< @brief 速度の修正回数
        int32_t driftSolverIterationCount_ = 0;                                                         ///< @brief 推進力の修正回数
        int32_t clusterSolverIterationCount_ = 4;                                                       ///< @brief 骨の修正回数
    };


    //-------------------------------------------------------------
    //!
    //! @brief マテリアル
    //! @brief ソフトボディのマテリアルを表す構造体
    //!
    //-------------------------------------------------------------
    struct S_Material
    {
        int32_t vertexDistance_ = 1;                                                                    ///< @brief 頂点間の距離
        float linearStiffness_ = 1.0f;                                                                  ///< @brief 剛性係数
        float angularStiffness_ = 1.0f;                                                                 ///< @brief 回転剛性係数
        float volumeStiffness_ = 1.0f;                                                                  ///< @brief ボリューム剛性係数
    };


    //-------------------------------------------------------------
    //!
    //! @brief ソフトボディ
    //! @brief 軟体を表すクラス
    //!
    //-------------------------------------------------------------
    class C_SoftBody
    {
    public:
        


        C_SoftBody() = default;                                                                         // デフォルトコンストラクタ
        C_SoftBody(SoftBodyInfo* pSoftBodyInfo,                                                         // コンストラクタ
                   const Transform& rTransform,
                   Vector3 vertexPositions[],
                   int32_t indices[],
                   uint32_t triangleCount,
                   float totalMass = 1.0f,
                   const Vector3& rScale = Vector3(1.0f, 1.0f, 1.0f),
                   const S_Config& rConfig = S_Config(),
                   const S_Material& rMaterial = S_Material(),
                   bool keepVolumeFlag = true,
                   bool innerFlameFlag = true,
                   bool keepShapeFlag = true);
        ~C_SoftBody();                                                                                  // デストラクタ
        void EnableActive(bool validFlag = true);                                                       // アクティブ状態を有効化
        void EnableCollisionResponse(bool validFlag = true);                                            // 衝突応答を有効化
        void EnableSoftBodyCollision(bool validFlag = true);                                            // 軟体との衝突を有効化
        void EnableCollisionCallback(bool validFlag = true);                                            // 衝突コールバックを有効化
        void ApplyForce(const Vector3& rForce);                                                         // 力を加える
        void ApplyForce(const Vector3& rForce, int32_t vertexIndex);                                    // 力を加える
        void ApplyAeroForceToVertex(const Vector3& rAeroForce, int32_t vertexIndex);                    // 頂点に風の力を加える
        void ApplyAeroForceToFace(const Vector3& rAeroForce, int32_t faceIndex);                        // 面に風の力を加える
        void AddPosition(const Vector3& rPosition);                                                     // 座標を加える
        void AddVelocity(const Vector3& rVelocity);                                                     // 速度を加える
        void AddVelocity(const Vector3& rVelocity, int32_t vertexIndex);                                // 速度を加える
        void AppendAnchor(int32_t vertexIndex,                                                          // アンカーを追加
                          C_RigidBody* pRigidBody,
                          bool collisionBetweenLinkedBodiesFlag = true,
                          float influence = 1.0f);
        void AppendLinearJoint(C_LinearJoint* pLinearJoint, C_SoftBody* pAnother);                      // 線形接合を追加
        void AppendAngularJoint(C_AngularJoint* pAngularJoint, C_SoftBody* pAnother);                   // 角接合を追加
        btSoftBody* GetSoftBody() const;                                                                // 軟体を取得
        const Transform& GetTransform() const;                                                          // トランスフォームを取得
        float GetMass(int32_t vertexIndex) const;                                                       // 質量を取得
        float GetTotalMass() const;                                                                     // 全体の質量を取得
        float GetFriction() const;                                                                      // 摩擦係数を取得
        float GetRollingFriction() const;                                                               // 転がり摩擦係数を取得
        float GetRestitution() const;                                                                   // 反発係数を取得
        std::tuple<Vector3, Vector3> GetAabb() const;                                                   // AABBを取得
        int32_t GetActivationState() const;                                                             // アクティベーションステートを取得
        int32_t GetUserIndex() const;                                                                   // 独自のインデックスを取得
        void* GetUserPointer() const;                                                                   // 独自のポインタを取得
        void SetConfig(const S_Config& rConfig);                                                        // コンフィグを設定
        void SetMaterial(const S_Material& rMaterial);                                                  // マテリアルを設定
        void SetTransform(const Transform& rTransform);                                                 // トランスフォームを設定
        void SetMass(float mass, int32_t vertexIndex);                                                  // 質量を設定
        void SetTotalMass(float totalMass);                                                             // 全体の質量を設定
        void SetTotalDensity(float totalDensity);                                                       // 全体の密度を設定
        void SetFriction(float friction = 1.0f);                                                        // 摩擦係数を設定
        void SetRollingFriction(float rollingFriction = 1.0f);                                          // 転がり摩擦係数を設定
        void SetRestitution(float restitution = 0.0f);                                                  // 反発係数を設定
        void SetActivationState(int32_t state);                                                         // アクティベーションステートを設定
        void SetUserIndex(int32_t index);                                                               // 独自のインデックスを設定
        void SetUserPointer(void* pData);                                                               // 独自のポインタを設定

        static C_SoftBody* s_CreateEllipsoid(SoftBodyInfo* pSoftBodyInfo,                               // 楕円体形状の軟体を作成
                                             const Vector3& rCenterPoint,
                                             const Vector3& rRadius,
                                             int32_t vertexCount,
                                             float totalMass = 1.0f,
                                             const Vector3& rScale = Vector3(1.0f, 1.0f, 1.0f),
                                             const S_Config& rConfig = S_Config(),
                                             const S_Material& rMaterial = S_Material(),
                                             bool keepVolumeFlag = true,
                                             bool innerFlameFlag = true,
                                             bool keepShapeFlag = true);
    private:
        std::unique_ptr<btSoftBody> upSoftBody_;                                                        ///< @brief 軟体
    };
}