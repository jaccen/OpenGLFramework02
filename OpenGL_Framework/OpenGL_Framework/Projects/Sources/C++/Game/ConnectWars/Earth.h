/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"
#include "../../Library/Shader/GLSL/Uniform/Manager/UniformBufferManager.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "BaseBackground.h"


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
    //! @brief アース
    //! @brief 地球を表すクラス
    //!
    //-------------------------------------------------------------
    class C_Earth : public C_BaseBackground
    {
    public:
        C_Earth(const std::string& rId, int32_t type);                          // コンストラクタ
        virtual ~C_Earth();                                                     // デストラクタ
    private:
        OpenGL::PrimitiveBufferPtr pModelData_;                                 ///< @brief モデル情報
        Texture::TextureDataPtr pTextureData_;                                  ///< @brief テクスチャデータ
        Matrix4x4 modelMatrix_;                                                 ///< @brief モデル行列

        virtual void DoUpdate() override;                                       // 非公開の更新処理
        virtual void DoDraw() override;                                         // 非公開の描画処理
        virtual bool DoMessageProcess(const Telegram& rTelegram) override;      // 非公開のメッセージ処理
    };
}