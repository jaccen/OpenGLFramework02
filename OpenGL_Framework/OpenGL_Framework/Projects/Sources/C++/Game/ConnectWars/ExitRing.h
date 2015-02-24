/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"
#include "../../Library/Shader/GLSL/Uniform/Manager/UniformBufferManager.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "../../Library/Material/Manager/MaterialManager.h"
#include "../../Library/Light/Manager/LightManager.h"
#include "../../Library/Camera/Manager/CameraManager.h"
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
    //! @brief エグジットリング
    //! @brief シェルターの出口のリングを表すクラス
    //!
    //-------------------------------------------------------------
    class C_ExitRing : public C_BaseBackground
    {
    public:
        C_ExitRing(const std::string& rId, int32_t type);                       // コンストラクタ
        virtual ~C_ExitRing();                                                  // デストラクタ
    private:
        OpenGL::PrimitiveBufferPtr pModelData_;                                 ///< @brief モデル情報
        Texture::TextureDataPtr pTextureData_;                                  ///< @brief テクスチャデータ
        Texture::TextureDataPtr pNormalTextureData_;                            ///< @brief 法線テクスチャデータ
        Matrix4x4 modelMatrix_;                                                 ///< @brief モデル行列
        Material::MaterialPtr pMaterial_;                                       ///< @brief マテリアル
        Light::LightPtr pLight_;                                                ///< @brief ライト
        int32_t cameraSubroutineIndex_ = 0;                                     ///< @brief カメラサブルーチンインデックス

        virtual void DoUpdate() override;                                       // 非公開の更新処理
        virtual void DoDraw() override;                                         // 非公開の描画処理
        virtual bool DoMessageProcess(const Telegram& rTelegram) override;      // 非公開のメッセージ処理
        void SetMaterial(const Material::MaterialPtr& prMaterial);              // マテリアルを設定
        void SetLight(const Light::LightPtr& prLight);                          // ライトを設定
    };
}