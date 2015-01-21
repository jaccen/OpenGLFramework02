#include "RigidBodyForceMoveLogic.h"
#include "../../Library/Debug/Helper/DebugHelper.h"


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
     *  @param  最初に加える力
     *  @param  最初に加えるトルク
     *
     ****************************************************************/
    C_RigidBodyForceMoveLogic::C_RigidBodyForceMoveLogic(const Physics::Vector3& rFirstAddForce,
                                                         const Physics::Vector3& rFirstAddTorque) :

        // 最初に加える力
        upFirstAddForce_(std::make_unique<Physics::Vector3>(rFirstAddForce)),

        // 最初に加えるトルク
        upFirstAddTorque_(std::make_unique<Physics::Vector3>(rFirstAddTorque))

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_RigidBodyForceMoveLogic::~C_RigidBodyForceMoveLogic()
    {
    }


    /*************************************************************//**
     *
     *  @brief  ディープコピーを行う
     *  @param  なし
     *  @return 自身のコピー
     *
     ****************************************************************/
    C_RigidBodyMoveLogic* C_RigidBodyForceMoveLogic::DeepCopy()
    {
        auto pRigidBodyMoveLogic = newEx C_RigidBodyForceMoveLogic(*upFirstAddForce_, *upAddTorque_);

        pRigidBodyMoveLogic->SetAddForce(*upAddForce_);
        pRigidBodyMoveLogic->SetAddTorque(*upAddTorque_);

        return pRigidBodyMoveLogic;
    }


    /*************************************************************//**
     *
     *  @brief  加える力を設定する
     *  @param  加える力
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBodyForceMoveLogic::SetAddForce(const Physics::Vector3& rAddForce)
    {
        *upAddForce_ = rAddForce;
    }


    /*************************************************************//**
     *
     *  @brief  加える力を設定する
     *  @param  加える力
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBodyForceMoveLogic::SetAddTorque(const Physics::Vector3& rAddTorque)
    {
        *upAddTorque_ = rAddTorque;
    }


    /*************************************************************//**
     *
     *  @brief  非公開の処理を行う
     *  @param  剛体
     *  @return なし
     *
     ****************************************************************/
    void C_RigidBodyForceMoveLogic::DoProcess(RigidBody* pRigidBody)
    {
        if (firstAddForceFlag_ == false)
        {
            pRigidBody->ApplyForce(*upFirstAddForce_);
            firstAddForceFlag_ = true;
        }

        if (firstAddTorqueFlag_ == false)
        {
            pRigidBody->ApplayTorque(*upAddTorque_);
            firstAddTorqueFlag_ = true;
        }

        pRigidBody->ApplyForce(*upAddForce_);
        pRigidBody->ApplayTorque(*upAddTorque_);
    }
}