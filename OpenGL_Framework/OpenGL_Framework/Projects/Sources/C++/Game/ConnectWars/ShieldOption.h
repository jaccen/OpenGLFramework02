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
    //! @brief �V�[���h�I�v�V����
    //! @brief �V�[���h�𒣂�I�v�V������\���N���X
    //!
    //-------------------------------------------------------------
    class C_ShieldOption : public C_BaseOption
    {
    public:
        C_ShieldOption(const std::string& rId, int32_t type);           // �R���X�g���N�^
        virtual ~C_ShieldOption() override;                             // �f�X�g���N�^
        void ConnectEffect() override;                                  // �A�����̌���
    private:
        void DoDraw() override;                                         // ����J�̕`�揈��
    };
}