/* �w�b�_�t�@�C�� */
#include "NormalGun.h"
#include "Shooter.h"
#include "ShotLogic.h"
#include "BulletGenerator.h"
#include "RigidBodyMoveLogic.h"


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
     *  @param  �ˌ���
     *
     ****************************************************************/
    C_NormalGun::C_NormalGun(C_Shooter* pShooter) : C_BaseGun(pShooter)
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_NormalGun::~C_NormalGun()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̎ˌ��������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_NormalGun::DoShot()
    {
        if (upShotLogic_->Process() == true)
        {
            auto pBulletMoveLogic = upBulletMoveLogic_->DeepCopy();

            if (autoDirectionFlag_ == true)
            {
                auto bulletDirection = pShooter_->GetRotation() * (*upDirection_);
                pBulletMoveLogic->SetDirection(bulletDirection);
            }

            C_BulletGenerator::s_GetInstance()->Create(bulletId_, 
                                                       pShooter_->GetPosition() + (*upOffsetFromShooter_),
                                                       upBulletPower_->GetValue(),
                                                       pBulletMoveLogic,
                                                       pShooter_->GetType());
        }
    }
}