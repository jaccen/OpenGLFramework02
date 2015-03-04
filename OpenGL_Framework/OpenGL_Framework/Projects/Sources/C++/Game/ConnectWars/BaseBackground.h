/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Library/GameObject/GameObject.h"
#include "../../Library/Shader/GLSL/Object/Manager/GlslObjectManager.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"
#include "ConnectWarsDefine.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* 前方宣言 */
    class C_BackgroundMoveLogic;


    //-------------------------------------------------------------
    //!
    //! @brief スペース
    //! @brief 宇宙のスカイスフィアを描画するクラス
    //!
    //-------------------------------------------------------------
    class C_BaseBackground : public GameObject::C_GameObject
    {
    public:
        C_BaseBackground(const std::string& rId, int32_t type);                         // コンストラクタ
        virtual ~C_BaseBackground();                                                    // デストラクタ
        bool Update() override;                                                         // 更新処理
        void Draw() override;                                                           // 描画処理
        bool MessageProcess(const Telegram& rTelegram) override;                        // メッセージ処理
        const Vector3& GetPosition() const;                                             // 座標を取得
        const Vector3& GetRotation() const;                                             // 回転量を取得
        C_BackgroundMoveLogic* GetMoveLogic() const;                                    // 移動ロジックを取得
        void SetPosition(const Vector3& rPosition);                                     // 座標を設定
        void SetRotation(const Vector3& rRotation);                                     // 回転量を設定
        virtual void SetScale(const Vector3& rScale);                                   // 拡大率を設定
        void SetLifeFrame(int32_t lifeFrame);                                           // 生存フレーム数を設定
    protected:
        Shader::GLSL::GlslObjectPtr pGlslObject_;                                       ///< @brief GLSLオブジェクト
        Shader::GLSL::UniformBufferPtr pUniformBuffer_;                                 ///< @brief ユニフォームバッファ
        Shader::GLSL::UniformBlockIndex uniformBlockIndex_ = 0;                         ///< @brief ユニフォームブロックのインデックス
        int32_t lifeFrame_ = 0;                                                         ///< @brief 生存フレーム数
        Timer::C_FrameCounter frameCounter_;                                            ///< @brief フレームカウンター
        Vector3 position_;                                                              ///< @brief 座標
        Vector3 rotation_;                                                              ///< @brief 回転量
        Vector3 scale_ = Vector3::s_ONE;                                                ///< @brief 拡大率
        std::unique_ptr<C_BackgroundMoveLogic> upMoveLogic_;                            ///< @brief 移動ロジック

        virtual void DoUpdate() = 0;                                                    // 非公開の更新処理
        virtual void DoDraw() = 0;                                                      // 非公開の描画処理
        virtual bool DoMessageProcess(const Telegram& rTelegram) = 0;                   // 非公開のメッセージ処理
    };
}