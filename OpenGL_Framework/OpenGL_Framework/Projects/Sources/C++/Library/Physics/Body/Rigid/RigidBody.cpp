/* �w�b�_�t�@�C�� */
#include "RigidBody.h"


//-------------------------------------------------------------
///
/// @brief �t�B�W�b�N�X
/// @brief �����֘A�̖��O���
///
//-------------------------------------------------------------
namespace Physics
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Փˌ`��
     *  @param  �g�����X�t�H�[��
     *  @param  ����( 0�̏ꍇ�͐ÓI���̂ƂȂ� )
     *  @param  �������[�����g
     *
     ****************************************************************/
    C_RigidBody::C_RigidBody(C_CollisionShape* pCollisionShape,
                             const Transform& rTransform,
                             float mass,
                             const Vector3& rInertia)
    {
        // ���[�V�����X�e�[�g���쐬���A���̂��쐬����
        upMotionState_ = std::make_unique<btDefaultMotionState>(rTransform);

        upRigidBody_ = std::make_unique<btRigidBody>(mass, 
                                                     upMotionState_.get(),
                                                     pCollisionShape->GetCollisionShape(),
                                                     rInertia);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_RigidBody::~C_RigidBody()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �A�N�e�B�u��Ԃ�L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::EnableActive(bool validFlag)
    {
        upRigidBody_->activate(validFlag);
    }


    /*************************************************************//**
     *
     *  @brief  �Փˉ�����L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
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
     *  @brief  �Փ˃R�[���o�b�N��L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
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
     *  @brief  ���W�̌Œ��L��������
     *  @param  X�������Œ肷��t���O
     *  @param  Y�������Œ肷��t���O
     *  @param  Z�������Œ肷��t���O
     *  @return �Ȃ�
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
     *  @brief  ��]�̌Œ��L��������
     *  @param  X�������Œ肷��t���O
     *  @param  Y�������Œ肷��t���O
     *  @param  Z�������Œ肷��t���O
     *  @return �Ȃ�
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
     *  @brief  �͂�������
     *  @param  ��
     *  @param  ���S����̃I�t�Z�b�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::ApplyForce(const Vector3& rForce,          
                                 const Vector3& rOffsetFromCenter)
    {
        upRigidBody_->applyForce(rForce, rOffsetFromCenter);
    }


    /*************************************************************//**
     *
     *  @brief  ���͂�������
     *  @param  ����
     *  @param  ���S����̃I�t�Z�b�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::ApplyImpulse(const Vector3& rImpulse,          
                                   const Vector3& rOffsetFromCenter)
    {
        upRigidBody_->applyImpulse(rImpulse, rOffsetFromCenter);
    }


    /*************************************************************//**
     *
     *  @brief  ���W��������
     *  @param  ���W
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::AddPosition(const Vector3& rPosition)
    {
        upRigidBody_->translate(rPosition);
    }


    /*************************************************************//**
     *
     *  @brief  ���x�����Z�b�g����
     *  @param  ���x
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::ResetVelocity()
    {
        SetLinearVelocity();
        SetAngularVelocity();
    }


    /*************************************************************//**
     *
     *  @brief  ���̂��擾����
     *  @param  �Ȃ�
     *  @return ����
     *
     ****************************************************************/
    btRigidBody* C_RigidBody::GetRigidBody() const
    {
        return upRigidBody_.get();
    }


    /*************************************************************//**
     *
     *  @brief  �Փˌ`����擾����
     *  @param  �Ȃ�
     *  @return �Փˌ`��
     *
     ****************************************************************/
    C_CollisionShape* C_RigidBody::GetCollisionShape() const
    {
        return upCollisionShape_.get();
    }


    /*************************************************************//**
     *
     *  @brief  �g�����X�t�H�[�����擾����
     *  @param  �Ȃ�
     *  @return �g�����X�t�H�[��
     *
     ****************************************************************/
    const Transform& C_RigidBody::GetTransform() const
    {
        return upRigidBody_->getWorldTransform();
    }


    /*************************************************************//**
     *
     *  @brief  �d�S�̃g�����X�t�H�[�����擾����
     *  @param  �Ȃ�
     *  @return �d�S�̃g�����X�t�H�[��
     *
     ****************************************************************/
    const Transform& C_RigidBody::GetCenterOfGravityTransform() const
    {
        return upRigidBody_->getCenterOfMassTransform();
    }


    /*************************************************************//**
     *
     *  @brief  �����x���擾����
     *  @param  �Ȃ�
     *  @return �����x
     *
     ****************************************************************/
    const Vector3& C_RigidBody::GetLinearVelocity() const
    {
        return upRigidBody_->getLinearVelocity();
    }


    /*************************************************************//**
     *
     *  @brief  �p���x���擾����
     *  @param  �Ȃ�
     *  @return �p���x
     *
     ****************************************************************/
    const Vector3& C_RigidBody::GetAngularVelocity() const
    {
        return upRigidBody_->getAngularVelocity();
    }


    /*************************************************************//**
     *
     *  @brief  ���C�W�����擾����
     *  @param  �Ȃ�
     *  @return ���C�W��
     *
     ****************************************************************/
    float C_RigidBody::GetFriction() const
    {
        return upRigidBody_->getFriction();
    }


    /*************************************************************//**
     *
     *  @brief  �]���薀�C�W�����擾����
     *  @param  �Ȃ�
     *  @return �]���薀�C�W��
     *
     ****************************************************************/
    float C_RigidBody::GetRollingFriction() const
    {
        return upRigidBody_->getRollingFriction();
    }


    /*************************************************************//**
     *
     *  @brief  �����W�����擾����
     *  @param  �Ȃ�
     *  @return �����W��
     *
     ****************************************************************/
    float C_RigidBody::GetRestitution() const
    {
        return upRigidBody_->getRestitution();
    }


    /*************************************************************//**
     *
     *  @brief  �ړ��������擾����
     *  @param  �Ȃ�
     *  @return �ړ�����
     *
     ****************************************************************/
    float C_RigidBody::GetLinearDamping() const
    {
        return upRigidBody_->getLinearDamping();
    }


    /*************************************************************//**
     *
     *  @brief  ��]�������擾����
     *  @param  �Ȃ�
     *  @return ��]����
     *
     ****************************************************************/
    float C_RigidBody::GetAngularDamping() const
    {
        return upRigidBody_->getAngularDamping();
    }


    /*************************************************************//**
     *
     *  @brief  AABB���擾����
     *  @param  �Ȃ�
     *  @return AABB�̍ŏ��l�ƍő�l
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
     *  @brief  �A�N�e�B�x�[�V�����X�e�[�g���擾����
     *  @param  �Ȃ�
     *  @return �A�N�e�B�x�[�V�����X�e�[�g
     *
     ****************************************************************/
    int32_t C_RigidBody::GetActivationState() const
    {
        return upRigidBody_->getActivationState();
    }


    /*************************************************************//**
     *
     *  @brief  �Ǝ��̃C���f�b�N�X���擾����
     *  @param  �Ȃ�
     *  @return �Ǝ��̃C���f�b�N�X
     *
     ****************************************************************/
    int32_t C_RigidBody::GetUserIndex() const
    {
        return upRigidBody_->getUserIndex();
    }


    /*************************************************************//**
     *
     *  @brief  �Ǝ��̃|�C���^���擾����
     *  @param  �Ȃ�
     *  @return �Ǝ��̃|�C���^
     *
     ****************************************************************/
    void* C_RigidBody::GetUserPointer() const
    {
        return upRigidBody_->getUserPointer();
    }


    /*************************************************************//**
     *
     *  @brief  �g�����X�t�H�[����ݒ肷��
     *  @param  �g�����X�t�H�[��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::SetTransform(const Transform& rTransform)
    {
        upRigidBody_->setWorldTransform(rTransform);
    }


    /*************************************************************//**
     *
     *  @brief  �d�S�̃g�����X�t�H�[����ݒ肷��
     *  @param  �d�S�̃g�����X�t�H�[��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::SetCenterOfGravityTransform(const Transform& rTransform)
    {
        upRigidBody_->setCenterOfMassTransform(rTransform);
    }


    /*************************************************************//**
     *
     *  @brief  �����x��ݒ肷��
     *  @param  �����x
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::SetLinearVelocity(const Vector3& rLinearVelocity)
    {
        upRigidBody_->setLinearVelocity(rLinearVelocity);
    }


    /*************************************************************//**
     *
     *  @brief  �p���x��ݒ肷��
     *  @param  �p���x
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::SetAngularVelocity(const Vector3& rAngularVelocity)
    {
        upRigidBody_->setAngularVelocity(rAngularVelocity);
    }


    /*************************************************************//**
     *
     *  @brief  ���C�W����ݒ肷��
     *  @param  ���C�W��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::SetFriction(float friction)
    {
        upRigidBody_->setFriction(friction);
    }


    /*************************************************************//**
     *
     *  @brief  �]���薀�C�W����ݒ肷��
     *  @param  �]���薀�C�W��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::SetRollingFriction(float rollingFriction)
    {
        upRigidBody_->setRollingFriction(rollingFriction);
    }


    /*************************************************************//**
     *
     *  @brief  �����W����ݒ肷��
     *  @param  �����W��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::SetRestitution(float restitution)
    {
        upRigidBody_->setRestitution(restitution);
    }


    /*************************************************************//**
     *
     *  @brief  �ړ�������ݒ肷��
     *  @param  �ړ�����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::SetLinearDamping(float linearDamping)
    {
        upRigidBody_->setDamping(linearDamping, GetAngularDamping());
    }


    /*************************************************************//**
     *
     *  @brief  ��]������ݒ肷��
     *  @param  ��]����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::SetAngularDamping(float angularDamping)
    {
        upRigidBody_->setDamping(GetLinearDamping(), angularDamping);
    }


    /*************************************************************//**
     *
     *  @brief  �A�N�e�B�x�[�V�����X�e�[�g��ݒ肷��
     *  @param  �A�N�e�B�x�[�V�����X�e�[�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::SetActivationState(int32_t state)
    {
        upRigidBody_->setActivationState(state);
    }


    /*************************************************************//**
     *
     *  @brief  �Ǝ���ID��ݒ肷��
     *  @param  �Ǝ���ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::SetUserIndex(int32_t index)
    {
        upRigidBody_->setUserIndex(index);
    }


    /*************************************************************//**
     *
     *  @brief  �Ǝ��̃|�C���^��ݒ肷��
     *  @param  �Ǝ��̃|�C���^
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RigidBody::SetUserPointer(void* pPointer)
    {
        upRigidBody_->setUserPointer(pPointer);
    }
}