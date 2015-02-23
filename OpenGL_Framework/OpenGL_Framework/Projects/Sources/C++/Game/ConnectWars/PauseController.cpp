/* �w�b�_�t�@�C�� */
#include "PauseController.h"
#include "LoadScene.h"
#include "LoadFunction.h"
#include "../../Library/Debug/Helper/DebugHelper.h"


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
    C_PauseController::C_PauseController(const std::string& rId, int32_t type) : C_SceneController(rId, type)
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PauseController::~C_PauseController()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PauseController::DoUpdate()
    {
        if (toTitleFlag_ == true)
        {
            auto pNextScece = newEx C_LoadScene;
            pSceneChanger_->ReplaceScene(pNextScece);

            pNextScece->SetNextSceneId(ID::Scene::s_pTITLE);
            pNextScece->SetLoadFunction(C_LoadFunction::s_LoadTitleData);
        }

    }


    /*************************************************************//**
     *
     *  @brief  ����J�̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_PauseController::DoDraw()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ���b�Z�[�W�������s��
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_PauseController::DoMessageProcess(const Telegram& rTelegram)
    {
        if (rTelegram.message_ == Message::s_pTO_TITLE_SCENE)
        {
            toTitleFlag_ = true;
        }
        else if (rTelegram.message_ == Message::s_pRESUME_GAME)
        {

        }
        else if (rTelegram.message_ == Message::s_pRESTART_GAME)
        {

        }
        return true;
    }
}