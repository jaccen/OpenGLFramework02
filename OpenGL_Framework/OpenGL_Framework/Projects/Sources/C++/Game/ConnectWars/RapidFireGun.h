/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "BaseGun.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"


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
    //! @brief ���s�b�h�t�@�C���[�K��
    //! @brief �A�ˏe��\���N���X
    //!
    //-------------------------------------------------------------
    class C_RapidFireGun : public C_BaseGun
    {
    public:
        C_RapidFireGun(C_Shooter* pShooter,                 // �R���X�g���N�^
                       int32_t rapidFireCount,
                       int32_t rapidFireInterval = 0);
        ~C_RapidFireGun() override;                         // �f�X�g���N�^
    private:
        int32_t shotCount_ = 0;                             ///< @brief �ˌ���
        int32_t rapidFireCount_ = 1;                        ///< @brief �A�ˉ�
        int32_t rapidFireInterval_ = 1;                     ///< @brief �A�ˊԊu
        Timer::C_FrameCounter frameCounter_;                ///< @brief �t���[���J�E���^

        void DoShot() override;                             // ����J�̎ˌ�����
    };
}