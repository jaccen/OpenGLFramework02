/* ヘッダファイル */
#include "BaseGun.h"
#include "Shooter.h"
#include "BasePower.h"
#include "RigidBodyMoveLogic.h"
#include "ShotLogic.h"


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
    C_BaseGun::C_BaseGun(C_Shooter* pShooter) :

        // 射撃者
        pShooter_(pShooter),

        // 射撃者からのオフセット
        upOffsetFromShooter_(std::make_unique<Physics::Vector3>(0.0f, 0.0f, 0.0f)),

        // 向き
        upDirection_(std::make_unique<Physics::Vector3>(0.0f, 0.0f, 0.0f))

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BaseGun::~C_BaseGun()
    {
    }


    /*************************************************************//**
     *
     *  @brief  射撃処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseGun::Shot()
    {
        DoShot();
    }


    /*************************************************************//**
     *
     *  @brief  射撃のロジックを設定する
     *  @param  射撃のロジック
     *  @return なし
     *
     ****************************************************************/
    void C_BaseGun::SetShotLogic(C_ShotLogic* pShotLogic)
    {
        upShotLogic_.reset(pShotLogic);
    }


    /*************************************************************//**
     *
     *  @brief  射撃者からのオフセットを設定する
     *  @param  射撃者からのオフセット
     *  @return なし
     *
     ****************************************************************/
    void C_BaseGun::SetOffsetFromShooter(const Physics::Vector3& rOffsetFromShooter)
    {
        *upOffsetFromShooter_ = rOffsetFromShooter;
    }


    /*************************************************************//**
     *
     *  @brief  弾のIDを設定する
     *  @param  弾のID
     *  @return なし
     *
     ****************************************************************/
    void C_BaseGun::SetBulletId(const std::string& rBulletId)
    {
        bulletId_ = rBulletId;
    }


    /*************************************************************//**
     *
     *  @brief  弾の移動ロジックを設定する
     *  @param  弾の移動ロジック
     *  @return なし
     *
     ****************************************************************/
    void C_BaseGun::SetBulletMoveLogic(C_RigidBodyMoveLogic* pBulletMoveLogic)
    {
        upBulletMoveLogic_.reset(pBulletMoveLogic);
    }


    /*************************************************************//**
     *
     *  @brief  弾の攻撃力を設定する
     *  @param  弾の攻撃力
     *  @return なし
     *
     ****************************************************************/
    void C_BaseGun::SetBulletPower(C_BasePower* pBulletPower)
    {
        upBulletPower_.reset(pBulletPower);
    }


    /*************************************************************//**
     *
     *  @brief  向きを設定する
     *  @param  向き
     *  @return なし
     *
     ****************************************************************/
    void C_BaseGun::SetDirection(const Physics::Vector3& rDirection)
    {
        *upDirection_ = rDirection;
    }


    /*************************************************************//**
     *
     *  @brief  向きを自動化するフラグを設定する
     *  @param  向きを自動化するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_BaseGun::SetAutoDirectionFlag(bool autoDirectionFlag)
    {
        autoDirectionFlag_ = autoDirectionFlag;
    }
}
