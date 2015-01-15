/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "BaseOption.h"


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
    //! @brief �X�s�[�h�A�b�v�I�v�V����
    //! @brief �ړ����x���グ��I�v�V������\���N���X
    //!
    //-------------------------------------------------------------
    class C_SpeedUpOption : public C_BaseOption
    {
    public:
        C_SpeedUpOption(const std::string& rId, int32_t type);          // �R���X�g���N�^
        virtual ~C_SpeedUpOption() override;                            // �f�X�g���N�^
        void ConnectEffect() override;                                  // �A�����̌���
        void ResetEffect() override;                                    // ���ʂ����Z�b�g
    private:
        void DoDraw() override;                                         // ����J�̕`�揈��
    };
}