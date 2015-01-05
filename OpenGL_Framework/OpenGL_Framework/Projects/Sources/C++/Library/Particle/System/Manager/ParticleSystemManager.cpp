/* �w�b�_�t�@�C�� */
#include "ParticleSystemManagerImpl.h"


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
    C_ParticleSystemManager::C_ParticleSystemManager() :

        // �������
        upImpl_(std::make_unique<C_ParticleSystemManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_ParticleSystemManager::~C_ParticleSystemManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystemManager::Update()
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
    void C_ParticleSystemManager::Draw()
    {
        upImpl_->Draw();
    }


    /*************************************************************//**
     *
     *  @brief  �p�[�e�B�N���V�X�e���̍쐬����
     *  @param  ID
     *  @param  �J����
     *  @parama �e�N�X�`���n���h��
     *  @param  �p�[�e�B�N���̍ő吔
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_ParticleSystemManager::Create(const std::string& rId,
                                         const std::shared_ptr<Camera::C_PerspectiveCamera>& sprCamera,
                                         Texture::TextureHandle textureHandle,
                                         uint32_t maxParticleNumber)
    {
        if (upImpl_->Create(rId, sprCamera, textureHandle, maxParticleNumber) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �p�[�e�B�N���V�X�e����j������
     *  @parama ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystemManager::Destroy(const std::string& rId)
    {
        upImpl_->Destroy(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �p�[�e�B�N���V�X�e����S�Ĕj������
     *  @parama �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ParticleSystemManager::AllDestroy()
    {
        upImpl_->AllDestroy();
    }


    /*************************************************************//**
     *
     *  @brief  �p�[�e�B�N���V�X�e�����擾����
     *  @parama ID
     *  @return �쐬����Ă���ꍇ  �F�p�[�e�B�N���V�X�e��
     *  @return �쐬����Ă��Ȃ��ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<ParticleSystemWeakPtr> C_ParticleSystemManager::GetParticleSystem(const std::string& rId)
    {
        return upImpl_->GetParticleSystem(rId);
    }
}