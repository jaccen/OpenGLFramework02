/* ヘッダファイル */
#include "FigureDrawer.h"
#include "../Shader/GLSL/Object/Manager/GlslObjectManager.h"
#include "../Debug/Helper/DebugHelper.h"
#include <array>


//-------------------------------------------------------------
//!
//! @brief フィギュア
//! @brief 図形関連の名前空間
//!
//-------------------------------------------------------------
namespace Figure
{
    /* 別名 */
    using VertexArrayObjectHandle = GLuint;                                                                                 // VertexArrayObjectHandle型
    using VertexBufferObjectHandle = GLuint;                                                                                // VertexBufferObjectHandle型
    

    /** プリミティブの種類 */
    enum ePrimitiveType
    {
        POINT,                                                                                                              ///< @brief 点
        LINE,                                                                                                               ///< @brief 線
        
        PRIMITIVE_TYPE_NUMBER,                                                                                              ///< @biref プリミティブの種類の数
    };


    /** 頂点の種類 */
    enum eVertexType
    {
        POSITION,                                                                                                           ///< @brief 座標
        COLOR,                                                                                                              ///< @brief 色

        VERTEX_TYPE_NUMBER,                                                                                                 ///< @brief 頂点の種類の数
    };


    //-------------------------------------------------------------
    //!
    //! @brief フィギュアドロワーインプリメント
    //! @brief フィギュアドロワーのプライベート情報の実装
    //!
    //-------------------------------------------------------------
    class C_FigureDrawer::C_FigureDrawerImpl
    {
    public:
        C_FigureDrawerImpl();                                                                                               // コンストラクタ
        ~C_FigureDrawerImpl();                                                                                              // デストラクタ
        bool Initialize();                                                                                                  // 初期化処理
        void Finalize();                                                                                                    // 終了処理
        void DrawPoint(const Vector3& rPosition,                                                                            // 点の描画
                       const Vector4& rColor,
                       const Matrix4x4& rViewProjectionMatrix);                           
        void DrawLine(const Vector3& rStartPosition,                                                                        // 線の描画
                      const Vector3& rEndPositiont, 
                      const Vector4& rColor,
                      const Matrix4x4& rViewProjectionMatrix);
        void SetPointSize(float pointSize);                                                                                 // 点のサイズを設定
    private:
        std::array<VertexArrayObjectHandle, PRIMITIVE_TYPE_NUMBER> vertexArrayObjectHandles_;                               ///< @brief 頂点配列オブジェクトハンドル
        std::array<VertexBufferObjectHandle, PRIMITIVE_TYPE_NUMBER> vertexBufferObjectHandles_;                             ///< @brief 頂点バッファオブジェクトハンドル
        Shader::GLSL::GlslObjectPtr pGlslObject_;                                                                           ///< @brief GLSLオブジェクト
        int32_t subroutineIndices_[2];                                                                                      ///< @brief サブルーチンのインデックス
        bool finalizeFlag_ = false;                                                                                         ///< @brief 終了処理を行ったか判断するフラグ

