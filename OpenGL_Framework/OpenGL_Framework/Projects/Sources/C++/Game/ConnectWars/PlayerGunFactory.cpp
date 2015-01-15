/* �w�b�_�t�@�C�� */
#include "PlayerGunFactory.h"
#include "NormalGun.h"
#include "InputShotLogic.h"
#include "BasePower.h"
#include "BasePlayer.h"
#include "RigidBodyStraightMoveLogic.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"


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
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PlayerBeamGunFactory::C_PlayerBeamGunFactory()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_PlayerBeamGunFactory::~C_PlayerBeamGunFactory()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �����������s��
     *  @param  �ˌ���
     *  @param  �C���f�b�N�X
     *  @param  ���
     *  @return �e
     *
     ****************************************************************/
    C_BaseGun* C_PlayerBeamGunFactory::Create(C_Shooter* pShooter, int32_t index, void* pData)
    {
        // �v���C���[�̏����擾
        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pNORMAL_PLAYER));
        auto pPlayerData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pNORMAL_PLAYER).get();

        auto pGun = newEx C_NormalGun(pShooter);

        auto direction = Physics::Vector3(static_cast<float>((*pPlayerData)["GunDatas"][index]["Direction"][0].GetValue<JSON::Real>()),
                                          static_cast<float>((*pPlayerData)["GunDatas"][index]["Direction"][1].GetValue<JSON::Real>()),
                                          static_cast<float>((*pPlayerData)["GunDatas"][index]["Direction"][2].GetValue<JSON::Real>()));

        auto offsetFromShooter = Physics::Vector3(static_cast<float>((*pPlayerData)["GunDatas"][index]["OffsetFromShooter"][0].GetValue<JSON::Real>()),
                                                  static_cast<float>((*pPlayerData)["GunDatas"][index]["OffsetFromShooter"][1].GetValue<JSON::Real>()),
                                                  static_cast<float>((*pPlayerData)["GunDatas"][index]["OffsetFromShooter"][2].GetValue<JSON::Real>()));

        pGun->SetShotLogic(newEx C_InputShotLogic((*pPlayerData)["GunDatas"][index]["ShotInterval"].GetValue<JSON::Integer>()));
        pGun->SetBulletId((*pPlayerData)["GunDatas"][index]["BulletId"].GetValue<JSON::String>());
        pGun->SetBulletPower(newEx C_BasePower((*pPlayerData)["GunDatas"][index]["BulletPower"].GetValue<JSON::Integer>()));



        pGun->SetBulletMoveLogic(newEx C_RigidBodyStraightMoveLogic(direction * static_cast<float>((*pPlayerData)["GunDatas"][index]["BulletMovement"].GetValue<JSON::Real>())));
        pGun->SetOffsetFromShooter(offsetFromShooter);
        pGun->SetDirection(direction);

        return pGun;
    }
}