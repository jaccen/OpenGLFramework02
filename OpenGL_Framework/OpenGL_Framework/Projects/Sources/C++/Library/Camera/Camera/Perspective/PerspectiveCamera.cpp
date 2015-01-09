/* �w�b�_�t�@�C�� */
#include "PerspectiveCamera.h"


//-------------------------------------------------------------
//!
//! @brief �J����
//! @brief �J�����֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Camera
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PerspectiveCamera::C_PerspectiveCamera()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PerspectiveCamera::~C_PerspectiveCamera()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�����̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PerspectiveCamera::Update()
    {
        // �r���[�s����X�V
        viewMatrix_ = Matrix4x4::s_CreateLookAt(eyePoint_,
                                                targetPoint_,
                                                upVector_);

        // �v���W�F�N�V�����s����X�V
        projectionMatrix_ = Matrix4x4::s_CreatePerspectiveProjection(fieldOfViewY_,
                                                                     aspectRatio_,
                                                                     nearClippingPlane_,
                                                                     farClippingPlane_);

        // �r���[�v���W�F�N�V�����s����v�Z
        viewProjectionMatrix_ = projectionMatrix_ * viewMatrix_;
    }


    /*************************************************************//**
     *
     *  @brief  ���_���擾����
     *  @param  �Ȃ�
     *  @return ���_
     *
     ****************************************************************/
    const Vector3& C_PerspectiveCamera::GetEyePoint() const
    {
        return eyePoint_;
    }


    /*************************************************************//**
     *
     *  @brief  �����_���擾����
     *  @param  �Ȃ�
     *  @return �����_
     *
     ****************************************************************/
    const Vector3& C_PerspectiveCamera::GetTargetPoint() const
    {
        return targetPoint_;
    }


    /*************************************************************//**
     *
     *  @brief  �A�b�v�x�N�g�����擾����
     *  @param  �Ȃ�
     *  @return �A�b�v�x�N�g��
     *
     ****************************************************************/
    const Vector3& C_PerspectiveCamera::GetUpVector() const
    {
        return upVector_;
    }


    /*************************************************************//**
     *
     *  @brief  �r���[�s����擾����
     *  @param  �Ȃ�
     *  @return �r���[�s��
     *
     ****************************************************************/
    const Matrix4x4& C_PerspectiveCamera::GetViewMatrix() const
    {
        return viewMatrix_;
    }


    /*************************************************************//**
     *
     *  @brief  �v���W�F�N�V�����s����擾����
     *  @param  �Ȃ�
     *  @return �v���W�F�N�V�����s��
     *
     ****************************************************************/
    const Matrix4x4& C_PerspectiveCamera::GetProjectionMatrix() const
    {
        return projectionMatrix_;
    }


    /*************************************************************//**
     *
     *  @brief  �r���[�v���W�F�N�V�����s����擾����
     *  @param  �Ȃ�
     *  @return �r���[�v���W�F�N�V�����s��
     *
     ****************************************************************/
    const Matrix4x4& C_PerspectiveCamera::GetViewProjectionMatrix() const
    {
        return viewProjectionMatrix_;
    }


    /*************************************************************//**
     *
     *  @brief  ���_��ݒ肷��
     *  @param  ���_
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PerspectiveCamera::SetEyePoint(const Vector3& rEyePoint)
    {
        eyePoint_ = rEyePoint;
    }


    /*************************************************************//**
     *
     *  @brief  �����_��ݒ肷��
     *  @param  �����_
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PerspectiveCamera::SetTargetPoint(const Vector3& rTargetPoint)
    {
        targetPoint_ = rTargetPoint;
    }


    /*************************************************************//**
     *
     *  @brief  �A�b�v�x�N�g����ݒ肷��
     *  @param  �A�b�v�x�N�g��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PerspectiveCamera::SetUpVector(const Vector3& rUpVector)
    {
        upVector_ = rUpVector;
    }


    /*************************************************************//**
     *
     *  @brief  ����̐��������̉�p��ݒ肷��
     *  @param  ����̐��������̉�p
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PerspectiveCamera::SetFieldOfViewY(float fieldOfViewY)
    {
        fieldOfViewY_ = fieldOfViewY;
    }


    /*************************************************************//**
     *
     *  @brief  �A�X�y�N�g���ݒ肷��
     *  @param  �A�X�y�N�g��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PerspectiveCamera::SetAspectRatio(float aspectRatio)
    {
        aspectRatio_ = aspectRatio;
    }


    /*************************************************************//**
     *
     *  @brief  ���_����ł��߂��N���b�v�ʂ�ݒ肷��
     *  @param  ���_����ł��߂��N���b�v��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PerspectiveCamera::SetNearClippingPlane(float nearClippingPlane)
    {
        nearClippingPlane_ = nearClippingPlane;
    }


    /*************************************************************//**
     *
     *  @brief  ���_����ł������N���b�v�ʂ�ݒ肷��
     *  @param  ���_����ł������N���b�v��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PerspectiveCamera::SetFarClippingPlane(float farClippingPlane)
    {
        farClippingPlane_ = farClippingPlane;
    }
}