        bool CreateAndEntryGlslObject();                                                                                    // GLSLオブジェクトの作成と登録
        void CreateVertexArrayObject(ePrimitiveType type, int32_t vertexCount);                                             // 頂点配列オブジェクトを作成
        void RewriteVertices(ePrimitiveType type, Vector3 positions[], const Vector4& rColor, int32_t vertexCount);         // 頂点の書き換え    
    };


    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_FigureDrawer::C_FigureDrawerImpl::C_FigureDrawerImpl()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_FigureDrawer::C_FigureDrawerImpl::~C_FigureDrawerImpl()
    {
        if (finalizeFlag_ == false) Finalize();
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    bool C_FigureDrawer::C_FigureDrawerImpl::Initialize()
    {
        // GLSLオブジェクトの作成と登録
        if (CreateAndEntryGlslObject() == false) return false;

        // 点のサイズを設定
        SetPointSize(1.0f);

        // 頂点配列オブジェクトを作成
        CreateVertexArrayObject(POINT, 1);
        CreateVertexArrayObject(LINE, 2);

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_FigureDrawer::C_FigureDrawerImpl::Finalize()
    {
        // 頂点バッファオブジェクトと頂点配列オブジェクトの削除
        glDeleteBuffers(PRIMITIVE_TYPE_NUMBER, vertexBufferObjectHandles_.data());
        glDeleteVertexArrays(PRIMITIVE_TYPE_NUMBER, vertexArrayObjectHandles_.data());
        vertexBufferObjectHandles_.fill(0);
        vertexArrayObjectHandles_.fill(0);

        // GLSLオブジェクトを除去
        if (Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID))
        {
            Shader::GLSL::C_GlslObjectManager::s_GetInstance()->Remove(Fixed::Shader::s_pGLSL_OBJECT_ID);
        }

        pGlslObject_.reset();

        // 終了処理済みフラグを立てる
        finalizeFlag_ = true;
    }


    /*************************************************************//**
     *
     *  @brief  点の描画を行う
     *  @param  座標
     *  @param  色
     *  @param  ビュープロジェクション行列
     *  @return なし
     *
     ****************************************************************/
    void C_FigureDrawer::C_FigureDrawerImpl::DrawPoint(const Vector3& rPosition,
                                                       const Vector4& rColor,
                                                       const Matrix4x4& rViewProjectionMatrix)
    {
        Vector3 positions[] = { rPosition };

        // 頂点の書き換え
        RewriteVertices(POINT, positions, rColor, 1);

        // 頂点配列オブジェクトをバインド
        glBindVertexArray(vertexArrayObjectHandles_[POINT]);

        // シェーダーの使用開始
        pGlslObject_->Begin();

        // サブルーチンを設定
        pGlslObject_->BindActiveSubroutine(subroutineIndices_[POINT], Shader::GLSL::Type::s_VERTEX);

        // ビュープロジェクション行列を設定
        pGlslObject_->SetUniformMatrix4x4("viewProjectionMatrix", rViewProjectionMatrix);

        ::glDrawArrays(GL_POINTS, 0, 1);

        // シェーダーの使用終了
        pGlslObject_->End();

        // 頂点配列オブジェクトをアンバインド
        glBindVertexArray(0);
    }


    /*************************************************************//**
     *
     *  @brief  線の描画を行う
     *  @param  開始座標
     *  @param  終了座標
     *  @param  色
     *  @param  ビュープロジェクション行列
     *  @return なし
     *
     ****************************************************************/
    void C_FigureDrawer::C_FigureDrawerImpl::DrawLine(const Vector3& rStartPosition,
                                                      const Vector3& rEndPosition,
                                                      const Vector4& rColor,
                                                      const Matrix4x4& rViewProjectionMatrix)
    {
        Vector3 positions[] = { rStartPosition, rEndPosition };

        // 頂点の書き換え
        RewriteVertices(LINE, positions, rColor, 2);

        // 頂点配列オブジェクトをバインド
        glBindVertexArray(vertexArrayObjectHandles_[LINE]);

        // シェーダーの使用開始
        pGlslObject_->Begin();

        // サブルーチンを設定
        pGlslObject_->BindActiveSubroutine(subroutineIndices_[LINE], Shader::GLSL::Type::s_VERTEX);

        // ビュープロジェクション行列を設定
        pGlslObject_->SetUniformMatrix4x4("viewProjectionMatrix", rViewProjectionMatrix);

        ::glDrawArrays(GL_LINES, 0, 2);

        // シェーダーの使用終了
        pGlslObject_->End();

        // 頂点配列オブジェクトをアンバインド
        glBindVertexArray(0);
    }


    
    /*************************************************************//**
     *
     *  @brief  点のサイズを設定する
     *  @param  点のサイズ
     *  @return なし
     *
     ****************************************************************/
    void C_FigureDrawer::C_FigureDrawerImpl::SetPointSize(float pointSize)
    {
        pGlslObject_->Begin();
        pGlslObject_->SetUniform1f("pointSize", pointSize);
        pGlslObject_->End();
    }


    /*************************************************************//**
     *
     *  @brief  GLSLオブジェクトの作成と登録を行う
     *  @param  なし
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_FigureDrawer::C_FigureDrawerImpl::CreateAndEntryGlslObject()
    {
        if (!Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID))
        {
            auto pGlslObject = Shader::GLSL::C_GlslObject::s_Create();

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pVERTEX_FILE_PATH, Shader::GLSL::Type::s_VERTEX) == false)
            {
                PrintLog("[ C_FigureDrawerImpl::CreateAndEntryGlslObject ] : 頂点シェーダーのコンパイルに失敗しました。\n");

                return false;
            }

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pFRAGMENT_FILE_PATH, Shader::GLSL::Type::s_FRAGMENT) == false)
            {
                PrintLog("[ C_FigureDrawerImpl::CreateAndEntryGlslObject ] : フラグメントシェーダーのコンパイルに失敗しました。\n");

                return false;
            }

            if (pGlslObject->Link() == false)
            {
                PrintLog("[ C_FigureDrawerImpl::CreateAndEntryGlslObject ] : シェーダーのリンクに失敗しました。\n");

                return false;
            }

            // GLSLオブジェクトを登録し、保持
            Shader::GLSL::C_GlslObjectManager::s_GetInstance()->Entry(pGlslObject, Fixed::Shader::s_pGLSL_OBJECT_ID);
            pGlslObject_ = pGlslObject;
        }
        else
        {
            pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID).get();
        }

        // サブルーチンのインデックスを取得
        subroutineIndices_[POINT] = pGlslObject_->GetSubroutineIndex(Shader::GLSL::Type::s_VERTEX, "PointProcess");
        subroutineIndices_[LINE] = pGlslObject_->GetSubroutineIndex(Shader::GLSL::Type::s_VERTEX, "LineProcess");

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  頂点配列オブジェクトの作成を行う
     *  @param  プリミティブの種類
     *  @param  頂点数
     *  @return なし
     *
     ****************************************************************/
    void C_FigureDrawer::C_FigureDrawerImpl::CreateVertexArrayObject(ePrimitiveType type, int32_t vertexCount)
    {
        // 仮の頂点
        struct Vertex 
        {
            Vector3 position_; 
            Vector4 color_; 
        };

        std::vector<Vertex> tempVertices;

        // 頂点バッファオブジェクトを作成し、バインド
        glGenBuffers(1, &vertexBufferObjectHandles_[type]);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectHandles_[type]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, tempVertices.data(), GL_DYNAMIC_DRAW);

        // 頂点配列オブジェクトを作成し、バインド
        glGenVertexArrays(1, &vertexArrayObjectHandles_[type]);
        glBindVertexArray(vertexArrayObjectHandles_[type]);
        
        // バイトオフセットを使用しないときの値
        const int32_t NO_USE_BYTE_OFFESET = 0;
        const int32_t BYTE_OFFSET = 0;

        // 頂点バッファに座標を転送
        const int32_t POSITION_ELEMENT_NUMBER = 3;
        
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, POSITION_ELEMENT_NUMBER, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLubyte*>(0));

