/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Library/Singleton/Assert/AssertSingleton.h"
#include "../../Library/Sprite/Creater/Manager/SpriteCreaterManager.h"
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
    //! @brief UIフォント
    //! @brief UI用のフォントを描画するクラス
    //! @brief ※ 使用する場合、フォント用のUIスプライトを作成後に生成すること
    //!
    //-------------------------------------------------------------
    class C_UiFont : public Singleton::C_AssertSingleton<C_UiFont>
    {
    public:
        C_UiFont();                                                                 // コンストラクタ
        ~C_UiFont() override;                                                       // デストラクタ
        void Draw(const std::string& rWords,                                        // 描画処理
                  const Vector2& rPosition,
                  float angle,
                  const Vector2& rSize,
                  float wordOffset = 0.0f,
                  const Vector4& rColor = Vector4::s_ONE);
        void DrawArrow(const Vector2& rPosition,                                    // 矢印の描画
                       float angle,
                       const Vector2& rSize,
                       const Vector4& rColor = Vector4::s_ONE);
    private:
        Sprite::SpriteCreaterWeakPtr wpSpriteCreater_;                              ///< @brief スプライトクリエイター
    };
}