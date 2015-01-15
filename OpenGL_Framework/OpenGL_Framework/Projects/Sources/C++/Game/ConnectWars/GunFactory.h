/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "BaseGun.h"
#include "../../Library/Debug/Helper/DebugHelper.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* �O���錾 */
    class C_Shooter;


    //-------------------------------------------------------------
    //!
    //! @brief �K���t�@�N�g���[( �C���^�[�t�F�[�X )
    //! @brief ���̐������s���N���X�̃C���^�[�t�F�[�X
    //!
    //-------------------------------------------------------------
    class IC_GunFactory
    {
    public:
        IC_GunFactory() = default;                                                                      // �R���X�g���N�^
        virtual ~IC_GunFactory() = default;                                                             // �f�X�g���N�^
        virtual C_BaseGun* Create(C_Shooter* pShooter, int32_t index, void* pData = nullptr) = 0;       // ��������
    };
}