/* ヘッダファイル */
#include "LinearJoint.h"


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
     *  @param  座標
     *  @param  拘束力の混合
     *  @param  エラー低減パラメータ
     *
     ****************************************************************/
    C_LinearJoint::C_LinearJoint(const Vector3& rPosition,
                                 float constraintForceMixing,
                                 float errorReductionParameter)
    {
        linearJointSpec_.cfm = constraintForceMixing;
        linearJointSpec_.erp = errorReductionParameter;
        linearJointSpec_.position = rPosition;
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_LinearJoint::~C_LinearJoint()
    {
    }


    /*************************************************************//**
     *
     *  @brief  線形接合のスペックを取得する
     *  @param  なし
     *  @result 線形接合のスペック
     *
     ****************************************************************/
    C_LinearJoint::LinearJointSpec* C_LinearJoint::GetLinearJointSpec()
    {
        return &linearJointSpec_;
    }
}