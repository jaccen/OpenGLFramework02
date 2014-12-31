/* �w�b�_�t�@�C�� */
#include "TimeManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief �^�C�}�[
//! @brief �^�C�}�[�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Timer
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_TimeManager::C_TimeManager() :

        // �������
        upImpl_(std::make_unique<C_TimeManagerImpl>())

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_TimeManager::~C_TimeManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �������������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TimeManager::Initialize()
    {
        upImpl_->Initialize();
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TimeManager::Update()
    {
        upImpl_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  �������x�̌v�����s��
     *  @param  �v���������֐�
     *  @return �v������( �b�P�� )
     *
     ****************************************************************/
    float C_TimeManager::MeasureProcess(const std::function<void()>& rFunction)
    {
        float startTime = GetTime();

        rFunction();

        float endTime = GetTime();

        return (endTime - startTime);
    }


    /*************************************************************//**
     *
     *  @brief  �t���[���X�L�b�v��L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TimeManager::EnableFrameSkip(bool validFlag)
    {
        upImpl_->EnableFrameSkip(validFlag);
    }


    /*************************************************************//**
     *
     *  @brief  FPS���擾����
     *  @param  �Ȃ�
     *  @return FPS
     *
     ****************************************************************/
    int16_t C_TimeManager::GetFps() const
    {
        return upImpl_->GetFps();
    }


    /*************************************************************//**
     *
     *  @brief  ���݂�FPS���擾����
     *  @param  �Ȃ�
     *  @return ���݂�FPS
     *
     ****************************************************************/
    float C_TimeManager::GetNowFps() const
    {
        return upImpl_->GetNowFps();
    }


    /*************************************************************//**
     *
     *  @brief  �v���O�������J�n���Ă���̎���
     *  @brief  ( �����ɂ�SDL�̏�������̎��� )���擾����
     *  @param  �Ȃ�
     *  @return �v���O�������J�n���Ă���̎���( �b�P�� )
     *
     ****************************************************************/
    float C_TimeManager::GetTime() const
    {
        return static_cast<float>(upImpl_->GetTime()) * s_RECIPROCAL_ONE_TOUSAND_MILLISECONDS * upImpl_->GetTimeScale();
    }


    /*************************************************************//**
     *
     *  @brief  ����( �o�� )���Ԃ��擾����
     *  @param  �Ȃ�
     *  @return ��������( �b�P�� )
     *
     ****************************************************************/
    float C_TimeManager::GetDeltaTime() const
    {
        return static_cast<float>(upImpl_->GetDeltaTime()) * s_RECIPROCAL_ONE_TOUSAND_MILLISECONDS * upImpl_->GetTimeScale();
    }


    /*************************************************************//**
     *
     *  @brief  �Q�[�����J�n���Ă���o�߂����t���[�������擾����
     *  @param  �Ȃ�
     *  @return �Q�[�����J�n���Ă���o�߂����t���[����
     *
     ****************************************************************/
    uint32_t C_TimeManager::GetFrameCount() const
    {
        return upImpl_->GetFrameCount();
    }


    /*************************************************************//**
     *
     *  @brief  �`��t���O���擾����
     *  @param  �Ȃ�
     *  @return �`��t���O
     *
     ****************************************************************/
    bool C_TimeManager::IsDrawFlag() const
    {
        return upImpl_->IsDrawFlag();
    }


    /*************************************************************//**
     *
     *  @brief  ���Ԃ̃X�P�[�����擾����
     *  @param  �Ȃ�
     *  @return ���Ԃ̃X�P�[��
     *
     ****************************************************************/
    float C_TimeManager::GetTimeScale() const
    {
        return upImpl_->GetTimeScale();
    }


    /*************************************************************//**
     *
     *  @brief  FPS��ݒ肷��
     *  @param  FPS
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TimeManager::SetFps(int16_t fps)
    {
        upImpl_->SetFps(fps);
    }


    /*************************************************************//**
     *
     *  @brief  ���Ԃ̃X�P�[����ݒ肷��
     *  @param  ���Ԃ̃X�P�[��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TimeManager::SetTimeScale(float timeScale)
    {
        upImpl_->SetTimeScale(timeScale);
    }


    /*************************************************************//**
     *
     *  @brief  �ҋ@���������邩���f����t���O��ݒ肷��
     *  @param  �ҋ@���������邩���f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_TimeManager::SetWaitFlag(bool waitFlag)
    {
        upImpl_->SetWaitFlag(waitFlag);
    }
}