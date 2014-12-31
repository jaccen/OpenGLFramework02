/* ヘッダファイル */
#include "RigidBody.h"


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
     *  @param  衝突形状
     *  @param  トランスフォーム
     *  @param  質量( 0の場合は静的剛体となる )
     *  @param  慣性モーメント
     *
     ****************************************************************/
    C_RigidBody::C_RigidBody(C_CollisionShape* pCollisionShape,
                             const Transform& rTransform,
                             float mass,
                             const Vector3& rInertia)
    {
        // モーションステートを作成し、剛体を作成する
        upMotionState_ = std::make_unique<btDefaultMotionState>(rTransform);

        upRigidBody_ = std::make_unique<btRigidBody>(mass, 
                                                     upMotionState_.get(),
                                                     pCollisionShape->GetCollisionShape(),
                                                     rInertia);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_RigidBody::~C_RigidBody()
    {
    }


    /*************************************************************//**
     *
     *  @brief  アクティブ状態を有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::EnableActive(bool validFlag)
    {
        upRigidBody_->activate(validFlag);
    }


    /*************************************************************//**
     *
     *  @brief  衝突応答を有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::EnableCollisionResponse(bool validFlag)
    {
        if (validFlag == true)
        {
            upRigidBody_->setCollisionFlags(upRigidBody_->getCollisionFlags() & (~btCollisionObject::CF_NO_CONTACT_RESPONSE));
        }
        else
        {
            upRigidBody_->setCollisionFlags(upRigidBody_->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
        }
    }


    /*************************************************************//**
     *
     *  @brief  衝突コールバックを有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::EnableCollisionCallback(bool validFlag)
    {
        if (validFlag == true)
        {
            upRigidBody_->setCollisionFlags(upRigidBody_->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
        }
        else
        {
            upRigidBody_->setCollisionFlags(upRigidBody_->getCollisionFlags() & (~btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK));
        }
    }


    /*************************************************************//**
     *
     *  @brief  座標の固定を有効化する
     *  @param  X方向を固定するフラグ
     *  @param  Y方向を固定するフラグ
     *  @param  Z方向を固定するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::EnableFreezePosition(bool x, bool y, bool z)
    {
        Vector3 linearFactor;

        linearFactor.setX((x == false) ? 1.0f : 0.0f);
        linearFactor.setY((y == false) ? 1.0f : 0.0f);
        linearFactor.setZ((z == false) ? 1.0f : 0.0f);

        upRigidBody_->setLinearFactor(linearFactor);
    }


    /*************************************************************//**
     *
     *  @brief  回転の固定を有効化する
     *  @param  X方向を固定するフラグ
     *  @param  Y方向を固定するフラグ
     *  @param  Z方向を固定するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::EnableFreezeRotation(bool x, bool y, bool z)
    {
        Vector3 angularFactor;

        angularFactor.setX((x == false) ? 1.0f : 0.0f);
        angularFactor.setY((y == false) ? 1.0f : 0.0f);
        angularFactor.setZ((z == false) ? 1.0f : 0.0f);

        upRigidBody_->setAngularFactor(angularFactor);
    }


    /*************************************************************//**
     *
     *  @brief  力を加える
     *  @param  力
     *  @param  中心からのオフセット
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::ApplyForce(const Vector3& rForce,          
                                 const Vector3& rOffsetFromCenter)
    {
        upRigidBody_->applyForce(rForce, rOffsetFromCenter);
    }


    /*************************************************************//**
     *
     *  @brief  撃力を加える
     *  @param  撃力
     *  @param  中心からのオフセット
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::ApplyImpulse(const Vector3& rImpulse,          
                                   const Vector3& rOffsetFromCenter)
    {
        upRigidBody_->applyImpulse(rImpulse, rOffsetFromCenter);
    }


    /*************************************************************//**
     *
     *  @brief  座標を加える
     *  @param  座標
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::AddPosition(const Vector3& rPosition)
    {
        upRigidBody_->translate(rPosition);
    }


    /*************************************************************//**
     *
     *  @brief  速度をリセットする
     *  @param  速度
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::ResetVelocity()
    {
        SetLinearVelocity();
        SetAngularVelocity();
    }


    /*************************************************************//**
     *
     *  @brief  剛体を取得する
     *  @param  なし
     *  @return 剛体
     *
     ****************************************************************/
    btRigidBody* C_RigidBody::GetRigidBody() const
    {
        return upRigidBody_.get();
    }


    /*************************************************************//**
     *
     *  @brief  衝突形状を取得する
     *  @param  なし
     *  @return 衝突形状
     *
     ****************************************************************/
    C_CollisionShape* C_RigidBody::GetCollisionShape() const
    {
        return upCollisionShape_.get();
    }


    /*************************************************************//**
     *
     *  @brief  トランスフォームを取得する
     *  @param  なし
     *  @return トランスフォーム
     *
     ****************************************************************/
    const Transform& C_RigidBody::GetTransform() const
    {
        return upRigidBody_->getWorldTransform();
    }


    /*************************************************************//**
     *
     *  @brief  重心のトランスフォームを取得する
     *  @param  なし
     *  @return 重心のトランスフォーム
     *
     ****************************************************************/
    const Transform& C_RigidBody::GetCenterOfGravityTransform() const
    {
        return upRigidBody_->getCenterOfMassTransform();
    }


    /*************************************************************//**
     *
     *  @brief  線速度を取得する
     *  @param  なし
     *  @return 線速度
     *
     ****************************************************************/
    const Vector3& C_RigidBody::GetLinearVelocity() const
    {
        return upRigidBody_->getLinearVelocity();
    }


    /*************************************************************//**
     *
     *  @brief  角速度を取得する
     *  @param  なし
     *  @return 角速度
     *
     ****************************************************************/
    const Vector3& C_RigidBody::GetAngularVelocity() const
    {
        return upRigidBody_->getAngularVelocity();
    }


    /*************************************************************//**
     *
     *  @brief  摩擦係数を取得する
     *  @param  なし
     *  @return 摩擦係数
     *
     ****************************************************************/
    float C_RigidBody::GetFriction() const
    {
        return upRigidBody_->getFriction();
    }


    /*************************************************************//**
     *
     *  @brief  転がり摩擦係数を取得する
     *  @param  なし
     *  @return 転がり摩擦係数
     *
     ****************************************************************/
    float C_RigidBody::GetRollingFriction() const
    {
        return upRigidBody_->getRollingFriction();
    }


    /*************************************************************//**
     *
     *  @brief  反発係数を取得する
     *  @param  なし
     *  @return 反発係数
     *
     ****************************************************************/
    float C_RigidBody::GetRestitution() const
    {
        return upRigidBody_->getRestitution();
    }


    /*************************************************************//**
     *
     *  @brief  移動減衰を取得する
     *  @param  なし
     *  @return 移動減衰
     *
     ****************************************************************/
    float C_RigidBody::GetLinearDamping() const
    {
        return upRigidBody_->getLinearDamping();
    }


    /*************************************************************//**
     *
     *  @brief  回転減衰を取得する
     *  @param  なし
     *  @return 回転減衰
     *
     ****************************************************************/
    float C_RigidBody::GetAngularDamping() const
    {
        return upRigidBody_->getAngularDamping();
    }


    /*************************************************************//**
     *
     *  @brief  AABBを取得する
     *  @param  なし
     *  @return AABBの最小値と最大値
     *
     ****************************************************************/
    std::tuple<Vector3, Vector3> C_RigidBody::GetAabb() const
    {
        std::tuple<Vector3, Vector3> aabb;
        upRigidBody_->getAabb(std::get<0>(aabb), std::get<1>(aabb));

        return aabb;
    }


    /*************************************************************//**
     *
     *  @brief  アクティベーションステートを取得する
     *  @param  なし
     *  @return アクティベーションステート
     *
     ****************************************************************/
    int32_t C_RigidBody::GetActivationState() const
    {
        return upRigidBody_->getActivationState();
    }


    /*************************************************************//**
     *
     *  @brief  独自のインデックスを取得する
     *  @param  なし
     *  @return 独自のインデックス
     *
     ****************************************************************/
    int32_t C_RigidBody::GetUserIndex() const
    {
        return upRigidBody_->getUserIndex();
    }


    /*************************************************************//**
     *
     *  @brief  独自のポインタを取得する
     *  @param  なし
     *  @return 独自のポインタ
     *
     ****************************************************************/
    void* C_RigidBody::GetUserPointer() const
    {
        return upRigidBody_->getUserPointer();
    }


    /*************************************************************//**
     *
     *  @brief  トランスフォームを設定する
     *  @param  トランスフォーム
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::SetTransform(const Transform& rTransform)
    {
        upRigidBody_->setWorldTransform(rTransform);
    }


    /*************************************************************//**
     *
     *  @brief  重心のトランスフォームを設定する
     *  @param  重心のトランスフォーム
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::SetCenterOfGravityTransform(const Transform& rTransform)
    {
        upRigidBody_->setCenterOfMassTransform(rTransform);
    }


    /*************************************************************//**
     *
     *  @brief  線速度を設定する
     *  @param  線速度
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::SetLinearVelocity(const Vector3& rLinearVelocity)
    {
        upRigidBody_->setLinearVelocity(rLinearVelocity);
    }


    /*************************************************************//**
     *
     *  @brief  角速度を設定する
     *  @param  角速度
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::SetAngularVelocity(const Vector3& rAngularVelocity)
    {
        upRigidBody_->setAngularVelocity(rAngularVelocity);
    }


    /*************************************************************//**
     *
     *  @brief  摩擦係数を設定する
     *  @param  摩擦係数
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::SetFriction(float friction)
    {
        upRigidBody_->setFriction(friction);
    }


    /*************************************************************//**
     *
     *  @brief  転がり摩擦係数を設定する
     *  @param  転がり摩擦係数
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::SetRollingFriction(float rollingFriction)
    {
        upRigidBody_->setRollingFriction(rollingFriction);
    }


    /*************************************************************//**
     *
     *  @brief  反発係数を設定する
     *  @param  反発係数
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::SetRestitution(float restitution)
    {
        upRigidBody_->setRestitution(restitution);
    }


    /*************************************************************//**
     *
     *  @brief  移動減衰を設定する
     *  @param  移動減衰
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::SetLinearDamping(float linearDamping)
    {
        upRigidBody_->setDamping(linearDamping, GetAngularDamping());
    }


    /*************************************************************//**
     *
     *  @brief  回転減衰を設定する
     *  @param  回転減衰
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::SetAngularDamping(float angularDamping)
    {
        upRigidBody_->setDamping(GetLinearDamping(), angularDamping);
    }


    /*************************************************************//**
     *
     *  @brief  アクティベーションステートを設定する
     *  @param  アクティベーションステート
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::SetActivationState(int32_t state)
    {
        upRigidBody_->setActivationState(state);
    }


    /*************************************************************//**
     *
     *  @brief  独自のIDを設定する
     *  @param  独自のID
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::SetUserIndex(int32_t index)
    {
        upRigidBody_->setUserIndex(index);
    }


    /*************************************************************//**
     *
     *  @brief  独自のポインタを設定する
     *  @param  独自のポインタ
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBody::SetUserPointer(void* pPointer)
    {
        upRigidBody_->setUserPointer(pPointer);
    }
}