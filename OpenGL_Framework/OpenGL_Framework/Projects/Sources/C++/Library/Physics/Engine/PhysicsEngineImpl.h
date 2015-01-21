/* �w�b�_�t�@�C�� */
#include "PhysicsEngine.h"
#include "../Body/Rigid/RigidBody.h"
#include "../Body/Soft/SoftBody.h"
#include <BulletSoftBody/btSoftBodyHelpers.h>
#include <BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>


//-------------------------------------------------------------
///
/// @brief �t�B�W�b�N�X
/// @brief �����֘A�̖��O���
///
//-------------------------------------------------------------
namespace Physics
{
    //-------------------------------------------------------------
    //!
    //! @brief �t�B�W�b�N�X�G���W���C���v�������g
    //! @brief �t�B�W�b�N�X�G���W���̃v���C�x�[�g���̎���
    //!
    //-------------------------------------------------------------
    class C_PhysicsEngine::C_PhysicsEngineImpl
    {
    public:
        C_PhysicsEngineImpl(const Vector3& rWorldMin,                                       // �R���X�g���N�^
                            const Vector3& rWorldMax,
                            uint16_t maxObjectCount);
        ~C_PhysicsEngineImpl();                                                             // �f�X�g���N�^
        void Initialize(const Vector3& rGravity,                                            // ����������
                        float airDensity);
        void Update();                                                                      // �X�V����
        void Finalize();                                                                    // �I������
        btSoftRigidDynamicsWorld* GetWorld() const;                                         // ���[���h���擾
        SoftBodyInfo* GetSoftBodyInfo() const;                                              // �\�t�g�{�f�B�����擾
        void SetFrameSimulationTime(float frameSimulationTime);                             // 1�t���[���̃V�~�����[�V�������Ԃ�ݒ�
        void SetMaxSubStepCount(int32_t maxSubStepCount);                                   // �ő�T�u�X�e�b�v����ݒ�
        void EnableActive(bool validFlag);                                                  // �A�N�e�B�u��Ԃ�L����
    private:
        float frameSimulationTime_ = 1.0f / 60.0f;                                          ///< @brief 1�t�[�����̃V�~�����[�V��������
        int32_t maxSubStepCount_ = 5;                                                       ///< @brief �ő�T�u�X�e�b�v��
        bool activeFlag_ = true;                                                            ///< @brief �A�N�e�B�u��Ԃ𔻒f����t���O
        std::unique_ptr<btDefaultCollisionConfiguration> upConfig_;                         ///< @brief �R���t�B�O
        std::unique_ptr<btCollisionDispatcher> upDispatcher_;                               ///< @brief �f�B�X�p�b�`���[
        std::unique_ptr<btBroadphaseInterface> upBroadphase_;                               ///< @brief �u���[�h�t�F�[�Y
        std::unique_ptr<btConstraintSolver> upSolver_;                                      ///< @brief �\���o
        std::unique_ptr<btSoftRigidDynamicsWorld> upWorld_;                                 ///< @brief ���[���h
        std::unique_ptr<SoftBodyInfo, C_SoftBodyInfoDeleter> upSoftBodyInfo_;               ///< @brief �\�t�g�{�f�B�[���
    };


    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  ���[���h��X���W�̍ŏ��l
     *  @param  ���[���h��Y���W�̍ŏ��l
     *  @param  ���[���h��Z���W�̍ŏ��l
     *  @param  ���[���h��X���W�̍ő�l
     *  @param  ���[���h��Y���W�̍ő�l
     *  @param  ���[���h��Z���W�̍ő�l
     *  @param  �ő�I�u�W�F�N�g��
     *
     ****************************************************************/
    C_PhysicsEngine::C_PhysicsEngineImpl::C_PhysicsEngineImpl(const Vector3& rWorldMin,        
                                                              const Vector3& rWorldMax, 
                                                              uint16_t maxObjectCount) :

        // �R���t�B�O
        upConfig_(std::make_unique<btSoftBodyRigidBodyCollisionConfiguration>()),

        // �\���o
        upSolver_(std::make_unique<btSequentialImpulseConstraintSolver>())

    {
        // �f�B�X�p�b�`���[�𐶐�
        upDispatcher_ = std::make_unique<btCollisionDispatcher>(upConfig_.get());

        // �u���[�h�t�F�[�Y�𐶐�
        upBroadphase_ = std::make_unique<btAxisSweep3>(rWorldMin, rWorldMax, maxObjectCount);
        // �� �󋵂ɂ���ău���[�h�t�F�[�Y���g��������( ���I�ȃI�u�W�F�N�g������ : btAxisSweep3 / ���Ȃ� : btDbvtBroadphase )
        // std::make_unique<btDbvtBroadphase>();

        // ���[���h���쐬
        upWorld_ = std::make_unique<btSoftRigidDynamicsWorld>(upDispatcher_.get(), 
                                                              upBroadphase_.get(),
                                                              upSolver_.get(),
                                                              upConfig_.get(), 
                                                              nullptr);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PhysicsEngine::C_PhysicsEngineImpl::~C_PhysicsEngineImpl()
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
    void C_PhysicsEngine::C_PhysicsEngineImpl::Initialize(const Vector3& rGravity,
                                                          float airDensity)
    {
        // �\�t�g�{�f�B����ݒ�
        upSoftBodyInfo_.reset(Common::C_CommonHelper::s_AlignedNew<SoftBodyInfo>());
        upSoftBodyInfo_->m_dispatcher = upDispatcher_.get();
        upSoftBodyInfo_->m_broadphase = upBroadphase_.get();
        upSoftBodyInfo_->m_gravity = rGravity;
        upSoftBodyInfo_->air_density = airDensity;
        upSoftBodyInfo_->water_density = 0.0f;
        upSoftBodyInfo_->water_offset = 0.0f;
        upSoftBodyInfo_->water_normal = btVector3(0.0f, 0.0f, 0.0f);
        upSoftBodyInfo_->m_sparsesdf.Initialize();

        // ���[���h�̐ݒ�
        upWorld_->setDebugDrawer(nullptr);
        upWorld_->setGravity(rGravity);
    }


    /*************************************************************//**
     *
     *  @brief  �����G���W���̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::C_PhysicsEngineImpl::Update()
    {
        if (activeFlag_ == true)
        {
            // �V�~�����[�V�������s��
            upWorld_->stepSimulation(frameSimulationTime_, maxSubStepCount_, frameSimulationTime_ / static_cast<float>(maxSubStepCount_));

            // �\�t�g�{�f�B���̃Z�����K�[�x�W�R���N�V��������
            upSoftBodyInfo_->m_sparsesdf.GarbageCollect();
        }
    }


    /*************************************************************//**
     *
     *  @brief  �����G���W���̏I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::C_PhysicsEngineImpl::Finalize()
    {
        // �Z���̃����������
        upSoftBodyInfo_->m_sparsesdf.Reset();
    }


    /*************************************************************//**
     *
     *  @brief  ���[���h���擾����
     *  @param  �Ȃ�
     *  @return ���[���h
     *
     ****************************************************************/
    btSoftRigidDynamicsWorld* C_PhysicsEngine::C_PhysicsEngineImpl::GetWorld() const
    {
        return upWorld_.get();
    }


    /*************************************************************//**
     *
     *  @brief  �\�t�g�{�f�B�����擾����
     *  @param  �Ȃ�
     *  @return �\�t�g�{�f�B���
     *
     ****************************************************************/
    SoftBodyInfo* C_PhysicsEngine::C_PhysicsEngineImpl::GetSoftBodyInfo() const
    {
        return upSoftBodyInfo_.get();
    }


    /*************************************************************//**
     *
     *  @brief  1�t���[���̃V�~�����[�V�������Ԃ�ݒ肷��
     *  @param  1�t���[���̃V�~�����[�V��������
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::C_PhysicsEngineImpl::SetFrameSimulationTime(float frameSimulationTime)
    {
        frameSimulationTime_ = frameSimulationTime;
    }


    /*************************************************************//**
     *
     *  @brief  �ő�T�u�X�e�b�v����ݒ肷��
     *  @param  �ő�T�u�X�e�b�v��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::C_PhysicsEngineImpl::SetMaxSubStepCount(int32_t maxSubStepCount)
    {
        maxSubStepCount_ = maxSubStepCount;
    }


    /*************************************************************//**
     *
     *  @brief  �ő�T�u�X�e�b�v����ݒ肷��
     *  @param  �ő�T�u�X�e�b�v��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PhysicsEngine::C_PhysicsEngineImpl::EnableActive(bool validFlag)
    {
        activeFlag_ = validFlag;
    }
}