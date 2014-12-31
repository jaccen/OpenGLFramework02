/* ヘッダファイル */
#include "AngularJoint.h"


//-------------------------------------------------------------
///
/// @brief フィジックス
/// @brief 物理関連の名前空間
///
//-------------------------------------------------------------
namespace Physics
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  軸
     *  @param  拘束力の混合
     *  @param  エラー低減パラメータ
     *
     ****************************************************************/
    C_AngularJoint::C_AngularJoint(const Vector3& rAxis,
                                   float constraintForceMixing,
                                   float errorReductionParameter)
    {
        angularJointSpec_.axis = rAxis;
        angularJointSpec_.cfm = constraintForceMixing;
        angularJointSpec_.erp = errorReductionParameter;
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_AngularJoint::~C_AngularJoint()
    {
    }


    /*************************************************************//**
     *
     *  @brief  角接合のスペックを取得する
     *  @param  なし
     *  @result 角接合のスペック
     *
     ****************************************************************/
    C_AngularJoint::AngularJointSpec* C_AngularJoint::GetAngularJointSpec()
    {
        return &angularJointSpec_;
    }
}