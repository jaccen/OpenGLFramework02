/* �w�b�_�t�@�C�� */
#include "ParticleSystemImpl.h"


//-------------------------------------------------------------
//!
//! @brief �p�[�e�B�N��
//! @brief �p�[�e�B�N���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Particle
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_ParticleSystem::C_ParticleSystem() :

        // �������
        upImpl_(std::make_unique<C_ParticleSystemImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_ParticleSystem::~C_ParticleSystem()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �J����
     *  @param  �e�N�X�`���n���h��
     *  @param  �p�[�e�B�N���̍ő吔
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_ParticleSystem::Initialize(const Camera::CameraPtr& prCamera,
                                      Texture::TextureHandle textureHandle,
                                      uint32_t maxParticleCount)
    {
        if (upImpl_->Initialize(prCamera, textureHandle, maxParticleCount) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    void C_ParticleSystem::Update()
    {
        upImpl_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::Draw()
    {
        upImpl_->Draw();
    }


    /*************************************************************//**
     *
     *  @brief  �I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::Finalize()
    {
        upImpl_->Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  �o�^�������s��
     *  @param  �����t���[����
     *  @param  ���W
     *  @param  ���x
     *  @param  �J�n���̉����x
     *  @param  �I�����̉����x
     *  @param  �J�n���̊p�x( ���W�A���l )
     *  @param  �I�����̊p�x( ���W�A���l )
     *  @param  �J�n���̕�
     *  @param  �I�����̕�
     *  @param  �J�n���̍���
     *  @param  �I�����̍���
     *  @param  �J�n���̐F
     *  @param  �I�����̐F
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::Entry(int32_t lifeFrame,
                                 const Vector3& rPosition,
                                 const Vector3& rVelocity,
                                 const Vector3& rStartAcceleration,
                                 const Vector3& rEndAcceleration,
                                 float startAngle,
                                 float endAngle,
                                 float startWidth,
                                 float endWidth,
                                 float startHeight,
                                 float endHeight,
                                 const Vector4& rStartColor,
                                 const Vector4& rEndColor)
    {
        upImpl_->Entry(S_CreateDara(lifeFrame,
                                    rPosition,
                                    rVelocity,
                                    rStartAcceleration,
                                    rEndAcceleration,
                                    startAngle,
                                    endAngle,
                                    startWidth,
                                    endWidth,
                                    startHeight,
                                    endHeight,
                                    rStartColor,
                                    rEndColor));
    }


    /*************************************************************//**
     *
     *  @brief  �o�^�������s��
     *  @param  �������
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::Entry(const S_CreateDara& rCreateData)
    {
        upImpl_->Entry(rCreateData);
    }


    /*************************************************************//**
     *
     *  @brief  �p�[�e�B�N���̍ő吔�̐ݒ���s��
     *  @param  �p�[�e�B�N���̍ő吔
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::SetMaxParticleCount(uint32_t maxParticleCount)
    {
        upImpl_->SetMaxParticleCount(maxParticleCount);
    }


    /*************************************************************//**
     *
     *  @brief  �r���{�[�h�̎�������L��������
     *  @param  �L�����𔻒f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::EnableAutoBillboard(bool validFlag)
    {

    }


    /*************************************************************//**
     *
     *  @brief  �J������ݒ肷��
     *  @param  �J����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::SetCamera(const Camera::CameraPtr& prCamera)
    {
        upImpl_->SetCamera(prCamera);
    }


    /*************************************************************//**
     *
     *  @brief  ���f���s���ݒ肷��
     *  @param  ���f���s��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::SetModelMatrix(const Matrix4x4& rModelMatrix)
    {
        upImpl_->SetModelMatrix(rModelMatrix);
    }


    /*************************************************************//**
     *
     *  @brief  �r���{�[�h�����邽�߂̍s���ݒ肷��
     *  @param  �r���{�[�h�����邽�߂̍s��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::SetBillboardMatrix(const Matrix4x4& rBillboardMatrix)
    {
        upImpl_->SetBillboardMatrix(rBillboardMatrix);
    }


    /*************************************************************//**
     *
     *  @brief  �O���̗͂�ݒ肷��
     *  @param  �O���̗�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::SetExternalPower(const Vector3& rExternalPower)
    {
        upImpl_->SetExternalPower(rExternalPower);
    }


    /*************************************************************//**
     *
     *  @brief  �e�N�X�`���n���h����ݒ肷��
     *  @param  �e�N�X�`���n���h��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::SetTextureHandle(Texture::TextureHandle textureHandle)
    {
        upImpl_->SetTextureHandle(textureHandle);
    }


    /*************************************************************//**
     *
     *  @brief  �����x�ɗp�����Ԋ֐���ݒ肷��
     *  @param  �����x�ɗp�����Ԋ֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::SetAccelerationInterpolationFunction(const InterpolationFunction& rFunction)
    {
        upImpl_->SetAccelerationInterpolationFunction(rFunction);
    }


    /*************************************************************//**
     *
     *  @brief  �p�x�ɗp�����Ԋ֐���ݒ肷��
     *  @param  �p�x�ɗp�����Ԋ֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::SetAngleInterpolationFunction(const InterpolationFunction& rFunction)
    {
        upImpl_->SetAngleInterpolationFunction(rFunction);
    }


    /*************************************************************//**
     *
     *  @brief  �X�P�[���ɗp�����Ԋ֐���ݒ肷��
     *  @param  �X�P�[���ɗp�����Ԋ֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::SetScaleInterpolationFunction(const InterpolationFunction& rFunction)
    {
        upImpl_->SetScaleInterpolationFunction(rFunction);
    }


    /*************************************************************//**
     *
     *  @brief  �F�ɗp�����Ԋ֐���ݒ肷��
     *  @param  �F�ɗp�����Ԋ֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::SetColorInterpolationFunction(const InterpolationFunction& rFunction)
    {
        upImpl_->SetColorInterpolationFunction(rFunction);
    }


    /*************************************************************//**
     *
     *  @brief  �e�N�X�`�����W�̍����ݒ�
     *  @param  �e�N�X�`�����W�̍���
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::SetTextureCoordUpperLeft(const Vector2& rTextureCoordUpperLeft)
    {
        upImpl_->SetTextureCoordUpperLeft(rTextureCoordUpperLeft);
    }


    /*************************************************************//**
     *
     *  @brief  �e�N�X�`�����W�̉E����ݒ�
     *  @param  �e�N�X�`�����W�̉E��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystem::SetTextureCoordLowerRight(const Vector2& rTextureCoordLowerRight)
    {
        upImpl_->SetTextureCoordLowerRight(rTextureCoordLowerRight);
    }
}