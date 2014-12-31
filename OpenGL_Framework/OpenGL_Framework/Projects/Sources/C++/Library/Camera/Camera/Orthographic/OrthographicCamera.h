/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../Camera.h"


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
    //! @brief �I���g�O���t�B�b�N�J����
    //! @brief �����e�̃J����
    //!
    //-------------------------------------------------------------
    class C_OrthographicCamera : public IC_Camera
    {
    public:
        C_OrthographicCamera();                                                     // �R���X�g���N�^
        virtual ~C_OrthographicCamera() override;                                   // �f�X�g���N�^
        virtual void Update() override;                                             // �X�V����
        virtual const Matrix4& GetViewMatrix() const override;                      // �r���[�s����擾
        virtual const Matrix4& GetProjectionMatrix() const override;                // �v���W�F�N�V�����s����擾
        virtual const Matrix4& GetViewProjectionMatrix() const override;            // �r���[�v���W�F�N�V�����s����擾
        virtual void SetClipSpace(float left,                                       // �N���b�v��Ԃ�ݒ�
                                  float right,
                                  float bottom,
                                  float top);
        virtual void SetNearClippingPlane(float nearClippingPlane) override;        // �j�A�[�N���b�v�ʂ�ݒ�
        virtual void SetFarClippingPlane(float farClippingPlane) override;          // �t�@�[�N���b�v�ʂ�ݒ�
    private:
        float clipSpaceLeft_ = 0.0f;                                                ///< @brief �N���b�v�ʂ̍���
        float clipSpaceRight_ = 0.0f;                                               ///< @brief �N���b�v�ʂ̉E��
        float clipSpaceBottom_ = 0.0f;                                              ///< @brief �N���b�v�ʂ̉���
        float clipSpaceTop_ = 0.0f;                                                 ///< @brief �N���b�v�ʂ̏㑤
        float nearClippingPlane_ = 0.0f;                                            ///< @brief �j�A�[�N���b�v��
        float farClippingPlane_ = 0.0f;                                             ///< @brief �t�@�[�N���b�v��
        Matrix4 projectionMatrix_;                                                  ///< @brief �v���W�F�N�V�����s��
    };
}