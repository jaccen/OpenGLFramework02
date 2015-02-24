/* ヘッダファイル */
#include "Space.h"
#include "../../Library/JSON/Object/Manager/JsonObjectManager.h"
#include "../../Library/OpenGL/Manager/OpenGlManager.h"


//-------------------------------------------------------------
//!
//! @brief コネクトウォーズ
//! @brief コネクトウォーズ関連の名前空間
//!
//-------------------------------------------------------------
namespace ConnectWars
{
    /*************************************************************//**
     *
     *  @brief  コンストラクタ
     *  @param  ID
     *  @param  種類
     *
     ****************************************************************/
    C_Space::C_Space(const std::string& rId, int32_t type) : C_BaseBackground(rId, type)
    {
        // スペースの情報を取得
        assert(JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSPACE));
        auto pSpaceData = JSON::C_JsonObjectManager::s_GetInstance()->GetJsonObject(ID::JSON::s_pSPACE).get();

        // モデル行列を作成
        float radius = static_cast<float>((*pSpaceData)["SpaceData"]["Radius"].GetValue<JSON::Real>());
        modelMatrix_ = Matrix4x4::s_CreateScaling(radius, radius, radius);

        // モデル情報を取得
        assert(OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pSPACE));
        pModelData_ = OpenGL::C_PrimitiveBufferManager::s_GetInstance()->GetPrimitiveBuffer(ID::Primitive::s_pSPACE).get();

        // テクスチャデータを取得
        assert(Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pSPACE));
        pTextureData_ = Texture::C_TextureManager::s_GetInstance()->GetTextureData(Path::Texture::s_pSPACE).get();

        // GLSLオブジェクトを取得
        assert(Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pCELESTIAL_SPHERE));
        pGlslObject_ = Shader::GLSL::C_GlslObjectManager::s_GetInstance()->GetGlslObject(ID::Shader::s_pCELESTIAL_SPHERE).get();

        pGlslObject_->Begin();
        pGlslObject_->SetUniform1i("u_texture", 0);
        pGlslObject_->End();

        // ユニフォームバッファとインデックスを取得
        assert(Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pBACKGROUND_CAMERA));
        pUniformBuffer_ = Shader::GLSL::C_UniformBufferManager::s_GetInstance()->GetUniformBuffer(ID::UniformBuffer::s_pBACKGROUND_CAMERA).get();
        uniformBlockIndex_ = pUniformBuffer_->GetBlockIndexFromProgramObject(pGlslObject_->GetProgramObjectHandle());
    }


    /*************************************************************//**
     *
     *  @brief  デストラクタ
     *  @param  なし
     *
     ****************************************************************/
    C_Space::~C_Space()
    {
    }


    /*************************************************************//**
     *
     *  @brief  更新処理を行う
     *  @param  なし
     *  @return タスク続行：true
     *  @return タスク終了：false
     *
     ****************************************************************/
    void C_Space::DoUpdate()
    {
    }


    /*************************************************************//**
     *
     *  @brief  描画処理を行う
     *  @param  なし
     *  @return なし
     *
     ****************************************************************/
    void C_Space::DoDraw()
    {
        pGlslObject_->BeginWithUnifomBuffer(pUniformBuffer_->GetHandle(), uniformBlockIndex_);

        modelMatrix_.a41_ = position_.x_;
        modelMatrix_.a42_ = position_.y_;
        modelMatrix_.a43_ = position_.z_;

        pGlslObject_->SetUniformMatrix4x4("u_modelMatrix", modelMatrix_);

        auto pOpenGlManager = OpenGL::C_OpenGlManager::s_GetInstance();
        auto pTextureManager = Texture::C_TextureManager::s_GetInstance();

        pOpenGlManager->SetCullingFace(OpenGL::Face::s_FRONT);

        // アクティブなテクスチャユニットを設定し、テクスチャをバインド
        pTextureManager->SetActiveUnit(0);
        pTextureManager->Bind(Texture::Type::s_2D, pTextureData_->handle_);

        pOpenGlManager->DrawPrimitiveWithIndices(OpenGL::Primitive::s_TRIANGLE,
                                                 pModelData_->GetVertexArrayObjectHandle(), 
                                                 pModelData_->GetIndexBufferObjectHandle(),
                                                 OpenGL::DataType::s_UNSIGNED_SHORT,
                                                 static_cast<int32_t>(pModelData_->GetIndexCount()));

        pTextureManager->Unbind(Texture::Type::s_2D);

        pOpenGlManager->SetCullingFace(OpenGL::Face::s_BACK);

        pGlslObject_->End();
    }


    /*************************************************************//**
     *
     *  @brief  メッセージ処理を行う
     *  @param  テレグラム
     *  @return 正常終了：true
     *  @return 異常終了：false
     *
     ****************************************************************/
    bool C_Space::DoMessageProcess(const Telegram& rTelegram)
    {
        return true;
    }
}