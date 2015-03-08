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
    //! @brief �I�v�V�����G�N�X�v���[�V�����G�t�F�N�g
    //! @brief �I�v�V�����̔����̃G�t�F�N�g
    //!
    //-------------------------------------------------------------
    class C_OptionExplosionEffect : public C_BaseEffect
    {
    public:
        C_OptionExplosionEffect(const std::string& rId, int32_t type);              // �R���X�g���N�^
        virtual ~C_OptionExplosionEffect() override;                                // �f�X�g���N�^
    private:
        Particle::ParticleSystemWeakPtr wpCircleParticleSystem_;                    ///< @brief �~�̃p�[�e�B�N���V�X�e��
        Particle::ParticleSystemWeakPtr wpSmokeParticleSystem_;                     ///< @brief ���̃p�[�e�B�N���V�X�e��

        void DoUpdate() override;                                                   // ����J�̍X�V����
        void DoDraw() override;                                                     // ����J�̕`�揈��
        bool DoMessageProcess(const Telegram& rTelegram) override;                  // ����J�̃��b�Z�[�W����
    };
}