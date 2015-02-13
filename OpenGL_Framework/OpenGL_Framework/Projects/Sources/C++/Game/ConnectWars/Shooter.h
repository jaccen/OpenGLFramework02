/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "CollisionObject.h"
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "../../Library/Material/Manager/MaterialManager.h"
#include "../../Library/Light/Manager/LightManager.h"


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
    //! @brief シューター
    //! @brief 弾を撃つオブジェクト
    //!
    //-------------------------------------------------------------
    class C_Shooter : public C_CollisionObject
    {
    public:
        C_Shooter(const std::string& rId, int32_t type);                                        // コンストラクタ
        virtual~C_Shooter() override;                                                           // デストラクタ
        virtual bool Update() override = 0;                                                     // 更新処理
        virtual void Draw() override = 0;                                                       // 描画処理
        virtual bool MessageProcess(const Telegram& rTelegram) override = 0;                    // メッセージ処理
        virtual void DispatchCollision(C_CollisionObject* pCollisionObject) override = 0;       // 衝突を発送
        virtual void Move() = 0;                                                                // 移動処理
        virtual void Shot() = 0;                                                                // 射撃処理
        virtual void CollisionProcess(C_BasePlayer* pPlayer) = 0;                               // プレイヤーとの衝突時処理
        virtual void CollisionProcess(C_BaseOption* pOption) = 0;                               // オプションとの衝突時処理
        virtual void CollisionProcess(C_BaseEnemy* pEnemy) = 0;                                 // 敵との衝突時処理
        virtual void CollisionProcess(C_BaseBullet* pBullet) = 0;                               // 弾との衝突時処理
        virtual void CollisionProcess(C_BaseObstacle* pObstacle) = 0;                           // 障害物との衝突時処理
        virtual void CollisionProcess(C_BaseBomb* pBomb) = 0;                                   // ボムとの衝突時処理
        virtual void MoveLimitCheck() override = 0;                                             // 移動制限を確認
        virtual const Physics::Vector3& GetPosition() const override = 0;                       // 座標を取得  
        virtual void SetPosition(const Physics::Vector3& rPosition) override = 0;               // 座標を設定
        virtual const Physics::Matrix3x3& GetRotation() const = 0;                              // 回転量を取得
        virtual void SetMaterial(const Material::MaterialPtr& prMaterial) = 0;                  // マテリアルを設定
        virtual void SetLight(const Light::LightPtr& prLight) = 0;                              // ライトを設定
    protected:
        OpenGL::PrimitiveBufferPtr pModelData_;                                                 ///< @brief モデル情報
        Texture::TextureDataPtr pModelTextureData_;                                             ///< @brief モデルのテクスチャ情報
        Material::MaterialPtr pBasicMaterial_;                                                  ///< @brief 基本のマテリアル
        Material::MaterialPtr pDamageMaterial_;                                                 ///< @brief ダメージマテリアル
        Material::MaterialPtr pNowMaterial_;                                                    ///< @brief 現在のマテリアル
        Light::LightPtr pMainLight_;                                                            ///< @brief メインライト
    };
}