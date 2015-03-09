/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "Shooter.h"
#include "../../Library/State/Machine/StateMachine.h"
#include "../../Library/Json/Object/JsonObject.h"


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
    class C_BaseBullet;
    class C_BaseObstacle;
    class C_BaseBomb;
    class C_BaseShield;
    class C_BaseGun;


    //-------------------------------------------------------------
    //!
    //! @brief ベースエネミー
    //! @brief 敵の基底クラス
    //!
    //-------------------------------------------------------------
    class C_BaseEnemy : public C_Shooter
    {
    public:
        C_BaseEnemy(const std::string& rId, int32_t type);                                  // コンストラクタ
        virtual ~C_BaseEnemy() override;                                                    // デストラクタ
        bool Update() override final;                                                       // 更新処理
        void Draw() override final;                                                         // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override final;                      // メッセージ処理
        void DispatchCollision(C_CollisionObject* pCollisionObject) override final;         // 衝突検知を発送
        virtual void CollisionProcess(C_BasePlayer* pPlayer) override;                      // プレイヤーとの衝突時処理
        virtual void CollisionProcess(C_BaseOption* pOption) override;                      // オプションとの衝突時処理
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) override;                        // 敵との衝突時処理
        virtual void CollisionProcess(C_BaseBullet* pBullet) override;                      // 弾との衝突時処理
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) override;                  // 障害物との衝突時処理
        virtual void CollisionProcess(C_BaseBomb* pBomb) override;                          // ボムとの衝突時処理
        virtual void CollisionProcess(C_BaseShield* pShiled) override;                      // シールドとの衝突時処理
        virtual void Move() = 0;                                                            // 移動処理
        virtual void Shot();                                                                // 射撃処理
        virtual void SetCreateDataWithJson(JSON::JsonObject* pJsonObject) = 0;              // JSONオブジェクトからデータを設定
        void SetMaterial(const Material::MaterialPtr& prMaterial) override;                 // マテリアルを設定
        void SetLight(const Light::LightPtr& prLight) override;                             // ライトを設定
        virtual bool IsFinishAdvent() const;                                                // 出現が終了しているか確認
        State::C_StateMachine<C_BaseEnemy>* GetStateMachine() const;                        // ステートマシーンを取得
    protected:
        std::vector<std::unique_ptr<C_BaseGun>> upGuns_;                                    ///< @brief 銃
        std::unique_ptr<State::C_StateMachine<C_BaseEnemy>> upStateMachine_;                ///< @brief ステートマシーン
        Vector3 scale_;                                                                     ///< @brief スケール

        virtual void DoUpdate() = 0;                                                        // 非公開の更新処理
        virtual void DoDraw() = 0;                                                          // 非公開の描画処理
        virtual bool DoMessageProcess(const Telegram& rTelegram) = 0;                       // 非公開のメッセージ処理
    };
}