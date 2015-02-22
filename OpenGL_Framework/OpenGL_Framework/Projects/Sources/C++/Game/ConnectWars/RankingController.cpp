/* �w�b�_�t�@�C�� */
#include "RankingController.h"
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
    C_RankingController::C_RankingController(const std::string& rId, int32_t type) : C_SceneController(rId, type)
    {
        upFade_ = std::make_unique<C_Fade>(ID::GameObject::s_pFADE, eGameObjectType::TYPE_FADE, 20, true);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_RankingController::~C_RankingController()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RankingController::DoUpdate()
    {
        if (toTitleFlag_ == true)
        {
            if (upFade_->IsFinishFadeOutFlag() == true)
            {
                auto pNextScece = newEx C_LoadScene;
                pSceneChanger_->ReplaceScene(pNextScece);

                pNextScece->SetNextSceneId(ID::Scene::s_pTITLE);
                pNextScece->SetLoadFunction(C_LoadFunction::s_LoadTitleData);
            }
        }

        upFade_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̕`�揈�����s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RankingController::DoDraw()
    {
        upFade_->Draw();
    }


    /*************************************************************//**
     *
     *  @brief  ���b�Z�[�W�������s��
     *  @param  �e���O����
     *  @return ����I���Ftrue
     *  @return �ُ�I���Ffalse
     *
     ****************************************************************/
    bool C_RankingController::DoMessageProcess(const Telegram& rTelegram)
    {
        if (Message::s_pTO_TITLE_SCENE)
        {
            toTitleFlag_ = true;
           
            assert(upFade_);
            upFade_->FadeOut();
        }

        return true;
    }
}