/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "ConnectWarsDefine.h"
#include "../../Library/Scene/BaseScene.h"
#include "../../Library/Texture/Manager/TextureManager.h"
#include "../../Library/OpenGL/Manager/OpenGlManager.h"
#include "../../Library/OpenGL/Buffer/Primitive/Manager/PrimitiveBufferManager.h"
#include "../../Library/Shader/GLSL/Object/GlslObject.h"
#include "../../Library/Camera/Manager/CameraManager.h"
#include "../../Library/Timer/Counter/Frame/FrameCounter.h"
#include "../../Library/Thread/Thread.h"
#include <atomic>


/* 前方宣言 */
namespace Font
{
    class C_FontManager;
}

namespace Shader
{
    namespace GLSL
    {
        class C_GlslObjectManager;
    }
}


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /* 別名 */
    using LoadFunction = bool(*)();


    /* ロード用のスレッドの情報 */
    struct S_LoadThreadData
    {
        std::atomic<bool> finishFlag_;                                                  ///< @brief 終了のフラグ
        LoadFunction pFunction = nullptr;                                               ///< @brief ロード時の関数
    };


    //-------------------------------------------------------------
    //!
    //! @brief ロードシーン
    //! @brief ロードを表すクラス
    //!
    //-------------------------------------------------------------
    class C_LoadScene : public Scene::C_BaseScene
    {
    public:
        C_LoadScene();                                                                  // コンストラクタ
        ~C_LoadScene() override;                                                        // デストラクタ
        Scene::ecSceneReturn Initialize() override;                                     // 初期化処理
        Scene::ecSceneReturn Update() override;                                         // 更新処理
        void Draw() override;                                                           // 描画処理
        void Finalize() override;                                                       // 終了処理
    private:
        Texture::C_TextureManager* pTextureManager_ = nullptr;                          ///< @brief テクスチャマネージャー
        Texture::TextureDataPtr pTextureData_;                                          ///< @brief テクスチャデータ
        Font::C_FontManager* pFontManager_ = nullptr;                                   ///< @brief フォントマネージャー
        OpenGL::C_PrimitiveBufferManager* pPrimitiveBufferManager_ = nullptr;           ///< @brief プリミティブバッファマネージャー
        OpenGL::C_OpenGlManager* pOpenGlManager_ = nullptr;                             ///< @brief OpenGLマネージャー
        Shader::GLSL::C_GlslObjectManager* pGlslObjectManager_ = nullptr;               ///< @brief GLSLオブジェクトマネージャー
        Camera::C_CameraManager* pCameraManager_ = nullptr;                             ///< @brief カメラマネージャー
        int32_t fontSize_ = 32;                                                         ///< @brief フォントサイズ
        OpenGL::PrimitiveBufferPtr pRectangleData_;                                     ///< @brief 矩形データ
        Shader::GLSL::GlslObjectPtr pGlslObject_;                                       ///< @brief GLSLオブジェクト
        Camera::CameraPtr pUiCamera_;                                                   ///< @brief UIカメラ
        Vector3 nowLoadingStringPosition_;                                              ///< @brief "NowLoading"の文字列の位置
        Timer::C_FrameCounter frameCounter_;                                            ///< @breif フレーム数のカウンタ
        Thread::C_Thread loadThread_;                                                   ///< @brief ロード処理用のスレッド
        S_LoadThreadData loadThreadData_;                                               ///< @brief ロード用のスレッドの情報
    };
}