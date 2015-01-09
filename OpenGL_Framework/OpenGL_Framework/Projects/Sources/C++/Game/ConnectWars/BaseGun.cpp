/* �w�b�_�t�@�C�� */
#include "BaseGun.h"
#include "Shooter.h"
#include "BasePower.h"
#include "RigidBodyMoveLogic.h"
#include "ShotLogic.h"


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
    C_BaseGun::C_BaseGun(C_Shooter* pShooter) :

        // �ˌ���
        pShooter_(pShooter)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_BaseGun::~C_BaseGun()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �ˌ��̃��W�b�N��ݒ肷��
     *  @param  �ˌ��̃��W�b�N
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseGun::SetShotLogic(C_ShotLogic* pShotLogic)
    {
        upShotLogic_.reset(pShotLogic);
    }


    /*************************************************************//**
     *
     *  @brief  �ˌ��҂���̃I�t�Z�b�g��ݒ肷��
     *  @param  �ˌ��҂���̃I�t�Z�b�g
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseGun::SetOffsetFromShooter(const Physics::Vector3& rOffsetFromShooter)
    {
        offsetFromShooter_ = rOffsetFromShooter;
    }


    /*************************************************************//**
     *
     *  @brief  �e��ID��ݒ肷��
     *  @param  �e��ID
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseGun::SetBulletId(const std::string& rBulletId)
    {
        bulletId_ = rBulletId;
    }


    /*************************************************************//**
     *
     *  @brief  �e�̈ړ����W�b�N��ݒ肷��
     *  @param  �e�̈ړ����W�b�N
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseGun::SetBulletMoveLogic(C_RigidBodyMoveLogic* pBulletMoveLogic)
    {
        upBulletMoveLogic_.reset(pBulletMoveLogic);
    }


    /*************************************************************//**
     *
     *  @brief  �e�̍U���͂�ݒ肷��
     *  @param  �e�̍U����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseGun::SetBulletPower(C_BasePower* pBulletPower)
    {
        upBulletPower_.reset(pBulletPower);
    }
}
