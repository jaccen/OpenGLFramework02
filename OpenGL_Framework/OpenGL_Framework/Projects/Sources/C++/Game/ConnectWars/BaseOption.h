/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectMachine.h"
#include "../../Library/State/Machine/StateMachine.h"
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"
#include "../../Library/Camera/Manager/CameraManager.h"


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
    class C_BaseEnemy;
    class C_BaseBullet;
    class C_BaseObstacle;
    class C_BaseBomb;
    class C_BaseGun;


    //-------------------------------------------------------------
    //!
    //! @brief ベースオプション
    //! @brief オプションの基底クラス
    //!
    //-------------------------------------------------------------
    class C_BaseOption : public C_ConnectMachine
    {
    public:
        C_BaseOption(const std::string& rId, int32_t type);                                         // コンストラクタ
        virtual ~C_BaseOption() override = 0;                                                       // デストラクタ
        bool Update() override final;                                                               // 更新処理
        void Draw() override final;                                                                 // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override final;                              // メッセージ処理
        void DispatchCollision(C_CollisionObject* pCollisionObject) override final;                 // 衝突検出を発送
        virtual void CollisionProcess(C_BasePlayer* pPlayer) override;                              // プレイヤーとの衝突時処理
        virtual void CollisionProcess(C_BaseOption* pOption) override;                              // オプションとの衝突時処理
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) override;                                // 敵との衝突時処理
        virtual void CollisionProcess(C_BaseBullet* pBullet) override;                              // 弾との衝突時処理
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) override;                          // 障害物との衝突時処理
        virtual void CollisionProcess(C_BaseBomb* pBomb) override;                                  // ボムとの衝突時処理
        virtual void Move() override;                                                               // 移動処理
        virtual void Shot() override;                                                               // 射撃処理
        virtual void AddConnectOption(C_BaseOption* pOption);                                       // 連結しているオプションを追加
        virtual void ResetConnect() override;                                                       // 連結をリセット
        virtual void NewConnect() override;                                                         // 新規連結
        virtual void MoveLimitCheck() override;                                                     // 移動制限を確認
        virtual void ConnectEffect();                                                               // 連結時の効果
        virtual void ResetEffect();                                                                 // 効果をリセット
        virtual void DispatchOwnCrash();                                                            // 自爆を発送
        virtual void OwnCrash();                                                                    // 自爆処理
        State::C_StateMachine<C_BaseOption>* GetStateMachine() const;                               // ステートマシーンを取得
        const Physics::Vector3& GetOffsetFromPlayer() const;                                        // プレイヤーからのオフセットを取得
        C_BasePlayer* GetPlayer() const;                                                            // プレイヤーを取得
        bool IsOnceConnectFlag() const;                                                             // 一度連結したか判断するフラグを取得
        bool IsConnectFlag() const;                                                                 // 連結フラグを取得
        bool IsDefeatedFlag() const;                                                                // 撃破フラグを取得
        int32_t GetDefeatedFrame() const;                                                           // 撃破状態のフレーム数を取得
        const std::string& GetBombSelfCrashEffectId() const;                                        // ボムの自爆エフェクトのIDを取得
        void SetOnceConnectFlag(bool onceConnectFlag);                                              // 一度連結したか判断するフラグを設定
        void SetConnectFlag(bool connectFlag);                                                      // 連結フラグを設定
        void SetOffsetFromPlayer(const Physics::Vector3& rOffsetFromPlayer);                        // プレイヤーからのオフセットを設定
        void SetPlayer(C_BasePlayer* pPlayer);                                                      // プレイヤーを設定
        void SetDefeatedFlag(bool defeatedFlag);                                                    // 撃破フラグを設定
    protected:
        std::unique_ptr<State::C_StateMachine<C_BaseOption>> upStateMachine_;                       ///< @brief ステートマシーン
        bool onceConnectFlag_ = false;                                                              ///< @brief 一度連結したか判断するフラグ
        bool connectFlag_ = false;                                                                  ///< @brief 連結されているか判断するフラグ
        std::unique_ptr<Physics::Vector3> upOffsetFromPlayer_;                                      ///< @brief プレイヤーからのオフセット
        C_BasePlayer* pPlayer_ = nullptr;                                                           ///< @brief プレイヤー
        bool defeatedFlag_ = false;                                                                 ///< @brief 撃破フラグ
        int32_t defeatedFrame_ = 60;                                                                ///< @brief 撃破状態のフレーム数
        int32_t ownCrashDelayFrame_ = 0;                                                            ///< @brief 自爆遅延フレーム数
        std::vector<std::unique_ptr<C_BaseGun>> upGuns_;                                            ///< @brief 銃

        virtual void DoUpdate();                                                                    // 非公開の更新処理
        virtual void DoDraw() = 0;                                                                  // 非公開の描画処理
        virtual bool DoMessageProcess(const Telegram& rTelegram);                                   // 非公開のメッセージ処理
    };
}