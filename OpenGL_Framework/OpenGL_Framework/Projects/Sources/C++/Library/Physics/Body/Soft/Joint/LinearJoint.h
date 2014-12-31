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
    //! @brief リニアジョイント
    //! @brief 直線接合を表すクラス
    //!
    //-------------------------------------------------------------
    class C_LinearJoint
    {
    public:
        /* 型変換 */
        using LinearJointSpec = btSoftBody::LJoint::Specs;      // LinearJointSpec型を宣言

        C_LinearJoint(const Vector3& rPosition,                 // コンストラクタ
                      float constraintForceMixing = 1.0f,
                      float errorReductionParameter = 1.0f);                
        ~C_LinearJoint();                                       // デストラクタ
        LinearJointSpec* GetLinearJointSpec();                  // 線形接合のスペックを取得
    private:
        LinearJointSpec linearJointSpec_;                       ///< @brief 線形接合
    };
}