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
    /* �O���錾 */
    class C_BaseGun;


    //-------------------------------------------------------------
    //!
    //! @brief �X���[���r�[���I�v�V����
    //! @brief �������r�[���e�����I�v�V������\���N���X
    //!
    //-------------------------------------------------------------
    class C_SmallBeamOption : public C_BaseOption
    {
    public:
        C_SmallBeamOption(const std::string& rId, int32_t type);            // �R���X�g���N�^
        virtual ~C_SmallBeamOption() override;                              // �f�X�g���N�^
    };
}