/* 二重インクルード防止 */
#pragma once


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
    //! @brief コリジョンシェイプ
    //! @brief 衝突形状を表すクラス
    //!
    //-------------------------------------------------------------
    class C_CollisionShape
    {
    public:
        C_CollisionShape();                                                 // コンストラクタ
        virtual ~C_CollisionShape();                                        // デストラクタ
        btCollisionShape* GetCollisionShape() const;                        // 衝突形状を取得
        int32_t GetShapeType() const;                                       // 形状の種類を取得
        float GetCollisionMargin() const;                                   // 衝突マージンを取得
        void SetCollisionMargin(float collisionMargin = 0.04f);             // 衝突マージンを設定
    protected:
        std::unique_ptr<btCollisionShape> upCollisionShape_;                ///< @brief 衝突形状
    };
}