/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "GunFactory.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief �I�v�V�����X���[���r�[���K���t�@�N�g���[
    //! @brief �I�v�V�����̏������r�[���e���쐬����N���X
    //!
    //-------------------------------------------------------------
    class C_OptionSmallBeamGunFactory : public IC_GunFactory
    {
    public:
        C_OptionSmallBeamGunFactory();                                                                  // �R���X�g���N�^
        ~C_OptionSmallBeamGunFactory() override;                                                        // �f�X�g���N�^
        C_BaseGun* Create(C_Shooter* pShooter, int32_t index, void* pData = nullptr) override;          // ��������
    };
}