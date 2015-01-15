/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "BaseEffect.h"
#include "../../Library/Particle/System/ParticleSystem.h"


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
    //! @brief �{���`���[�W�G�t�F�N�g
    //! @brief �{���̃`���[�W�̃G�t�F�N�g
    //!
    //-------------------------------------------------------------
    class C_BombChargeEffect : public C_BaseEffect
    {
    public:
        C_BombChargeEffect(const std::string& rId, int32_t type);           // �R���X�g���N�^
        virtual ~C_BombChargeEffect() override;                             // �f�X�g���N�^
    private:
        Particle::ParticleSystemWeakPtr wpCircleParticleSystem_;            ///< @brief �~�̃p�[�e�B�N���V�X�e��
        Particle::ParticleSystemWeakPtr wpRingParticleSystem_;              ///< @brief �ւ̃p�[�e�B�N���V�X�e��

        void DoUpdate() override;                                           // ����J�̍X�V����
        void DoDraw() override;                                             // ����J�̕`�揈��
        bool DoMessageProcess(const Telegram& rTelegram) override;          // ����J�̃��b�Z�[�W����
    };
}