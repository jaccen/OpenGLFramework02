/* �w�b�_�t�@�C�� */
#include "SpriteCreaterManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief �X�v���C�g
//! @brief �X�v���C�g�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Sprite
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SpriteCreaterManager::C_SpriteCreaterManager() :

        // �������
        upImpl_(std::make_unique<C_SpriteCreaterManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SpriteCreaterManager::~C_SpriteCreaterManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreaterManager::Draw()
    {
        upImpl_->Draw();
    }


    /*************************************************************//**
     *
     *  @brief  �\�[�g�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreaterManager::Sort()
    {
        upImpl_->Sort();
    }


    /*************************************************************//**
     *
     *  @brief  �X�v���C�g�V�X�e���̍쐬����
     *  @param  ID
     *  @param  �J����
     *  @parama �e�N�X�`�����
     *  @param  �X�v���C�g�̍ő吔
     *  @param  �D��x
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SpriteCreaterManager::Create(const std::string& rId,
                                        const Camera::CameraPtr& prCamera,
                                        const Texture::TextureDataPtr pTextureData,
                                        uint32_t maxSpriteCount,
                                        float priority)
    {
        if (upImpl_->Create(rId, prCamera, pTextureData, maxSpriteCount, priority) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  �X�v���C�g�V�X�e����j������
     *  @parama ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreaterManager::Destroy(const std::string& rId)
    {
        upImpl_->Destroy(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �X�v���C�g�V�X�e����S�Ĕj������
     *  @parama �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SpriteCreaterManager::AllDestroy()
    {
        upImpl_->AllDestroy();
    }


    /*************************************************************//**
     *
     *  @brief  �X�v���C�g�V�X�e�����擾����
     *  @parama ID
     *  @return �쐬����Ă���ꍇ  �F�X�v���C�g�V�X�e��
     *  @return �쐬����Ă��Ȃ��ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<SpriteCreaterWeakPtr> C_SpriteCreaterManager::GetSpriteCreater(const std::string& rId)
    {
        return upImpl_->GetSpriteCreater(rId);
    }
}