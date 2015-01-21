/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "RigidBodyMoveLogic.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief ���M�b�h�{�f�B�t�H�[�X���[�u���W�b�N
    //! @brief ���̗̂͂ł̈ړ��̃��W�b�N��\���N���X
    //!
    //-------------------------------------------------------------
    class C_RigidBodyForceMoveLogic : public C_RigidBodyMoveLogic
    {
    public:
        C_RigidBodyForceMoveLogic(const Physics::Vector3& rFirstAddForce,           // �R���X�g���N�^
                                  const Physics::Vector3& rFirstAddTorque);
        virtual ~C_RigidBodyForceMoveLogic() override;                              // �f�X�g���N�^
        C_RigidBodyMoveLogic* DeepCopy() override;                                  // �f�B�[�v�R�s�[
        void SetAddForce(const Physics::Vector3& rAddForce);                        // ������͂�ݒ�
        void SetAddTorque(const Physics::Vector3& rAddTorque);                      // ������g���N��ݒ�
    private:
        std::unique_ptr<Physics::Vector3> upFirstAddForce_;                         ///< @brief �ŏ��ɉ������
        std::unique_ptr<Physics::Vector3> upAddForce_;                              ///< @brief �������
        std::unique_ptr<Physics::Vector3> upFirstAddTorque_;                        ///< @brief �ŏ��ɉ�����g���N
        std::unique_ptr<Physics::Vector3> upAddTorque_;                             ///< @brief ������g���N
        bool firstAddForceFlag_ = false;                                            ///< @brief �ŏ��ɉ�����͂������������f����t���O
        bool firstAddTorqueFlag_ = false;                                           ///< @brief �ŏ��ɉ�����g���N�������������f����t���O

        void DoProcess(RigidBody* pRigidBody) override;                             // ����J�̏���
    };
}