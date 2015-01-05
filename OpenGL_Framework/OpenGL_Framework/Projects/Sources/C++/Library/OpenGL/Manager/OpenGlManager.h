/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../../Singleton/Singleton.h"
#include "../OpenGlDefine.h"
#include "../../Window/Window/BaseWindow.h"


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL関連の名前空間
//!
//-------------------------------------------------------------
namespace OpenGL
{
    namespace
    {
        /* レンダリングコンテキストのID */
        namespace RenderingContextID
        {
            const char* s_pMAIN = "MainRenderingContext";
        }
    }


    //-------------------------------------------------------------
    //!
    //! @brief OpenGLマネージャー
    //! @brief OpenGLを管理するクラス
    //!
    //-------------------------------------------------------------
    class C_OpenGlManager : public Singleton::C_Singleton<C_OpenGlManager>
    {
        friend C_Singleton<C_OpenGlManager>;                                                                        // シングルトンクラスをフレンド化
    public:
        bool Initialize(const Window::C_BaseWindow& rMainWindow);                                                   // 初期化処理
        bool InitializeWithJsonFile(const Window::C_BaseWindow& rMainWindow,                                        // JSONファイルで初期化処理
                                    const std::string& rFilePath);
        void Finalize();                                                                                            // 終了処理
        bool CreateRenderingContext(const std::string& rId);                                                        // レンダリングコンテキストを作成
        void DestroyRenderingContext(const std::string& rId);                                                       // レンダリングコンテキストを破棄
        void AllDestroyRenderingContext();                                                                          // 全てのレンダリングコンテキストを破棄
        bool SetCurrentRenderingContext(const std::string& rId = RenderingContextID::s_pMAIN);                      // レンダリングコンテキストをカレントに設定
        void ResetCurrentRenderingContext();                                                                        // カレントのレンダリングコンテキストをリセット
        void ClearBackBuffer(float red = 0.0f,                                                                      // バックバッファをクリア
                             float green = 0.0f,
                             float blue = 0.0f,
                             float alpha = 0.0f,
                             BufferBitFlag bufferClearFlag = Buffer::Pixel::s_COLOR | Buffer::Pixel::s_DEPTH);
        void SwapBuffer();                                                                                          // バッファの入れ替え
        void SetViewport(int32_t positionX,                                                                         // ビューポートの設定
                         int32_t positionY,
                         int32_t width,
                         int32_t height);
        void EnableColorMask(bool redValidFlag = true,                                                              // カラーマスクを有効化
                             bool greenValidFlag = true,
                             bool blueValidFlag = true,
                             bool alphaValidFlag = true);
        void EnableDepthTest(bool validFlag = true);                                                                // 深度テストの有効化
        void EnableDepthMask(bool validFlag = true);                                                                // 深度マスクの有効化
        void EnableStencilTest(bool validFlag = true);                                                              // ステンシルテストを有効化
        void EnableStencilMask(bool validFlag = true);                                                              // ステンシルマスクを有効化
        void EnableMultiSample(bool validFlag = true);                                                              // マルチサンプルの有効化
        void EnableBlend(bool validFlag = true);                                                                    // ブレンドの有効化
        void EnableCulling(bool validFlag = true);                                                                  // カリングの有効化
        void EnableRasterrizerDiscard(bool validFlag = true);                                                       // ラスタライザの停止を有効化
        void EnableShaderProgramPointSize(bool balidFlag = true);                                                   // シェーダープログラムでの点のサイズを有効化
        void SetBlendFunction(BlendEnum sourceFactor = BlendFactor::s_ALL_ONE,                                      // ブレンドの関数を設定
                              BlendEnum destinationFactor = BlendFactor::s_ALL_ZERO);
        void SetCullingFace(FaceEnum face = Face::s_BACK);                                                          // カリングをする面を設定
        void SetStencilClearValue(int32_t clearValue = 0);                                                          // ステンシルのクリア値を設定
        void SetStencilFunction(StencilEnum frontFaceFunction,                                                      // ステンシルの関数を設定
                                StencilEnum backFaceFunction,
                                int32_t comparisonValue,
                                uint32_t mask = ~0);
        void SetStencilProcess(StencilEnum stencilFail,                                                             // ステンシルの処理を設定
                               StencilEnum stencilPassAndDepthFail,
                               StencilEnum stencilPassAndDepthPass,
                               FaceEnum face = Face::s_BOTH);
        void DrawPrimitive(PrimitiveEnum primitive,                                                                 // プリミティブを描画
                           VertexArrayObjectHandle vertexArrayObjectHandle,
                           int32_t vertexCount,
                           int32_t firstVertexNumber = 0);
        void DrawPrimitiveInstanced(PrimitiveEnum primitive,                                                        // プリミティブを描画
                                    VertexArrayObjectHandle vertexArrayObjectHandle,                                // プリミティブをインスタンシング描画
                                    int32_t vertexCount,
                                    int32_t instanceCount,
                                    int32_t firstVertexNumber = 0);
        void DrawPrimitiveWithIndices(PrimitiveEnum primitive,                                                      // インデックスを用いてプリミティブを描画
                                      VertexArrayObjectHandle vertexArrayObjectHandle,
                                      IndexBufferObjenctHandle indexBufferObjectHandle,
                                      DataEnum indexDataType,
                                      int32_t indexCount);
        void DrawPrimitiveInstancedWithIndices(PrimitiveEnum primitive,                                             // インデックスを用いてプリミティブをインスタンシング描画
                                               VertexArrayObjectHandle vertexArrayObjectHandle,
                                               IndexBufferObjenctHandle indexBufferObjectHandle,
                                               DataEnum indexDataType,
                                               int32_t indexCount,
                                               int32_t instanceCount);
    private:
        /* 前方宣言 */
        class C_OpenGlManagerImpl;

        std::unique_ptr<C_OpenGlManagerImpl> upImpl_;                                                               ///< @brief 実装情報

        C_OpenGlManager();                                                                                          // コンストラクタ
        ~C_OpenGlManager() override;                                                                                // デストラクタ
    };
}