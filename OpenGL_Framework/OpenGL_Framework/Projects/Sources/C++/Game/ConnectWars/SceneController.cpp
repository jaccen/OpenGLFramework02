/* �w�b�_�t�@�C�� */
#include "SceneController.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  ID
     *  @param  ���
     *
     ****************************************************************/
    C_SceneController::C_SceneController(const std::string& rId, int32_t type) : C_GameObject(rId, type)
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SceneController::~C_SceneController()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �X�V�������s��
     *  @param  �Ȃ�
     *  @return �^�X�N���s�Ftrue
     *  @return �^�X�N�I���Ffalse
     *
     ****************************************************************/
    bool C_SceneController::Update()
    {
        if (waitFlag_ == false) frameCounter_.CountUp();

        DoUpdate();

        return C_GameObject::existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  �`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SceneController::Draw()
    {
        DoDraw();
    }


    /*************************************************************//**
     *
     *  @brief  ���b�Z�[�W�������s��
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_SceneController::MessageProcess(const Telegram& rTelegram)
    {
        return DoMessageProcess(rTelegram);
    }


    /*************************************************************//**
     *
     *  @brief  �ҋ@��Ԃ�L��������
     *  @param  �L�������f����t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SceneController::EnableWait(bool validFlag)
    {
        waitFlag_ = validFlag;
    }


    /*************************************************************//**
     *
     *  @brief  ���݂̃t���[�������擾����
     *  @param  �Ȃ�
     *  @return ���݂̃t���[����
     *
     ****************************************************************/
    int32_t C_SceneController::GetNowFrame() const
    {
        return frameCounter_.GetCount();
    }


    /*************************************************************//**
     *
     *  @brief  �V�[���`�F���W���[��ݒ肷��
     *  @param  �V�[���`�F���W���[
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_SceneController::SetSceneChanger(Scene::IC_SceneChanger* pSceneChanger)
    {
        pSceneChanger_ = pSceneChanger;
    }
}