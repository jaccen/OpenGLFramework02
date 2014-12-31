/* ヘッダファイル */
#include "SoftBody.h"
#include "../Rigid/RigidBody.h"
#include "../../../Debug/Helper/DebugHelper.h"
#include "Joint/LinearJoint.h"
#include "Joint/AngularJoint.h"
#include <BulletSoftBody/btSoftBodyHelpers.h>


//-------------------------------------------------------------
///
/// @brief フィジックス
/// @brief 物理関連の名前空間
///
//-------------------------------------------------------------
namespace Physics
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ソフトボディ情報
     *  @param  頂点座標
     *  @param  インデックス
     *  @param  三角形の数
     *  @param  全体の質量
     *  @param  拡大率
     *  @param  コンフィグ
     *  @param  マテリアル
     *  @param  体積を保つか判断するフラグ
     *  @param  内部フレームが有効か判断するフラグ
     *  @param  形状を保つか判断するフラグ
     *
     ****************************************************************/
    C_SoftBody::C_SoftBody(SoftBodyInfo* pSoftBodyInfo,
                           const Transform& rTransform,
                           Vector3 vertexPositions[],
                           int32_t indices[],
                           uint32_t triangleCount,
                           float totalMass,
                           const Vector3& rScale,
                           const S_Config& rConfig,
                           const S_Material& rMaterial,
                           bool keepVolumeFlag, 
                           bool innerFlameFlag,
                           bool keepShapeFlag) : 

        // 軟体
        upSoftBody_(btSoftBodyHelpers::CreateFromTriMesh(*pSoftBodyInfo,
                                                         reinterpret_cast<btScalar*>(vertexPositions),
                                                         indices,
                                                         static_cast<int32_t>(triangleCount)))

    {
        // コンフィグを設定
        SetConfig(rConfig);

        // 大きさを変更
        upSoftBody_->scale(rScale);

        // 体積保存と内部フレームを設定
        upSoftBody_->setPose(keepVolumeFlag, innerFlameFlag);

        // マテリアルを設定し、近くの頂点同士を拘束
        if (rMaterial.vertexDistance_ > 0)
        {
            SetMaterial(rMaterial);
            upSoftBody_->generateBendingConstraints(rMaterial.vertexDistance_, upSoftBody_->m_materials[0]);
        }

        // ソフトボディ同士の衝突を有効化
        EnableSoftBodyCollision();

        // ランダムに頂点間を拘束し、全体の形状を保つ
        if (keepShapeFlag == true) upSoftBody_->randomizeConstraints();

        // トランスフォームを設定
        upSoftBody_->setWorldTransform(rTransform);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SoftBody::~C_SoftBody()
    {
    }


    /*************************************************************//**
     *
     *  @brief  アクティブ状態を有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::EnableActive(bool validFlag)
    {
        upSoftBody_->activate(validFlag);
    }


    /*************************************************************//**
     *
     *  @brief  衝突応答を有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::EnableCollisionResponse(bool validFlag)
    {
        if (validFlag == true)
        {
            upSoftBody_->setCollisionFlags(upSoftBody_->getCollisionFlags() & (~btCollisionObject::CF_NO_CONTACT_RESPONSE));
        }
        else
        {
            upSoftBody_->setCollisionFlags(upSoftBody_->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
        }
    }


    /*************************************************************//**
     *
     *  @brief  軟体との衝突判定を有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::EnableSoftBodyCollision(bool validFlag)
    {
        if (validFlag == true)
        {
		    upSoftBody_->m_cfg.collisions |= btSoftBody::fCollision::VF_SS;
        }
        else
        {
		    upSoftBody_->m_cfg.collisions &= ~btSoftBody::fCollision::VF_SS;
        }
    }


     /*************************************************************//**
     *
     *  @brief  衝突コールバックを有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::EnableCollisionCallback(bool validFlag)
    {
        if (validFlag == true)
        {
            upSoftBody_->setCollisionFlags(upSoftBody_->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
        }
        else
        {
            upSoftBody_->setCollisionFlags(upSoftBody_->getCollisionFlags() & (~btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK));
        }
    }


    /*************************************************************//**
     *
     *  @brief  力を加える
     *  @param  力
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::ApplyForce(const Vector3& rForce)
    {
        upSoftBody_->addForce(rForce);
    }


    /*************************************************************//**
     *
     *  @brief  頂点に風の力を加える
     *  @param  風の力
     *  @param  頂点インデックス
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::ApplyAeroForceToVertex(const Vector3& rAeroForce, int32_t vertexIndex)
    {
        upSoftBody_->addAeroForceToNode(rAeroForce, vertexIndex);
    }


    /*************************************************************//**
     *
     *  @brief  面に風の力を加える
     *  @param  風の力
     *  @param  面のインデックス
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::ApplyAeroForceToFace(const Vector3& rAeroForce, int32_t faceIndex)
    {
        upSoftBody_->addAeroForceToFace(rAeroForce, faceIndex);
    }


    /*************************************************************//**
     *
     *  @brief  力を加える
     *  @param  力
     *  @param  頂点インデックス
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::ApplyForce(const Vector3& rForce, int32_t vertexIndex)
    {
        upSoftBody_->addForce(rForce, vertexIndex);
    }


    /*************************************************************//**
     *
     *  @brief  座標を加える
     *  @param  座標
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::AddPosition(const Vector3& rPosition)
    {
        upSoftBody_->translate(rPosition);
    }


    /*************************************************************//**
     *
     *  @brief  速度を加える
     *  @param  速度
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::AddVelocity(const Vector3& rVelocity)
    {
        upSoftBody_->addVelocity(rVelocity);
    }


    /*************************************************************//**
     *
     *  @brief  速度を加える
     *  @param  速度
     *  @param  頂点インデックス
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::AddVelocity(const Vector3& rVelocity, int32_t vertexIndex)
    {
        upSoftBody_->addVelocity(rVelocity, vertexIndex);
    }


    /*************************************************************//**
     *
     *  @brief  アンカーを追加する
     *  @param  頂点インデックス
     *  @param  剛体
     *  @param  リンクのボディ間の衝突を行うか判断するフラグ
     *  @param  アンカー強度
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::AppendAnchor(int32_t vertexIndex,
                                  C_RigidBody* pRigidBody,
                                  bool collisionBetweenLinkedBodiesFlag,
                                  float influence)
    {
        upSoftBody_->appendAnchor(vertexIndex, pRigidBody->GetRigidBody(), collisionBetweenLinkedBodiesFlag, influence);
    }


    /*************************************************************//**
     *
     *  @brief  直線接合を追加する
     *  @param  直線接合
     *  @param  もう一つのソフトボディ
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::AppendLinearJoint(C_LinearJoint* pLinearJoint, C_SoftBody* pAnother)
    {
        upSoftBody_->appendLinearJoint(*pLinearJoint->GetLinearJointSpec(), pAnother->GetSoftBody());
    }


    /*************************************************************//**
     *
     *  @brief  角接合を追加する
     *  @param  角接合
     *  @param  もう一つのソフトボディ
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::AppendAngularJoint(C_AngularJoint* pAngularJoint, C_SoftBody* pAnother)
    {
        upSoftBody_->appendAngularJoint(*pAngularJoint->GetAngularJointSpec(), pAnother->GetSoftBody());
    }


    /*************************************************************//**
     *
     *  @brief  軟体を取得する
     *  @param  なし
     *  @return 軟体
     *
     ****************************************************************/
    btSoftBody* C_SoftBody::GetSoftBody() const
    {
        return upSoftBody_.get();
    }


    /*************************************************************//**
     *
     *  @brief  トランスフォームを取得する
     *  @param  なし
     *  @return トランスフォーム
     *
     ****************************************************************/
    const Transform& C_SoftBody::GetTransform() const
    {
        return upSoftBody_->getWorldTransform();
    }


    /*************************************************************//**
     *
     *  @brief  質量を取得する
     *  @param  なし
     *  @return 質量
     *
     ****************************************************************/
    float C_SoftBody::GetMass(int32_t vertexIndex) const
    {
        return upSoftBody_->getMass(vertexIndex);
    }


    /*************************************************************//**
     *
     *  @brief  全体の質量を取得する
     *  @param  なし
     *  @return 全体の質量
     *
     ****************************************************************/
    float C_SoftBody::GetTotalMass() const
    {
        return upSoftBody_->getTotalMass();
    }


    /*************************************************************//**
     *
     *  @brief  摩擦係数を取得する
     *  @param  なし
     *  @return 摩擦係数
     *
     ****************************************************************/
    float C_SoftBody::GetFriction() const
    {
        return upSoftBody_->getFriction();
    }


    /*************************************************************//**
     *
     *  @brief  転がり摩擦係数を取得する
     *  @param  なし
     *  @return 転がり摩擦係数
     *
     ****************************************************************/
    float C_SoftBody::GetRollingFriction() const
    {
        return upSoftBody_->getRollingFriction();
    }


    /*************************************************************//**
     *
     *  @brief  反発係数を取得する
     *  @param  なし
     *  @return 反発係数
     *
     ****************************************************************/
    float C_SoftBody::GetRestitution() const
    {
        return upSoftBody_->getRestitution();
    }


    /*************************************************************//**
     *
     *  @brief  AABBを取得する
     *  @param  なし
     *  @return AABBの最小値と最大値
     *
     ****************************************************************/
    std::tuple<Vector3, Vector3> C_SoftBody::GetAabb() const
    {
        std::tuple<Vector3, Vector3> aabb;
        upSoftBody_->getAabb(std::get<0>(aabb), std::get<1>(aabb));

        return aabb;
    }


    /*************************************************************//**
     *
     *  @brief  アクティベーションステートを取得する
     *  @param  なし
     *  @return アクティベーションステート
     *
     ****************************************************************/
    int32_t C_SoftBody::GetActivationState() const
    {
        return upSoftBody_->getActivationState();
    }


    /*************************************************************//**
     *
     *  @brief  独自のインデックスを取得する
     *  @param  なし
     *  @return 独自のインデックス
     *
     ****************************************************************/
    int32_t C_SoftBody::GetUserIndex() const
    {
        return upSoftBody_->getUserIndex();
    }


    /*************************************************************//**
     *
     *  @brief  独自のポインタを取得する
     *  @param  なし
     *  @return 独自のポインタ
     *
     ****************************************************************/
    void* C_SoftBody::GetUserPointer() const
    {
        return upSoftBody_->getUserPointer();
    }


    /*************************************************************//**
     *
     *  @brief  コンフィグを設定する
     *  @param  コンフィグ
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::SetConfig(const S_Config& rConfig)
    {
        upSoftBody_->m_cfg.kDP = rConfig.damping_;
        upSoftBody_->m_cfg.kDF = rConfig.dynamicFriction_;
        upSoftBody_->m_cfg.kMT = rConfig.poseMatching_;
        upSoftBody_->m_cfg.kVC = rConfig.volumeConversation_;
        upSoftBody_->m_cfg.kCHR = rConfig.rigidContactHardness_;
        upSoftBody_->m_cfg.kSHR = rConfig.softContactHardness_;
        upSoftBody_->m_cfg.kKHR = rConfig.kineticContactHardness_;
        upSoftBody_->m_cfg.kAHR = rConfig.anchorsHardness_;
        upSoftBody_->m_cfg.kPR = rConfig.pressure_;
        upSoftBody_->m_cfg.piterations = rConfig.positionSolverIterationCount_;
        upSoftBody_->m_cfg.viterations = rConfig.velocitySolverIterationCount_;
        upSoftBody_->m_cfg.diterations = rConfig.driftSolverIterationCount_;
        upSoftBody_->m_cfg.citerations = rConfig.clusterSolverIterationCount_;
    }


    /*************************************************************//**
     *
     *  @brief  マテリアルを設定する
     *  @param  マテリアル
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::SetMaterial(const S_Material& rMaterial)
    {
        upSoftBody_->m_materials[0]->m_kLST = rMaterial.linearStiffness_;
        upSoftBody_->m_materials[0]->m_kAST = rMaterial.angularStiffness_;
        upSoftBody_->m_materials[0]->m_kVST = rMaterial.volumeStiffness_;
    }


    /*************************************************************//**
     *
     *  @brief  トランスフォームを設定する
     *  @param  トランスフォーム
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::SetTransform(const Transform& rTransform)
    {
        upSoftBody_->setWorldTransform(rTransform);
    }


    /*************************************************************//**
     *
     *  @brief  質量を設定する
     *  @param  質量
     *  @param  頂点インデックス
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::SetMass(float mass, int32_t vertexIndex)
    {
        upSoftBody_->setMass(vertexIndex, mass);
    }


    /*************************************************************//**
     *
     *  @brief  全体の質量を設定する
     *  @param  全体の質量
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::SetTotalMass(float totalMass)
    {
        upSoftBody_->setTotalMass(totalMass);
    }


    /*************************************************************//**
     *
     *  @brief  全体の密度を設定する
     *  @param  全体の密度
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::SetTotalDensity(float totalDensity)
    {
        upSoftBody_->setTotalDensity(totalDensity);
    }


    /*************************************************************//**
     *
     *  @brief  摩擦係数を設定する
     *  @param  摩擦係数
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::SetFriction(float friction)
    {
        upSoftBody_->setFriction(friction);
    }


    /*************************************************************//**
     *
     *  @brief  転がり摩擦係数を設定する
     *  @param  転がり摩擦係数
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::SetRollingFriction(float rollingFriction)
    {
        upSoftBody_->setRollingFriction(rollingFriction);
    }


    /*************************************************************//**
     *
     *  @brief  反発係数を設定する
     *  @param  反発係数
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::SetRestitution(float restitution)
    {
        upSoftBody_->setRestitution(restitution);
    }


    /*************************************************************//**
     *
     *  @brief  アクティベーションステートを設定する
     *  @param  アクティベーションステート
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::SetActivationState(int32_t state)
    {
        upSoftBody_->setActivationState(state);
    }


    /*************************************************************//**
     *
     *  @brief  独自のインデックスを設定する
     *  @param  独自のインデックス
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::SetUserIndex(int32_t index)
    {
        upSoftBody_->setUserIndex(index);
    }


    /*************************************************************//**
     *
     *  @brief  独自のポインタを設定する
     *  @param  独自のポインタ
     *  @return なし
     *
     ****************************************************************/
    void C_SoftBody::SetUserPointer(void * pPointer)
    {
        upSoftBody_->setUserPointer(pPointer);
    }


    /*************************************************************//**
     *
     *  @brief  楕円体形状の軟体を作成する
     *  @param  ソフトボディ情報
     *  @param  中心座標
     *  @param  半径
     *  @param  頂点数
     *  @param  全体の質量
     *  @param  拡大率
     *  @param  コンフィグ
     *  @param  マテリアル
     *  @param  体積を保つか判断するフラグ
     *  @param  内部フレームが有効か判断するフラグ
     *  @param  形状を保つか判断するフラグ
     *  @return 楕円体形状の軟体
     *
     ****************************************************************/
    C_SoftBody* C_SoftBody::s_CreateEllipsoid(SoftBodyInfo* pSoftBodyInfo,
                                              const Vector3& rCenterPoint,
                                              const Vector3& rRadius,
                                              int32_t vertexCount,
                                              float totalMass,
                                              const Vector3& rScale,
                                              const S_Config& rConfig,
                                              const S_Material& rMaterial,
                                              bool keepVolumeFlag,
                                              bool innerFlameFlag,
                                              bool keepShapeFlag)
    {
        // 楕円形状の軟体を作成
        C_SoftBody* pEllipsoidSoftBody = newEx C_SoftBody;
        auto& rpSoftBody = pEllipsoidSoftBody->upSoftBody_;

        rpSoftBody.reset(btSoftBodyHelpers::CreateEllipsoid(*pSoftBodyInfo,
                                                            rCenterPoint,
                                                            rRadius,
                                                            vertexCount));

        // コンフィグを設定
        pEllipsoidSoftBody->SetConfig(rConfig);

        // 大きさを変更
        rpSoftBody->scale(rScale);

        // 体積保存と内部フレームを設定
        rpSoftBody->setPose(keepVolumeFlag, innerFlameFlag);

        // マテリアルを設定し、近くの頂点同士を拘束
        if (rMaterial.vertexDistance_ > 0)
        {
            pEllipsoidSoftBody->SetMaterial(rMaterial);
            rpSoftBody->generateBendingConstraints(rMaterial.vertexDistance_, rpSoftBody->m_materials[0]);
        }

        // ソフトボディ同士の衝突を有効化
        pEllipsoidSoftBody->EnableSoftBodyCollision();

        // ランダムに頂点間を拘束し、全体の形状を保つ
        if (keepShapeFlag == true) rpSoftBody->randomizeConstraints();

        return pEllipsoidSoftBody;
    }
}