/* ヘッダファイル */
#include "BasePlayer.h"
#include "BaseOption.h"
#include "CollisionProcess.h"
#include "InputShotLogic.h"
#include "BaseGun.h"
#include "PlayerCombatState.h"
#include "PlayerConnectState.h"
#include "PlayerBombChargeState.h"
#include "RigidBodyInputMoveLogic.h"
#include "../../Library/Debug/Helper/DebugHelper.h"
#include "../../Library/Model/SelfMade/Loader/ModelLoader.h"
#include "../../Library/OpenGL/Buffer/Primitive/PrimitiveDefine.h"


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
    C_BasePlayer::C_BasePlayer(const std::string& rId, int32_t type) : C_ConnectMachine(rId, type),

        // ステートマシーン
        upStateMachine_(std::make_unique<State::C_StateMachine<C_BasePlayer>>(this, C_PlayerCombatState::s_GetInstance()))

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BasePlayer::~C_BasePlayer()
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
    bool C_BasePlayer::Update()
    {
        DoUpdate();

        return existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::Draw()
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
    bool C_BasePlayer::MessageProcess(const Telegram& rTelegram)
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
    void C_BasePlayer::DispatchCollision(C_CollisionObject* pCollisionObject)
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
    void C_BasePlayer::CollisionProcess(C_BasePlayer* pPlayer)
    {
        C_CollisionProcess::s_PlayerAndPlayer(this, pPlayer);
    }


    /*************************************************************//**
     *
     *  @brief  オプションとの衝突時処理を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BaseOption* pOption)
    {
        C_CollisionProcess::s_PlayerAndOption(this, pOption);
    }


    /*************************************************************//**
     *
     *  @brief  敵との衝突時処理を行う
     *  @param  敵
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BaseEnemy* pEnemy)
    {
        C_CollisionProcess::s_PlayerAndEnemy(this, pEnemy);
    }


    /*************************************************************//**
     *
     *  @brief  弾との衝突時処理を行う
     *  @param  弾
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BaseBullet* pBullet)
    {
        C_CollisionProcess::s_PlayerAndBullet(this, pBullet);
    }


    /*************************************************************//**
     *
     *  @brief  障害物との衝突時処理を行う
     *  @param  障害物
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BaseObstacle* pObstacle)
    {
        C_CollisionProcess::s_PlayerAndObstacle(this, pObstacle);
    }


    /*************************************************************//**
     *
     *  @brief  ボムとの衝突時処理を行う
     *  @param  ボム
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::CollisionProcess(C_BaseBomb* pBomb)
    {
        C_CollisionProcess::s_PlayerAndBomb(this, pBomb);
    }


    /*************************************************************//**
     *
     *  @brief  移動処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::Move()
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
    void C_BasePlayer::Shot()
    {
        for (auto& uprGun : upGuns_) uprGun->Shot();
    }


    /*************************************************************//**
     *
     *  @brief  ボム処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::Bomb()
    {
        if ((connectOptionCount_ > 0)
         && (upStateMachine_->CheckCurrentState(*C_PlayerCombatState::s_GetInstance()) == true)
         && ((Input::C_KeyboardManager::s_GetInstance()->GetPressingCount(bombKeyCode_) == 1)
         ||  (Input::C_GamepadManager::s_GetInstance()->GetButtonPressingCount(bombGamepadButton_) == 1)))
        {
            // ボムのチャージ状態に変更
            upStateMachine_->ChangeState(C_PlayerBombChargeState::s_GetInstance());

            // 連結しているオプションに自爆を発送
            for (auto pOption : pConnectOptionList_) pOption->DispatchOwnCrash();
        }
    }


    /*************************************************************//**
     *
     *  @brief  連結しているオプションのIDを追加する
     *  @param  連結しているオプションのID
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::AddConnectOption(C_BaseOption* pOption)
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
    void C_BasePlayer::ResetConnect()
    {
        pConnectOptionList_.clear();
    }


    /*************************************************************//**
     *
     *  @brief  連結の確認を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::ConnectCheck()
    {
        for (auto pOption : pConnectOptionList_)
        {
            // オプションリストの、移動制限境界ボックスの更新と連結の確認
            UpdateMoveLimitBoundingBox(pOption);
            ConnectCheck(pOption);
        }
    }


    /*************************************************************//**
     *
     *  @brief  連結の確認を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::ConnectCheck(C_BaseOption* pOption)
    {
        for (auto pAnotherOption : *pOption->GetConnectOptionList())
        {
            if (pAnotherOption->IsConnectFlag() == false)
            {
                // 連結フラグを設定
                pAnotherOption->SetConnectFlag(true);

                if (pAnotherOption->IsOnceConnectFlag() == false)
                {
                    // プレイヤーを設定
                    pAnotherOption->SetPlayer(this);

                    // 一度連結したか判断するフラグ
                    pAnotherOption->SetOnceConnectFlag(true);

                    // プレイヤーからのオフセットを求める
                    auto anotherOptionTransform = pAnotherOption->GetRigidBody()->GetTransform();

                    Physics::Vector3 anotherOptionOffsetFromPlayer = anotherOptionTransform.getOrigin() - pOption->GetRigidBody()->GetTransform().getOrigin();
                    anotherOptionOffsetFromPlayer = anotherOptionOffsetFromPlayer.normalize();
                    anotherOptionOffsetFromPlayer = pOption->GetOffsetFromPlayer()
                                                  + (anotherOptionOffsetFromPlayer * pOption->GetRadius())
                                                  + (anotherOptionOffsetFromPlayer * pAnotherOption->GetRadius());
                    anotherOptionOffsetFromPlayer *= Connect::s_offsetFactor;
                    pAnotherOption->SetOffsetFromPlayer(anotherOptionOffsetFromPlayer);

                    // オプションの座標を設定
                    anotherOptionTransform.setOrigin(upRigidBody_->GetTransform().getOrigin() + anotherOptionOffsetFromPlayer);
                    pAnotherOption->GetRigidBody()->SetTransform(anotherOptionTransform);

                    // 新規連結処理を行う
                    NewConnect();
                    pAnotherOption->NewConnect();

                    // 連結の効果を処理
                    pAnotherOption->ConnectEffect();

                    // 移動制限境界ボックスの更新
                    UpdateMoveLimitBoundingBox(pAnotherOption);
                }

                // そのオプションの連結の確認
                ConnectCheck(pAnotherOption);
            }
        }
    }


    /*************************************************************//**
     *
     *  @brief  新規連結を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::NewConnect()
    {
        // オプション数を1増加
        AddConnectOptionCount(1);

        // 連結状態に変更
        upStateMachine_->ChangeState(C_PlayerConnectState::s_GetInstance());
    }


    /*************************************************************//**
     *
     *  @brief  移動制限の確認を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::MoveLimitCheck()
    {
        auto transform = upRigidBody_->GetTransform();
        auto& rPosition = transform.getOrigin();

        if (rPosition.x() + moveLimitBoundingBox_.min_.x_ < StageSize::s_left)
        {
            rPosition.setX(StageSize::s_left - moveLimitBoundingBox_.min_.x_);
        }
        else if (rPosition.x() + moveLimitBoundingBox_.max_.x_ > StageSize::s_right)
        {
            rPosition.setX(StageSize::s_right - moveLimitBoundingBox_.max_.x_);
        }

        if (rPosition.y() + moveLimitBoundingBox_.min_.y_ < StageSize::s_bottom)
        {
            rPosition.setY(StageSize::s_bottom - moveLimitBoundingBox_.min_.y_);
        }
        else if (rPosition.y() + moveLimitBoundingBox_.max_.y_ > StageSize::s_top)
        {
            rPosition.setY(StageSize::s_top - moveLimitBoundingBox_.max_.y_);
        }

        upRigidBody_->SetTransform(transform);
    }


    /*************************************************************//**
     *
     *  @brief  移動制限境界ボックスの更新を行う
     *  @param  オプション
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::UpdateMoveLimitBoundingBox(C_BaseOption* pOption)
    {
        auto& rPlayerPosition = upRigidBody_->GetTransform().getOrigin();
        auto& rOptionPosition = pOption->GetRigidBody()->GetTransform().getOrigin();
        
        float optionRadius = pOption->GetRadius();

        if (rPlayerPosition.x() + moveLimitBoundingBox_.min_.x_ > rOptionPosition.x() - optionRadius)
        {
            moveLimitBoundingBox_.min_.x_ = rOptionPosition.x() - rPlayerPosition.x() - optionRadius;
        }
        else if (rPlayerPosition.x() + moveLimitBoundingBox_.max_.x_ < rOptionPosition.x() + optionRadius)
        {
            moveLimitBoundingBox_.max_.x_ = rOptionPosition.x() - rPlayerPosition.x() + optionRadius;
        }

        if (rPlayerPosition.y() + moveLimitBoundingBox_.min_.y_ > rOptionPosition.y() - optionRadius)
        {
            moveLimitBoundingBox_.min_.y_ = rOptionPosition.y() - rPlayerPosition.y() - optionRadius;
        }
        else if (rPlayerPosition.y() + moveLimitBoundingBox_.max_.y_ < rOptionPosition.y() + optionRadius)
        {
            moveLimitBoundingBox_.max_.y_ = rOptionPosition.y() - rPlayerPosition.y() + optionRadius;
        }
    }


    /*************************************************************//**
     *
     *  @brief  移動制限境界ボックスのリセットを行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::ResetMoveLimitBoundingBox()
    {
        moveLimitBoundingBox_.min_.Fill(-radius_);
        moveLimitBoundingBox_.max_.Fill(radius_);
    }


    /*************************************************************//**
     *
     *  @brief  移動速度のレベルを加算する
     *  @param  移動速度のレベル
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::AddMoveSpeedLevel(int32_t moveSpeedLevel)
    {
        moveSpeedLevel_ += moveSpeedLevel;

        assert(moveSpeedLevel_ >= 0);
        assert(dynamic_cast<C_RigidBodyInputMoveLogic*>(upMoveLogic_.get()));

        auto pInputMoveLogic = static_cast<C_RigidBodyInputMoveLogic*>(upMoveLogic_.get());

        if (moveSpeedLevel < s_MAX_MOVE_SPEED_LEVEL)
        {
            pInputMoveLogic->SetMovementScale(1.0f + moveSpeedUpInterval_ * moveSpeedLevel_);
        }
        else
        {
            pInputMoveLogic->SetMovementScale(1.0f + moveSpeedUpInterval_ * s_MAX_MOVE_SPEED_LEVEL);
        }
    }


    /*************************************************************//**
     *
     *  @brief  連結したオプションの数を加算する
     *  @param  連結したオプションの数
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::AddConnectOptionCount(int32_t connectOptionCount)
    {
        connectOptionCount_ += connectOptionCount;
    }


    /*************************************************************//**
     *
     *  @brief  ステートマシーンを取得する
     *  @param  なし
     *  @return ステートマシーン
     *
     ****************************************************************/
    State::C_StateMachine<C_BasePlayer>* C_BasePlayer::GetStateMachine() const
    {
        return upStateMachine_.get();
    }


    /*************************************************************//**
     *
     *  @brief  連結の硬直フレーム数を取得する
     *  @param  なし
     *  @return 連結の硬直フレーム数
     *
     ****************************************************************/
    int32_t C_BasePlayer::GetConnectPetrifyFrame() const
    {
        return connectPetrifyFrame_;
    }


    /*************************************************************//**
     *
     *  @brief  ボムのチャージフレーム数を取得する
     *  @param  なし
     *  @return ボムのチャージフレーム数
     *
     ****************************************************************/
    int32_t C_BasePlayer::GetBombChargeFrame() const
    {
        return bombChargeFrame_;
    }


    /*************************************************************//**
     *
     *  @brief  ボムの無敵フレーム数を取得する
     *  @param  なし
     *  @return ボムの無敵フレーム数
     *
     ****************************************************************/
    int32_t C_BasePlayer::GetBombInvincibleFrame() const
    {
        return bombInvincibleFrame_;
    }


    /*************************************************************//**
     *
     *  @brief  ボムのチャージフラグを取得する
     *  @param  なし
     *  @return ボムのチャージフラグ
     *
     ****************************************************************/
    bool C_BasePlayer::IsBombChargeFlag() const
    {
        return bombChargeFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  ボムのチャージフラグを設定する
     *  @param  ボムのチャージフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::SetBombChargeFlag(bool bombChargeFlag)
    {
        bombChargeFlag_ = bombChargeFlag;
    }


    /*************************************************************//**
     *
     *  @brief  非公開の更新処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BasePlayer::DoUpdate()
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
    bool C_BasePlayer::DoMessageProcess(const Telegram& rTelegram)
    {
        return (upStateMachine_->MessageProcess(rTelegram) == true);
    }
}