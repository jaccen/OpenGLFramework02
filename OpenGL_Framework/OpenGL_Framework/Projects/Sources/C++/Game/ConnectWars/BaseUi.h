/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Library/GameObject/GameObject.h"
#include "ConnectWarsDefine.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /** 文字UIの情報 */
    struct S_ImageUiData
    {
        Vector2 position_;
        Vector2 size_;
        Vector4 color_;
        Vector2 textureUpperLeft_;
        Vector2 textureLowerRight_;
    };

    /** 画像UIの情報 */
    struct S_WordUiData
    {
        std::string words_;
        Vector2 position_;
        Vector2 size_;
        Vector4 color_;
        float wordOffset_ = 0.0f;
    };


    //-------------------------------------------------------------
    //!
    //! @brief ベースUI
    //! @brief UIの基底クラス
    //!
    //-------------------------------------------------------------
    class C_BaseUi : public GameObject::C_GameObject
    {
    public:
        C_BaseUi(const std::string& rId, int32_t type);                         // コンストラクタ
        virtual ~C_BaseUi() override;                                           // デストラクタ
        bool Update() override;                                                 // 更新処理
        void Draw() override;                                                   // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override;                // メッセージ処理
    protected:
        bool updateLockFlag_ = false;                                           ///< @brief 更新ロックフラグ

        virtual void DoUpdate() = 0;                                            // 非公開の更新処理
        virtual void DoDraw() = 0;                                              // 非公開の描画処理
        virtual bool DoMessageProcess(const Telegram& rTelegram) = 0;           // 非公開のメッセージ処理
    };
}