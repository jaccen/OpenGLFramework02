/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "Shooter.h"
#include "RigidBodyMoveLogic.h"
#include "../../Library/Physics/Body/Rigid/Rigidbody.h"
#include "../../Library/Physics/CollisionShape/Convex/Sphere/SphereShape.h"
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* 前方宣言 */
    class C_BaseOption;
    class C_BaseEnemy;
    class C_BaseBullet;
    class C_BaseObstacle;
    class C_BaseBomb;


    //-------------------------------------------------------------
    //!
    //! @brief コネクトマシーン
    //! @brief 連結機械を表すクラス
    //!
    //-------------------------------------------------------------
    class C_ConnectMachine : public C_Shooter
    {
    public:
        /* 定数 */
        static const int32_t s_MAX_MOVE_SPEED_LEVEL = 4;                                        ///< @brief 移動スピードの最大レベル 
        
        C_ConnectMachine(const std::string& rId, int32_t type);                                 // コンストラクタ
        virtual ~C_ConnectMachine() override;                                                   // デストラクタ
        virtual bool Update() override = 0;                                                     // 更新処理
        virtual void Draw() override = 0;                                                       // 描画処理
        virtual bool MessageProcess(const Telegram& rTelegram) override = 0;                    // メッセージ処理
        virtual void DispatchCollision(C_CollisionObject* pCollisionObject) override = 0;       // 衝突を発送
        virtual void CollisionProcess(C_BasePlayer* pPlayer) = 0;                               // プレイヤーとの衝突時処理
        virtual void CollisionProcess(C_BaseOption* pOption) = 0;                               // オプションとの衝突時処理
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) = 0;                                 // 敵との衝突時処理
        virtual void CollisionProcess(C_BaseBullet* pBullet) = 0;                               // 弾との衝突時処理
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) = 0;                           // 障害物との衝突時処理
        virtual void CollisionProcess(C_BaseBomb* pBomb) = 0;                                   // ボムとの衝突時処理
        virtual void Move() override = 0;                                                       // 移動処理
        virtual void Shot() override = 0;                                                       // 射撃処理
        virtual void AddConnectOption(C_BaseOption* pOption) = 0;                               // 連結しているオプションを追加
        virtual void ResetConnect() = 0;                                                        // 連結をリセット
        virtual void NewConnect() = 0;                                                          // 新規連結
        std::vector<C_BaseOption*>* GetConnectOptionList();                                     // 連結しているオプションのリストを取得
        Physics::C_RigidBody* GetRigidBody() const;                                             // 剛体を取得
        float GetRadius() const;                                                                // 半径を取得
        virtual const Physics::Vector3& GetPosition() const override;                           // 座標を取得
        virtual void SetPosition(const Physics::Vector3& rPosition) override;                   // 座標を設定

        static void s_SetOwnCrashDerayFrameInterval(uint32_t ownCrashDerayFrameInterval);       // 自爆遅延フレーム数の間隔を設定
    protected:
        std::vector<C_BaseOption*> pConnectOptionList_;                                         ///< @brief 連結しているオプションのリスト
        float radius_ = 0.0f;                                                                   ///< @brief 半径
        std::unique_ptr<Physics::C_RigidBody> upRigidBody_;                                     ///< @brief 剛体
        std::unique_ptr<C_RigidBodyMoveLogic> upMoveLogic_;                                     ///< @brief 移動ロジック
        OpenGL::PrimitiveBufferPtr pModelData_;                                                 ///< @brief モデル情報

        static uint32_t s_ownCrashDerayFrameInterval;                                           ///< @brief 自爆遅延フレーム数の間隔
    };
}