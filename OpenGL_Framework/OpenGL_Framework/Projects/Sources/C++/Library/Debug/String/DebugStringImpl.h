/* ヘッダファイル */
#include "DebugString.h"
#include "../../Shader/GLSL/Object/Manager/GlslObjectManager.h"
#include "../../Font/FontManager.h"
#include "../../Math/Matrix/Matrix4x4.h"
#include "../Helper/DebugHelper.h"
#include "../../Window/Manager/WindowManager.h"
#include "../../Texture/Manager/TextureManager.h"
#include "../../OpenGL/Manager/OpenGlManager.h"
#include "../../Common/CommonHelper.h"


//-------------------------------------------------------------
//!
//! @brief デバッグ
//! @brief デバッグ関連の名前空間
//!
//-------------------------------------------------------------
namespace Debug
{
    /* 別名 */
    using VertexArrayObjectHandle = GLuint;                                                     // VertexArrayObjectHandle型
    using Matrix4x4 = Math::S_Matrix4x4<float>;                                                 // Matrix4x4型


    //-------------------------------------------------------------
    //!
    //! @brief デバッグストリングインプリメント
    //! @brief デバッグストリングのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_DebugString::C_DebugStringImpl
    {
    public:
        C_DebugStringImpl();                                                                    // コンストラクタ                                  
        ~C_DebugStringImpl();                                                                   // デストラクタ
        bool Initialize(const std::string& rFontFilePath,                                       // 初期化処理
                        int32_t fontSize);
        void Draw(const std::string& rString,                                                     // 描画処理
                  const Vector3& rPosition,
                  float scale,
                  uint8_t red,
                  uint8_t green,
                  uint8_t blue,
                  ecTypographicAlignment alignment);
        void Finalize();                                                                        // 終了処理
    private:
        Font::FontPtr pFont_;                                                                   ///< @brief フォント
        std::string fontFilePath_;                                                              ///< @brief フォントのファイルパス
        int32_t fontSize_ = 0;                                                                  ///< @brief フォントのサイズ
        Shader::GLSL::GlslObjectPtr pGlslObject_;                                               ///< @brief GLSLオブジェクト
        VertexArrayObjectHandle vertexArrayObjectHandle_ = 0;                                   ///< @brief 頂点配列オブジェクトのハンドル
        Matrix4x4 orthographicProjectionMatrix_;                                                ///< @brief 正投影の射影行列

        bool LoadFont(const std::string& rFilePath, int32_t size);                              // フォントのロード処理
        bool CreateAndEntryGlslObject();                                                        // GLSLオブジェクトの作成と登録
        void CreateVertexArrayObject();                                                         // 頂点配列オブジェクトの作成
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_DebugString::C_DebugStringImpl::C_DebugStringImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_DebugString::C_DebugStringImpl::~C_DebugStringImpl()
    {
        if (vertexArrayObjectHandle_ != 0) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  フォントのファイルパス
     *  @param  フォントのサイズ
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_DebugString::C_DebugStringImpl::Initialize(const std::string& rFontFilePath,
                                                      int32_t fontSize)
    {
        // フォントのロード処理
        if (LoadFont(rFontFilePath, fontSize) == false) return false;

        // GLSLオブジェクトを作成し、登録
        if (CreateAndEntryGlslObject() == false) return false;
        
        // 頂点配列オブジェクトを作成
        CreateVertexArrayObject();
        
        // ユニフォーム変数を設定
        pGlslObject_->Begin();
        pGlslObject_->SetUniform1i("Texture", Fixed::Texture::s_UNIT_NUMBER);
        pGlslObject_->End();

        // ウィンドウのサイズで正投影の射影行列を作成
        assert(Window::C_WindowManager::s_GetInstance()->GetWindow());
        auto pMainWindow = Window::C_WindowManager::s_GetInstance()->GetWindow().get();
        
        orthographicProjectionMatrix_ = Matrix4x4::s_CreateOrthographicProjection(0.0f,
                                                                                  static_cast<float>(pMainWindow->GetWidth()),
                                                                                  static_cast<float>(pMainWindow->GetHeight()), 
                                                                                  0.0f);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  デバックフォントの描画処理を行う
     *  @param  文字列
     *  @param  座標
     *  @param  スケール
     *  @param  赤
     *  @param  緑
     *  @param  青
     *  @param  文字揃え
     *  @return なし
     *
     ****************************************************************/
    void C_DebugString::C_DebugStringImpl::Draw(const std::string& rString,
                                                const Vector3& rPosition,
                                                float scale,
                                                uint8_t red,
                                                uint8_t green,
                                                uint8_t blue,
                                                ecTypographicAlignment alignment)
    {
        // アルファを有効にする
        OpenGL::C_OpenGlManager::s_GetInstance()->EnableBlend(true);
        OpenGL::C_OpenGlManager::s_GetInstance()->SetBlendFunction(OpenGL::BlendFactor::s_SOURCE_ALPHA, OpenGL::BlendFactor::s_ONE_MINUS_SOURCE_ALPHA);

        // フォントからテクスチャを作成
        static const char* s_pFONT_ID = "DebugFontTexture";

        assert(!Texture::C_TextureManager::s_GetInstance()->GetTextureData(s_pFONT_ID));
        Texture::C_TextureManager::s_GetInstance()->Create2DFromFont(pFont_, s_pFONT_ID, Common::C_CommonHelper::s_ConvertShiftJisToUtf8(rString), red, green, blue);

        // テクスチャユニットを設定し、テクスチャのバインド
        auto pTextureData = Texture::C_TextureManager::s_GetInstance()->GetTextureData(s_pFONT_ID).get();

        Texture::C_TextureManager::s_GetInstance()->SetActiveUnit(Fixed::Texture::s_UNIT_NUMBER);
        Texture::C_TextureManager::s_GetInstance()->Bind(Texture::Type::s_2D, pTextureData->handle_);

        // 深度のマスクを有効化
        OpenGL::C_OpenGlManager::s_GetInstance()->EnableDepthMask(true);

        // シェーダーの使用開始
        pGlslObject_->Begin();

        // テクスチャの幅と高さを設定
        pGlslObject_->SetUniform1f("Width", static_cast<float>(pTextureData->width_ * scale));
        pGlslObject_->SetUniform1f("Height", static_cast<float>(pTextureData->height_ * scale));
        pGlslObject_->SetUniformVector3("Position", rPosition);
        pGlslObject_->SetUniformMatrix4x4("OrthographicProjectionMatrix", orthographicProjectionMatrix_);
        pGlslObject_->SetUniform1i("Alignment", static_cast<int32_t>(alignment));

        // スプライトの描画
        const int32_t VERTEX_NUMBER = 1;
        const int32_t BYTE_OFFSET = 0;

        glBindVertexArray(vertexArrayObjectHandle_);
        glDrawArrays(GL_POINTS, BYTE_OFFSET, VERTEX_NUMBER);
        glBindVertexArray(0);

        // シェーダーの使用終了
        pGlslObject_->End();

        // テクスチャのアンバインド
        Texture::C_TextureManager::s_GetInstance()->Unbind(Texture::Type::s_2D);

        // テクスチャを破棄
        Texture::C_TextureManager::s_GetInstance()->Destroy(s_pFONT_ID);

        // 深度のマスクを無効化
        OpenGL::C_OpenGlManager::s_GetInstance()->EnableDepthMask(false);

        // アルファを無効にする
        OpenGL::C_OpenGlManager::s_GetInstance()->EnableBlend(false);
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_DebugString::C_DebugStringImpl::Finalize()
    {
        // フォントの解放
        if (Font::C_FontManager::s_GetInstance()->GetFont(fontFilePath_, fontSize_))
        {
            Font::C_FontManager::s_GetInstance()->Release(fontFilePath_, fontSize_);
        }

        pFont_.reset();

        // GLSLオブジェクトを除去
        if (Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID))
        {
            Shader::GLSL::C_GlslObjectManager::s_GetInstance()->Remove(Fixed::Shader::s_pGLSL_OBJECT_ID);
        }

        pGlslObject_.reset();

        // 頂点バッファオブジェクトの削除 
        const int32_t DELETE_VERTEX_ARRAY_OBJECT_NUMBER = 1;
        glDeleteVertexArrays(DELETE_VERTEX_ARRAY_OBJECT_NUMBER, &vertexArrayObjectHandle_);
        vertexArrayObjectHandle_ = 0;
    }


    /*************************************************************//**
     *
     *  @brief  フォントのロード処理を行う
     *  @param  
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_DebugString::C_DebugStringImpl::LoadFont(const std::string& rFilePath, int32_t size)
    {
        // フォントのロード処理
        if (!Font::C_FontManager::s_GetInstance()->GetFont(rFilePath, size))
        {
            if (Font::C_FontManager::s_GetInstance()->Load(rFilePath, size) == false)
            {
                PrintLog("[ C_DebugStringImpl::Initialize ] : フォントのロード処理に失敗しました。\n");

                return false;
            }
        }

        // ファイルパスとフォントを保持
        fontFilePath_ = rFilePath;
        pFont_ = Font::C_FontManager::s_GetInstance()->GetFont(rFilePath, size).get();
        fontSize_ = size;

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  シェーダーのコンパイルとリンクを行う
     *  @param  なし
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_DebugString::C_DebugStringImpl::CreateAndEntryGlslObject()
    {
        if (!Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID))
        {
            auto pGlslObject = Shader::GLSL::C_GlslObject::s_Create();

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pVERTEX_FILE_PATH, Shader::GLSL::Type::s_VERTEX) == false)
            {
                PrintLog("[ C_DebugStringImpl::Initialize ] : 頂点シェーダーのコンパイルに失敗しました。\n");

                return false;
            }

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pGEOMETRY_FILE_PATH, Shader::GLSL::Type::s_GEOMETRY) == false)
            {
                PrintLog("[ C_DebugStringImpl::Initialize ] : ジオメトリシェーダーのコンパイルに失敗しました。\n");

                return false;
            }

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pFRAGMENT_FILE_PATH, Shader::GLSL::Type::s_FRAGMENT) == false)
            {
                PrintLog("[ C_DebugStringImpl::Initialize ] : フラグメントシェーダーのコンパイルに失敗しました。\n");

                return false;
            }

            if (pGlslObject->Link() == false)
            {
                PrintLog("[ C_DebugStringImpl::Initialize ] : シェーダーのリンクに失敗しました。\n");

                return false;
            }

            Shader::GLSL::C_GlslObjectManager::s_GetInstance()->Entry(pGlslObject, Fixed::Shader::s_pGLSL_OBJECT_ID);
            pGlslObject_ = pGlslObject;
        }
        else
        {
            pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID).get();
        }

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  頂点配列オブジェクトを作成する
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_DebugString::C_DebugStringImpl::CreateVertexArrayObject()
    {
        // 仮の座標
        Vector3 tempPosition;

        // 頂点バッファを作成し、データを転送
        const int32_t POSITION_ELEMENT_NUMBER = 3;
        const int32_t BUFFER_INDEX = 0;
        const int32_t VERTEX_ARRAY_OBJECT_NUMBER = 1;
        const int32_t NO_USE_BYTE_OFFSET = 0;
        const int32_t POSITION_BYTE_OFFSET = 0;

        // 頂点バッファオブジェクトハンドル
        GLuint vertexBufferObjectHandle = 0;

        glGenBuffers(VERTEX_ARRAY_OBJECT_NUMBER, &vertexBufferObjectHandle);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectHandle);
        glBufferData(GL_ARRAY_BUFFER, POSITION_ELEMENT_NUMBER * sizeof(float), tempPosition.a_, GL_STATIC_DRAW);

        // 頂点配列オブジェクトを作成し、バインド
        glGenVertexArrays(1, &vertexArrayObjectHandle_);
        glBindVertexArray(vertexArrayObjectHandle_);
        glEnableVertexAttribArray(BUFFER_INDEX);
        glVertexAttribPointer(BUFFER_INDEX, POSITION_ELEMENT_NUMBER, GL_FLOAT, GL_FALSE, NO_USE_BYTE_OFFSET, reinterpret_cast<GLubyte*>(POSITION_BYTE_OFFSET));

        // 各バッファをアンバインド
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // 頂点バッファオブジェクトを削除
        glDeleteBuffers(1, &vertexBufferObjectHandle);
    }
}