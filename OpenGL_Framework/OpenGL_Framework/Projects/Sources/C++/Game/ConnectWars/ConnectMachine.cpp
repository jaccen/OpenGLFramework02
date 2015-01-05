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
}