/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../CollisionShape.h"
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
    //! @brief カプセルシェイプ
    //! @brief カプセル形状を表すクラス
    //!
    //-------------------------------------------------------------
    class C_CapsuleShape : public C_CollisionShape
    {
    public:
        C_CapsuleShape(float radius,                                    // コンストラクタ
                       float height,
                       ecDirection direction = ecDirection::Y);
        ~C_CapsuleShape() override;                                     // デストラクタ
    private:

    };
}