/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Library/GameObject/GameObject.h"
#include "../../Library/Shader/GLSL/Object/Manager/GlslObjectManager.h"
#include "ConnectWarsDefine.h"


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
    //! @brief スペース
    //! @brief 宇宙のスカイスフィアを描画するクラス
    //!
    //-------------------------------------------------------------
    class C_BaseBackground : public GameObject::C_GameObject
    {
    public:
        C_BaseBackground(const std::string& rId, int32_t type);                 // コンストラクタ
        virtual ~C_BaseBackground();                                            // デストラクタ
        bool Update() override;                                                 // 更新処理
        void Draw() override;                                                   // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override;                // メッセージ処理
    protected:
        Shader::GLSL::GlslObjectPtr pGlslObject_;                               ///< @brief GLSLオブジェクト
        Shader::GLSL::UniformBufferPtr pUniformBuffer_;                         ///< @brief ユニフォームバッファ
        Shader::GLSL::UniformBlockIndex uniformBlockIndex_ = 0;                 ///< @brief ユニフォームブロックのインデックス

        virtual void DoUpdate() = 0;                                            // 非公開の更新処理
        virtual void DoDraw() = 0;                                              // 非公開の描画処理
        virtual bool DoMessageProcess(const Telegram& rTelegram) = 0;           // 非公開のメッセージ処理
    };
}