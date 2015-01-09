/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../../Math/Vector/Vector3.h"
#include "../../Math/Matrix/Matrix4x4.h"


//-------------------------------------------------------------
//!
//! @brief �J����
//! @brief �J�����֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Camera
{
    /* �O���錾 */
    class IC_Camera;


    /* �ʖ� */
    using Vector3 = Math::S_Vector3<float>;                                     // Vector3�^
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                 // Matrix4x4�^
    using CameraPtr = std::shared_ptr<IC_Camera>;                               // CameraPtr�^


    //-------------------------------------------------------------
    //!
    //! @brief �J����
    //! @brief �J�����̃C���^�t�F�[�X
    //!
    //-------------------------------------------------------------
    class IC_Camera
    {
    public:
        IC_Camera() = default;                                                  // �R���X�g���N�^
        virtual ~IC_Camera() = default;                                         // �f�X�g���N�^
        virtual void Update() = 0;                                              // �X�V����
        virtual const Matrix4x4& GetViewMatrix() const = 0;                     // �r���[�s����擾
        virtual const Matrix4x4& GetProjectionMatrix() const = 0;               // �v���W�F�N�V�����s����擾
        virtual const Matrix4x4& GetViewProjectionMatrix() const = 0;           // �r���[�v���W�F�N�V�����s����擾
        virtual void SetNearClippingPlane(float nearClippingPlane) = 0;         // �j�A�[�N���b�v�ʂ�ݒ�
        virtual void SetFarClippingPlane(float farClippingPlane) = 0;           // �t�@�[�N���b�v�ʂ�ݒ�
    };
}