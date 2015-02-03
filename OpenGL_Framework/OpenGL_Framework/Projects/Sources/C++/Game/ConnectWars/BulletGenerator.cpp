/* �w�b�_�t�@�C�� */
#include "BulletGenerator.h"
#include "BaseBullet.h"
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
    C_BulletGenerator::C_BulletGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BulletGenerator::~C_BulletGenerator()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �����������s��
     *  @param  ID
     *  @param  ���W
     *  @param  �p���[
     *  @param  �ړ��̃��W�b�N
     *  @return �ˌ��҂̎��
     *
     ****************************************************************/
    BulletPtr C_BulletGenerator::Create(const std::string& rId,
                                        const Physics::Vector3& rPosition,
                                        int32_t power,
                                        C_RigidBodyMoveLogic* pMoveLogic,
                                        int32_t shooterType)
    {
        // �e�𐶐�
        BulletPtr pBullet(pCreateFunctions_.at(rId)(shooterType));

        // �e�ݒ���s��
        pBullet->SetMoveLogic(pMoveLogic);
        pBullet->GetPower()->SetValue(power);
        pBullet->SetPosition(rPosition);
        pBullet->AddStringToId(std::to_string(number));

        // �^�X�N�V�X�e���ɓo�^
        pTaskSystem_->Entry(pBullet, Priority::Task::Update::s_bullet, Priority::Task::Draw::s_bullet);

        ++number;

        return pBullet;
    }


    /*************************************************************//**
     *
     *  @brief  �֐��̓o�^���s��
     *  @param  ID
     *  @param  �����֐�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BulletGenerator::RegistFunction( const std::string& rId, CreateFunction pCreateFunction)
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
    void C_BulletGenerator::SetTaskSystem(Task::C_GeneralTaskSystem* pTaskSystem)
    {
        pTaskSystem_ = pTaskSystem;
    }
}