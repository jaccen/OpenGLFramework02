/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectMachine.h"
#include "../../Library/State/Machine/StateMachine.h"
#include "../../Library/Camera/Manager/CameraManager.h"
#include "../../Library/Collision/BoundingBox/AABB/Aabb2D.h"
#include "../../Library/Input/Keyboard/KeyboardManager.h"
#include "../../Library/Input/Gamepad/Manager/GamepadManager.h"


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
    class C_BaseGun;


    //-------------------------------------------------------------
    //!
    //! @brief ベースプレイヤー
    //! @brief プレイヤーの基底クラス
    //!
    //-------------------------------------------------------------
    class C_BasePlayer : public C_ConnectMachine
    {
    public:
        /* 銃の情報 */
        struct S_GunData
        {
            std::string bulletId_;                                                                      ///< @brief 弾のID
            int32_t bulletPower_ = 1000;                                                                ///< @brief 弾のパワー
            float bulletMovement_ = 5.0f;                                                               ///< @brief 弾の移動量
            int32_t shotInterval_ = 5;                                                                  ///< @brief 射撃の間隔
            std::shared_ptr<Physics::Vector3> spOffsetFromShooter_;                                     ///< @brief 射撃者からのオフセット
            std::shared_ptr<Physics::Vector3> spDirection_;                                             ///< @brief 向き
            bool autoDirectionFlag_ = false;                                                            ///< @brief 向きを自動化するフラグ
        };


        enum eMoveType
        {
            ADVENT,
            INPUT,
        };


        C_BasePlayer(const std::string& rId, int32_t type);                                             // コンストラクタ
        virtual ~C_BasePlayer() override = 0;                                                           // デストラクタ
        bool Update() override final;                                                                   // 更新処理
        void Draw() override final;                                                                     // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override final;                                  // メッセージ処理
        void DispatchCollision(C_CollisionObject* pCollisionObject) override final;                     // 衝突を発送
        virtual void CollisionProcess(C_BasePlayer* pPlayer) override;                                  // プレイヤーとの衝突時処理
        virtual void CollisionProcess(C_BaseOption* pOption) override;                                  // オプションとの衝突時処理
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) override;                                    // 敵との衝突時処理
        virtual void CollisionProcess(C_BaseBullet* pBullet) override;                                  // 弾との衝突時処理
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) override;                              // 障害物との衝突時処理
        virtual void CollisionProcess(C_BaseBomb* pBomb) override;                                      // ボムとの衝突時処理
        virtual void Move() override;                                                                   // 移動処理
        virtual void Shot() override;                                                                   // 射撃処理
        virtual void Bomb();                                                                            // ボム処理
        virtual void AddConnectOption(C_BaseOption* pOption) override;                                  // 連結しているオプションを追加
        virtual void ResetConnect() override;                                                           // 連結をリセット
        virtual void ConnectCheck();                                                                    // 連結の確認
        virtual void ConnectCheck(C_BaseOption* pOption);                                               // 連結の確認
        virtual void NewConnect() override;                                                             // 新規連結
        virtual void MoveLimitCheck() override;                                                         // 移動制限を確認
        virtual void UpdateMoveLimitBoundingBox(C_BaseOption* pOption);                                 // 移動制限境界ボックスの更新
        virtual void ResetMoveLimitBoundingBox();                                                       // 移動制限境界ボックスをリセット
        virtual void AddMoveSpeedLevel(int32_t moveSpeedLevel);                                         // 移動速度のレベルを加算
        void AddConnectOptionCount(int32_t connectOptionCount);                                         // オプションの数を加算
        State::C_StateMachine<C_BasePlayer>* GetStateMachine() const;                                   // ステートマシーンを取得
        int32_t GetConnectPetrifyFrame() const;                                                         // 連結の硬直フレーム数を取得
        int32_t GetBombChargeFrame() const;                                                             // ボムのチャージフレーム数を取得
        int32_t GetBombInvincibleFrame() const;                                                         // ボムの無敵フレーム数を取得
        bool IsBombChargeFlag() const;                                                                  // ボムのチャージフラグを取得
        const std::string& GetBombChargeEffectId() const;                                               // ボムのチャージエフェクトのID
        const std::string& GetBombId() const;                                                           // ボムのIDを取得
        void SetBombChargeFlag(bool bombChargeFlag);                                                    // ボムのチャージフラグを設定
        bool IsFinishAdvent() const;                                                                    // 出現し終えたか確認
        void ChangeMove(eMoveType moveType);                                                            // 移動を変更
    protected:
        std::unique_ptr<State::C_StateMachine<C_BasePlayer>> upStateMachine_;                           ///< @brief ステートマシーン
        Camera::CameraPtr pCamera_;                                                                     ///< @brief カメラ
        std::vector<std::unique_ptr<C_BaseGun>> upGuns_;                                                ///< @brief 銃
        int32_t connectPetrifyFrame_ = 0;                                                               ///< @brief 連結時の硬直フレーム数
        int32_t bombChargeFrame_ = 60;                                                                  ///< @brief ボムのチャージフレーム数
        int32_t bombInvincibleFrame_ = 100;                                                             ///< @brief ボムの無敵フレーム数
        int32_t remainLife_ = 3;                                                                        ///< @brief 残機
        int32_t moveSpeedLevel_ = 0;                                                                    ///< @brief 移動スピードのレベル
        float moveSpeedUpInterval_ = 0.3f;                                                              ///< @brief 移動スピードのアップ間隔
        int32_t connectOptionCount_ = 0;                                                                ///< @brief オプション数
        bool bombChargeFlag_ = false;                                                                   ///< @brief ボムのチャージフラグ
        Collision::S_Aabb2D<float> moveLimitBoundingBox_;                                               ///< @brief 移動制限境界ボックス
        Input::KeyCode bombKeyCode_ = Input::KeyCode::SDL_SCANCODE_X;                                   ///< @brief ボムのキーコード
        Input::C_Gamepad::eButton bombGamepadButton_ = Input::C_Gamepad::BUTTON_FOUR_RIGHT;             ///< @brief ボムのゲームパッドのボタン

        virtual void DoUpdate();                                                                        // 非公開の更新処理
        virtual void DoDraw() = 0;                                                                      // 非公開の描画処理
        virtual bool DoMessageProcess(const Telegram& rTelegram);                                       // 非公開のメッセージ処理
    };
}