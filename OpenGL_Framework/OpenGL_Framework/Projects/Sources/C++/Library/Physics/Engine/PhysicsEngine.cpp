/* ヘッダファイル */
#include "PhysicsEngineImpl.h"


/* 外部で定義されているコールバック関数 */
extern ContactProcessedCallback gContactProcessedCallback;


//-------------------------------------------------------------
///
/// @brief フィジックス
/// @brief 物理関連の名前空間
///
//-------------------------------------------------------------
namespace Physics
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ワールドの最小値
     *  @param  ワールドの最大値
     *  @param  最大オブジェクト数
     *
     ****************************************************************/
    C_PhysicsEngine::C_PhysicsEngine(const Vector3& rWorldMin,
        const Vector3& rWorldMax,
        uint16_t maxObjectCount) :

        // 実装情報
        upImpl_(std::make_unique<C_PhysicsEngineImpl>(rWorldMin,
        rWorldMax,
        maxObjectCount))

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_PhysicsEngine::~C_PhysicsEngine()
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
    void C_PhysicsEngine::Initialize(const Vector3& rGravity,
        float airDensity)
    {
        upImpl_->Initialize(rGravity, airDensity);
    }


    /*************************************************************//**
     *
     *  @brief  物理エンジンの更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::Update()
    {
        upImpl_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  物理エンジンの終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::Finalize()
    {
        upImpl_->Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  剛体を追加する
     *  @param  剛体
     *  @param  衝突物の種類
     *  @param  衝突のマスク
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::AddRigidBody(C_RigidBody* pRigidBody,
        int16_t collisionObjectType,
        int16_t collisionMask)
    {
        if (collisionObjectType == -1 || collisionMask == -1)
        {
            upImpl_->GetWorld()->addRigidBody(pRigidBody->GetRigidBody());
        }
        else
        {
            upImpl_->GetWorld()->addRigidBody(pRigidBody->GetRigidBody(), collisionObjectType, collisionMask);
        }
    }


    /*************************************************************//**
     *
     *  @brief  軟体を追加する
     *  @param  軟体
     *  @param  衝突物の種類
     *  @param  衝突のマスク
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::AddSoftBody(C_SoftBody* pSoftBody,
        int16_t collisionObjectType,
        int16_t collisionMask)
    {
        upImpl_->GetWorld()->addSoftBody(pSoftBody->GetSoftBody(), collisionObjectType, collisionMask);
    }


    /*************************************************************//**
     *
     *  @brief  剛体を除去する
     *  @param  剛体
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::RemoveRigidBody(C_RigidBody* pRigidBody)
    {
        upImpl_->GetWorld()->removeRigidBody(pRigidBody->GetRigidBody());
    }


    /*************************************************************//**
     *
     *  @brief  軟体を除去する
     *  @param  軟体
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::RemoveSoftBody(C_SoftBody* pSoftBody)
    {
        upImpl_->GetWorld()->removeSoftBody(pSoftBody->GetSoftBody());
    }


    /*************************************************************//**
     *
     *  @brief  重力を取得する
     *  @param  なし
     *  @return 重力
     *
     ****************************************************************/
    const Vector3& C_PhysicsEngine::GetGravity() const
    {
        return upImpl_->GetWorld()->getGravity();
    }


    /*************************************************************//**
     *
     *  @brief  ソフトボディ情報を取得する
     *  @param  なし
     *  @return ソフトボディ情報
     *
     ****************************************************************/
    SoftBodyInfo* C_PhysicsEngine::GetSoftBodyInfo() const
    {
        return upImpl_->GetSoftBodyInfo();
    }


    /*************************************************************//**
     *
     *  @brief  重力を設定する
     *  @param  重力
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::SetGravity(const Vector3& rGravity)
    {
        upImpl_->GetWorld()->setGravity(rGravity);
    }


    /*************************************************************//**
     *
     *  @brief  衝突コールバック関数を設定する
     *  @param  衝突コールバック関数
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::SetCollisionCallbackFunction(CollisionCallbackFunction pCollisionCallbackFunction)
    {
        gContactProcessedCallback = pCollisionCallbackFunction;
    }


    /*************************************************************//**
     *
     *  @brief  シミュレーションのサブステップコールバック関数を設定する
     *  @param  シミュレーションのサブステップコールバック関数
     *  @param  ワールドの独自の情報
     *  @param  サブステップの前に呼ぶコールバック関数として登録するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::SetSimulationSubstepCallbackFunction(SimulationSubstepCallbackFunction pSimulationSubstepCallbackFunction,
        void* pWorldUserInfo,
        bool previousSubstepCallbackFlag)
    {
        upImpl_->GetWorld()->setInternalTickCallback(pSimulationSubstepCallbackFunction,
            pWorldUserInfo,
            previousSubstepCallbackFlag);
    }


    /*************************************************************//**
     *
     *  @brief  1フレームのシミュレーション時間を設定する
     *  @param  1フレームのシミュレーション時間
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::SetFrameSimulationTime(float frameSimulationTime)
    {
        upImpl_->SetFrameSimulationTime(frameSimulationTime);
    }


    /*************************************************************//**
     *
     *  @brief  最大サブステップ数を設定する
     *  @param  最大サブステップ数
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::SetMaxSubStepCount(int32_t maxSubStepCount)
    {
        upImpl_->SetMaxSubStepCount(maxSubStepCount);
    }


    /*************************************************************//**
     *
     *  @brief  アクティブ状態を有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_PhysicsEngine::EnableActive(bool validFlag)
    {

    }
}