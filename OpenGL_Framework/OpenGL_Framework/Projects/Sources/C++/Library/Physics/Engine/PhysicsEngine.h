/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Singleton/Assert/AssertSingleton.h"
#include "../PhysicsDefine.h"


//-------------------------------------------------------------
///
/// @brief �t�B�W�b�N�X
/// @brief �����֘A�̖��O���
///
//-------------------------------------------------------------
namespace Physics
{
    /* �O���錾 */
    class C_RigidBody;
    class C_SoftBody;
    

    namespace
    {
        /* �f�t�H���g */
        namespace Default
        {
            const Vector3 s_GRAVITY = Vector3(0.0f, 9.8f, 0.0f);                                                                ///< @brief �d��
            const float s_AIR_DENSITY = 1.2f;                                                                                   ///< @brief ��C���x
        }
    }

    //-------------------------------------------------------------
    //!
    //! @brief �t�B�W�b�N�X�G���W��
    //! @brief �����G���W����\���N���X
    //!
    //-------------------------------------------------------------
    class C_PhysicsEngine : public Singleton::C_AssertSingleton<C_PhysicsEngine>
    {
    public:
        /* �ʖ� */
        using BroadphaseFilterType = btBroadphaseProxy;                                                                         // BroadphaseFilterType�^

        C_PhysicsEngine(const Vector3& rWorldMin = Vector3(-10000.0f, -10000.0f, -10000.0f),                                    // �R���X�g���N�^
                        const Vector3& rWorldMax = Vector3( 10000.0f,  10000.0f,  10000.0f),
                        uint16_t maxObjectCount = 10000);
        ~C_PhysicsEngine() override;                                                                                            // �f�X�g���N�^
        void Initialize(const Vector3& rGravity = Default::s_GRAVITY,                                                           // ����������
                        float airDensity = Default::s_AIR_DENSITY);
        void Update(float deltaTime);                                                                                           // �X�V����
        void Finalize();                                                                                                        // �I������
        void AddRigidBody(C_RigidBody* pRigidBody,                                                                              // ���̂�ǉ�
                          int16_t collisionType = BroadphaseFilterType::AllFilter, 
                          int16_t collisionMask = BroadphaseFilterType::AllFilter);
        void AddSoftBody(C_SoftBody* pSoftBody,                                                                                 // ��̂�ǉ�
                         int16_t collisionType = BroadphaseFilterType::DefaultFilter,
                         int16_t collisionMask = BroadphaseFilterType::AllFilter);
        void RemoveRigidBody(C_RigidBody* pRigidBody);                                                                          // ���̂�����
        void RemoveSoftBody(C_SoftBody* pSoftBody);                                                                             // ��̂�����
        const Vector3& GetGravity() const;                                                                                      // �d�͂��擾
        SoftBodyInfo* GetSoftBodyInfo() const;                                                                                  // �\�t�g�{�f�B�����擾
        void SetGravity(const Vector3& rGravity = Default::s_GRAVITY);                                                          // �d�͂�ݒ�
        void SetCollisionCallbackFunction(CollisionCallbackFunction pCollisionCallbackFunction);                                // �Փ˃R�[���o�b�N�֐���ݒ�
        void SetSimulationSubstepCallbackFunction(SimulationSubstepCallbackFunction pSimulationSubstepCallbackFunction,         // �V�~�����[�V�����̃T�u�X�e�b�v�R�[���o�b�N�֐���ݒ�
                                                  void* pWorldUserInfo = nullptr,
                                                  bool previousSubstepCallbackFlag = false);
    private:
        /* �O���錾 */
        class C_PhysicsEngineImpl;

        std::unique_ptr<C_PhysicsEngineImpl> upImpl_;                                                                           ///< @brief �������
    };
}