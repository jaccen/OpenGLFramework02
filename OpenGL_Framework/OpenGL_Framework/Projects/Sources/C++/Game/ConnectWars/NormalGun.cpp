/* ヘッダファイル */
#include "NormalGun.h"
#include "Shooter.h"
#include "ShotLogic.h"
#include "BulletGenerator.h"
#include "RigidBodyMoveLogic.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  射撃者
     *
     ****************************************************************/
    C_NormalGun::C_NormalGun(C_Shooter* pShooter) : C_BaseGun(pShooter)
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_NormalGun::~C_NormalGun()
    {
    }


    /*************************************************************//**
     *
     *  @brief  非公開の射撃処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_NormalGun::DoShot()
    {
        if (upShotLogic_->Process() == true)
        {
            auto pBulletMoveLogic = upBulletMoveLogic_->DeepCopy();

            if (autoDirectionFlag_ == true)
            {
                auto bulletDirection = pShooter_->GetRotation() * (*upDirection_);
                pBulletMoveLogic->SetDirection(bulletDirection);
            }

            C_BulletGenerator::s_GetInstance()->Create(bulletId_, 
                                                       pShooter_->GetPosition() + (*upOffsetFromShooter_),
                                                       upBulletPower_->GetValue(),
                                                       pBulletMoveLogic,
                                                       pShooter_->GetType());
        }
    }
}