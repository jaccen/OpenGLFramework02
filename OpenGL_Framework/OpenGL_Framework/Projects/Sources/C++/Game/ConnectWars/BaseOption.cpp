/* ヘッダファイル */
#include "BaseOption.h"
#include "BasePlayer.h"
#include "CollisionProcess.h"
#include "OptionDropState.h"
#include "OptionConnectState.h"
#include "OptionWaitOwnCrashState.h"
#include "OptionOwnCrashState.h"
#include "BaseGun.h"
#include "RigidBodyConnectMoveLogic.h"
#include "EffectGenerator.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ID
     *  @param  種類
     *
     ****************************************************************/
    C_BaseOption::C_BaseOption(const std::string& rId, int32_t type) : C_ConnectMachine(rId, type),

        // ステートマシーン
        upStateMachine_(std::make_unique<State::C_StateMachine<C_BaseOption>>(this))

    {
        // 現在のステートを設定
		upStateMachine_->ChangeState(C_OptionDropState::s_GetInstance());
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BaseOption::~C_BaseOption()
    {
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return タスク続行：true
     *  @return タスク終了：false
     *
     ****************************************************************/
    bool C_BaseOption::Update()
    {
        // 常に剛体をアクティブ状態とする
        upRigidBody_->EnableActive(true);

        // 非公開の更新処理
        DoUpdate();

        // 衝突したオブジェクトのIDを全てリセット
        ResetCollidedObjectId();

        return C_GameObject::existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::Draw()
    {
        if (pPlayer_ == nullptr 
         || waitOwnCrashFlag_ == true
         || pPlayer_->IsDrawFlag() == true)
        {
            DoDraw();
        }
    }


    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_BaseOption::MessageProcess(const Telegram& rTelegram)
    {
        if (DoMessageProcess(rTelegram) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  衝突検出の発行を行う
     *  @param  衝突オブジェクト
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::DispatchCollision(C_CollisionObject* pCollisionObject)
    {
        pCollisionObject->CollisionProcess(this);
    }


    /*************************************************************//**
     *
     *  @brief  プレイヤーとの衝突時処理を行う
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::CollisionProcess(C_BasePlayer* pPlayer)
    {
        C_CollisionProcess::s_PlayerAndOption(pPlayer, this);
    }


    /*************************************************************//**
     *
     *  @brief  オプションとの衝突時処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::CollisionProcess(C_BaseOption* pOption)
    {
        C_CollisionProcess::s_OptionAndOption(this, pOption);
    }


    /*************************************************************//**
     *
     *  @brief  敵との衝突時処理を行う
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::CollisionProcess(C_BaseEnemy* pEnemy)
    {
        C_CollisionProcess::s_OptionAndEnemy(this, pEnemy);
    }


    /*************************************************************//**
     *
     *  @brief  弾との衝突時処理を行う
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::CollisionProcess(C_BaseBullet* pBullet)
    {
        C_CollisionProcess::s_OptionAndBullet(this, pBullet);
    }


    /*************************************************************//**
     *
     *  @brief  障害物との衝突時処理を行う
     *  @param  障害物
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::CollisionProcess(C_BaseObstacle* pObstacle)
    {
        C_CollisionProcess::s_OptionAndObstacle(this, pObstacle);
    }


    /*************************************************************//**
     *
     *  @brief  ボムとの衝突時処理を行う
     *  @param  ボム
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::CollisionProcess(C_BaseBomb* pBomb)
    {
        C_CollisionProcess::s_OptionAndBomb(this, pBomb);
    }


    /*************************************************************//**
     *
     *  @brief  シールドとの衝突時処理を行う
     *  @param  シールド
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::CollisionProcess(C_BaseShield* pShield)
    {
        C_CollisionProcess::s_OptionAndShield(this, pShield);
    }


    /*************************************************************//**
     *
     *  @brief  移動処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::Move()
    {
        upMoveLogic_->Process(upRigidBody_.get());
    }


    /*************************************************************//**
     *
     *  @brief  射撃処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::Shot()
    {
        for (auto& uprGun : upGuns_) uprGun->Shot();
    }


    /*************************************************************//**
     *
     *  @brief  効果をリセットする
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::ResetEffect()
    {
    }


    /*************************************************************//**
     *
     *  @brief  連結しているオプションを追加する
     *  @param  連結しているオプション
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::AddConnectOption(C_BaseOption* pOption)
    {
        pConnectOptionList_.push_back(pOption);
    }


    /*************************************************************//**
     *
     *  @brief  連結のリセットを行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::ResetConnect()
    {
        connectFlag_ = false;
        pConnectOptionList_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  新規連結を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::NewConnect()
    {
        // 連結状態へ変更
        upStateMachine_->ChangeState(C_OptionConnectState::s_GetInstance());

        C_EffectGenerator::s_GetInstance()->Create(ID::Generator::Effect::s_pCONNECT,
                                                   Vector3(upRigidBody_->GetTransform().getOrigin().x(),
                                                           upRigidBody_->GetTransform().getOrigin().y(),
                                                           upRigidBody_->GetTransform().getOrigin().z()));

        // 剛体に加えられている力をリセット
        upRigidBody_->EnableActive(true);
        upRigidBody_->SetLinearVelocity();
        upRigidBody_->SetAngularVelocity();
        upRigidBody_->ResetVelocity();

        // 連結時の移動ロジックに変更
        assert(pPlayer_);
        upMoveLogic_ = std::make_unique<C_RigidBodyConnectMoveLogic>(pPlayer_, *upOffsetFromPlayer_);
    }


    /*************************************************************//**
     *
     *  @brief  移動制限の確認を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::MoveLimitCheck()
    {
        if (upRigidBody_->GetTransform().getOrigin().y() < StageSize::s_bottom - 10.0f)
        {
            existenceFlag_ = false;
        }
    }



    /*************************************************************//**
     *
     *  @brief  連結時の効果を処理する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::ConnectEffect()
    {
    }


    /*************************************************************//**
     *
     *  @brief  自爆の発送を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::DispatchOwnCrash()
    {
        if (upStateMachine_->CheckCurrentState(C_OptionWaitOwnCrashState::s_GetInstance()) == false)
        {
            upStateMachine_->ChangeState(C_OptionWaitOwnCrashState::s_GetInstance());
            waitOwnCrashFlag_ = true;

            for (auto& prOption : pConnectOptionList_)
            {
                prOption->DispatchOwnCrash();
            }

            ResetConnect();
        }
    }


    /*************************************************************//**
     *
     *  @brief  自爆処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::OwnCrash()
    {
        upStateMachine_->ChangeState(C_OptionOwnCrashState::s_GetInstance());

        // エフェクトを生成
        auto& rPosition = GetPosition();
        C_EffectGenerator::s_GetInstance()->Create(GetBombOwnCrashEffectId(),
                                                   Vector3(rPosition.x(), rPosition.y(), rPosition.z()));
    }


    /*************************************************************//**
     *
     *  @brief  連結の無効化をする
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::DisableConnect()
    {
        if (enableConnectFlag_ == true)
        {
            enableConnectFlag_ = false;

            for (auto& prOption : pConnectOptionList_) prOption->DisableConnect();
        }
    }


    /*************************************************************//**
     *
     *  @brief  ステートマシーンを取得する
     *  @param  なし
     *  @return ステートマシーン
     *
     ****************************************************************/
    State::C_StateMachine<C_BaseOption>* C_BaseOption::GetStateMachine() const
    {
        return upStateMachine_.get();
    }


    /*************************************************************//**
     *
     *  @brief  プレイヤーからのオフセットを取得する
     *  @param  なし
     *  @return プレイヤーからのオフセット
     *
     ****************************************************************/
    const Physics::Vector3& C_BaseOption::GetOffsetFromPlayer() const
    {
        return *upOffsetFromPlayer_;
    }


    /*************************************************************//**
     *
     *  @brief  プレイヤーを取得する
     *  @param  なし
     *  @return プレイヤー
     *
     ****************************************************************/
    C_BasePlayer* C_BaseOption::GetPlayer() const
    {
        return pPlayer_;
    }


    /*************************************************************//**
     *
     *  @brief  一度連結したか判断するフラグを取得
     *  @param  なし
     *  @return 一度連結したか判断するフラグ
     *
     ****************************************************************/
    bool C_BaseOption::IsOnceConnectFlag() const
    {
        return onceConnectFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  連結フラグを取得
     *  @param  なし
     *  @return 連結フラグ
     *
     ****************************************************************/
    bool C_BaseOption::IsConnectFlag() const
    {
        return connectFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  撃破フラグを取得
     *  @param  なし
     *  @return 撃破フラグ
     *
     ****************************************************************/
    bool C_BaseOption::IsDefeatedFlag() const
    {
        return defeatedFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  撃破状態のフレーム数を取得
     *  @param  なし
     *  @return 撃破状態のフレーム数
     *
     ****************************************************************/
    int32_t C_BaseOption::GetDefeatedFrame() const
    {
        return defeatedFrame_;
    }


    /*************************************************************//**
     *
     *  @brief  ボムの自爆エフェクトのIDを取得
     *  @param  なし
     *  @return ボムの自爆エフェクトのID
     *
     ****************************************************************/
    const std::string& C_BaseOption::GetBombOwnCrashEffectId() const
    {
        return bombOwnCrashEffectId_;
    }


    /*************************************************************//**
     *
     *  @brief  一度連結したか判断するフラグを設定する
     *  @param  一度連結したか判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::SetOnceConnectFlag(bool onceConnectFlag)
    {
        onceConnectFlag_ = onceConnectFlag;
    }


    /*************************************************************//**
     *
     *  @brief  連結フラグを設定する
     *  @param  連結フラグ
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::SetConnectFlag(bool connectFlag)
    {
        connectFlag_ = connectFlag;
    }


    /*************************************************************//**
     *
     *  @brief  プレイヤーからのオフセットを設定する
     *  @param  プレイヤーからのオフセット
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::SetOffsetFromPlayer(const Physics::Vector3& rOffsetFromPlayer)
    {
        upOffsetFromPlayer_ = std::make_unique<Physics::Vector3>(rOffsetFromPlayer);
    }


    /*************************************************************//**
     *
     *  @brief  プレイヤーを設定する
     *  @param  プレイヤー
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::SetPlayer(C_BasePlayer* pPlayer)
    {
        pPlayer_ = pPlayer;
    }


    /*************************************************************//**
     *
     *  @brief  撃破フラグを設定する
     *  @param  撃破フラグ
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::SetDefeatedFlag(bool defeatedFlag)
    {
        defeatedFlag_ = defeatedFlag;
    }


    /*************************************************************//**
     *
     *  @brief  撃破フラグを設定する
     *  @param  撃破フラグ
     *  @return なし
     *
     ****************************************************************/
    bool C_BaseOption::IsWaitOwnCrashFlag() const
    {
        return waitOwnCrashFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  撃破フラグを設定する
     *  @param  撃破フラグ
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::SetWaitOwnCrashFlag(bool waitOwnCrashFlag)
    {
        waitOwnCrashFlag_ = waitOwnCrashFlag;
    }


    /*************************************************************//**
     *
     *  @brief  自爆フレームカウンタを取得する
     *  @param  なし
     *  @return 自爆フレームカウンタ
     *
     ****************************************************************/
    Timer::C_FrameCounter* C_BaseOption::GetOwnCrashFrameCounter()
    {
        return &ownCrashFrameCounter_;
    }


    /*************************************************************//**
     *
     *  @brief  非公開の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::DoUpdate()
    {
        upStateMachine_->Update();
    }


    /*************************************************************//**
     *
     *  @brief  非公開のメッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_BaseOption::DoMessageProcess(const Telegram& rTelegram)
    {
        return (upStateMachine_->MessageProcess(rTelegram) == true);
    }
}