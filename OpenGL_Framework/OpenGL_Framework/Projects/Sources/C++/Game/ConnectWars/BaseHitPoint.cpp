/* �w�b�_�t�@�C�� */
#include "BaseHitPoint.h"


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
     *  @param  �ő�l
     *
     ****************************************************************/
    C_BaseHitPoint::C_BaseHitPoint(int32_t maxValue) :

        // �l
        value_(maxValue),

        // �ő�l
        maxValue_(maxValue)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BaseHitPoint::~C_BaseHitPoint()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �l��������Ԃɖ߂�
     *  @param  �ő�l
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseHitPoint::Reset()
    {
        SetValue(maxValue_);
    }


    /*************************************************************//**
     *
     *  @brief  �l�𑫂�
     *  @param  �l
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseHitPoint::Add(int32_t hitPoint)
    {
        value_ += hitPoint;

        if (value_ > maxValue_) SetValue(maxValue_);
    }


    /*************************************************************//**
     *
     *  @brief  �l������
     *  @param  �l
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseHitPoint::Subtract(int32_t hitPoint)
    {
        value_ -= hitPoint;

        if (value_ > maxValue_) SetValue(maxValue_);
    }


    /*************************************************************//**
     *
     *  @brief  �l���c���Ă��邩�m�F���s��
     *  @param  �Ȃ�
     *  @return �l���c���Ă���  �Ftrue
     *  @return �l���c���Ă��Ȃ��Ffalse
     *
     ****************************************************************/
    bool C_BaseHitPoint::CheckRemainValue() const
    {
        return value_ > 0;
    }


    /*************************************************************//**
     *
     *  @brief  �l���擾����
     *  @param  �Ȃ�
     *  @return �l
     *
     ****************************************************************/
    int32_t C_BaseHitPoint::GetValue() const
    {
        return value_;
    }


    /*************************************************************//**
     *
     *  @brief  �ő�l���擾����
     *  @param  �Ȃ�
     *  @return �ő�l
     *
     ****************************************************************/
    int32_t C_BaseHitPoint::GetMaxValue() const
    {
        return maxValue_;
    }


    /*************************************************************//**
     *
     *  @brief  �l��ݒ肷��
     *  @param  �l
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseHitPoint::SetValue(int32_t hitPoint)
    {
        (hitPoint <= maxValue_) ? (value_ = hitPoint) : SetValue(maxValue_);
    }


    /*************************************************************//**
     *
     *  @brief  �ő�l��ݒ肷��
     *  @param  �ő�l
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseHitPoint::SetMaxValue(int32_t maxValue)
    {
        maxValue_ = maxValue;
    }
}