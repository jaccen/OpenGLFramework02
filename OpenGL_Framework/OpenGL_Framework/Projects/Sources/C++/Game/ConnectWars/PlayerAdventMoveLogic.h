/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "RigidBodyMoveLogic.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"


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
    //! @brief ���M�b�h�{�f�B�C���v�b�g���[�u���W�b�N
    //! @brief ���̂̓��͈ړ��̃��W�b�N��\���N���X
    //!
    //-------------------------------------------------------------
    class C_PlayerAdventMoveLogic : public C_RigidBodyMoveLogic
    {
    public:
        C_PlayerAdventMoveLogic();                                                      // �R���X�g���N�^
        ~C_PlayerAdventMoveLogic() override;                                            // �f�X�g���N�^
        void SetDirection(const Physics::Vector3& rDirection) override {};              // ������ݒ�
        void SetMovement(float movement) override;                                      // �ړ��ʂ�ݒ�
        C_RigidBodyMoveLogic* DeepCopy() override;                                      // �f�B�[�v�R�s�[
        bool IsMoveFinish() const;                                                      // �ړ��I�����m�F
    private:
        float movement_ = 1.0f;                                                         ///< @brief �ړ���
        Timer::C_FrameCounter frameCounter_;                                            ///< @brief �t���[���J�E���^�[
        int32_t finishCount = 40;                                                       ///< @brief �I���J�E���g��

        void DoProcess(RigidBody* pRigidBody) override;                                 // ����J�̏���
    };
}