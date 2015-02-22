/* ヘッダファイル */
#include "SpriteCreater.h"
#include "../../Debug/Helper/DebugHelper.h"
#include "../../OpenGL/Manager/OpenGlManager.h"


//-------------------------------------------------------------
//!
//! @brief スプライト
//! @brief スプライト関連の名前空間
//!
//-------------------------------------------------------------
namespace Sprite
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SpriteCreater::C_SpriteCreater()
    {
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_SpriteCreater::~C_SpriteCreater()
    {
    }


    /*************************************************************//**
     *
     *  @brief  初期化処理を行う
     *  @param  カメラ
     *  @param  テクスチャ情報
     *  @param  最大スプライト数
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_SpriteCreater::Initialize(const Camera::CameraPtr& prCamera,
                                     const Texture::TextureDataPtr& prTextureData,
                                     uint32_t maxSpriteCount)
    {
        // GLSLオブジェクトを作成し、保持
        if (!Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID))
        {
            auto pGlslObject = Shader::GLSL::C_GlslObject::s_Create();

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pVERTEX_FILE_PATH, Shader::GLSL::Type::s_VERTEX) == false)
            {
                PrintLog("[ C_SpriteCreater::Initialize ] : 頂点シェーダーのコンパイルに失敗しました。\n");

                return false;
            }

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pGEOMETRY_FILE_PATH, Shader::GLSL::Type::s_GEOMETRY) == false)
            {
                PrintLog("[ C_SpriteCreater::Initialize ] : ジオメトリシェーダーのコンパイルに失敗しました。\n");

                return false;
            }

            if (pGlslObject->CompileFromFile(Fixed::Shader::s_pFRAGMENT_FILE_PATH, Shader::GLSL::Type::s_FRAGMENT) == false)
            {
                PrintLog("[ C_SpriteCreater::Initialize ] : フラグメントシェーダーのコンパイルに失敗しました。\n");

                return false;
            }

            if (pGlslObject->Link() == false)
            {
                PrintLog("[ C_SpriteCreater::Initialize ] : シェーダーのリンクに失敗しました。\n");

                return false;
            }

            pGlslObject_ = pGlslObject;
            Shader::GLSL::C_GlslObjectManager::s_GetInstance()->Entry(pGlslObject_, Fixed::Shader::s_pGLSL_OBJECT_ID);

            // サブルーチンのインデックスを取得
            subroutineIndices_[Camera::PERSPECTIVE] = pGlslObject_->GetSubroutineIndex(Shader::GLSL::Type::s_GEOMETRY, "PerspectiveProcess");
            subroutineIndices_[Camera::ORTHOGRAPHIC] = pGlslObject_->GetSubroutineIndex(Shader::GLSL::Type::s_GEOMETRY, "OrthographicProcess");
        }
        else
        {
            pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(Fixed::Shader::s_pGLSL_OBJECT_ID).get();

            // サブルーチンのインデックスを取得
            subroutineIndices_[Camera::PERSPECTIVE] = pGlslObject_->GetSubroutineIndex(Shader::GLSL::Type::s_GEOMETRY, "PerspectiveProcess");
            subroutineIndices_[Camera::ORTHOGRAPHIC] = pGlslObject_->GetSubroutineIndex(Shader::GLSL::Type::s_GEOMETRY, "OrthographicProcess");
        }

        // 頂点のメモリを確保
        vertices_.resize(maxSpriteCount);

        // プリミティブを作成し、取得
        if (!OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(Fixed::Primitive::s_pSPRITE_ID))
        {
            uint32_t vertexAttributeElementCountList[] = { 3, 2, 1, 4, 2, 2, 2 };
            std::array<OpenGL::DataEnum, 7> vertexAttributeDataTypeList;
            vertexAttributeDataTypeList.fill(OpenGL::DataType::s_FLOAT);
            uint32_t vertexByteOffsetList[] = { 4, 4, 4, 4, 4, 4, 4 };
            bool vertexTransferFlagList[] = { true, true, true, true, true, true, true };

            pPointDatas_ = OpenGL::C_PrimitiveBuffer::s_Create(vertices_.data(),        
                                                               vertices_.size(),
                                                               7, 
                                                               vertexAttributeElementCountList,
                                                               vertexAttributeDataTypeList.data(),
                                                               OpenGL::Modify::s_DYNAMIC,
                                                               vertexByteOffsetList,
                                                               vertexTransferFlagList);

            OpenGL::C_PrimitiveBufferManager::s_GetInstance()->Entry(pPointDatas_, Fixed::Primitive::s_pSPRITE_ID);
        }
        else
        {
            pPointDatas_ = OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(Fixed::Primitive::s_pSPRITE_ID).get();
        }

        // カメラとテクスチャ情報を設定
        pCamera_ = prCamera;
        pTextureData_ = prTextureData;

        // テクスチャユニットを設定
        pGlslObject_->Begin();
        pGlslObject_->SetUniform1i("texture", Fixed::Texture::s_UNIT_NUMBER);
        pGlslObject_->End();

        return true;
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreater::Draw()
    {
        // 頂点の書き換え
        pPointDatas_->RewriteVertices(vertices_.data(), drawSpriteCount_);

        // シェーダーの使用開始
        pGlslObject_->Begin();

        // サブルーチンを設定
        pGlslObject_->BindActiveSubroutine(subroutineIndices_[cameraType_], Shader::GLSL::Type::s_GEOMETRY);
        
        // ユニフォーム変数を設定
        SetUniformVariable();

        // テクスチャマネージャーとOpenGLマネージャーを取得
        auto pTextureManager = Texture::C_TextureManager::s_GetInstance();
        auto pOpenGlManager = OpenGL::C_OpenGlManager::s_GetInstance();

        // ブレンドを有効化し、ブレンドに使用する関数を設定
        pOpenGlManager->EnableBlend(true);
        pOpenGlManager->SetBlendFunction(sourceFactor_, destinationFactor_);

        // カリングを無効化
        pOpenGlManager->EnableCulling(false);

        // 深度のマスクを有効化
        pOpenGlManager->EnableDepthMask(true);

        // アクティブなテクスチャユニットを設定し、テクスチャをバインド
        pTextureManager->SetActiveUnit(Fixed::Texture::s_UNIT_NUMBER);
        pTextureManager->Bind(Texture::Type::s_2D, pTextureData_->handle_);

        // スプライトを描画
        pOpenGlManager->DrawPrimitive(OpenGL::Primitive::s_POINT, pPointDatas_->GetVertexArrayObjectHandle(), drawSpriteCount_);

        // 深度のマスクを無効化
        pOpenGlManager->EnableDepthMask(false);

        // カリングを有効化
        pOpenGlManager->EnableCulling(true);

        // ブレンドを無効化
        pOpenGlManager->EnableBlend(false);

        // テクスチャをアンバインド
        pTextureManager->Unbind(Texture::Type::s_2D);

        // シェーダーの使用終了
        pGlslObject_->End();

        drawSpriteCount_ = 0;
    }


    /*************************************************************//**
     *
     *  @brief  終了処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreater::Finalize()
    {
        // 点の情報を破棄
        pPointDatas_.reset();

        // 頂点を削除
        vertices_.clear();

        // 描画するスプライトの数をリセット
        drawSpriteCount_ = 0;
        
        // GLSLオブジェクトの管理を破棄
        pGlslObject_.reset();
    }


    /*************************************************************//**
     *
     *  @brief  登録処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreater::Entry(const Vector3& rPosition,
                                const Vector2& rSize,                                   
                                float angle,                                            
                                const Vector4& rColor,                                  
                                const Vector2& rTextureUpperLeft,                       
                                const Vector2& rTextureLowerRight)
    {
        Entry(S_CreateData(rPosition, rSize, angle, rColor, rTextureUpperLeft, rTextureLowerRight));
    }


    /*************************************************************//**
     *
     *  @brief  登録処理を行う
     *  @param  生成情報
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreater::Entry(const S_CreateData& rCreateData)
    {
        if (drawSpriteCount_ >= vertices_.size()) return;

        vertices_[drawSpriteCount_].position_ = rCreateData.position_;
        vertices_[drawSpriteCount_].size_ = rCreateData.size_;
        vertices_[drawSpriteCount_].angle_ = rCreateData.angle_;
        vertices_[drawSpriteCount_].color_ = rCreateData.color_;
        vertices_[drawSpriteCount_].textureLowerRight_ = rCreateData.textureLowerRight_;
        vertices_[drawSpriteCount_].textureUpperLeft_ = rCreateData.textureUpperLeft_;
        vertices_[drawSpriteCount_].textureSize_.width_ = static_cast<float>(pTextureData_->width_);
        vertices_[drawSpriteCount_].textureSize_.height_ = static_cast<float>(pTextureData_->height_);

        ++drawSpriteCount_;
    }


    /*************************************************************//**
     *
     *  @brief  ビルボードの自動化をさせるフラグを設定する
     *  @param  ビルボードの自動化をさせるフラグ
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreater::SetAutoBillboardFlag(bool autoBillboardFlag)
    {
        autoBillboardFlag_ = autoBillboardFlag;
    }


    /*************************************************************//**
     *
     *  @brief  カメラを設定
     *  @param  カメラ
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreater::SetCamera(const Camera::CameraPtr& prCamera)
    {
        pCamera_ = prCamera;
    }


    /*************************************************************//**
     *
     *  @brief  カメラの種類を設定
     *  @param  カメラの種類
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreater::SetCameraType(Camera::eType cameraType)
    {
        cameraType_ = cameraType;
    }


    /*************************************************************//**
     *
     *  @brief  ブレンドの関数を設定する
     *  @param  新しい色の要素
     *  @param  現在の色の要素
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreater::SetBlendFunction(OpenGL::BlendEnum sourceFactor, OpenGL::BlendEnum destinationFactor)
    {
        sourceFactor_ = sourceFactor;
        destinationFactor_ = destinationFactor;
    }


    /*************************************************************//**
     *
     *  @brief  ユニフォーム変数を設定
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_SpriteCreater::SetUniformVariable()
    {
        // ビルボードを自動化するフラグが立っている場合、
        // ビュー行列からビルボードさせる行列を求める
        if (autoBillboardFlag_ == true)
        {
            billboardMatrix_ = pCamera_->GetViewMatrix();

            std::swap(billboardMatrix_.a12_, billboardMatrix_.a21_);
            std::swap(billboardMatrix_.a13_, billboardMatrix_.a31_);
            std::swap(billboardMatrix_.a23_, billboardMatrix_.a32_);

            billboardMatrix_.a41_ = 0.0f;
            billboardMatrix_.a42_ = 0.0f;
            billboardMatrix_.a43_ = 0.0f;
        }

        // 各行列を設定
        pGlslObject_->SetUniformMatrix4x4("viewProjectionMatrix", pCamera_->GetViewProjectionMatrix());
        pGlslObject_->SetUniformMatrix4x4("billboardMatrix", billboardMatrix_);
    }
}