/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../CollisionShape.h"
#include "../../../PhysicsDefine.h"
#include <deque>


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
    //! @brief コンパウンドシェイプ
    //! @brief 合成形状を表すクラス
    //!
    //-------------------------------------------------------------
    class C_CompoundShape : public C_CollisionShape
    {
    public:
        C_CompoundShape();                                                      // コンストラクタ
        ~C_CompoundShape() override;                                            // デストラクタ
        void AddChildShape(C_CollisionShape* pChildShape,                       // 子形状を追加
                           const Transform& rTransform);
    private:
        std::deque<std::unique_ptr<C_CollisionShape>> upChildShapes_;           ///< @brief 子形状
    };
}