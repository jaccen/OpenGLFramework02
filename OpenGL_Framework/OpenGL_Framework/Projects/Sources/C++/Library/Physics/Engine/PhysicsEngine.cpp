/* �w�b�_�t�@�C�� */
#include "PhysicsEngineImpl.h"


/* �O���Œ�`����Ă���R�[���o�b�N�֐� */
extern ContactProcessedCallback gContactProcessedCallback;


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
     *  @param  ���[���h�̍ŏ��l
     *  @param  ���[���h�̍ő�l
     *  @param  �ő�I�u�W�F�N�g��
     *
     ****************************************************************/
    C_PhysicsEngine::C_PhysicsEngine(const Vector3& rWorldMin,
        const Vector3& rWorldMax,
        uint16_t maxObjectCount) :

        // �������
        upImpl_(std::make_unique<C_PhysicsEngineImpl>(rWorldMin,
        rWorldMax,
        maxObjectCount))

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PhysicsEngine::~C_PhysicsEngine()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �����G���W���̏������������s��
     *  @param  �d��
     *  @param  ��C���x
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::Initialize(const Vector3& rGravity,
        float airDensity)
    {
        upImpl_->Initialize(rGravity, airDensity);
    }


    /*************************************************************//**
     *
     *  @brief  �����G���W���̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::Update()
    {
        upImpl_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  �����G���W���̏I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::Finalize()
    {
        upImpl_->Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  ���̂�ǉ�����
     *  @param  ����
     *  @param  �Փ˕��̎��
     *  @param  �Փ˂̃}�X�N
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::AddRigidBody(C_RigidBody* pRigidBody,
        int16_t collisionObjectType,
        int16_t collisionMask)
    {
        if (collisionObjectType == -1 || collisionMask == -1)
        {
            upImpl_->GetWorld()->addRigidBody(pRigidBody->GetRigidBody());
        }
        else
        {
            upImpl_->GetWorld()->addRigidBody(pRigidBody->GetRigidBody(), collisionObjectType, collisionMask);
        }
    }


    /*************************************************************//**
     *
     *  @brief  ��̂�ǉ�����
     *  @param  ���
     *  @param  �Փ˕��̎��
     *  @param  �Փ˂̃}�X�N
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::AddSoftBody(C_SoftBody* pSoftBody,
        int16_t collisionObjectType,
        int16_t collisionMask)
    {
        upImpl_->GetWorld()->addSoftBody(pSoftBody->GetSoftBody(), collisionObjectType, collisionMask);
    }


    /*************************************************************//**
     *
     *  @brief  ���̂���������
     *  @param  ����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::RemoveRigidBody(C_RigidBody* pRigidBody)
    {
        upImpl_->GetWorld()->removeRigidBody(pRigidBody->GetRigidBody());
    }


    /*************************************************************//**
     *
     *  @brief  ��̂���������
     *  @param  ���
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::RemoveSoftBody(C_SoftBody* pSoftBody)
    {
        upImpl_->GetWorld()->removeSoftBody(pSoftBody->GetSoftBody());
    }


    /*************************************************************//**
     *
     *  @brief  �d�͂��擾����
     *  @param  �Ȃ�
     *  @return �d��
     *
     ****************************************************************/
    const Vector3& C_PhysicsEngine::GetGravity() const
    {
        return upImpl_->GetWorld()->getGravity();
    }


    /*************************************************************//**
     *
     *  @brief  �\�t�g�{�f�B�����擾����
     *  @param  �Ȃ�
     *  @return �\�t�g�{�f�B���
     *
     ****************************************************************/
    SoftBodyInfo* C_PhysicsEngine::GetSoftBodyInfo() const
    {
        return upImpl_->GetSoftBodyInfo();
    }


    /*************************************************************//**
     *
     *  @brief  �d�͂�ݒ肷��
     *  @param  �d��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::SetGravity(const Vector3& rGravity)
    {
        upImpl_->GetWorld()->setGravity(rGravity);
    }


    /*************************************************************//**
     *
     *  @brief  �Փ˃R�[���o�b�N�֐���ݒ肷��
     *  @param  �Փ˃R�[���o�b�N�֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::SetCollisionCallbackFunction(CollisionCallbackFunction pCollisionCallbackFunction)
    {
        gContactProcessedCallback = pCollisionCallbackFunction;
    }


    /*************************************************************//**
     *
     *  @brief  �V�~�����[�V�����̃T�u�X�e�b�v�R�[���o�b�N�֐���ݒ肷��
     *  @param  �V�~�����[�V�����̃T�u�X�e�b�v�R�[���o�b�N�֐�
     *  @param  ���[���h�̓Ǝ��̏��
     *  @param  �T�u�X�e�b�v�̑O�ɌĂԃR�[���o�b�N�֐��Ƃ��ēo�^����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::SetSimulationSubstepCallbackFunction(SimulationSubstepCallbackFunction pSimulationSubstepCallbackFunction,
        void* pWorldUserInfo,
        bool previousSubstepCallbackFlag)
    {
        upImpl_->GetWorld()->setInternalTickCallback(pSimulationSubstepCallbackFunction,
            pWorldUserInfo,
            previousSubstepCallbackFlag);
    }


    /*************************************************************//**
     *
     *  @brief  1�t���[���̃V�~�����[�V�������Ԃ�ݒ肷��
     *  @param  1�t���[���̃V�~�����[�V��������
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::SetFrameSimulationTime(float frameSimulationTime)
    {
        upImpl_->SetFrameSimulationTime(frameSimulationTime);
    }


    /*************************************************************//**
     *
     *  @brief  �ő�T�u�X�e�b�v����ݒ肷��
     *  @param  �ő�T�u�X�e�b�v��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::SetMaxSubStepCount(int32_t maxSubStepCount)
    {
        upImpl_->SetMaxSubStepCount(maxSubStepCount);
    }


    /*************************************************************//**
     *
     *  @brief  �A�N�e�B�u��Ԃ�L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::EnableActive(bool validFlag)
    {

    }
}