/* �w�b�_�t�@�C�� */
#include "Shooter.h"
/*
#include "BasePlayer.h"
#include "BaseOption.h"
#include "BaseEnemy.h"
#include "BaseBullet.h"
*/


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
    C_Shooter::C_Shooter(const std::string& rId, int32_t type) : C_CollisionObject(rId, type)
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_Shooter::~C_Shooter()
    {
    }
}