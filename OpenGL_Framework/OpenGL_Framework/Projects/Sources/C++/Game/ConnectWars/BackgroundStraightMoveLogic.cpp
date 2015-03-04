#include "BackgroundStraightMoveLogic.h"


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
    C_BackgroundStraightMoveLogic::C_BackgroundStraightMoveLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BackgroundStraightMoveLogic::~C_BackgroundStraightMoveLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̏������s��
     *  @param  ����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BackgroundStraightMoveLogic::DoProcess(C_BaseBackground* pBackground)
    {
        rotationVelocity_ += rotationAccelaration_;
        velocity_ += accelaration_;

        pBackground->SetPosition(pBackground->GetPosition() + velocity_);
        pBackground->SetRotation(pBackground->GetRotation() + rotationVelocity_);
    }
}