/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../PerspectiveCamera.h"


//-------------------------------------------------------------
//!
//! @brief �J����
//! @brief �J�����֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Camera
{
    //-------------------------------------------------------------
    //!
    //! @brief �e�X�g�J����
    //! @brief �e�X�g�p�̃J�����ƂȂ�N���X
    //!
    //-------------------------------------------------------------
    class C_TestCamera : public C_PerspectiveCamera
    {
    public:
        C_TestCamera();                                                     // �R���X�g���N�^
        ~C_TestCamera() override;                                           // �f�X�g���N�^
        void Update() override;                                             // �X�V����
        void SetEyePoint(const Vector3& rEyePoint) override;                // ���_��ݒ�
        void SetTargetPoint(const Vector3& rTargetPoint) override;          // �����_��ݒ�
        void SetKeyboradFlag(bool keyboardFlag);                            // �L�[���̓t���O��ݒ�
        void SetMouseFlag(bool mouseFlag);                                  // �}�E�X���̓t���O��ݒ�
        void SetMoveScale(float moveScale);                                 // �ړ��̑傫����ݒ�
    private:
        int32_t previousMousePositionX_ = 0;                                ///< @brief 1�t���[���O�̂̃}�E�X��X���W
        int32_t previousMousePositionY_ = 0;                                ///< @brief 1�t���[���O�̃}�E�X��Y���W
        float mouseRightDragAngleX_ = 0.0f;                                 ///< @brief �E�N���b�N�̃h���b�O����X�����̊p�x
        float mouseRightDragAngleY_ = 0.0f;                                 ///< @brief �E�N���b�N�̃h���b�O����Y�����̊p�x
        float moveScale_ = 1.0f;                                            ///< @brief �ړ��̑傫��
        bool keyboardFlag_ = true;                                          ///< @brief �L�[���͂𔻒f����t���O
        bool mouseFlag_ = true;                                             ///< @brief �}�E�X���͂𔻒f����t���O
        bool pointChangeFlag_ = false;                                      ///< @brief ���_�������_��ύX���������f����t���O
        Vector3 direction_;                                                 ///< @brief �J�����̌���
        Vector3 distance_;                                                  ///< @brief ����

        void InputKeyboardUpdate();                                         // �L�[���͂ɂ��X�V����
        void InputMouseUpdate();                                            // �}�E�X���͂ɂ��X�V����
    };
}