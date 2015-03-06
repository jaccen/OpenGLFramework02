/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "BaseEnemy.h"
#include "RigidBodyMoveLogic.h"
#include "../../Library/Physics/Body/Rigid/Rigidbody.h"
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    //-------------------------------------------------------------
    //!
    //! @brief ボックスエネミー
    //! @brief 箱状の敵を表すクラス
    //!
    //-------------------------------------------------------------
    class C_BoxEnemy : public C_BaseEnemy
    {
    public:
        C_BoxEnemy(const std::string& rId, int32_t type);                                   // コンストラクタ
        virtual ~C_BoxEnemy() override;                                                     // デストラクタ
        void Move() override;                                                               // 移動処理
        void MoveLimitCheck() override;                                                     // 移動制限の確認
        void SetCreateDataWithJson(JSON::JsonObject* pJsonObject);                          // JSONオブジェクトからデータを設定
        const Physics::Vector3& GetPosition() const override;                               // 座標を取得
        void SetPosition(const Physics::Vector3& rPosition);                                // 座標を設定
        const Physics::Matrix3x3& GetRotation() const override;                             // 回転量を取得
    protected:
        std::unique_ptr<Physics::C_RigidBody> upRigidBody_;                                 ///< @brief 剛体
        std::unique_ptr<C_RigidBodyMoveLogic> upMoveLogic_;                                 ///< @brief 移動ロジック
        OpenGL::PrimitiveBufferPtr pModelData_;                                             ///< @brief モデル情報
        Vector3 size_;                                                                      ///< @brief サイズ

        void DoUpdate() override;                                                           // 非公開の更新処理
        void DoDraw() override;                                                             // 非公開の描画処理
        bool DoMessageProcess(const Telegram& rTelegram) override;                          // 非公開のメッセージ処理
    };
}