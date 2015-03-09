/* �w�b�_�t�@�C�� */
#include "ShieldGenerator.h"
#include "BaseShield.h"
#include "../../Library/Task/System/General/GeneralTaskSystem.h"


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
    C_ShieldGenerator::C_ShieldGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_ShieldGenerator::~C_ShieldGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �����������s��
     *  @param  ID
     *  @param  ���W
     *  @param  �ˌ��҂̎��
     *  @return �V�[���h
     *
     ****************************************************************/
    ShieldPtr C_ShieldGenerator::Create(const std::string& rId,
                                        const Physics::Vector3& rPosition,
                                        int32_t shooterType,
                                        C_CollisionObject* pTarget)
    {
        // �V�[���h�𐶐�
        ShieldPtr pShield(pCreateFunctions_.at(rId)(shooterType, pTarget));

        // �e�ݒ���s��
        pShield->SetPosition(rPosition);
        pShield->AddStringToId(std::to_string(number));

        // �^�X�N�V�X�e���ɓo�^
        pTaskSystem_->Entry(pShield, Priority::Task::Update::s_shield, Priority::Task::Draw::s_shield);

        ++number;

        return pShield;
    }


    /*************************************************************//**
     *
     *  @brief  �֐��̓o�^���s��
     *  @param  ID
     *  @param  �����֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ShieldGenerator::RegistFunction( const std::string& rId, CreateFunction pCreateFunction)
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
    void C_ShieldGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }
}