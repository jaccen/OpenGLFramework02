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
    //! @brief �v���C���[�r�[���K���t�@�N�g���[
    //! @brief �v���C���[�̃r�[���e���쐬����N���X
    //!
    //-------------------------------------------------------------
    class C_PlayerBeamGunFactory : public IC_GunFactory
    {
    public:
        C_PlayerBeamGunFactory();                                                                       // �R���X�g���N�^
        ~C_PlayerBeamGunFactory() override;                                                             // �f�X�g���N�^
        C_BaseGun* Create(C_Shooter* pShooter, int32_t index, void* pData = nullptr) override;          // ��������
    };
}