/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectMachine.h"
#include "../../Library/State/Machine/StateMachine.h"
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"
#include "../../Library/Camera/Manager/CameraManager.h"
#include "../../Library/Collision/BoundingBox/AABB/Aabb2D.h"


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
    //! @brief ベースプレイヤー
    //! @brief プレイヤーの基底クラス
    //!
    //-------------------------------------------------------------
    class C_BasePlayer : public C_ConnectMachine
    {
    public:
        /** プレイヤーの情報 */
        struct S_PlayerData
        {
            int32_t hitPoint_ = 5000;                                                           ///< @brief ヒットポイント
            int32_t remainLife_ = 3;                                                            ///< @brief 残機
            float radius_ = 0.9f;                                                               ///< @brief 半径
            float movement_ = 0.2f;                                                             ///< @brief 移動量
            int32_t moveSpeedLevel_ = 0;                                                        ///< @brief 移動スピードレベル
            int32_t gunLevel_ = 0;                                                              ///< @brief 銃レベル
            int32_t connectPetrifyFrame_ = 10;                                                  ///< @brief 連結時の硬直フレーム数
            int32_t bombChargeFrame_ = 60;                                                      ///< @brief ボムのチャージフレーム数 
            int32_t bombInvincibleFrame_ = 100;                                                 ///< @brief ボムの無敵フレーム数
        };


        C_BasePlayer(const std::string& rId, int32_t type);                                     // コンストラクタ
        virtual ~C_BasePlayer() override;                                                       // デストラクタ
        bool Update() override final;                                                           // 更新処理
        void Draw() override final;                                                             // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override final;                          // メッセージ処理
        void DispatchCollision(C_CollisionObject* pCollisionObject) override final;             // 衝突を発送
        virtual void CollisionProcess(C_BasePlayer* pPlayer) override;                          // プレイヤーとの衝突時処理
        virtual void CollisionProcess(C_BaseOption* pOption) override;                          // オプションとの衝突時処理
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) override;                            // 敵との衝突時処理
        virtual void CollisionProcess(C_BaseBullet* pBullet) override;                          // 弾との衝突時処理
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) override;                      // 障害物との衝突時処理
        virtual void CollisionProcess(C_BaseBomb* pBomb) override;                              // ボムとの衝突時処理
        virtual void Move() override;                                                           // 移動処理
        virtual void Shot() override;                                                           // 射撃処理
        virtual void Bomb();                                                                    // ボム処理
        virtual void AddConnectOption(C_BaseOption* pOption) override;                          // 連結しているオプションを追加
        virtual void ResetConnect() override;                                                   // 連結をリセット
        virtual void ConnectCheck();                                                            // 連結の確認
        virtual void ConnectCheck(C_BaseOption* pOption);                                       // 連結の確認
        virtual void NewConnect() override;                                                     // 新規連結
        virtual void MoveLimitCheck() override;                                                 // 移動制限を確認
        virtual void UpdateMoveLimitBoundingBox(C_BaseOption* pOption);                         // 移動制限境界ボックスの更新
        virtual void ResetMoveLimitBoundingBox();                                               // 移動制限境界ボックスをリセット
        virtual void AddMoveSpeedLevel(int32_t moveSpeedLevel);                                 // 移動速度のレベルを加算
        virtual void AddGunLevel(int32_t powerLevel);                                           // 銃のレベルを加算
        void AddOptionCount(int32_t optionCount);                                               // オプションの数を加算
        State::C_StateMachine<C_BasePlayer>* GetStateMachine() const;                           // ステートマシーンを取得
        //const AABB2D& GetMoveLimitBoundingBox() const;                                        // 移動制限境界ボックスを取得
        int32_t GetGunLevel() const;                                                            // 銃のレベルを取得
        int32_t GetConnectPetrifyFrame() const;                                                 // 連結の硬直フレーム数を取得
        int32_t GetBombChargeFrame() const;                                                     // ボムのチャージフレーム数を取得
        int32_t GetBombInvincibleFrame() const;                                                 // ボムの無敵フレーム数を取得
        bool IsBombChargeFlag() const;                                                          // ボムのチャージフラグ
        const std::string& GetBombChargeEffectId() const;                                       // ボムのチャージエフェクトのID
        const std::string& GetBombId() const;                                                   // ボムのIDを取得
        int32_t GetOptionCount() const;                                                         // オプションの数を取得
        //void SetMoveLimitBoundingBox(const AABB2D& rMoveLimitBoundingBox);                    // 移動制限境界ボックスを設定
        void SetBombChargeFlag(bool bombChargeFlag);                                            // ボムのチャージフラグを設定
    protected:
        std::unique_ptr<State::C_StateMachine<C_BasePlayer>> upStateMachine_;                   ///< @brief ステートマシーン
        OpenGL::PrimitiveBufferPtr pModelData_;                                                 ///< @brief モデル情報
        Camera::CameraPtr pCamera_;                                                             ///< @brief カメラ
        int32_t connectPetrifyFrame_ = 0;                                                       ///< @brief 連結時の硬直フレーム数
        int32_t bombChargeFrame_ = 60;                                                          ///< @brief ボムのチャージフレーム数
        int32_t bombInvincibleFrame_ = 100;                                                     ///< @brief ボムの無敵フレーム数
        int32_t remainLife_ = 3;                                                                ///< @brief 残機
        int32_t moveSpeedLevel_ = 0;                                                            ///< @brief 移動スピードのレベル
        int32_t gunLevel_ = 0;                                                                  ///< @brief 銃のレベル
        int32_t optionCount_ = 0;                                                               ///< @brief オプション数
        bool bombChargeFlag_ = false;                                                           ///< @brief ボムのチャージフラグ
        bool bombEnableFlag_ = false;                                                           ///< @brief ボムが有効か判断するフラグ
        Collision::S_Aabb2D<float> moveLimitBoundingBox_;                                       ///< @brief 移動制限境界ボックス


        //std::string bombChargeEffectId_ = GameObjectDefine::Id::s_BOMB_CHARGE_EFFECT;           ///< @brief ボムのチャージエフェクトのID
        //std::string bombId_ = GameObjectDefine::Id::s_NORMAL_BOMB;                              ///< @brief ボムのID
        //std::deque<std::unique_ptr<C_BaseGun>> upGuns_;                                         ///< @brief 銃

        virtual void DoUpdate();                                                                // 非公開の更新処理
        virtual void DoDraw();                                                                  // 非公開の描画処理
        virtual bool DoMessageProcess(const Telegram& rTelegram);                               // 非公開のメッセージ処理
    };
}