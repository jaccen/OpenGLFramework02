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
    //! @brief �I�v�V�����X���[���r�[���o���b�g
    //! @brief �I�v�V�����̏������r�[���e��\���N���X
    //!
    //-------------------------------------------------------------
    class C_OptionSmallBeamBullet : public C_BaseBullet
    {
    public:
        C_OptionSmallBeamBullet(const std::string& rId,                 // �R���X�g���N�^
                                int32_t type,
                                int32_t shooterType);               
        ~C_OptionSmallBeamBullet() override;                            // �f�X�g���N�^
    private:
        Sprite::SpriteCreaterWeakPtr wpSpriteCreater_;                  ///< @brief �X�v���C�g�N���G�C�^�[
        Sprite::S_CreateData spriteCreateData_;                         ///< @brief �X�v���C�g�̍쐬���

        void DoDraw() override;                                         // ����J�̕`�揈��
    };
}