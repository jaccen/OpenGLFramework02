/* �w�b�_�t�@�C�� */
#include "OptionGunFactory.h"
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
    C_OptionSmallBeamGunFactory::C_OptionSmallBeamGunFactory()
    {
    }


    /*************************************************************//**
     *
     *  @brief  �f�X�g���N�^
     *  @param  �Ȃ�
     *
     ****************************************************************/
    C_OptionSmallBeamGunFactory::~C_OptionSmallBeamGunFactory()
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
    C_BaseGun* C_OptionSmallBeamGunFactory::Create(C_Shooter* pShooter, int32_t index, void* pData)
    {
        // �v���C���[�̏����擾
        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSMALL_BEAM_OPTION));
        auto pOptionData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSMALL_BEAM_OPTION).get();

        auto pGun = newEx C_NormalGun(pShooter);

        auto direction = Physics::Vector3(static_cast<float>((*pOptionData)["GunDatas"][index]["Direction"][0].GetValue<JSON::Real>()),
                                          static_cast<float>((*pOptionData)["GunDatas"][index]["Direction"][1].GetValue<JSON::Real>()),
                                          static_cast<float>((*pOptionData)["GunDatas"][index]["Direction"][2].GetValue<JSON::Real>()));

        auto offsetFromShooter = Physics::Vector3(static_cast<float>((*pOptionData)["GunDatas"][index]["OffsetFromShooter"][0].GetValue<JSON::Real>()),
                                                  static_cast<float>((*pOptionData)["GunDatas"][index]["OffsetFromShooter"][1].GetValue<JSON::Real>()),
                                                  static_cast<float>((*pOptionData)["GunDatas"][index]["OffsetFromShooter"][2].GetValue<JSON::Real>()));

        pGun->SetShotLogic(newEx C_InputShotLogic((*pOptionData)["GunDatas"][index]["ShotInterval"].GetValue<JSON::Integer>()));
        pGun->SetBulletId((*pOptionData)["GunDatas"][index]["BulletId"].GetValue<JSON::String>());
        pGun->SetBulletPower(newEx C_BasePower((*pOptionData)["GunDatas"][index]["BulletPower"].GetValue<JSON::Integer>()));

        auto pMoveLogic = newEx C_RigidBodyStraightMoveLogic;

        pMoveLogic->SetDirection(direction);
        pMoveLogic->SetMovement(static_cast<float>((*pOptionData)["GunDatas"][index]["BulletMovement"].GetValue<JSON::Real>()));

        pGun->SetBulletMoveLogic(pMoveLogic);

        pGun->SetOffsetFromShooter(offsetFromShooter);
        pGun->SetDirection(direction);

        return pGun;
    }
}