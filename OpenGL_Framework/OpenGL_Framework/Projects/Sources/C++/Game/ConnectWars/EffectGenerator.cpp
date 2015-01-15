/* �w�b�_�t�@�C�� */
#include "EffectGenerator.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"
#include "BaseEffect.h"


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
    C_EffectGenerator::C_EffectGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_EffectGenerator::~C_EffectGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �����������s��
     *  @param  ID
     *  @param  ���W
     *  @return �G�t�F�N�g
     *
     ****************************************************************/
    EffectPtr C_EffectGenerator::Create(const std::string& rId, const Vector3& rPosition)
    {
        // �G�t�F�N�g�𐶐����A���W��ݒ�
        EffectPtr pEffect(pCreateFunctions_.at(rId)());
        pEffect->SetPosition(rPosition);
        pEffect->AddStringToId(std::to_string(number));

        // �^�X�N�V�X�e���ɓo�^
        pTaskSystem_->Entry(pEffect, Priority::Task::Update::s_effect, Priority::Task::Draw::s_effect);

        ++number;
        
        return pEffect;
    }


    /*************************************************************//**
     *
     *  @brief  �֐��̓o�^���s��
     *  @param  ID
     *  @param  �����֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EffectGenerator::RegistFunction(const std::string& rId, CreateFunction pCreateFunction)
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
    void C_EffectGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }
}