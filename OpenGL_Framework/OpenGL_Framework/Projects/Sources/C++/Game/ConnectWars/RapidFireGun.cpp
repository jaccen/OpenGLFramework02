/* �w�b�_�t�@�C�� */
#include "RapidFireGun.h"
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
     *  @param  �A�ˉ�
     *  @param  �A�ˊԊu
     *
     ****************************************************************/
    C_RapidFireGun::C_RapidFireGun(C_Shooter* pShooter,
                                   int32_t rapidFireCount,
                                   int32_t rapidFireInterval) : C_BaseGun(pShooter),

        // �A�ˉ�
        rapidFireCount_(rapidFireCount),

        // �A�ˊԊu
        rapidFireInterval_(rapidFireInterval)

    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_RapidFireGun::~C_RapidFireGun()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̎ˌ��������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_RapidFireGun::DoShot()
    {
        if (upShotLogic_->Process() == true) shotCount_ = 0;

        if (shotCount_ < rapidFireCount_)
        {
            if (frameCounter_.GetCount() == rapidFireInterval_ || shotCount_ == 0)
            {
                ++shotCount_;

                // ���Z�b�g
                frameCounter_.Reset();
            }
            else
            {
                // �J�E���g�A�b�v
                frameCounter_.CountUp();
            }
        }
    }
}