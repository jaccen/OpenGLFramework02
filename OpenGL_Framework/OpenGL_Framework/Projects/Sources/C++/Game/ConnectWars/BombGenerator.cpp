/* �w�b�_�t�@�C�� */
#include "BombGenerator.h"
#include "BaseBomb.h"
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
    C_BombGenerator::C_BombGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BombGenerator::~C_BombGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �����������s��
     *  @param  ID
     *  @param  ���W
     *  @param  ���x��
     *  @return �{��
     *
     ****************************************************************/
    BombPtr C_BombGenerator::Create(const std::string& rId, const Physics::Vector3& rPosition, int32_t level)
    {
        // �G�𐶐�
        BombPtr pBomb(pCreateFunctions_.at(rId)());

        // �e�ݒ���s��
        pBomb->SetPosition(rPosition);
        pBomb->SetLevel(level);

        // �^�X�N�V�X�e���ɓo�^
        pTaskSystem_->Entry(pBomb, Priority::Task::Update::s_bomb, Priority::Task::Draw::s_bomb);
        ++number;

        return pBomb;
    }


    /*************************************************************//**
     *
     *  @brief  �֐��̓o�^���s��
     *  @param  ID
     *  @param  �����֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BombGenerator::RegistFunction( const std::string& rId, CreateFunction pCreateFunction)
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
    void C_BombGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }
}