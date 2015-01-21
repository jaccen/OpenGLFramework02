/* ヘッダファイル */
#include "PhysicsEngine.h"
#include "../Body/Rigid/RigidBody.h"
#include "../Body/Soft/SoftBody.h"
#include <BulletSoftBody/btSoftBodyHelpers.h>
#include <BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>


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
    //! @brief フィジックスエンジンインプリメント
    //! @brief フィジックスエンジンのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_PhysicsEngine::C_PhysicsEngineImpl
    {
    public:
        C_PhysicsEngineImpl(const Vector3& rWorldMin,                                       // コンストラクタ
                            const Vector3& rWorldMax,
                            uint16_t maxObjectCount);
        ~C_PhysicsEngineImpl();                                                             // デストラクタ
        void Initialize(const Vector3& rGravity,                                            // 初期化処理
                        float airDensity);
        void Update();                                                                      // 更新処理
        void Finalize();                                                                    // 終了処理
        btSoftRigidDynamicsWorld* GetWorld() const;                                         // ワールドを取得
        SoftBodyInfo* GetSoftBodyInfo() const;                                              // ソフトボディ情報を取得
        void SetFrameSimulationTime(float frameSimulationTime);                             // 1フレームのシミュレーション時間を設定
        void SetMaxSubStepCount(int32_t maxSubStepCount);                                   // 最大サブステップ数を設定
        void EnableActive(bool validFlag);                                                  // アクティブ状態を有効化
    private:
        float frameSimulationTime_ = 1.0f / 60.0f;                                          ///< @brief 1フーレムのシミュレーション時間
        int32_t maxSubStepCount_ = 5;                                                       ///< @brief 最大サブステップ数
        bool activeFlag_ = true;                                                            ///< @brief アクティブ状態を判断するフラグ
        std::unique_ptr<btDefaultCollisionConfiguration> upConfig_;                         ///< @brief コンフィグ
        std::unique_ptr<btCollisionDispatcher> upDispatcher_;                               ///< @brief ディスパッチャー
        std::unique_ptr<btBroadphaseInterface> upBroadphase_;                               ///< @brief ブロードフェーズ
        std::unique_ptr<btConstraintSolver> upSolver_;                                      ///< @brief ソルバ
        std::unique_ptr<btSoftRigidDynamicsWorld> upWorld_;                                 ///< @brief ワールド
        std::unique_ptr<SoftBodyInfo, C_SoftBodyInfoDeleter> upSoftBodyInfo_;               ///< @brief ソフトボディー情報
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ワールドのX座標の最小値
     *  @param  ワールドのY座標の最小値
     *  @param  ワールドのZ座標の最小値
     *  @param  ワールドのX座標の最大値
     *  @param  ワールドのY座標の最大値
     *  @param  ワールドのZ座標の最大値
     *  @param  最大オブジェクト数
     *
     ****************************************************************/
    C_PhysicsEngine::C_PhysicsEngineImpl::C_PhysicsEngineImpl(const Vector3& rWorldMin,        
                                                              const Vector3& rWorldMax, 
                                                              uint16_t maxObjectCount) :

        // コンフィグ
        upConfig_(std::make_unique<btSoftBodyRigidBodyCollisionConfiguration>()),

        // ソルバ
        upSolver_(std::make_unique<btSequentialImpulseConstraintSolver>())

    {
        // ディスパッチャーを生成
        upDispatcher_ = std::make_unique<btCollisionDispatcher>(upConfig_.get());

        // ブロードフェーズを生成
        upBroadphase_ = std::make_unique<btAxisSweep3>(rWorldMin, rWorldMax, maxObjectCount);
        // ※ 状況によってブロードフェーズを使い分ける( 動的なオブジェクトが多い : btAxisSweep3 / 少ない : btDbvtBroadphase )
        // std::make_unique<btDbvtBroadphase>();

        // ワールドを作成
        upWorld_ = std::make_unique<btSoftRigidDynamicsWorld>(upDispatcher_.get(), 
                                                              upBroadphase_.get(),
                                                              upSolver_.get(),
                                                              upConfig_.get(), 
                                                              nullptr);
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PhysicsEngine::C_PhysicsEngineImpl::~C_PhysicsEngineImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  物理エンジンの初期化処理を行う
     *  @param  重力
     *  @param  空気密度
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::C_PhysicsEngineImpl::Initialize(const Vector3& rGravity,
                                                          float airDensity)
    {
        // ソフトボディ情報を設定
        upSoftBodyInfo_.reset(Common::C_CommonHelper::s_AlignedNew<SoftBodyInfo>());
        upSoftBodyInfo_->m_dispatcher = upDispatcher_.get();
        upSoftBodyInfo_->m_broadphase = upBroadphase_.get();
        upSoftBodyInfo_->m_gravity = rGravity;
        upSoftBodyInfo_->air_density = airDensity;
        upSoftBodyInfo_->water_density = 0.0f;
        upSoftBodyInfo_->water_offset = 0.0f;
        upSoftBodyInfo_->water_normal = btVector3(0.0f, 0.0f, 0.0f);
        upSoftBodyInfo_->m_sparsesdf.Initialize();

        // ワールドの設定
        upWorld_->setDebugDrawer(nullptr);
        upWorld_->setGravity(rGravity);
    }


    /*************************************************************//**
     *
     *  @brief  物理エンジンの更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::C_PhysicsEngineImpl::Update()
    {
        if (activeFlag_ == true)
        {
            // シミュレーションを行う
            upWorld_->stepSimulation(frameSimulationTime_, maxSubStepCount_, frameSimulationTime_ / static_cast<float>(maxSubStepCount_));

            // ソフトボディ情報のセルをガーベジコレクションする
            upSoftBodyInfo_->m_sparsesdf.GarbageCollect();
        }
    }


    /*************************************************************//**
     *
     *  @brief  物理エンジンの終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::C_PhysicsEngineImpl::Finalize()
    {
        // セルのメモリを解放
        upSoftBodyInfo_->m_sparsesdf.Reset();
    }


    /*************************************************************//**
     *
     *  @brief  ワールドを取得する
     *  @param  なし
     *  @return ワールド
     *
     ****************************************************************/
    btSoftRigidDynamicsWorld* C_PhysicsEngine::C_PhysicsEngineImpl::GetWorld() const
    {
        return upWorld_.get();
    }


    /*************************************************************//**
     *
     *  @brief  ソフトボディ情報を取得する
     *  @param  なし
     *  @return ソフトボディ情報
     *
     ****************************************************************/
    SoftBodyInfo* C_PhysicsEngine::C_PhysicsEngineImpl::GetSoftBodyInfo() const
    {
        return upSoftBodyInfo_.get();
    }


    /*************************************************************//**
     *
     *  @brief  1フレームのシミュレーション時間を設定する
     *  @param  1フレームのシミュレーション時間
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::C_PhysicsEngineImpl::SetFrameSimulationTime(float frameSimulationTime)
    {
        frameSimulationTime_ = frameSimulationTime;
    }


    /*************************************************************//**
     *
     *  @brief  最大サブステップ数を設定する
     *  @param  最大サブステップ数
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::C_PhysicsEngineImpl::SetMaxSubStepCount(int32_t maxSubStepCount)
    {
        maxSubStepCount_ = maxSubStepCount;
    }


    /*************************************************************//**
     *
     *  @brief  最大サブステップ数を設定する
     *  @param  最大サブステップ数
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::C_PhysicsEngineImpl::EnableActive(bool validFlag)
    {
        activeFlag_ = validFlag;
    }
}