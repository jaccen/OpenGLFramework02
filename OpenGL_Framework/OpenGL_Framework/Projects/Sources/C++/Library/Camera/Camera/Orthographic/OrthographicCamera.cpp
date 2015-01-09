/* �w�b�_�t�@�C�� */
#include "OrthographicCamera.h"
#include "../../../Debug/Helper/DebugHelper.h"


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
    C_OrthographicCamera::C_OrthographicCamera()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_OrthographicCamera::~C_OrthographicCamera()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�����̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OrthographicCamera::Update()
    {
        projectionMatrix_ = Matrix4x4::s_CreateOrthographicProjection(clipSpaceLeft_,
                                                                      clipSpaceRight_,
                                                                      clipSpaceBottom_,
                                                                      clipSpaceTop_,
                                                                      nearClippingPlane_,
                                                                      farClippingPlane_);
    }


    /*************************************************************//**
     *
     *  @brief  �r���[�s����擾����
     *  @param  �Ȃ�
     *  @return �r���[�s��
     *
     ****************************************************************/
    const Matrix4x4& C_OrthographicCamera::GetViewMatrix() const
    {
        return Matrix4x4::s_IDENTITY;
    }


    /*************************************************************//**
     *
     *  @brief  �v���W�F�N�V�����s����擾����
     *  @param  �Ȃ�
     *  @return �v���W�F�N�V�����s��
     *
     ****************************************************************/
    const Matrix4x4& C_OrthographicCamera::GetProjectionMatrix() const
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
    const Matrix4x4& C_OrthographicCamera::GetViewProjectionMatrix() const
    {
        return projectionMatrix_;
    }


    /*************************************************************//**
     *
     *  @brief  �N���b�v��Ԃ�ݒ肷��
     *  @param  �N���b�v��Ԃ̍���
     *  @param  �N���b�v��Ԃ̉E��
     *  @param  �N���b�v��Ԃ̉���
     *  @param  �N���b�v��Ԃ̏㑤
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OrthographicCamera::SetClipSpace(float left, float right, float bottom, float top)
    {
        clipSpaceLeft_ = left;
        clipSpaceRight_ = right;
        clipSpaceBottom_ = bottom;
        clipSpaceTop_ = top;
    }


    /*************************************************************//**
     *
     *  @brief  �j�A�[�N���b�v�ʂ�ݒ肷��
     *  @param  �j�A�[�N���b�v��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OrthographicCamera::SetNearClippingPlane(float nearClippingPlane)
    {
        nearClippingPlane_ = nearClippingPlane;
    }

    /*************************************************************//**
     *
     *  @brief  �t�@�[�N���b�v�ʂ�ݒ肷��
     *  @param  �t�@�[�N���b�v��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OrthographicCamera::SetFarClippingPlane(float farClippingPlane)
    {
        farClippingPlane_ = farClippingPlane;
    }
}