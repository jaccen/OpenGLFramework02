/* ヘッダファイル */
#include "BaseBackground.h"
#include "BackgroundStraightMoveLogic.h"


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
    C_BaseBackground::C_BaseBackground(const std::string& rId, int32_t type) : C_GameObject(rId, type)
    {
        upMoveLogic_ = std::make_unique<C_BackgroundStraightMoveLogic>();
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_BaseBackground::~C_BaseBackground()
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
    bool C_BaseBackground::Update()
    {
        DoUpdate();

        upMoveLogic_->Process(this);

        if (lifeFrame_ == frameCounter_.GetCount())
        {
            existenceFlag_ = false;
        }
        else
        {
            frameCounter_.CountUp();
        }

        return C_GameObject::existenceFlag_;
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBackground::Draw()
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
    bool C_BaseBackground::MessageProcess(const Telegram& rTelegram)
    {
        return DoMessageProcess(rTelegram);
    }


    /*************************************************************//**
     *
     *  @brief  座標を取得する
     *  @param  なし
     *  @return 座標
     *
     ****************************************************************/
    const Vector3& C_BaseBackground::GetPosition() const
    {
        return position_;
    }


    /*************************************************************//**
     *
     *  @brief  回転量を取得する
     *  @param  なし
     *  @return 回転量
     *
     ****************************************************************/
    const Vector3& C_BaseBackground::GetRotation() const
    {
        return rotation_;
    }


    /*************************************************************//**
     *
     *  @brief  移動ロジックを取得する
     *  @param  なし
     *  @return 移動ロジック
     *
     ****************************************************************/
    C_BackgroundMoveLogic* C_BaseBackground::GetMoveLogic() const
    {
        return upMoveLogic_.get();
    }


    /*************************************************************//**
     *
     *  @brief  座標を設定する
     *  @param  座標
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBackground::SetPosition(const Vector3& rPosition)
    {
        position_ = rPosition;
    }


    /*************************************************************//**
     *
     *  @brief  回転量を設定する
     *  @param  回転量
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBackground::SetRotation(const Vector3& rRotation)
    {
        rotation_ = rRotation;
    }


    /*************************************************************//**
     *
     *  @brief  拡大率を設定する
     *  @param  拡大率
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBackground::SetScale(const Vector3& rScale)
    {
        scale_ = rScale;
    }


    /*************************************************************//**
     *
     *  @brief  生存フレーム数を設定する
     *  @param  生存フレーム数
     *  @return なし
     *
     ****************************************************************/
    void C_BaseBackground::SetLifeFrame(int32_t lifeFrame)
    {
        lifeFrame_ = lifeFrame;
    }
}