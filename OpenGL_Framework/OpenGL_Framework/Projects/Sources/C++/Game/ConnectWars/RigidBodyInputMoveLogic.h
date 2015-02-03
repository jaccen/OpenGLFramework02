/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "RigidBodyMoveLogic.h"


/* �O���錾 */
namespace Input
{
    class C_KeyboardManager;
    class C_GamepadManager;
}


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
    class C_RigidBodyInputMoveLogic : public C_RigidBodyMoveLogic
    {
    public:
        C_RigidBodyInputMoveLogic(float movement = 1.0f, float movementScale = 1.0f);       // �R���X�g���N�^
        ~C_RigidBodyInputMoveLogic() override;                                              // �f�X�g���N�^
        void SetDirection(const Physics::Vector3& rDirection) override {};                  // ������ݒ�
        void SetMovement(float movement) override;                                          // �ړ��ʂ�ݒ�
        C_RigidBodyMoveLogic* DeepCopy() override;                                          // �f�B�[�v�R�s�[
        void SetMovementScale(float movementScale);                                         // �ړ��ʂ̃X�P�[����ݒ�
    private:
        float movement_ = 1.0f;                                                             ///< @brief �ړ���
        float movementScale_ = 1.0f;                                                        ///< @brief �ړ��ʂ̃X�P�[��
        Input::C_KeyboardManager* pKeyboardManager_ = nullptr;                              ///< @brief �L�[�{�[�h�}�l�[�W���[
        Input::C_GamepadManager* pGamepadManager_ = nullptr;                                ///< @brief �Q�[���p�b�h�}�l�[�W���[

        void DoProcess(RigidBody* pRigidBody) override;                                     // ����J�̏���
    };
}