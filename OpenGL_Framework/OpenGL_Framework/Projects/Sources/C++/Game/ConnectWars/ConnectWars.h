/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Library/Framework/Framework.h"
#include "../../Library/Scene/Manager/SceneManager.h"
#include "../../Library/Lua/LuaStateManager.h"
#include "../../Library/GameObject/Manager/GameObjectManager.h"
#include "../../Library/GameObject/Message/Dispatcher/MessageDispatcher.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
#include "../../Library/Particle/System/Manager/ParticleSystemManager.h"
#include "../../Library/Physics/Engine/PhysicsEngine.h"


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
    //! @brief コネクトウォーズ
    //! @brief コネクトウォーズを表すクラス
    //!
    //-------------------------------------------------------------
    class C_ConnectWars : public Framework::C_Framework
    {
    public:
        C_ConnectWars();                                                                    // コンストラクタ
        virtual ~C_ConnectWars() override;                                                  // デストラクタ
    private:
        std::unique_ptr<Scene::C_SceneManager> upSceneManager_;                             ///< @brief シーンマネージャー
        std::unique_ptr<Lua::C_LuaStateManager> upLuaStateManager_;                         ///< @brief Luaステートマネージャー
        std::unique_ptr<Sprite::C_SpriteCreaterManager> upSpriteCreaterManager_;            ///< @brief スプライトクリエイターマネージャー
        std::unique_ptr<Particle::C_ParticleSystemManager> upParticleSystemManager_;        ///< @brief パーティクルシステムマネージャー
        std::unique_ptr<GameObject::C_GameObjectManager> upGameObjectManager_;              ///< @brief ゲームオブジェクトマネージャー
        std::unique_ptr<GameObject::Message::C_MessageDispatcher> upMessageDispatcher_;     ///< @brief メッセージディスパッチャー
        std::unique_ptr<Physics::C_PhysicsEngine> upPhysicsEngine_;                         ///< @brief フィジックスエンジン

        bool Initialize() override;                                                         // 初期化処理
        bool Update() override;                                                             // 更新処理
        void Draw() override;                                                               // 描画処理
        void Finalize() override;                                                           // 終了処理
    };
}