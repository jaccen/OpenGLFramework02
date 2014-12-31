/* �w�b�_�t�@�C�� */
#include "SceneManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief �V�[��
//! @brief �V�[���֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Scene
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �ŏ��̃V�[��
     *
     ****************************************************************/
    C_SceneManager::C_SceneManager(C_BaseScene* pFirstScene) :

        // �������
        upImpl_(std::make_unique<C_SceneManagerImpl>(pFirstScene, this))

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SceneManager::~C_SceneManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �V�[���}�l�[�W���[�̏������������s��
     *  @param  �Ȃ�
     *  @return ����I���FSUCCESSFUL
     *  @return �ُ�I���FERROR_TERMINATION
     *
     ****************************************************************/
    ecSceneReturn C_SceneManager::Initialize()
    {
        if (upImpl_->Initialize() == ecSceneReturn::ERROR_TERMINATION) return ecSceneReturn::ERROR_TERMINATION;

        return ecSceneReturn::SUCCESSFUL;
    }


    /*************************************************************//**
     *
     *  @brief  �V�[���}�l�[�W���[�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return ����I���FCONTINUATIOIN
     *  @return ����I���FSUCCESSFUL
     *  @return �ُ�I���FERROR_TERTINATION
     *
     ****************************************************************/
    ecSceneReturn C_SceneManager::Update()
    {
        ecSceneReturn returnValue = upImpl_->Update();

        if (returnValue != ecSceneReturn::CONTINUATIOIN)
        {
            if (returnValue == ecSceneReturn::ERROR_TERMINATION)
            {
                return ecSceneReturn::ERROR_TERMINATION;
            }
            else
            {
                return ecSceneReturn::SUCCESSFUL;
            }
        }

        return ecSceneReturn::CONTINUATIOIN;
    }


    /*************************************************************//**
     *
     *  @brief  �V�[���}�l�[�W���[�̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SceneManager::Draw()
    {
        upImpl_->Draw();
    }


    /*************************************************************//**
     *
     *  @brief  �V�[���}�l�[�W���[�̏I���������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SceneManager::Finalize()
    {
        upImpl_->Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  ���̃V�[�����v�b�V������
     *  @param  ���̃V�[��
     *  @param  �ȑO�̃V�[���ɐݒ肷��X�V�t���O
     *  @param  �ȑO�̃V�[���ɐݒ肷��`��t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SceneManager::PushScene(C_BaseScene* pNextScene,
                                   bool previousUpdateFlag,
                                   bool presiousDrawFlag)
    {
        upImpl_->PushScene(pNextScene, previousUpdateFlag, presiousDrawFlag);
    }


    /*************************************************************//**
     *
     *  @brief  ���̃V�[�����|�b�v����
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SceneManager::PopScene()
    {
        upImpl_->PopScene();
    }


    /*************************************************************//**
     *
     *  @brief  ���݂̃V�[���Ƃ̓���ւ�������
     *  @param  ���̃V�[��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SceneManager::ReplaceScene(C_BaseScene* pNextScene)
    {
        upImpl_->ReplaceScene(pNextScene);
    }
}