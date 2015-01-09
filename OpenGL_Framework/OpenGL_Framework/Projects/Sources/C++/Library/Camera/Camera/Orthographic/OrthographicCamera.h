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
        C_OrthographicCamera();                                                                                         // �R���X�g���N�^
        virtual ~C_OrthographicCamera() override;                                                                       // �f�X�g���N�^
        virtual void Update() override;                                                                                 // �X�V����
        virtual const Matrix4x4& GetViewMatrix() const override;                                                        // �r���[�s����擾
        virtual const Matrix4x4& GetProjectionMatrix() const override;                                                  // �v���W�F�N�V�����s����擾
        virtual const Matrix4x4& GetViewProjectionMatrix() const override;                                              // �r���[�v���W�F�N�V�����s����擾
        virtual void SetClipSpace(float left, float right, float bottom, float top);                                    // �N���b�v��Ԃ�ݒ�
        virtual void SetNearClippingPlane(float nearClippingPlane = Matrix4x4::s_ORTHOGRAPHIC_2D_NEAR) override;        // �j�A�[�N���b�v�ʂ�ݒ�
        virtual void SetFarClippingPlane(float farClippingPlane = Matrix4x4::s_ORTHOGRAPHIC_2D_FAR) override;           // �t�@�[�N���b�v�ʂ�ݒ�
    private:
        float clipSpaceLeft_ = 0.0f;                                                                                    ///< @brief �N���b�v�ʂ̍���
        float clipSpaceRight_ = 0.0f;                                                                                   ///< @brief �N���b�v�ʂ̉E��
        float clipSpaceBottom_ = 0.0f;                                                                                  ///< @brief �N���b�v�ʂ̉���
        float clipSpaceTop_ = 0.0f;                                                                                     ///< @brief �N���b�v�ʂ̏㑤
        float nearClippingPlane_ = Matrix4x4::s_ORTHOGRAPHIC_2D_NEAR;                                                   ///< @brief �j�A�[�N���b�v��
        float farClippingPlane_ = Matrix4x4::s_ORTHOGRAPHIC_2D_FAR;                                                     ///< @brief �t�@�[�N���b�v��
        Matrix4x4 projectionMatrix_;                                                                                    ///< @brief �v���W�F�N�V�����s��
    };
}