/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "BasePlayer.h"


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
    //! @brief �m�[�}���v���C���[
    //! @brief �ʏ�̃v���C���[��\���N���X
    //!
    //-------------------------------------------------------------
    class C_NormalPlayer : public C_BasePlayer
    {
    public:
        C_NormalPlayer(const std::string& rId, int32_t type);                   // �R���X�g���N�^
        ~C_NormalPlayer() override;                                             // �f�X�g���N�^
    private:
    };
}