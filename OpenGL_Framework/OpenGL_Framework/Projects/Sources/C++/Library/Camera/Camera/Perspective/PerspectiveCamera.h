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
    //! @brief �p�[�X�y�N�e�B�u�J����
    //! @brief �������e���s���J����
    //!
    //-------------------------------------------------------------
    class C_PerspectiveCamera : public IC_Camera
    {
    public:
        C_PerspectiveCamera();                                                      // �R���X�g���N�^
        virtual ~C_PerspectiveCamera() override;                                    // �f�X�g���N�^
        virtual void Update() override;                                             // �X�V����
        const Vector3& GetEyePoint() const;                                         // ���_���擾
        const Vector3& GetTargetPoint() const;                                      // �����_���擾
        const Vector3& GetUpVector() const;                                         // �A�b�v�x�N�g�����擾
        virtual const Matrix4& GetViewMatrix() const override;                      // �r���[�s����擾
        virtual const Matrix4& GetProjectionMatrix() const override;                // �v���W�F�N�V�����s����擾
        virtual const Matrix4& GetViewProjectionMatrix() const override;            // �r���[�v���W�F�N�V�����s����擾
        virtual void SetEyePoint(const Vector3& rEyePoint);                         // ���_��ݒ�
        virtual void SetTargetPoint(const Vector3& rTargetPoint);                   // �����_��ݒ�
        void SetUpVector(const Vector3& rUpVector);                                 // �A�b�v�x�N�g����ݒ�
        void SetFieldOfViewY(float fieldOfView);                                    // ����̐��������̉�p
        void SetAspectRatio(float aspectRatio);                                     // �A�X�y�N�g���ݒ�
        virtual void SetNearClippingPlane(float nearClippingPlane) override;        // �j�A�[�N���b�v�ʂ�ݒ�
        virtual void SetFarClippingPlane(float farClippingPlane) override;          // �t�@�[�N���b�v�ʂ�ݒ�
    protected:
        float fieldOfViewY_ = 0.0f;                                                 ///< @brief ����̐��������̉�p
        float aspectRatio_ = 0.0f;                                                  ///< @brief �A�X�y�N�g��
        float nearClippingPlane_ = 0.0f;                                            ///< @brief �j�A�[�N���b�v��
        float farClippingPlane_ = 0.0f;                                             ///< @brief �t�@�[�N���b�v��
        Vector3 eyePoint_;                                                          ///< @brief ���_
        Vector3 targetPoint_;                                                       ///< @brief �����_
        Vector3 upVector_;                                                          ///< @brief �A�b�v�x�N�g��
        Matrix4 viewMatrix_;                                                        ///< @brief �r���[�s��
        Matrix4 projectionMatrix_;                                                  ///< @brief �v���W�F�N�V�����s��
        Matrix4 viewProjectionMatrix_;                                              ///< @brief �r���[�v���W�F�N�V�����s��
    };
}