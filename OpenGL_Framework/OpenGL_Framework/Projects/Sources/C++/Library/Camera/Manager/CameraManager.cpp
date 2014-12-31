/* �w�b�_�t�@�C�� */
#include "CameraManagerImpl.h"


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
    C_CameraManager::C_CameraManager() :

        // �������
        upImpl_(std::make_unique<C_CameraManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_CameraManager::~C_CameraManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �J�����̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CameraManager::Update()
    {
        upImpl_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  �J�����̓o�^�������s��
     *  @param  �J����
     *  @param  ID
     *  @param  �X�V�t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CameraManager::Entry(const CameraPtr& prCamera,
                                const std::string& rId,
                                bool updateFlag)
    {
        upImpl_->Entry(prCamera, rId, updateFlag);
    }


    /*************************************************************//**
     *
     *  @brief  �J�����̏����������s��
     *  @param  ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CameraManager::Remove(const std::string& rId)
    {
        upImpl_->Remove(rId);
    }


    /*************************************************************//**
     *
     *  @brief  �S�ẴJ�����̏����������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_CameraManager::AllRemove()
    {
        upImpl_->AllRemove();
    }


    /*************************************************************//**
     *
     *  @brief  �J�������擾����
     *  @param  ID
     *  @return �擾�ł����ꍇ      �F�J����
     *  @return �擾�ł��Ȃ������ꍇ�Fnone
     *
     ****************************************************************/
    boost::optional<const CameraPtr&> C_CameraManager::GetCamera(const std::string& rId) const
    {
        return upImpl_->GetCamera(rId);
    }
}