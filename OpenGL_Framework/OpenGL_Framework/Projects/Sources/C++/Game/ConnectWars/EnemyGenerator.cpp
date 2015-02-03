/* �w�b�_�t�@�C�� */
#include "EnemyGenerator.h"
#include "BaseEnemy.h"
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
    C_EnemyGenerator::C_EnemyGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_EnemyGenerator::~C_EnemyGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �����������s��
     *  @param  ID
     *  @param  ���W
     *  @return �ˌ��҂̎��
     *
     ****************************************************************/
    EnemyPtr C_EnemyGenerator::Create(const std::string& rId)
    {
        // �G�𐶐�
        EnemyPtr pEnemy(pCreateFunctions_.at(rId)());

        // �e�ݒ���s��
        pEnemy->SetCreateDataWithJson(&(*pEnemyData_)["EnemyData"][0]);
        pEnemy->AddStringToId(std::to_string(number));

        // �^�X�N�V�X�e���ɓo�^
        pTaskSystem_->Entry(pEnemy, Priority::Task::Update::s_bullet, Priority::Task::Draw::s_bullet);

        ++number;

        return pEnemy;
    }


    /*************************************************************//**
     *
     *  @brief  �֐��̓o�^���s��
     *  @param  ID
     *  @param  �����֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EnemyGenerator::RegistFunction( const std::string& rId, CreateFunction pCreateFunction)
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
    void C_EnemyGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }


    /*************************************************************//**
     *
     *  @brief  �G�f�[�^��ݒ肷��
     *  @param  �G�f�[�^
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_EnemyGenerator::SetEnemyData(const JSON::JsonObjectPtr& prEnemyData)
    {
        pEnemyData_ = prEnemyData;
    }
}