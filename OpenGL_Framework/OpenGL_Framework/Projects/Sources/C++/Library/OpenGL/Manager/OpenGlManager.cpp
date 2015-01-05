/* ヘッダファイル */
#include "OpenGlManagerImpl.h"


//-------------------------------------------------------------
//!
//! @brief OpenGL
//! @brief OpenGL関連の名前空間
//!
//-------------------------------------------------------------
namespace OpenGL
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_OpenGlManager::C_OpenGlManager() :

        // 実装情報
        upImpl_(std::make_unique<C_OpenGlManagerImpl>(this))

    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_OpenGlManager::~C_OpenGlManager()
    {
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  メインウィンドウ
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_OpenGlManager::Initialize(const Window::C_BaseWindow& rMainWindow)
    {
        if (upImpl_->Initialize(rMainWindow) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  JSONファイルで初期化処理を行う
     *  @param  メインウィンドウ
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_OpenGlManager::InitializeWithJsonFile(const Window::C_BaseWindow& rMainWindow,
                                                 const std::string& rFilePath)
    {
        if (upImpl_->InitializeWithJsonFile(rMainWindow, rFilePath) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::Finalize()
    {
        upImpl_->Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  レンダリングコンテキストを作成する
     *  @param  ID
     *  @return 正常終了：true ・ 異常終了：false
     *
     ****************************************************************/
    bool C_OpenGlManager::CreateRenderingContext(const std::string& rId)
    {
        if (upImpl_->CreateRenderingContext(rId) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  レンダリングコンテキストを破棄する
     *  @param  ID
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::DestroyRenderingContext(const std::string& rId)
    {
        upImpl_->DestroyRenderingContext(rId);
    }


    /*************************************************************//**
     *
     *  @brief  全てのレンダリングコンテキストを破棄する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::AllDestroyRenderingContext()
    {
        upImpl_->AllDestroyRenderingContext();
    }


    /*************************************************************//**
     *
     *  @brief  レンダリングコンテキストをカレントに設定する
     *  @param  ID
     *  @return 正常終了：true ・ 異常終了：false
     *
     ****************************************************************/
    bool C_OpenGlManager::SetCurrentRenderingContext(const std::string& rId)
    {
        if (upImpl_->SetCurrentRenderingContext(rId) == false) return false;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  カレントのレンダリングコンテキストをリセットする
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::ResetCurrentRenderingContext()
    {
        upImpl_->ResetCurrentRenderingContext();
    }


    /*************************************************************//**
     *
     *  @brief  バックバッファのクリアを行う
     *  @param  クリアカラーの赤
     *  @param  クリアカラーの緑
     *  @param  クリアカラーの青
     *  @param  クリアからのアルファ
     *  @param  バッファのクリアフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::ClearBackBuffer(float red,
                                          float green,
                                          float blue,
                                          float alpha,
                                          BufferBitFlag bufferClearFlag)
    {
        // バックバッファをクリアする色を設定
        ::glClearColor(red, green, blue, alpha);

        // バックバッファをクリア
        ::glClear(bufferClearFlag);
    }


    /*************************************************************//**
     *
     *  @brief  バッファの入れ替えを行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::SwapBuffer()
    {
        upImpl_->SwapBuffer();
    }


    /*************************************************************//**
     *
     *  @brief  ビューポートの設定を行う
     *  @param  ビューの( 左端 )X座標
     *  @param  ビューの( 上端 )Y座標
     *  @param  ビューの幅
     *  @param  ビューの高さ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::SetViewport(int32_t positionX,
                                      int32_t positionY,
                                      int32_t width,
                                      int32_t height)
    {
        // ビューポートの設定
        ::glViewport(positionX, positionY, width, height);
    }


    /*************************************************************//**
     *
     *  @brief  カラーマスクを有効化する
     *  @param  赤が有効か判断するフラグ
     *  @param  緑が有効か判断するフラグ
     *  @param  青が有効か判断するフラグ
     *  @param  アルファが有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::EnableColorMask(bool redValidFlag,
                                          bool greenValidFlag,
                                          bool blueValidFlag,
                                          bool alphaValidFlag)
    {
        static auto s_ChangeGlBoolean = [](bool validFlag){ return (validFlag == true) ? GL_FALSE : GL_TRUE; };

        ::glColorMask(s_ChangeGlBoolean(redValidFlag),
                      s_ChangeGlBoolean(greenValidFlag),
                      s_ChangeGlBoolean(blueValidFlag),
                      s_ChangeGlBoolean(alphaValidFlag));
    }

    /*************************************************************//**
     *
     *  @brief  深度テストを有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::EnableDepthTest(bool validFlag)
    {
        (validFlag == true) ? ::glEnable(GL_DEPTH_TEST) : ::glDisable(GL_DEPTH_TEST);
    }


    /*************************************************************//**
     *
     *  @brief  深度マスクを有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::EnableDepthMask(bool validFlag)
    {
        (validFlag == true) ? ::glDepthMask(GL_FALSE) : ::glDepthMask(GL_TRUE);
    }


    /*************************************************************//**
     *
     *  @brief  ステンシルテストを有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::EnableStencilTest(bool validFlag)
    {
        (validFlag == true) ? ::glEnable(GL_STENCIL_TEST) : ::glDisable(GL_STENCIL_TEST);
    }


    /*************************************************************//**
     *
     *  @brief  ステンシルマスクを有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::EnableStencilMask(bool validFlag)
    {
        (validFlag == true) ? ::glStencilMask(GL_FALSE) : ::glStencilMask(GL_TRUE);
    }


    /*************************************************************//**
     *
     *  @brief  マルチサンプルを有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::EnableMultiSample(bool validFlag)
    {
        (validFlag == true) ? ::glEnable(GL_MULTISAMPLE) : ::glDisable(GL_MULTISAMPLE);
    }


    /*************************************************************//**
     *
     *  @brief  ブレンドを有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::EnableBlend(bool validFlag)
    {
        (validFlag == true) ? ::glEnable(GL_BLEND) : ::glDisable(GL_BLEND);
    }


    /*************************************************************//**
     *
     *  @brief  カリングを有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::EnableCulling(bool validFlag)
    {
        (validFlag == true) ? ::glEnable(GL_CULL_FACE) : ::glDisable(GL_CULL_FACE);
    }


    /*************************************************************//**
     *
     *  @brief  ラスタライザの停止を有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::EnableRasterrizerDiscard(bool validFlag)
    {
        (validFlag == true) ? ::glEnable(GL_RASTERIZER_DISCARD) : ::glDisable(GL_RASTERIZER_DISCARD);
    }


    /*************************************************************//**
     *
     *  @brief  シェーダープログラムでの点のサイズを有効化する
     *  @param  有効か判断するフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::EnableShaderProgramPointSize(bool validFlag)
    {
        (validFlag == true) ? ::glEnable(GL_PROGRAM_POINT_SIZE) : ::glDisable(GL_PROGRAM_POINT_SIZE);
    }


    /*************************************************************//**
     *
     *  @brief  ブレンドの関数の設定を行う
     *  @param  新しい色の要素
     *  @param  現在の色の要素
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::SetBlendFunction(BlendEnum sourceFactor,
                                           BlendEnum destinationFactor)
    {
        ::glBlendFunc(sourceFactor, destinationFactor);
    }


    /*************************************************************//**
     *
     *  @brief  カリングする面の設定を行う
     *  @param  面
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::SetCullingFace(FaceEnum face)
    {
        ::glCullFace(face);
    }


    /*************************************************************//**
     *
     *  @brief  ステンシルのクリア値の設定を行う
     *  @param  ステンシルのクリア値
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::SetStencilClearValue(int32_t clearValue)
    {
        ::glClearStencil(clearValue);
    }


    /*************************************************************//**
     *
     *  @brief  ステンシルの関数の設定を行う
     *  @param  表面の関数
     *  @param  裏面の関数
     *  @param  比較値
     *  @param  マスク
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::SetStencilFunction(StencilEnum frontFaceFunction,
                                             StencilEnum backFaceFunction,
                                             int32_t comparisonValue,
                                             uint32_t mask)
    {
        glStencilFuncSeparate(frontFaceFunction, backFaceFunction, comparisonValue, mask);
    }


    /*************************************************************//**
     *
     *  @brief  ステンシルの関数の設定を行う
     *  @param  関数の種類
     *  @param  比較値
     *  @param  マスク
     *  @param  面
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::SetStencilProcess(StencilEnum stencilFail,
                                            StencilEnum stencilPassAndDepthFail,
                                            StencilEnum stencilPassAndDepthPass,
                                            FaceEnum face)
    {
        glStencilOpSeparate(face, stencilFail, stencilPassAndDepthFail, stencilPassAndDepthPass);
    }


    /*************************************************************//**
     *
     *  @brief  プリミティブの描画を行う
     *  @param  プリミティブの種類
     *  @param  頂点配列オブジェクトハンドル
     *  @param  頂点数
     *  @param  描画を開始する最初の頂点番号
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::DrawPrimitive(PrimitiveEnum primitive,
                                        VertexArrayObjectHandle vertexArrayObjectHandle,
                                        int32_t vertexCount,
                                        int32_t firstVertexNumber)
    {
        assert(vertexArrayObjectHandle != 0);

        glBindVertexArray(vertexArrayObjectHandle);
        ::glDrawArrays(primitive, firstVertexNumber, vertexCount);
        glBindVertexArray(0);
    }


    /*************************************************************//**
     *
     *  @brief  プリミティブのインスタンシング描画を行う
     *  @param  プリミティブの種類
     *  @param  頂点配列オブジェクトハンドル
     *  @param  頂点数
     *  @param  インスタンス数
     *  @param  描画を開始する最初の頂点番号
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::DrawPrimitiveInstanced(PrimitiveEnum primitive,
                                                 VertexArrayObjectHandle vertexArrayObjectHandle,
                                                 int32_t vertexCount,
                                                 int32_t instanceCount,
                                                 int32_t firstVertexNumber)
    {
        assert(vertexArrayObjectHandle != 0);

        glBindVertexArray(vertexArrayObjectHandle);
        ::glDrawArraysInstanced(primitive, firstVertexNumber, vertexCount, instanceCount);
        glBindVertexArray(0);
    }


    /*************************************************************//**
     *
     *  @brief  インデックスを用いてプリミティブの描画を行う
     *  @param  プリミティブの種類
     *  @param  頂点配列オブジェクトハンドル
     *  @param  インデックスバッファオブジェクトハンドル
     *  @param  インデックスのデータ型
     *  @param  インデックス数
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::DrawPrimitiveWithIndices(PrimitiveEnum primitive,
                                                   VertexArrayObjectHandle vertexArrayObjectHandle,
                                                   IndexBufferObjenctHandle indexBufferObjectHandle,
                                                   DataEnum indexDataType,
                                                   int32_t indexCount)
    {
        assert(vertexArrayObjectHandle != 0);
        assert(indexBufferObjectHandle != 0);
        
        glBindVertexArray(vertexArrayObjectHandle);
        glBindBuffer(Buffer::s_INDEX, indexBufferObjectHandle);

        const int32_t NO_USE_RAW_DATA_INDICES = 0;
        ::glDrawElements(primitive, indexCount, indexDataType, reinterpret_cast<GLubyte*>(NO_USE_RAW_DATA_INDICES));

        glBindBuffer(Buffer::s_INDEX, 0);
        glBindVertexArray(0);
    }


    /*************************************************************//**
     *
     *  @brief  インデックスを用いてプリミティブの描画を行う
     *  @param  プリミティブの種類
     *  @param  頂点配列オブジェクトハンドル
     *  @param  インデックスバッファオブジェクトハンドル
     *  @param  インデックスのデータ型
     *  @param  インデックス数
     *  @param  インスタンス数
     *  @return なし
     *
     ****************************************************************/
    void C_OpenGlManager::DrawPrimitiveInstancedWithIndices(PrimitiveEnum primitive,
                                                            VertexArrayObjectHandle vertexArrayObjectHandle,
                                                            IndexBufferObjenctHandle indexBufferObjectHandle,
                                                            DataEnum indexDataType,
                                                            int32_t indexCount,
                                                            int32_t instanceCount)
    {
        assert(vertexArrayObjectHandle != 0);
        assert(indexBufferObjectHandle != 0);
        
        glBindVertexArray(vertexArrayObjectHandle);
        glBindBuffer(Buffer::s_INDEX, indexBufferObjectHandle);

        const int32_t NO_USE_RAW_DATA_INDICES = 0;
        ::glDrawElementsInstanced(primitive, indexCount, indexDataType, reinterpret_cast<GLubyte*>(NO_USE_RAW_DATA_INDICES), instanceCount);

        glBindBuffer(Buffer::s_INDEX, 0);
        glBindVertexArray(0);
    }
}