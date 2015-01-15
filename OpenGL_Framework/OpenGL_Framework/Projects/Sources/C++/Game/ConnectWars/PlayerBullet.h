/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "BaseBullet.h"
#include "../../Library/Sprite/Creater/SpriteCreater.h"


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
    //! @brief �v���C���[�r�[���o���b�g
    //! @brief �v���C���[�̃r�[���e��\���N���X
    //!
    //-------------------------------------------------------------
    class C_PlayerBeamBullet : public C_BaseBullet
    {
    public:
        C_PlayerBeamBullet(const std::string& rId,                      // �R���X�g���N�^
                           int32_t type,
                           int32_t shooterType);               
        ~C_PlayerBeamBullet() override;                                 // �f�X�g���N�^
    private:
        Sprite::SpriteCreaterWeakPtr wpSpriteCreater_;                  ///< @brief �X�v���C�g�N���G�C�^�[
        Sprite::S_CreateData spriteCreateData_;                         ///< @brief �X�v���C�g�̍쐬���

        void DoDraw() override;                                         // ����J�̕`�揈��
    };
}