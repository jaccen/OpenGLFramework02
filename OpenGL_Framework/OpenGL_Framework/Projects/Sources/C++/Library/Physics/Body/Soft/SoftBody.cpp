/* �w�b�_�t�@�C�� */
#include "SoftBody.h"
#include "../Rigid/RigidBody.h"
#include "../../../Debug/Helper/DebugHelper.h"
#include "Joint/LinearJoint.h"
#include "Joint/AngularJoint.h"
#include <BulletSoftBody/btSoftBodyHelpers.h>


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
     *  @param  �\�t�g�{�f�B���
     *  @param  ���_���W
     *  @param  �C���f�b�N�X
     *  @param  �O�p�`�̐�
     *  @param  �S�̂̎���
     *  @param  �g�嗦
     *  @param  �R���t�B�O
     *  @param  �}�e���A��
     *  @param  �̐ς�ۂ����f����t���O
     *  @param  �����t���[�����L�������f����t���O
     *  @param  �`���ۂ����f����t���O
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

        // ���
        upSoftBody_(btSoftBodyHelpers::CreateFromTriMesh(*pSoftBodyInfo,
                                                         reinterpret_cast<btScalar*>(vertexPositions),
                                                         indices,
                                                         static_cast<int32_t>(triangleCount)))

    {
        // �R���t�B�O��ݒ�
        SetConfig(rConfig);

        // �傫����ύX
        upSoftBody_->scale(rScale);

        // �̐ϕۑ��Ɠ����t���[����ݒ�
        upSoftBody_->setPose(keepVolumeFlag, innerFlameFlag);

        // �}�e���A����ݒ肵�A�߂��̒��_���m���S��
        if (rMaterial.vertexDistance_ > 0)
        {
            SetMaterial(rMaterial);
            upSoftBody_->generateBendingConstraints(rMaterial.vertexDistance_, upSoftBody_->m_materials[0]);
        }

        // �\�t�g�{�f�B���m�̏Փ˂�L����
        EnableSoftBodyCollision();

        // �����_���ɒ��_�Ԃ��S�����A�S�̂̌`���ۂ�
        if (keepShapeFlag == true) upSoftBody_->randomizeConstraints();

        // �g�����X�t�H�[����ݒ�
        upSoftBody_->setWorldTransform(rTransform);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SoftBody::~C_SoftBody()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �A�N�e�B�u��Ԃ�L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::EnableActive(bool validFlag)
    {
        upSoftBody_->activate(validFlag);
    }


    /*************************************************************//**
     *
     *  @brief  �Փˉ�����L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
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
     *  @brief  ��̂Ƃ̏Փ˔����L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
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
     *  @brief  �Փ˃R�[���o�b�N��L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
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
     *  @brief  �͂�������
     *  @param  ��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::ApplyForce(const Vector3& rForce)
    {
        upSoftBody_->addForce(rForce);
    }


    /*************************************************************//**
     *
     *  @brief  ���_�ɕ��̗͂�������
     *  @param  ���̗�
     *  @param  ���_�C���f�b�N�X
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::ApplyAeroForceToVertex(const Vector3& rAeroForce, int32_t vertexIndex)
    {
        upSoftBody_->addAeroForceToNode(rAeroForce, vertexIndex);
    }


    /*************************************************************//**
     *
     *  @brief  �ʂɕ��̗͂�������
     *  @param  ���̗�
     *  @param  �ʂ̃C���f�b�N�X
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::ApplyAeroForceToFace(const Vector3& rAeroForce, int32_t faceIndex)
    {
        upSoftBody_->addAeroForceToFace(rAeroForce, faceIndex);
    }


    /*************************************************************//**
     *
     *  @brief  �͂�������
     *  @param  ��
     *  @param  ���_�C���f�b�N�X
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::ApplyForce(const Vector3& rForce, int32_t vertexIndex)
    {
        upSoftBody_->addForce(rForce, vertexIndex);
    }


    /*************************************************************//**
     *
     *  @brief  ���W��������
     *  @param  ���W
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::AddPosition(const Vector3& rPosition)
    {
        upSoftBody_->translate(rPosition);
    }


    /*************************************************************//**
     *
     *  @brief  ���x��������
     *  @param  ���x
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::AddVelocity(const Vector3& rVelocity)
    {
        upSoftBody_->addVelocity(rVelocity);
    }


    /*************************************************************//**
     *
     *  @brief  ���x��������
     *  @param  ���x
     *  @param  ���_�C���f�b�N�X
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::AddVelocity(const Vector3& rVelocity, int32_t vertexIndex)
    {
        upSoftBody_->addVelocity(rVelocity, vertexIndex);
    }


    /*************************************************************//**
     *
     *  @brief  �A���J�[��ǉ�����
     *  @param  ���_�C���f�b�N�X
     *  @param  ����
     *  @param  �����N�̃{�f�B�Ԃ̏Փ˂��s�������f����t���O
     *  @param  �A���J�[���x
     *  @return �Ȃ�
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
     *  @brief  �����ڍ���ǉ�����
     *  @param  �����ڍ�
     *  @param  ������̃\�t�g�{�f�B
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::AppendLinearJoint(C_LinearJoint* pLinearJoint, C_SoftBody* pAnother)
    {
        upSoftBody_->appendLinearJoint(*pLinearJoint->GetLinearJointSpec(), pAnother->GetSoftBody());
    }


    /*************************************************************//**
     *
     *  @brief  �p�ڍ���ǉ�����
     *  @param  �p�ڍ�
     *  @param  ������̃\�t�g�{�f�B
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::AppendAngularJoint(C_AngularJoint* pAngularJoint, C_SoftBody* pAnother)
    {
        upSoftBody_->appendAngularJoint(*pAngularJoint->GetAngularJointSpec(), pAnother->GetSoftBody());
    }


    /*************************************************************//**
     *
     *  @brief  ��̂��擾����
     *  @param  �Ȃ�
     *  @return ���
     *
     ****************************************************************/
    btSoftBody* C_SoftBody::GetSoftBody() const
    {
        return upSoftBody_.get();
    }


    /*************************************************************//**
     *
     *  @brief  �g�����X�t�H�[�����擾����
     *  @param  �Ȃ�
     *  @return �g�����X�t�H�[��
     *
     ****************************************************************/
    const Transform& C_SoftBody::GetTransform() const
    {
        return upSoftBody_->getWorldTransform();
    }


    /*************************************************************//**
     *
     *  @brief  ���ʂ��擾����
     *  @param  �Ȃ�
     *  @return ����
     *
     ****************************************************************/
    float C_SoftBody::GetMass(int32_t vertexIndex) const
    {
        return upSoftBody_->getMass(vertexIndex);
    }


    /*************************************************************//**
     *
     *  @brief  �S�̂̎��ʂ��擾����
     *  @param  �Ȃ�
     *  @return �S�̂̎���
     *
     ****************************************************************/
    float C_SoftBody::GetTotalMass() const
    {
        return upSoftBody_->getTotalMass();
    }


    /*************************************************************//**
     *
     *  @brief  ���C�W�����擾����
     *  @param  �Ȃ�
     *  @return ���C�W��
     *
     ****************************************************************/
    float C_SoftBody::GetFriction() const
    {
        return upSoftBody_->getFriction();
    }


    /*************************************************************//**
     *
     *  @brief  �]���薀�C�W�����擾����
     *  @param  �Ȃ�
     *  @return �]���薀�C�W��
     *
     ****************************************************************/
    float C_SoftBody::GetRollingFriction() const
    {
        return upSoftBody_->getRollingFriction();
    }


    /*************************************************************//**
     *
     *  @brief  �����W�����擾����
     *  @param  �Ȃ�
     *  @return �����W��
     *
     ****************************************************************/
    float C_SoftBody::GetRestitution() const
    {
        return upSoftBody_->getRestitution();
    }


    /*************************************************************//**
     *
     *  @brief  AABB���擾����
     *  @param  �Ȃ�
     *  @return AABB�̍ŏ��l�ƍő�l
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
     *  @brief  �A�N�e�B�x�[�V�����X�e�[�g���擾����
     *  @param  �Ȃ�
     *  @return �A�N�e�B�x�[�V�����X�e�[�g
     *
     ****************************************************************/
    int32_t C_SoftBody::GetActivationState() const
    {
        return upSoftBody_->getActivationState();
    }


    /*************************************************************//**
     *
     *  @brief  �Ǝ��̃C���f�b�N�X���擾����
     *  @param  �Ȃ�
     *  @return �Ǝ��̃C���f�b�N�X
     *
     ****************************************************************/
    int32_t C_SoftBody::GetUserIndex() const
    {
        return upSoftBody_->getUserIndex();
    }


    /*************************************************************//**
     *
     *  @brief  �Ǝ��̃|�C���^���擾����
     *  @param  �Ȃ�
     *  @return �Ǝ��̃|�C���^
     *
     ****************************************************************/
    void* C_SoftBody::GetUserPointer() const
    {
        return upSoftBody_->getUserPointer();
    }


    /*************************************************************//**
     *
     *  @brief  �R���t�B�O��ݒ肷��
     *  @param  �R���t�B�O
     *  @return �Ȃ�
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
     *  @brief  �}�e���A����ݒ肷��
     *  @param  �}�e���A��
     *  @return �Ȃ�
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
     *  @brief  �g�����X�t�H�[����ݒ肷��
     *  @param  �g�����X�t�H�[��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::SetTransform(const Transform& rTransform)
    {
        upSoftBody_->setWorldTransform(rTransform);
    }


    /*************************************************************//**
     *
     *  @brief  ���ʂ�ݒ肷��
     *  @param  ����
     *  @param  ���_�C���f�b�N�X
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::SetMass(float mass, int32_t vertexIndex)
    {
        upSoftBody_->setMass(vertexIndex, mass);
    }


    /*************************************************************//**
     *
     *  @brief  �S�̂̎��ʂ�ݒ肷��
     *  @param  �S�̂̎���
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::SetTotalMass(float totalMass)
    {
        upSoftBody_->setTotalMass(totalMass);
    }


    /*************************************************************//**
     *
     *  @brief  �S�̖̂��x��ݒ肷��
     *  @param  �S�̖̂��x
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::SetTotalDensity(float totalDensity)
    {
        upSoftBody_->setTotalDensity(totalDensity);
    }


    /*************************************************************//**
     *
     *  @brief  ���C�W����ݒ肷��
     *  @param  ���C�W��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::SetFriction(float friction)
    {
        upSoftBody_->setFriction(friction);
    }


    /*************************************************************//**
     *
     *  @brief  �]���薀�C�W����ݒ肷��
     *  @param  �]���薀�C�W��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::SetRollingFriction(float rollingFriction)
    {
        upSoftBody_->setRollingFriction(rollingFriction);
    }


    /*************************************************************//**
     *
     *  @brief  �����W����ݒ肷��
     *  @param  �����W��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::SetRestitution(float restitution)
    {
        upSoftBody_->setRestitution(restitution);
    }


    /*************************************************************//**
     *
     *  @brief  �A�N�e�B�x�[�V�����X�e�[�g��ݒ肷��
     *  @param  �A�N�e�B�x�[�V�����X�e�[�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::SetActivationState(int32_t state)
    {
        upSoftBody_->setActivationState(state);
    }


    /*************************************************************//**
     *
     *  @brief  �Ǝ��̃C���f�b�N�X��ݒ肷��
     *  @param  �Ǝ��̃C���f�b�N�X
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::SetUserIndex(int32_t index)
    {
        upSoftBody_->setUserIndex(index);
    }


    /*************************************************************//**
     *
     *  @brief  �Ǝ��̃|�C���^��ݒ肷��
     *  @param  �Ǝ��̃|�C���^
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SoftBody::SetUserPointer(void * pPointer)
    {
        upSoftBody_->setUserPointer(pPointer);
    }


    /*************************************************************//**
     *
     *  @brief  �ȉ~�̌`��̓�̂��쐬����
     *  @param  �\�t�g�{�f�B���
     *  @param  ���S���W
     *  @param  ���a
     *  @param  ���_��
     *  @param  �S�̂̎���
     *  @param  �g�嗦
     *  @param  �R���t�B�O
     *  @param  �}�e���A��
     *  @param  �̐ς�ۂ����f����t���O
     *  @param  �����t���[�����L�������f����t���O
     *  @param  �`���ۂ����f����t���O
     *  @return �ȉ~�̌`��̓��
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
        // �ȉ~�`��̓�̂��쐬
        C_SoftBody* pEllipsoidSoftBody = newEx C_SoftBody;
        auto& rpSoftBody = pEllipsoidSoftBody->upSoftBody_;

        rpSoftBody.reset(btSoftBodyHelpers::CreateEllipsoid(*pSoftBodyInfo,
                                                            rCenterPoint,
                                                            rRadius,
                                                            vertexCount));

        // �R���t�B�O��ݒ�
        pEllipsoidSoftBody->SetConfig(rConfig);

        // �傫����ύX
        rpSoftBody->scale(rScale);

        // �̐ϕۑ��Ɠ����t���[����ݒ�
        rpSoftBody->setPose(keepVolumeFlag, innerFlameFlag);

        // �}�e���A����ݒ肵�A�߂��̒��_���m���S��
        if (rMaterial.vertexDistance_ > 0)
        {
            pEllipsoidSoftBody->SetMaterial(rMaterial);
            rpSoftBody->generateBendingConstraints(rMaterial.vertexDistance_, rpSoftBody->m_materials[0]);
        }

        // �\�t�g�{�f�B���m�̏Փ˂�L����
        pEllipsoidSoftBody->EnableSoftBodyCollision();

        // �����_���ɒ��_�Ԃ��S�����A�S�̂̌`���ۂ�
        if (keepShapeFlag == true) rpSoftBody->randomizeConstraints();

        return pEllipsoidSoftBody;
    }
}