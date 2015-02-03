/* �w�b�_�t�@�C�� */
#include "ConnectMachine.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
#pragma region �ÓI�����o�ϐ��̏�����


    /* �����x���t���[�����̊Ԋu */
    uint32_t C_ConnectMachine::s_ownCrashDerayFrameInterval = 10;


#pragma endregion



    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  ID
     *  @param  ���
     *  @param  ���W
     *
     ****************************************************************/
    C_ConnectMachine::C_ConnectMachine(const std::string& rId, int32_t type) : C_Shooter(rId, type)
    {
        // �I�v�V����4���̃����������炩���ߊm�ۂ��Ă���
        pConnectOptionList_.reserve(4);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_ConnectMachine::~C_ConnectMachine()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �A�����Ă���I�v�V�����̃��X�g���擾����
     *  @param  �Ȃ�
     *  @return �A�����Ă���I�v�V�����̃��X�g
     *
     ****************************************************************/
    std::vector<C_BaseOption*>* C_ConnectMachine::GetConnectOptionList()
    {
        return &pConnectOptionList_;
    }


    /*************************************************************//**
     *
     *  @brief  ���̂��擾����
     *  @param  �Ȃ�
     *  @return ����
     *
     ****************************************************************/
    Physics::C_RigidBody* C_ConnectMachine::GetRigidBody() const
    {
        return upRigidBody_.get();
    }


    /*************************************************************//**
     *
     *  @brief  ���a���擾����
     *  @param  �Ȃ�
     *  @return ���a
     *
     ****************************************************************/
    float C_ConnectMachine::GetRadius() const
    {
        return radius_;
    }


    /*************************************************************//**
     *
     *  @brief  ���W���擾����
     *  @param  �Ȃ�
     *  @return ���W
     *
     ****************************************************************/
    const Physics::Vector3& C_ConnectMachine::GetPosition() const
    {
        return upRigidBody_->GetTransform().getOrigin();
    }


    /*************************************************************//**
     *
     *  @brief  ���W��ݒ肷��
     *  @param  ���W
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ConnectMachine::SetPosition(const Physics::Vector3& rPosition)
    {
        auto transform = upRigidBody_->GetTransform();
        transform.setOrigin(rPosition);
        upRigidBody_->SetTransform(transform);
    }


    /*************************************************************//**
     *
     *  @brief  ��]�ʂ��擾����
     *  @param  �Ȃ�
     *  @return ��]��
     *
     ****************************************************************/
    const Physics::Matrix3x3& C_ConnectMachine::GetRotation() const
    {
        return upRigidBody_->GetTransform().getBasis();
    }


    /*************************************************************//**
     *
     *  @brief  �����x���t���[�����̊Ԋu��ݒ肷��
     *  @param  �����x���t���[�����̊Ԋu
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_ConnectMachine::s_SetOwnCrashDerayFrameInterval(uint32_t ownCrashDerayFrameInterval)
    {
        s_ownCrashDerayFrameInterval = ownCrashDerayFrameInterval;
    }
}