        // 頂点バッファに色を転送
        const int32_t COLOR_ElEMENT_NUMBER = 4;

        // 頂点配列オブジェクトにバインド
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, COLOR_ElEMENT_NUMBER, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLubyte*>(12));

        // 各オブジェクトをアンバインド
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }


    /*************************************************************//**
     *
     *  @brief  頂点の書き換えを行う
     *  @param  プリミティブの種類
     *  @param  座標
     *  @param  色
     *  @param  頂点の数
     *  @return なし
     *
     ****************************************************************/
    void C_FigureDrawer::C_FigureDrawerImpl::RewriteVertices(ePrimitiveType type, Vector3 positions[], const Vector4& rColor, int32_t vertexCount)
    {
        // 頂点バッファをバインド
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectHandles_[type]);

        // 頂点バッファをマップ
        float* pVertices = reinterpret_cast<float*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        assert(pVertices);

        // 頂点バッファのデータを書き換え
        for (int32_t i = 0, vertexIndex = 0; i < vertexCount; ++i)
        {
            pVertices[vertexIndex] = positions[i].x_;
            pVertices[vertexIndex + 1] = positions[i].y_;
            pVertices[vertexIndex + 2] = positions[i].z_;
            pVertices[vertexIndex + 3] = rColor.red_;
            pVertices[vertexIndex + 4] = rColor.green_;
            pVertices[vertexIndex + 5] = rColor.blue_;
            pVertices[vertexIndex + 6] = rColor.alpha_;

            vertexIndex += 7;
        }

        // バッファをアンマップ
        glUnmapBuffer(GL_ARRAY_BUFFER);

        // 頂点バッファをアンバインド
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}