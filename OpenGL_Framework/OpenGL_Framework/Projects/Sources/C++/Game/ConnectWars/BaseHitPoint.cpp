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
     *  @param  �ő�q�b�g�|�C���g
     *
     ****************************************************************/
    C_BaseHitPoint::C_BaseHitPoint(int32_t maxHitPoint) :

        // �q�b�g�|�C���g
        hitPoint_(maxHitPoint),

        // �ő�q�b�g�|�C���g
        maxHitPoint_(maxHitPoint)

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
     *  @brief  �q�b�g�|�C���g��������Ԃɖ߂�
     *  @param  �ő�q�b�g�|�C���g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseHitPoint::Reset()
    {
        SetHitPoint(maxHitPoint_);
    }


    /*************************************************************//**
     *
     *  @brief  �q�b�g�|�C���g��������
     *  @param  �q�b�g�|�C���g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseHitPoint::Add(int32_t hitPoint)
    {
        hitPoint_ += hitPoint;

        if (hitPoint_ > maxHitPoint_) SetHitPoint(maxHitPoint_);
    }


    /*************************************************************//**
     *
     *  @brief  �q�b�g�|�C���g���c���Ă��邩�m�F���s��
     *  @param  �Ȃ�
     *  @return �q�b�g�|�C���g���c���Ă���  �Ftrue
     *  @return �q�b�g�|�C���g���c���Ă��Ȃ��Ffalse
     *
     ****************************************************************/
    bool C_BaseHitPoint::CheckRemainHitPoint() const
    {
        return hitPoint_ > 0;
    }


    /*************************************************************//**
     *
     *  @brief  �q�b�g�|�C���g���擾����
     *  @param  �Ȃ�
     *  @return �q�b�g�|�C���g
     *
     ****************************************************************/
    int32_t C_BaseHitPoint::GetHitPoint() const
    {
        return hitPoint_;
    }


    /*************************************************************//**
     *
     *  @brief  �ő�q�b�g�|�C���g���擾����
     *  @param  �Ȃ�
     *  @return �ő�q�b�g�|�C���g
     *
     ****************************************************************/
    int32_t C_BaseHitPoint::GetMaxHitPoint() const
    {
        return maxHitPoint_;
    }


    /*************************************************************//**
     *
     *  @brief  �q�b�g�|�C���g��ݒ肷��
     *  @param  �q�b�g�|�C���g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseHitPoint::SetHitPoint(int32_t hitPoint)
    {
        (hitPoint <= maxHitPoint_) ? (hitPoint_ = hitPoint) : SetHitPoint(maxHitPoint_);
    }


    /*************************************************************//**
     *
     *  @brief  �ő�q�b�g�|�C���g��ݒ肷��
     *  @param  �ő�q�b�g�|�C���g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseHitPoint::SetMaxHitPoint(int32_t maxHitPoint)
    {
        maxHitPoint_ = maxHitPoint;
    }
}