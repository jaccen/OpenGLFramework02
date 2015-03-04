/* �w�b�_�t�@�C�� */
#include "BackgroundMoveLogic.h"


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
     *  @brief  �������s��
     *  @param  ����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BackgroundMoveLogic::Process(Background* pBackground)
    {
        DoProcess(pBackground);
    }


    /*************************************************************//**
     *
     *  @brief  ���x�̐ݒ������
     *  @param  ���x
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BackgroundMoveLogic::SetVelocity(const Vector3& rVelocity)
    {
        velocity_ = rVelocity;
    }


    /*************************************************************//**
     *
     *  @brief  �����x�̐ݒ������
     *  @param  �����x
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BackgroundMoveLogic::SetAccelaration(const Vector3& rAccelaration)
    {
        accelaration_ = rAccelaration;
    }


    /*************************************************************//**
     *
     *  @brief  ��]���x�̐ݒ������
     *  @param  ��]���x
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BackgroundMoveLogic::SetRotationVelocity(const Vector3& rRotationVelocity)
    {
        rotationVelocity_ = rRotationVelocity;
    }


    /*************************************************************//**
     *
     *  @brief  ��]�����x�̐ݒ������
     *  @param  ��]�����x
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BackgroundMoveLogic::SetRotationAccelaration(const Vector3& rRotationAccelaration)
    {
        rotationAccelaration_ = rRotationAccelaration;
    }
}