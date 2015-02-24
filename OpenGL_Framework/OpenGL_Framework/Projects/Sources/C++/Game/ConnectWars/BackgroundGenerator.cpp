/* �w�b�_�t�@�C�� */
#include "BackgroundGenerator.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"
#include "BaseBackground.h"


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
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BackgroundGenerator::C_BackgroundGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BackgroundGenerator::~C_BackgroundGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �����������s��
     *  @param  ID
     *  @param  ���W
     *  @param  �����t���[����
     *  @return �w�i
     *
     ****************************************************************/
    BackgroundPtr C_BackgroundGenerator::Create(const std::string& rId, const Vector3& rPosition, int32_t lifeFrame)
    {
        // �w�i�𐶐����A���W��ݒ�
        BackgroundPtr pBackground(pCreateFunctions_.at(rId)());
        pBackground->SetPosition(rPosition);
        pBackground->AddStringToId(std::to_string(number));
        pBackground->SetLifeFrame(lifeFrame);

        // �^�X�N�V�X�e���ɓo�^
        pTaskSystem_->Entry(pBackground, Priority::Task::Update::s_background, Priority::Task::Draw::s_background);

        ++number;
        
        return pBackground;
    }


    /*************************************************************//**
     *
     *  @brief  �֐��̓o�^���s��
     *  @param  ID
     *  @param  �����֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BackgroundGenerator::RegistFunction(const std::string& rId, CreateFunction pCreateFunction)
    {
        pCreateFunctions_.emplace(rId, pCreateFunction);
    }


    /*************************************************************//**
     *
     *  @brief  �^�X�N�V�X�e����ݒ肷��
     *  @param  �^�X�N�V�X�e��
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BackgroundGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }


    /*************************************************************//**
     *
     *  @brief  �w�i�f�[�^��ݒ肷��
     *  @param  �w�i�f�[�^
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BackgroundGenerator::SetBackgroundData(const JSON::JsonObjectPtr& prBackgroundData)
    {
        pBackgroundData_ = prBackgroundData;
    }
}