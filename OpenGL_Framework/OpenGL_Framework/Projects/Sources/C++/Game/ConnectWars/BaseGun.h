/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectWarsDefine.h"
#include "../../Library/Physics/PhysicsDefine.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* 前方宣言 */
    class C_BasePower;
    class C_ShotLogic;
    class C_Shooter;
    class C_RigidBodyMoveLogic;


    //-------------------------------------------------------------
    //!
    //! @brief ベースガン
    //! @brief ガンの基底クラス
    //!
    //-------------------------------------------------------------
    class C_BaseGun
    {
    public:
        C_BaseGun(C_Shooter* pShooter);                                                     // コンストラクタ
        virtual ~C_BaseGun();                                                               // デストラクタ
        void Shot();                                                                        // 射撃処理
        void SetShotLogic(C_ShotLogic* pShotLogic);                                         // 射撃のロジックを設定
        void SetOffsetFromShooter(const Physics::Vector3& rOffsetFromShooter);              // 射撃者からのオフセットを設定
        void SetBulletId(const std::string& rBulletId);                                     // 弾のIDを設定
        void SetBulletMoveLogic(C_RigidBodyMoveLogic* pBulletMoveLogic);                    // 弾の移動ロジックを設定
        void SetBulletPower(C_BasePower* pBulletPower);                                     // 弾の攻撃力を設定
    protected:
        C_Shooter* pShooter_ = nullptr;                                                     ///< @brief 射撃者
        Physics::Vector3 offsetFromShooter_ = Physics::Vector3(0.0f, 0.0f, 0.0f);           ///< @brief 射撃者からのオフセット
        Physics::Vector3 direction_ = Physics::Vector3(0.0f, 0.0f, 0.0f);                   ///< @brief 向き
        bool autoDirectionFlag_ = false;                                                    ///< @brief 向きを自動化するフラグ
        std::unique_ptr<C_ShotLogic> upShotLogic_;                                          ///< @brief 射撃のロジック
        std::string bulletId_;                                                              ///< @brief 弾のID
        std::unique_ptr<C_BasePower> upBulletPower_;                                        ///< @brief 弾の攻撃力
        std::shared_ptr<C_RigidBodyMoveLogic> upBulletMoveLogic_;                           ///< @brief 弾の移動ロジック

        virtual void DoShot() = 0;                                                          ///< @brief 非公開の射撃処理
    };
}


