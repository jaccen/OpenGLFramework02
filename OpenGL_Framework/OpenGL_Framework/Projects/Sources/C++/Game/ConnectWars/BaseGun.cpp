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
        pShooter_(pShooter),

        // �ˌ��҂���̃I�t�Z�b�g
        upOffsetFromShooter_(std::make_unique<Physics::Vector3>(0.0f, 0.0f, 0.0f)),

        // ����
        upDirection_(std::make_unique<Physics::Vector3>(0.0f, 0.0f, 0.0f))

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
     *  @brief  �ˌ��������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseGun::Shot()
    {
        DoShot();
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
        *upOffsetFromShooter_ = rOffsetFromShooter;
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


    /*************************************************************//**
     *
     *  @brief  ������ݒ肷��
     *  @param  ����
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseGun::SetDirection(const Physics::Vector3& rDirection)
    {
        *upDirection_ = rDirection;
    }


    /*************************************************************//**
     *
     *  @brief  ����������������t���O��ݒ肷��
     *  @param  ����������������t���O
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_BaseGun::SetAutoDirectionFlag(bool autoDirectionFlag)
    {
        autoDirectionFlag_ = autoDirectionFlag;
    }
}
