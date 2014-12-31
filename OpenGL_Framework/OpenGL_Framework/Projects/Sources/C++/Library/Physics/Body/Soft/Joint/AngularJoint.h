/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../../PhysicsDefine.h"


//-------------------------------------------------------------
///
/// @brief フィジックス
/// @brief 物理関連の名前空間
///
//-------------------------------------------------------------
namespace Physics
{
    //-------------------------------------------------------------
    //!
    //! @brief アンギュラージョイント
    //! @brief 角接合を表すクラス
    //!
    //-------------------------------------------------------------
    class C_AngularJoint
    {
    public:
        /* 型変換 */
        using AngularJointSpec = btSoftBody::AJoint::Specs;         // AngularJointSpec型を宣言

        C_AngularJoint(const Vector3& rAxis,                        // コンストラクタ
                       float constraintForceMixing = 1.0f,
                       float errorReductionParameter = 1.0f);
        ~C_AngularJoint();                                          // デストラクタ
        AngularJointSpec* GetAngularJointSpec();                    // 角接合のスペックを取得
    private:
        AngularJointSpec angularJointSpec_;                         ///< @brief 角接合のスペック
    };
}