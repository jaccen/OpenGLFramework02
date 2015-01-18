/* ヘッダファイル */
#include "BaseOption.h"
#include "BasePlayer.h"
#include "CollisionProcess.h"
#include "OptionDropState.h"
#include "OptionConnectState.h"
#include "OptionWaitOwnCrashState.h"


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
		upStateMachine_->SetCurrentState(C_OptionDropState::s_GetInstance());
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BaseOption::~C_BaseOption()
    {
        if (onceConnectFlag_ == true) pPlayer_->AddConnectOptionCount(-1);
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
        DoUpdate();

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
        DoDraw();
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
     *  @brief  連結時の移動処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseOption::ConnectMove()
    {
        auto transform = upRigidBody_->GetTransform();
        auto position = transform.getOrigin();

        transform.setOrigin(pPlayer_->GetRigidBody()->GetTransform().getOrigin() + offsetFromPlayer_);
        upRigidBody_->SetTransform(transform);
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
        upStateMachine_->ChangeState(C_OptionConnectState::s_GetInstance());
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
        /*
        if (position_.y_ < GameDefine::StageSize::s_BORDER_BOTTOM - 5.0f)
        {
            existenceFlag_ = false;
        }
        */
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
        //upStateMachine_->ChangeState(C_OptionSelfCrashState::s_GetInstance());
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
        return offsetFromPlayer_;
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
    const std::string& C_BaseOption::GetBombSelfCrashEffectId() const
    {
        // TODO TODO TODO
        //return bombSelfCrashEffectId_;
        static std::string s;
        return s;
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
        offsetFromPlayer_ = rOffsetFromPlayer;
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