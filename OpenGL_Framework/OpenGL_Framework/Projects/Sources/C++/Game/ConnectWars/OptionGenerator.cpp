/* �w�b�_�t�@�C�� */
#include "OptionGenerator.h"
#include "../../Library/GameObject/Manager/GameObjectManager.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"
#include "BaseOption.h"


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
    C_OptionGenerator::C_OptionGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_OptionGenerator::~C_OptionGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �����������s��
     *  @param  ID
     *  @param  ���W
     *  @return �I�v�V����
     *
     ****************************************************************/
    OptionPtr C_OptionGenerator::Create(const std::string& rId, const Physics::Vector3& rPosition)
    {
        // �I�v�V�����𐶐����A���W��ݒ�
        OptionPtr pOption(pCreateFunctions_.at(rId)());
        pOption->SetPosition(rPosition);
        pOption->AddStringToId(std::to_string(number));

        // �^�X�N�V�X�e���ɓo�^
        pTaskSystem_->Entry(pOption, Priority::Task::Update::s_option, Priority::Task::Draw::s_option);

        // �Q�[���I�u�W�F�N�g�}�l�[�W���[�ɓo�^
        GameObject::C_GameObjectManager::s_GetInstance()->Entry(pOption);

        ++number;
        
        return pOption;
    }


    /*************************************************************//**
     *
     *  @brief  �֐��̓o�^���s��
     *  @param  ID
     *  @param  �����֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_OptionGenerator::RegistFunction(const std::string& rId, CreateFunction pCreateFunction)
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
    void C_OptionGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }
}