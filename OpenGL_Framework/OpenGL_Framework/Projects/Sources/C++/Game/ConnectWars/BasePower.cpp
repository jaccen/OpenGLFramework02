/* �w�b�_�t�@�C�� */
#include "BasePower.h"


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
     *  @param  �l
     *
     ****************************************************************/
    C_BasePower::C_BasePower(int32_t value) :

        // �l
        value_(value)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BasePower::~C_BasePower()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �l��������
     *  @param  �l
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePower::Add(int32_t value)
    {
        value_ += value;
    }


    /*************************************************************//**
     *
     *  @brief  �l������
     *  @param  �l
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePower::Subtract(int32_t value)
    {
        value_ -= value;
    }


    /*************************************************************//**
     *
     *  @brief  �l���擾����
     *  @param  �Ȃ�
     *  @return �l
     *
     ****************************************************************/
    int32_t C_BasePower::GetValue() const
    {
        return value_;
    }


    /*************************************************************//**
     *
     *  @brief  �l��ݒ肷��
     *  @param  �l
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BasePower::SetValue(int32_t value)
    {
        value_ = value;
    }
}