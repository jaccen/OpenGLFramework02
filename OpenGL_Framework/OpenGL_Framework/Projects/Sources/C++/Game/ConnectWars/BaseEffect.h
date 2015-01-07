/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectWarsDefine.h"
#include "../../Library/GameObject/GameObject.h"


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
    //! @brief ベースエフェクト
    //! @brief エフェクトの基底クラス
    //!
    //-------------------------------------------------------------
    class C_BaseEffect : public GameObject::C_GameObject
    {
    public:
        C_BaseEffect(const std::string& rId, int32_t type);                     // コンストラクタ
        virtual ~C_BaseEffect() override;                                       // デストラクタ
        bool Update() override;                                                 // 更新処理
        void Draw() override;                                                   // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override;                // メッセージ処理
    protected:
        virtual void DoUpdate() = 0;                                            // 非公開の更新処理
        virtual void DoDraw() = 0;                                              // 非公開の描画処理
        virtual bool DoMessageProcess(const Telegram& rTelegram) = 0;           // 非公開のメッセージ処理
    };
}
