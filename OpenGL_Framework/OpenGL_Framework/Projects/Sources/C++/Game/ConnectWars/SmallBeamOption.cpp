/* �w�b�_�t�@�C�� */
#include "SmallBeamOption.h"
#include "OptionDropState.h"


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
     *  @param  ���W
     *
     ****************************************************************/
    C_SmallBeamOption::C_SmallBeamOption(const std::string& rId, int32_t type) : C_BaseOption(rId, type)
    {
        // �q�b�g�|�C���g�𐶐�
        upHitPoint_ = std::make_unique<C_BaseHitPoint>(10000);
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_SmallBeamOption::~C_SmallBeamOption()
    {
    }
}