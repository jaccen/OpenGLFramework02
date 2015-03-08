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
    //! @brief �I�v�V�����I�E���N���b�V���G�t�F�N�g01
    //! @brief �I�v�V�����̎����G�t�F�N�g01
    //!
    //-------------------------------------------------------------
    class C_OptionOwnCrashEffect01 : public C_BaseEffect
    {
    public:
        C_OptionOwnCrashEffect01(const std::string& rId, int32_t type);                 // �R���X�g���N�^
        virtual ~C_OptionOwnCrashEffect01() override;                                   // �f�X�g���N�^
    private:
        Particle::ParticleSystemWeakPtr wpCircleParticleSystem_;                        ///< @brief �~�̃p�[�e�B�N���V�X�e��
        Particle::ParticleSystemWeakPtr wpSmokeParticleSystem_;                         ///< @brief ���̃p�[�e�B�N���V�X�e��

        void DoUpdate() override;                                                       // ����J�̍X�V����
        void DoDraw() override;                                                         // ����J�̕`�揈��
        bool DoMessageProcess(const Telegram& rTelegram) override;                      // ����J�̃��b�Z�[�W����
    };
}