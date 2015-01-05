/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectWarsDefine.h"
#include "BaseHitPoint.h"
#include "BasePower.h"
#include "../../Library/GameObject/GameObject.h"
#include "../../Library/Math/Vector/Vector4.h"
#include "../../Library/Shader/GLSL/Uniform/Manager/UniformBufferManager.h"
#include "../../Library/Shader/GLSL/Object/Manager/GlslObjectManager.h"
#include "../../Library/Common/CommonHelper.h"
#include "../../Library/Physics/PhysicsDefine.h"
#include <vector>


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* 前方宣言 */
    class C_BasePlayer;
    class C_BaseOption;
    class C_BaseEnemy;
    class C_BaseBullet;
    class C_BaseObstacle;
    class C_BaseBomb;


    //-------------------------------------------------------------
    //!
    //! @brief コリジョンオブジェクト
    //! @brief 衝突時処理を行うオブジェクト
    //!
    //-------------------------------------------------------------
    class C_CollisionObject : public GameObject::C_GameObject
    {
    public:
        /* フィルタの種類 */
        enum eFilterType
        {
            FILTER_TYPE_NOTHING = 0,                                                                        ///< @brief なし
            FILTER_TYPE_PLAYER = ShiftBit(1),                                                               ///< @brief プレイヤー
            FILTER_TYPE_OPTION = ShiftBit(2),                                                               ///< @brief オプション
            FILTER_TYPE_ENEMY = ShiftBit(3),                                                                ///< @brief 敵
            FILTER_TYPE_CONNECTMACHINE_BULLET = ShiftBit(4),                                                ///< @brief 連結機械の弾
            FILTER_TYPE_ENEMY_BULLET = ShiftBit(5),                                                         ///< @brief 敵の弾
            FILTER_TYPE_OBSTACLE = ShiftBit(6),                                                             ///< @brief 障害物
            FILTER_TYPE_BOMB = ShiftBit(7),                                                                 ///< @brief ボム
        };


        C_CollisionObject(const std::string& rId, int32_t type);                                            // コンストラクタ
        virtual ~C_CollisionObject() override;                                                              // デストラクタ
        virtual bool Update() override = 0;                                                                 // 更新処理
        virtual void Draw() override = 0;                                                                   // 描画処理
        virtual bool MessageProcess(const Telegram& rTelegram) override = 0;                                // メッセージ処理
        virtual void DispatchCollision(C_CollisionObject* pCollisionObject) = 0;                            // 衝突を発送
        virtual void CollisionProcess(C_BasePlayer* pPlayer) = 0;                                           // プレイヤーとの衝突時処理
        virtual void CollisionProcess(C_BaseOption* pOption) = 0;                                           // オプションとの衝突時処理
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) = 0;                                             // 敵との衝突時処理
        virtual void CollisionProcess(C_BaseBullet* pBullet) = 0;                                           // 弾との衝突時処理
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) = 0;                                       // 障害物との衝突時処理
        virtual void CollisionProcess(C_BaseBomb* pBomb) = 0;                                               // ボムとの衝突時処理
        virtual void MoveLimitCheck() = 0;                                                                  // 移動制限を確認
        bool CheckCollidedObjectId(const std::string& rId);                                                 // 衝突したオブジェクトのIDが存在するか確認
        void EntryCollidedObjectId(const std::string& rId);                                                 // 衝突したオブジェクトのIDを登録
        void SetCollisionPoint(const Physics::Vector3& rCollisionPoint);                                    // 衝突点を設定
    protected:
        Matrix4x4 modelMatrix_;                                                                             ///< @brief モデル行列
        std::unique_ptr<C_BaseHitPoint> upHitPoint_;                                                        ///< @brief ヒットポイント
        std::unique_ptr<C_BasePower> upPower_;                                                              ///< @brief パワー
        Shader::GLSL::GlslObjectPtr pGlslObject_;                                                           ///< @brief GLSLオブジェクト
        Shader::GLSL::UniformBufferPtr pUniformBuffer_;                                                     ///< @brief ユニフォームバッファ
        Shader::GLSL::UniformBlockIndex uniformBlockIndex_ = 0;                                             ///< @brief ユニフォームブロックのインデックス

        void ResetCollidedObjectId();                                                                       // 衝突したオブジェクトのIDをリセット
        const Physics::Vector3& GetCollisionPoint() const;                                                  // 衝突点を取得
    private:
        std::vector<std::string> collidedObjectIdList_;                                                     ///< @brief 衝突したオブジェクトのIDリスト
        Physics::Vector3 collisionPoint_;                                                                   ///< @brief 衝突点
    };
}