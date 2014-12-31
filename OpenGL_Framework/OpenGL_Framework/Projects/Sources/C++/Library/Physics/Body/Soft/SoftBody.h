/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../PhysicsDefine.h"
#include <tuple>


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
    class C_LinearJoint;
    class C_AngularJoint;


    //-------------------------------------------------------------
    //!
    //! @brief �R���t�B�O
    //! @brief �\�t�g�{�f�B�̐�����\���\����
    //!
    //-------------------------------------------------------------
    struct S_Config
    {
        float damping_ = 0.0f;                                                                          ///< @brief �����W��
        float dynamicFriction_ = 0.0f;                                                                  ///< @brief �����C�W��
        float poseMatching_ = 0.0f;                                                                     ///< @brief �`��ێ���
        float rigidContactHardness_ = 1.0f;                                                             ///< @brief �����ڐG�W��( ���ˋ )
        float softContactHardness_ = 1.0f;                                                              ///< @brief ��ڐG�W��
        float kineticContactHardness_ = 0.1f;                                                           ///< @brief �^���ڐG�W��
        float anchorsHardness_ = 1.0f;                                                                  ///< @brief �A���J�[�d�x
        float pressure_ = 1000.0f;                                                                      ///< @brief ����
        float volumeConversation_ = 10.0f;                                                              ///< @brief �̐ϕۑ��W��
        int32_t positionSolverIterationCount_ = 1;                                                      ///< @brief ���W�̏C����
        int32_t velocitySolverIterationCount_ = 0;                                                      ///< @brief ���x�̏C����
        int32_t driftSolverIterationCount_ = 0;                                                         ///< @brief ���i�͂̏C����
        int32_t clusterSolverIterationCount_ = 4;                                                       ///< @brief ���̏C����
    };


    //-------------------------------------------------------------
    //!
    //! @brief �}�e���A��
    //! @brief �\�t�g�{�f�B�̃}�e���A����\���\����
    //!
    //-------------------------------------------------------------
    struct S_Material
    {
        int32_t vertexDistance_ = 1;                                                                    ///< @brief ���_�Ԃ̋���
        float linearStiffness_ = 1.0f;                                                                  ///< @brief �����W��
        float angularStiffness_ = 1.0f;                                                                 ///< @brief ��]�����W��
        float volumeStiffness_ = 1.0f;                                                                  ///< @brief �{�����[�������W��
    };


    //-------------------------------------------------------------
    //!
    //! @brief �\�t�g�{�f�B
    //! @brief ��̂�\���N���X
    //!
    //-------------------------------------------------------------
    class C_SoftBody
    {
    public:
        


        C_SoftBody() = default;                                                                         // �f�t�H���g�R���X�g���N�^
        C_SoftBody(SoftBodyInfo* pSoftBodyInfo,                                                         // �R���X�g���N�^
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
        ~C_SoftBody();                                                                                  // �f�X�g���N�^
        void EnableActive(bool validFlag = true);                                                       // �A�N�e�B�u��Ԃ�L����
        void EnableCollisionResponse(bool validFlag = true);                                            // �Փˉ�����L����
        void EnableSoftBodyCollision(bool validFlag = true);                                            // ��̂Ƃ̏Փ˂�L����
        void EnableCollisionCallback(bool validFlag = true);                                            // �Փ˃R�[���o�b�N��L����
        void ApplyForce(const Vector3& rForce);                                                         // �͂�������
        void ApplyForce(const Vector3& rForce, int32_t vertexIndex);                                    // �͂�������
        void ApplyAeroForceToVertex(const Vector3& rAeroForce, int32_t vertexIndex);                    // ���_�ɕ��̗͂�������
        void ApplyAeroForceToFace(const Vector3& rAeroForce, int32_t faceIndex);                        // �ʂɕ��̗͂�������
        void AddPosition(const Vector3& rPosition);                                                     // ���W��������
        void AddVelocity(const Vector3& rVelocity);                                                     // ���x��������
        void AddVelocity(const Vector3& rVelocity, int32_t vertexIndex);                                // ���x��������
        void AppendAnchor(int32_t vertexIndex,                                                          // �A���J�[��ǉ�
                          C_RigidBody* pRigidBody,
                          bool collisionBetweenLinkedBodiesFlag = true,
                          float influence = 1.0f);
        void AppendLinearJoint(C_LinearJoint* pLinearJoint, C_SoftBody* pAnother);                      // ���`�ڍ���ǉ�
        void AppendAngularJoint(C_AngularJoint* pAngularJoint, C_SoftBody* pAnother);                   // �p�ڍ���ǉ�
        btSoftBody* GetSoftBody() const;                                                                // ��̂��擾
        const Transform& GetTransform() const;                                                          // �g�����X�t�H�[�����擾
        float GetMass(int32_t vertexIndex) const;                                                       // ���ʂ��擾
        float GetTotalMass() const;                                                                     // �S�̂̎��ʂ��擾
        float GetFriction() const;                                                                      // ���C�W�����擾
        float GetRollingFriction() const;                                                               // �]���薀�C�W�����擾
        float GetRestitution() const;                                                                   // �����W�����擾
        std::tuple<Vector3, Vector3> GetAabb() const;                                                   // AABB���擾
        int32_t GetActivationState() const;                                                             // �A�N�e�B�x�[�V�����X�e�[�g���擾
        int32_t GetUserIndex() const;                                                                   // �Ǝ��̃C���f�b�N�X���擾
        void* GetUserPointer() const;                                                                   // �Ǝ��̃|�C���^���擾
        void SetConfig(const S_Config& rConfig);                                                        // �R���t�B�O��ݒ�
        void SetMaterial(const S_Material& rMaterial);                                                  // �}�e���A����ݒ�
        void SetTransform(const Transform& rTransform);                                                 // �g�����X�t�H�[����ݒ�
        void SetMass(float mass, int32_t vertexIndex);                                                  // ���ʂ�ݒ�
        void SetTotalMass(float totalMass);                                                             // �S�̂̎��ʂ�ݒ�
        void SetTotalDensity(float totalDensity);                                                       // �S�̖̂��x��ݒ�
        void SetFriction(float friction = 1.0f);                                                        // ���C�W����ݒ�
        void SetRollingFriction(float rollingFriction = 1.0f);                                          // �]���薀�C�W����ݒ�
        void SetRestitution(float restitution = 0.0f);                                                  // �����W����ݒ�
        void SetActivationState(int32_t state);                                                         // �A�N�e�B�x�[�V�����X�e�[�g��ݒ�
        void SetUserIndex(int32_t index);                                                               // �Ǝ��̃C���f�b�N�X��ݒ�
        void SetUserPointer(void* pData);                                                               // �Ǝ��̃|�C���^��ݒ�

        static C_SoftBody* s_CreateEllipsoid(SoftBodyInfo* pSoftBodyInfo,                               // �ȉ~�̌`��̓�̂��쐬
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
        std::unique_ptr<btSoftBody> upSoftBody_;                                                        ///< @brief ���
    };
}