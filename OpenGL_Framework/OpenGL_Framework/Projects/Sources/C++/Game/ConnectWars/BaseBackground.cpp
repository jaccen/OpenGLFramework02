/* ヘッダファイル */
#include "BaseBackground.h"


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