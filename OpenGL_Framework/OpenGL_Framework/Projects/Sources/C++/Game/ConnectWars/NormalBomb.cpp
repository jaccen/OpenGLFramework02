/* �w�b�_�t�@�C�� */
#include "NormalBomb.h"
#include "BasePower.h"
#include "BaseOption.h"


//-------------------------------------------------------------
//!
//! @brief �R�l�N�g�E�H�[�Y
//! @brief �R�l�N�g�E�H�[�Y�֘A�̖��O���
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  �R���X�g���N�^
     *  @param  ID
     *  @param  ���
     *
     ****************************************************************/
    C_NormalBomb::C_NormalBomb(const std::string& rId, int32_t type) : C_BaseBomb(rId, type)
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_NormalBomb::~C_NormalBomb()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ����J�̍X�V�������s��
     *  @param  �Ȃ�
     *  @return �Ȃ�
     *
     ****************************************************************/
    void C_NormalBomb::DoUpdate()
    {
        if (frameCounter_.GetCount() >= stayFrame_) existenceFlag_ = false;
    }
}