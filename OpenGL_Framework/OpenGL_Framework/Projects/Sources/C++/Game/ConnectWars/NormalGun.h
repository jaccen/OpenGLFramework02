/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "BaseGun.h"


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
    //! @brief �m�[�}���K��
    //! @brief �ʏ�̏e��\���N���X
    //!
    //-------------------------------------------------------------
    class C_NormalGun : public C_BaseGun
    {
    public:
        C_NormalGun(C_Shooter* pShooter);       // �R���X�g���N�^
        ~C_NormalGun() override;                // �f�X�g���N�^
    private:
        void DoShot() override;                 ///< @brief ����J�̎ˌ�����
    };
}